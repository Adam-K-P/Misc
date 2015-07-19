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

inline int get_size (Matrix *this_matrix) { 
   if (this_matrix == NULL) error("get_size", "this_matrix is NULL");
   return this_matrix->size; 
}

inline int get_nnz (Matrix *this_matrix) {
   if (this_matrix == NULL) error("get_size", "this_matrix is NULL");
   return this_matrix->entries;
}

//helper function for change_entry
//just creates a new list, appends an entry onto it
//then appends that list onto the outer list
static void full_append (List outer_list, int row, int column, double value) {
   List this_list = newList();
   Entry *ins_entry = new_entry(row, column, value);
   append(this_list, ins_entry, sizeof(Entry));
   append(outer_list, this_list, sizeof(struct List));
}

void change_entry (Matrix *this_matrix, int row, int column, double value) {
   if (this_matrix == NULL) error("change_entry", "this_matrix is NULL");
   if (row > this_matrix->size || column > this_matrix->size) 
      error("change_entry", "invalid entry");
   List outer_list = this_matrix->row;
   if (length(outer_list) == 0) 
      { full_append(outer_list, row, column, value); return; }
   for (moveFront(outer_list); index(outer_list) >= 0; moveNext(outer_list)) {
      List inner_list = (List)get(outer_list);
      for (moveFront(inner_list); index(inner_list) >= 0;
           moveNext(inner_list)) {
         Entry *this_entry = (Entry *)get(inner_list);
         if (this_entry->row < row) break;
         if (this_entry->row > row) {
            List this_list = newList();
            Entry *ins_entry = new_entry(row, column, value);
            append(this_list, ins_entry, sizeof(Entry));
            insertBefore(outer_list, this_list, sizeof(struct List));
            return;
         }
         if (this_entry->column > column) {
            Entry *ins_entry = new_entry(row, column, value);
            insertBefore(inner_list, ins_entry, sizeof(Entry));
            return;
         }
         //TODO delete entry if value is 0
         if (this_entry->column == column) 
            { this_entry->value = value; return; }
      }
      Entry *ins_entry = new_entry(row, column, value);
      append(inner_list, ins_entry, sizeof(Entry));
   }
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

//TODO
Matrix *add (Matrix *this_matrix, Matrix *that_matrix) {
   if (get_size(this_matrix) != get_size(that_matrix))
      error("add", "matrices sizes are not equal");
   Matrix *add = new_matrix(get_size(this_matrix));
   return add;
}


void print_matrix (Matrix *this_matrix) {
   List outer_list = this_matrix->row;
   for (moveFront(outer_list); index(outer_list) >= 0; moveNext(outer_list)) {
      List inner_list = (List)get(outer_list);
      for (moveFront(inner_list); index(inner_list) >= 0; 
           moveNext(inner_list)) {
         Entry *this_entry = (Entry *)get(inner_list);
         printf("row:%d\ncolumn:%d\nvalue:%f\n\n", 
                 this_entry->row, this_entry->column, this_entry->value);
      }
   }
}






            




















   












