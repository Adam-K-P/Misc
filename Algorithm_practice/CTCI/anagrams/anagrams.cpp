#include <iostream>
#include <unordered_set>
#include <cstdlib>

using namespace std;

bool anagrams (string& this_str, string& that_str) {
   int these_chrs [256];
   int those_chrs [256];

   for (int i = 0; i <= 256; ++i) {
      these_chrs[i] = 0;
      those_chrs[i] = 0;
   }

   for (size_t i = 0; i < this_str.size(); ++i) {
      int c = this_str.at(i);
      ++these_chrs[c];
   }

   for (size_t i = 0; i < that_str.size(); ++i) {
      int c = that_str.at(i);
      ++those_chrs[c];
   }

   for (size_t i = 0; i <= 256; ++i) {
      if (these_chrs[i] != those_chrs[i]) {
         cout << i << endl;
         cout << these_chrs[i] << endl << those_chrs[i] << endl;
         return false;
      }
   }
   return true;
}

int main () {
   string this_str = "blahh";
   string that_str = "hhalb";
   bool test = anagrams (this_str, that_str);
   if (test) cout << "yay" << endl;
   else cout << "boo" << endl;
   return EXIT_SUCCESS;
}
   

