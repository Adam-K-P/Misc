#include <cstdlib>
#include <iostream>

#include "graph.h"

/* tests directed_graph class */

using namespace std;

int main () {
   directed_graph<string> agraph;

   agraph.add_vertex (1, "one");
   agraph.add_vertex (2, "two");
   agraph.add_vertex (3, "three");
   agraph.add_vertex (4, "four");
   agraph.add_vertex (5, "five");
   agraph.add_vertex (6, "six");
   agraph.add_vertex (7, "seven");
   agraph.add_vertex (8, "eight");
   agraph.add_vertex (9, "nine");
   agraph.add_vertex (10, "ten");

   vector<int> top_sort = agraph.topological (1);

   return EXIT_SUCCESS;
}
