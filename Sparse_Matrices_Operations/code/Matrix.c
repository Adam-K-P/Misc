#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

typedef struct Entry {
   int row;
   int column;
   double value;
} Entry;

//simple error function
static void error (char *function, char *message) {
   fprintf(stderr, "Error in function - %s: %s\n", function, message);
   exit(EXIT_FAILURE);
}

//Entry constructor
static Entry *new_entry (int row, int column, double value) {
   Entry *this_entry  = malloc(sizeof(Entry));
   this_entry->row    = row;
   this_entry->column = column;
   this_entry->value  = value;
   return this_entry;
}

//Matrix constructor
Matrix *new_matrix (double size) {
   Matrix *this_matrix  = malloc(sizeof(Matrix));
   this_matrix->size    = size;
   this_matrix->entries = 0;
   this_matrix->row     = newList();
   return this_matrix;
}

/*void free_matrix (Matrix *this_matrix) {
   if (this_matrix == NULL || this_matrix->row == NULL) return;
   for (int i = 0; ; ++i) {
      if (this_matrix->row[i] == NULL) break;
      freeList(&this_matrix->row[i]);
   }
   free(this_matrix);
}*/

inline double get_size (Matrix *this_matrix) { 
   if (this_matrix == NULL) error("get_size", "this_matrix is NULL");
   return this_matrix->size; 
}

inline int get_nnz (Matrix *this_matrix) {
   if (this_matrix == NULL) error("get_size", "this_matrix is NULL");
   return this_matrix->entries;
}

void make_zero (Matrix *this_matrix) {
   List outer_list = this_matrix->row;
   for (moveFront(outer_list); index(outer_list) >= 0; moveNext(outer_list)) {
      List inner_list = (List)get(outer_list);
      clear(inner_list);
   }
   clear(outer_list);
}

Matrix *copy (Matrix *this_matrix) {
   Matrix *copy = new_matrix(this_matrix->size);
   List outer_list = this_matrix->row;
   for (moveFront(outer_list); index(outer_list) >= 0; moveNext(outer_list)) {
      List inner_list = (List)get(outer_list);
      for (moveFront(inner_list); index(inner_list) >= 0;
           moveNext(inner_list)) {
         Entry *this_entry = (Entry *)get(inner_list);
         change_entry(copy, this_entry->row, this_entry->column, 
                                             this_entry->value);
      }
   }
   return copy;
}

//helper function for change_entry
//just creates a new list, appends an entry onto it
//then appends that list onto the outer list
static void full_append (Matrix *this_matrix, List outer_list,
                         int row, int column, double value) {
   if (value == 0) return;
   List this_list = newList();
   Entry *ins_entry = new_entry(row, column, value);
   append(this_list, ins_entry, sizeof(Entry));
   append(outer_list, this_list, sizeof(struct List));
   ++this_matrix->entries;
}

//helper function for change_entry
//returns true if an Entry was inserted and false otherwise
static bool determine_ins (Entry *this_entry, int row, int column, double value, 
                           List outer_list, List inner_list) {
   bool insert = false;
   if (this_entry->row > row) {
      List this_list = newList();
      Entry *ins_entry = new_entry(row, column, value);
      append(this_list, ins_entry, sizeof(Entry));
      insertBefore(outer_list, this_list, sizeof(struct List));
      insert = true;
   }
   if (this_entry->column > column) {
      Entry *ins_entry = new_entry(row, column, value);
      insertBefore(inner_list, ins_entry, sizeof(Entry));
      insert = true;
   }
   if (this_entry->column == column)
      { this_entry->value = value; insert = true; }
   return insert;
}

