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
   this_graph->add_vertex (6); 
   this_graph->add_vertex (7); 
   this_graph->add_vertex (8); 
   this_graph->add_vertex (9); 
   this_graph->add_vertex (10); 
   this_graph->add_vertex (11); 
   this_graph->add_vertex (12); 
   this_graph->add_vertex (13); 
   this_graph->add_vertex (14); 
   this_graph->add_vertex (15); 
   this_graph->add_vertex (16); 
   this_graph->add_vertex (17); 
   this_graph->add_vertex (18);
   this_graph->add_vertex (19);
   this_graph->add_vertex (20);

   this_graph->add_arc (1, 20);
   this_graph->add_arc (2, 19);
   this_graph->add_arc (3, 18);
   this_graph->add_arc (4, 17);
   this_graph->add_arc (5, 16);
   this_graph->add_arc (6, 15);
   this_graph->add_arc (7, 14);
   this_graph->add_arc (8, 13);
   this_graph->add_arc (9, 12);
   this_graph->add_arc (10, 11);
     
   
   this_graph->print ();
   return EXIT_SUCCESS;
}
