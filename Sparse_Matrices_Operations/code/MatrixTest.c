#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main (void) {
   Matrix *m = new_matrix(1000000000000000);
   change_entry(m, 1, 1, 2.0);
   change_entry(m, 1, 2, 3.0);
   change_entry(m, 99, 99, 991231);
   Matrix *n = scalar_mult(m, 5);
   Matrix *ad = add(m, n);
   Matrix *t = transpose(ad);
   print_matrix(m);
   print_matrix(n);
   print_matrix(ad);
   print_matrix(t);
   printf("mult:\n");

   Matrix *matr0 = new_matrix(1000000000000000);
   change_entry(matr0, 1, 1, 1);
   change_entry(matr0, 1, 2, 1);
   change_entry(matr0, 1, 3, 1);
   change_entry(matr0, 2, 1, 1);
   change_entry(matr0, 2, 2, 1);
   change_entry(matr0, 2, 3, 1);
   change_entry(matr0, 3, 1, 1);
   change_entry(matr0, 3, 2, 1);
   change_entry(matr0, 3, 3, 1);
   Matrix *matr1 = add(matr0, n);
   Matrix *prod = mult(matr0, matr1);
   print_matrix(prod);


   return EXIT_SUCCESS;
}
