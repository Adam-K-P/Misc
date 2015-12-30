#include <iostream>
#include <cstdlib>
#include <unordered_set>

using namespace std;

template <class T>
class list {
   public:
      list () :head(nullptr), tail(nullptr) {}

      class node {
         private:
            T data;
            node* next;

         public:
            node (T data) :data(data), next(nullptr) {}
            inline T get () const { return data; }
            inline void set_next (node* this_node) { next = this_node; }
            inline node* get_next () const { return next; }

      };

      inline node* get_head () const { return head; }
      inline node* get_tail () const { return tail; }
      void push_back (T data);
      void remove_duplicates ();
      void delete_node (node* this_node);

   private:
      node* head;
      node* tail;
      unordered_set<T> duplicate_tracker;

};

template <class T>
void list<T>::delete_node (node* this_node) {
   if (this_node == head) {
      node* temp = head;
      head = temp->get_next();
      delete temp;
   }
   else {
      node* prev = head;
      node* curr = head;
      while (curr != this_node) {
         prev = curr;
         curr = curr->get_next();
      }
      prev->set_next (curr->get_next());
      delete curr;
   }
}

template <class T>
void list<T>::push_back (T data) {
   node* this_node = new node (data);
   if (head == nullptr) 
      head = this_node;
   else 
      tail->set_next (this_node);
   tail = this_node;
}

template <class T>
void list<T>::remove_duplicates () {
   for (node* curr = head; curr != nullptr; curr = curr->get_next()) {
      auto found = duplicate_tracker.find(curr->get());
      if (found == duplicate_tracker.end())
         duplicate_tracker.insert(curr->get());
      else 
         delete_node (curr);
   }

   for (node* curr = head; curr != nullptr; curr = curr->get_next()) 
      cout << curr->get() << endl;
}

int main () {
   list<int> test;

   test.push_back(2);
   test.push_back(1);
   test.push_back(5);
   test.push_back(10);
   test.push_back(7);
   test.push_back(5);
   test.push_back(3);
   test.push_back(2);

   test.remove_duplicates();

   return EXIT_SUCCESS;
}
