#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct queue {

   void insert (T);
   void display () const;

   private:
   vector<T> stack_one;
   vector<T> stack_two;
   void make_normal ();
   void make_reverse ();
   
};

template <class T>
void queue<T>::insert (T inserter) {
   make_reverse ();
   stack_one.push_back (inserter);
   make_normal ();
}

template <class T>
void queue<T>::display () const {
   for (int i = 0; i < stack_two.size (); ++i) 
      cout << stack_two.at (i) << endl;
}

//reverse using two stacks
//finish on stack_two
template <class T>
void queue<T>::make_normal () {
   while (stack_one.size()) {
      stack_two.push_back (stack_one.at (stack_one.size() - 1));
      stack_one.pop_back();
   }
}

template <class T>
void queue<T>::make_reverse () {
   while (stack_two.size()) {
      stack_one.push_back (stack_two.at (stack_two.size() - 1));
      stack_two.pop_back();
   }
}

int main () {
   queue<int> test;

   test.insert (1);
   test.insert (2);
   test.insert (3);
   test.insert (4);
   test.insert (5);

   test.display();
   
   return EXIT_SUCCESS;
}

