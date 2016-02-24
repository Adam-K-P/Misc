#include <cstdlib>
#include <iostream>

#include "graph.h"

using namespace std;

int main () {
   graph<int>* this_graph = new graph<int>;
   this_graph->bfs (2);
   return EXIT_SUCCESS;
}
