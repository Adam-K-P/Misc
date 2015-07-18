#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main (void) {
   Matrix *m = new_matrix(100);
   change_entry(m, 1, 1, 2.0);
   change_entry(m, 1, 2, 3.0);
   return EXIT_SUCCESS;
}
