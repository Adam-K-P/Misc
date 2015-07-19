#ifndef __MATRIX__
#define __MATRIX__

#include <stdbool.h>
#include "List.h"

typedef struct Matrix {
   double size;
   int entries;
   List row;
} Matrix;

Matrix *new_matrix (double);
void free_matrix (Matrix *);
int get_size (Matrix *);
int get_nnz (Matrix *);
bool matr_equals (Matrix *, Matrix *);
void make_zero (Matrix *);
Matrix *copy (Matrix *);
void change_entry (Matrix *, int, int, double);
Matrix *scalar_mult (Matrix *, double);
Matrix *add (Matrix *, Matrix *);
Matrix *sub (Matrix *, Matrix *);
Matrix *transpose (Matrix *);
Matrix *mult (Matrix *, Matrix *);
void print_matrix (Matrix *);

#endif






