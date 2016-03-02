#include <cstdlib>
#include <iostream>

#include "graph.h"

using namespace std;

int main () {
   graph<int>* this_graph = new graph<int>;

   this_graph->add_vertex (1); 
   this_graph->add_vertex (2);
   this_graph->add_vertex (3);
   this_graph->add_vertex (4); 
   this_graph->add_vertex (5); 
   this_graph->add_vertex (7); 

   //this_graph->dijkstra (1);
   this_graph->print ();
   return EXIT_SUCCESS;
}
