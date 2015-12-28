/* merge.cpp
 * Adam Pinarbasi
 * Performs merge sort on a vector
 * Just for practice ;-)
 */

#include <iostream>

#include "merge.h"

using namespace std;

merge_vec merge (merge_vec this_vec, merge_vec that_vec) {
   size_t i = 0, j = 0;
   merge_vec ret_vec;
   while (i < this_vec.size() && j < that_vec.size()) {
      if (this_vec.at(i) < that_vec.at(j)) ret_vec.push_back(this_vec.at(i++));
      else ret_vec.push_back(that_vec.at(j++));
   }
   while (i < this_vec.size()) ret_vec.push_back(this_vec.at(i++));
   while (j < that_vec.size()) ret_vec.push_back(that_vec.at(j++));

   return ret_vec;
}

merge_vec merge_sort (merge_vec this_vec) {
   size_t size = this_vec.size();

   if (size > 1) {
      auto first = this_vec.begin();
      auto last  = this_vec.begin() + (size / 2);

      merge_vec new_vec(first, last);
      merge_vec oth_vec(last, this_vec.end());

      merge_vec new_sorted = merge_sort (new_vec);
      merge_vec oth_sorted = merge_sort (oth_vec);

      return merge (new_sorted, oth_sorted);
   }

   else return this_vec;
}