void change_entry (Matrix *this_matrix, int row, int column, double value) {
   if (this_matrix == NULL) error("change_entry", "this_matrix is NULL");
   if (row > this_matrix->size || column > this_matrix->size) 
      error("change_entry", "invalid entry");
   List outer_list = this_matrix->row;
   if (length(outer_list) == 0) 
      { full_append(this_matrix, outer_list, row, column, value); return; }
   for (moveFront(outer_list); index(outer_list) >= 0; moveNext(outer_list)) {
      List inner_list = (List)get(outer_list);
      bool this_row = false;
      for (moveFront(inner_list); index(inner_list) >= 0;
           moveNext(inner_list)) {
         Entry *this_entry = (Entry *)get(inner_list);
         if (this_entry->row < row) break;
         if (determine_ins(this_entry, row, column, value, outer_list,
                                                           inner_list)) {
            ++this_matrix->entries;
            return;
         }
         if (this_entry->row == row) this_row = true;
      }
      if (this_row && value != 0) { 
         Entry *ins_entry = new_entry(row, column, value);
         append(inner_list, ins_entry, sizeof(Entry));
         ++this_matrix->entries;
         return;
      }
   }
   full_append(this_matrix, outer_list, row, column, value); 
}

Matrix *scalar_mult (Matrix *this_matrix, double scalar) {
   if (this_matrix == NULL) error("scalar_mult", "this_matrix is NULL");
   Matrix *that_matrix = new_matrix(this_matrix->size);
   List outer_list = this_matrix->row;
   for (moveFront(outer_list); index(outer_list) >= 0; moveNext(outer_list)) {
      List inner_list = (List)get(outer_list);
      for (moveFront(inner_list); index(inner_list) >= 0;
           moveNext(inner_list)) {
         Entry *this_entry = (Entry *)get(inner_list);
         change_entry(that_matrix, this_entry->row, this_entry->column,
                                   this_entry->value * scalar);
      }
   }
   return that_matrix;
}

static void finish (Matrix *add, List this_list) {
   for ( ; index(this_list) >= 0; moveNext(this_list)) {
      Entry *this_entry = (Entry *)get(this_list);
      change_entry(add, this_entry->row, this_entry->column,
                                         this_entry->value);
   }
}

static bool check_rows (Matrix *add, 
                        List this_outer_list, List that_outer_list, 
                        List this_inner_list, List that_inner_list) {
   bool appended = false;
   moveFront(this_inner_list);
   moveFront(that_inner_list);
   Entry *this_first_entry = (Entry *)get(this_inner_list);
   Entry *that_first_entry = (Entry *)get(that_inner_list);
   if (this_first_entry->row < that_first_entry->row) {
      append(add->row, this_inner_list, sizeof(struct List));
      moveNext(this_outer_list);
      appended = true;
   }
   if (that_first_entry->row < this_first_entry->row) {
      append(add->row, that_inner_list, sizeof(struct List));
      moveNext(that_outer_list);
      appended = true;
   }
   return appended;
}

static void add_rows (Matrix *add, List this_inner_list, List that_inner_list) {
   for (moveFront(this_inner_list), moveFront(that_inner_list);
        index(this_inner_list) >= 0 && index(that_inner_list) >= 0;) {
      Entry *this_entry = (Entry *)get(this_inner_list);
      Entry *that_entry = (Entry *)get(that_inner_list);
      if (this_entry->column < that_entry->column) {
         change_entry(add, this_entry->row, this_entry->column, 
                                            this_entry->value);
         moveNext(this_inner_list);
      }
      if (that_entry->column < this_entry->column) {
         change_entry(add, that_entry->row, that_entry->column,
                                            that_entry->value);
         moveNext(that_inner_list);
      }
      if (this_entry->column == that_entry->column) {
         change_entry(add, this_entry->row, this_entry->column,
                           this_entry->value + that_entry->value);
         moveNext(this_inner_list);
         moveNext(that_inner_list);
      }
   }
}

