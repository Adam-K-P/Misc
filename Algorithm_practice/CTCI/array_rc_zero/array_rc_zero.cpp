#include <iostream>
#include <cstdlib>

using namespace std;

int** array_rc_zero (int** array, int m, int n) {
   int** ret;
   ret = new int *[m];
   for (int i = 0; i < m; ++i)
      ret[i] = new int[n];

   for (int i = 0; i < m; ++i) 
      for (int j = 0; j < n; ++j) 
         ret[i][j] = array[i][j];

   for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
         if (array[i][j] == 0) {
            for (int k = 0; k < m; ++k)
               ret[k][j] = 0;
            for (int k = 0; k < n; ++k)
               ret[i][k] = 0;
         }
      }
   }
   return ret;
}

int main () {
   int **test;
   test = new int *[4];
   for (int i = 0; i < 4; ++i)
      test[i] = new int[4];

   for (int i = 0, num = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
         test[i][j] = num++;

   for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
         cout << test[i][j] << endl;

   test = array_rc_zero (test, 4, 4);

   cout << endl;
   for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
         cout << test[i][j] << endl;
   
   return EXIT_SUCCESS;
}
