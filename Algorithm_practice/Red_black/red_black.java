//Adam Pinarbasi
//Red-black tree implementation in Java

class red_black {

   //node field
   
   class node {
      int key;
      int color; //0 is black, 1 is red
      Object value;
      node parent;
      node right;
      node left;
   }
   static node root = null;

   //methods

   //returns null if key not found
   Object get (int key) {
      for (node curr = root; curr != null;) {
         if (key == curr.key) 
            return curr.value;

         if (key < curr.key) 
            curr = curr.left;

         if (key > curr.key) 
            curr = curr.right;
      }
      return null;
   }

   void bt_insert (int key) {
      if (root == null) {
         node x   = new node();
         x.key    = key;
         x.color  = 0;
         x.parent = null;
         x.right  = null;
         x.left   = null;
         root     = x;
         return;
      }

      for (node curr = root; curr != null;) {
         if (key == curr.key) return;

         node x   = new node();
         x.key    = key;
         x.color  = 1;
         x.parent = null
         x.right  = null;
         x.left   = null;

         if (key < curr.key) {
            if (curr.left == null) {
               x.parent  = curr;
               curr.left = x;
               return;
            }
            else curr = curr.left;
         }

         else {
            if (curr.right == null) {
               x.parent   = curr;
               curr.right = x;
               return;
            }
            else curr = curr.right;
         }
      }
   }

   void insert (int key) {
      bt_insert(key);
   }
   
   void delete (int key) {}

   static void print () {
   }
}

