#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

//A row value of -1 indicates that the Entry is not the first element of a row
typedef struct Entry {
   int column;
   double value;
} Entry;

static void error (char *function, char *message) {
   fprintf(stderr, "Error in function - %s: %s\n", function, message);
   exit(EXIT_FAILURE);
}

static Entry *new_entry (int column, double value) {
   Entry *this_entry  = malloc(sizeof(Entry));
   this_entry->column = column;
   this_entry->value  = value;
   return this_entry;
}

Matrix *new_matrix (int size) {
   Matrix *this_matrix  = malloc(sizeof(Matrix));
   this_matrix->size    = size;
   this_matrix->entries = 0;
   this_matrix->row     = newList();
   return this_matrix;
}

void free_matrix (Matrix *this_matrix) {
   if (this_matrix == NULL || this_matrix->row == NULL) return;
   for (int i = 0; ; ++i) {
      if (this_matrix->row[i] == NULL) break;
      freeList(&this_matrix->row[i]);
   }
   free(this_matrix);
}

inline int get_size (Matrix *this_matrix) { 
   if (this_matrix == NULL) error("get_size", "this_matrix is NULL");
   return this_matrix->size; 
}

inline int get_nnz (Matrix *this_matrix) {
   if (this_matrix == NULL) error("get_size", "this_matrix is NULL");
   return this_matrix->entries;
}

void change_entry (Matrix *this_matrix, int row, int column, double value) {
   //assert(this_matrix->row != NULL);
   if (row > this_matrix->size || column > this_matrix->size) 
      error("change_entry", "invalid entry");
   if (this_matrix->row == NULL || this_matrix->row[row] == NULL) {
      this_matrix->row[row] = newList();
      Entry *this_entry = new_entry(column, value);
      append(this_matrix->row[row], this_entry);
      return;
   }
   for (moveFront(this_matrix->row[row]); index(this_matrix->row[row]) >= 0;
        moveNext(this_matrix->row[row])) {
      Entry *this_entry = (Entry *)get(this_matrix->row[row]);
      if (this_entry->column == column) { 
         if (value == 0) delete(this_matrix->row[row]);
         else this_entry->value = value;
         return;
      }
   }
   if (value == 0) return;
   Entry *this_entry = new_entry(column, value);
   ++this_matrix->entries;
   for (moveFront(this_matrix->row[row]); index(this_matrix->row[row]) >= 0;
        moveNext(this_matrix->row[row])) {
      Entry *that_entry = (Entry *)get(this_matrix->row[row]);
      if (that_entry->column > column) {
         insertBefore(this_matrix->row[row], this_entry);
         return;
      }
   }
   append(this_matrix->row[row], this_entry);
}












   