Matrix *add (Matrix *this_matrix, Matrix *that_matrix) {
   if (get_size(this_matrix) != get_size(that_matrix))
      error("add", "matrices sizes are not equal");
   Matrix *add = new_matrix(this_matrix->size);
   if (this_matrix->entries == 0) return that_matrix;
   if (that_matrix->entries == 0) return this_matrix;
   List this_outer_list = this_matrix->row;
   List that_outer_list = that_matrix->row;
   for (moveFront(this_outer_list), moveFront(that_outer_list);
        index(this_outer_list) >= 0 && index(that_outer_list) >= 0;) {
      List this_inner_list = (List)get(this_outer_list);
      List that_inner_list = (List)get(that_outer_list);
      if (check_rows(add, this_outer_list, that_outer_list, 
                          this_inner_list, that_inner_list)) 
         continue;
      add_rows(add, this_inner_list, that_inner_list);
      finish(add, this_inner_list);
      finish(add, that_inner_list);
      moveNext(this_outer_list);
      moveNext(that_outer_list);
   }
   return add;
}

Matrix *sub (Matrix *this_matrix, Matrix *that_matrix) {
   Matrix *inv_matrix = scalar_mult(that_matrix, -1);
   return add(this_matrix, inv_matrix);
}

Matrix *transpose (Matrix *this_matrix) {
   Matrix *tran = new_matrix(this_matrix->size);
   List outer_list = this_matrix->row;
   for (moveFront(outer_list); index(outer_list) >= 0; moveNext(outer_list)) {
      List inner_list = (List)get(outer_list);
      for (moveFront(inner_list); index(inner_list) >= 0; 
           moveNext(inner_list)) {
         Entry *this_entry = (Entry *)get(inner_list);
         change_entry(tran, this_entry->column, this_entry->row, 
                                                this_entry->value);
      }
   }
   return tran;
}

static void dot_product (Matrix *this_matrix, List this_inner_list, 
                                              List tran_inner_list) {
   double value = 0;
   Entry *this_entry = NULL;
   Entry *tran_entry = NULL;
   for (moveFront(this_inner_list), moveFront(tran_inner_list); 
        index(this_inner_list) >= 0 && index(tran_inner_list) >= 0;) {
      this_entry = (Entry *)get(this_inner_list);
      tran_entry = (Entry *)get(tran_inner_list);
      if (this_entry->column == tran_entry->column) {
         value += this_entry->value * tran_entry->value;
         moveNext(this_inner_list);
         moveNext(tran_inner_list);
         continue;
      }
      if (this_entry->column > tran_entry->column) moveNext(tran_inner_list);
      else moveNext(this_inner_list);
   }
   assert(this_entry != NULL && tran_entry != NULL);
   change_entry(this_matrix, this_entry->row, tran_entry->row, value);
}

Matrix *mult (Matrix *this_matrix, Matrix *that_matrix) {
   if (this_matrix->size != that_matrix->size) 
      error("mult", "matrices entered have different sizes\n");
   Matrix *prod = new_matrix(this_matrix->size);
   Matrix *tran = transpose(that_matrix);
   List this_outer_list = this_matrix->row;
   for (moveFront(this_outer_list); index(this_outer_list) >= 0; 
        moveNext(this_outer_list)) {
      List this_inner_list = (List)get(this_outer_list);
      List tran_outer_list = tran->row;
      for (moveFront(tran_outer_list); index(tran_outer_list) >= 0; 
           moveNext(tran_outer_list)) {
         List tran_inner_list = (List)get(tran_outer_list);
         dot_product(prod, this_inner_list, tran_inner_list);
      }
   }
   return prod;
}

void print_matrix (Matrix *this_matrix) {
   List outer_list = this_matrix->row;
   for (moveFront(outer_list); index(outer_list) >= 0; moveNext(outer_list)) {
      List inner_list = (List)get(outer_list);
      for (moveFront(inner_list); index(inner_list) >= 0; 
           moveNext(inner_list)) {
         Entry *this_entry = (Entry *)get(inner_list);
         printf("(%d, %d, %f) ", this_entry->row, this_entry->column,
                                                  this_entry->value);
      }
      printf("\n");
   }
   printf("\n");
}






            




















   












