#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

string remove_duplicates (string& this_str) {
   bool chars[256];
   string* ret_str = new string();
   for (size_t i = 0; i < this_str.size(); ++i) {
      int chr = this_str.at(i);
      if (not chars[chr]) {
         ret_str->push_back(chr);
         chars[chr] = true;
      }
   }
   return *ret_str;
}

int main () {
   string test = "aaaaaabbbbbbcccccdddd";
   cout << remove_duplicates(test) << endl;
   return EXIT_SUCCESS;
}






