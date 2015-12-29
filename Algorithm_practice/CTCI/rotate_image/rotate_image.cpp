#include <iostream>
#include <cstdlib>

using namespace std;

int** rotate_image (int** image, int n) {
   int x = 0, y = 0, swap1, swap2, swap3;

   for (int i = 0; i < (n / 2); ++i) {
      for (int j = 0; j < (n / 2); ++j) {

         swap1 = image[i + (n / 2)][j];
         swap2 = image[i + (n / 2)][j + (n / 2)];
         swap3 = image[i][j + (n / 2)];

         image[i + (n / 2)][j] = image[i][j];
         image[i + (n / 2)][j + (n / 2)] = swap1;
         image[i][j + (n / 2)] = swap2;
         image[i][j] = swap3;
      }
   }

   return image;
}

int main () {
   int **test;
   test = new int *[4];
   for (int i = 0; i < 4; ++i) 
      test[i] = new int[4];

   int num = 1;
   for (int i = 0; i < 4; ++i) 
      for (int j = 0; j < 4; ++j) 
         test[i][j] = num++;

   for (int i = 0; i < 4; ++i) 
      for (int j = 0; j < 4; ++j) 
         cout << test[i][j] << endl;

   test = rotate_image (test, 4);
   cout << endl;

   for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
         cout << test[i][j] << endl;

   return EXIT_SUCCESS;
}

