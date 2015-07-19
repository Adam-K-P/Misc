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
   print_matrix(m);
   print_matrix(n);
   return EXIT_SUCCESS;
}
