#include <iostream>

#include "merge.h"

using namespace std;

int main () {
   merge_vec* this_vec = new merge_vec;

   this_vec->emplace_back(1);
   this_vec->emplace_back(7);
   this_vec->emplace_back(5);
   this_vec->emplace_back(3);
   this_vec->emplace_back(10);
   this_vec->emplace_back(6);
   this_vec->emplace_back(0);

   merge_vec new_vec = merge_sort (*this_vec);

   for (size_t i = 0; i < new_vec.size(); ++i) 
      cout << new_vec.at(i) << endl;

   return 1;
}
