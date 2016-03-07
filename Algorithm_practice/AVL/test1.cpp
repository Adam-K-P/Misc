#include <cstdlib>
#include <iostream>

#include "avl.h"

using namespace std;

int main () {
   avl<int> tree;

   //unique_ptr<int> one = unique_ptr<int> (new int(1));
   tree.insert (1);
   tree.insert (2);
   tree.insert (3);
   tree.insert (4);
   tree.insert (5);

   tree.print ();

   return EXIT_SUCCESS;
}
