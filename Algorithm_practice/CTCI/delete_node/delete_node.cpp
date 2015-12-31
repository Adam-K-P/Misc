#include <iostream>
#include <cstdlib>

using namespace std;
using node = struct node;

template <class T>
struct list {
   struct node {
      T data;
      node* next;
   };
   node* head;
   node* tail;
   void delete_node (node*);
};

template <class T>
void list<T>::delete_node (node* this_node) {
   if (this_node == nullptr or this_node->next == nullptr)
      exit (1);
   node* temp = this_node->next;
   this_node->data = this_node->next->data;
   this_node->next = this_node->next->next;
   delete temp;
}

int main () {
   return EXIT_SUCCESS;
}
