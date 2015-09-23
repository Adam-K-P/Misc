//Adam Pinarbasi
//red_black
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
   node root = null;
   node nil  = new node ();

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

   node bt_insert (int key) {
      if (root == null) {
         node x   = new node();
         x.key    = key;
         x.color  = 0;
         x.parent = null;
         x.right  = nil;
         x.left   = nil;
         root     = x;
         return root;
      }

      for (node curr = root; curr != null;) {
         if (key == curr.key) return null;

         node x   = new node();
         x.key    = key;
         x.color  = 1;
         x.parent = null;
         x.right  = nil;
         x.left   = nil;

         if (key < curr.key) {
            if (curr.left == null) {
               x.parent  = curr;
               curr.left = x;
               return x;
            }
            else curr = curr.left;
         }

         else {
            if (curr.right == null) {
               x.parent   = curr;
               curr.right = x;
               return x;
            }
            else curr = curr.right;
         }
      }
      return null;
   }

   //precondition: element.right != null
   void left_rotate (node element) {
      node y = element.right;
      element.right = y.left;
      if (y.left != nil) 
         y.left.parent = element;
      y.parent = element.parent;
      if (element.parent == nil) 
         root = y;
      else if (element == element.parent.left)
         element.parent.left = y;
      else 
         element.parent.right = y;
      y.left = element;
      element.parent = y;
   }

   void right_rotate (node element) {
      node y = element.left;
      element.left = y.right;
      if (y.right != nil) 
         y.right.parent = element;
      y.parent = element.parent;
      if (element.parent == nil)
         root = y;
      else if (element == element.parent.right)
         element.parent.right = y;
      else
         element.parent.left = y;
      y.right = element;
      element.parent = y;
   }

   void insert (int key) {
      node inserted = bt_insert(key);
      if (inserted == null) return;
      inserted.color = 1;
      while (inserted != root && inserted.color == 1) {
         if (inserted.parent == inserted.parent.parent.left) {
            node x = inserted.parent.parent.right;
            if (x.color == 1) { 
               //case 1
            }
            else {
               if (x == inserted.parent.right) {
                  //case 2
               }
               //case 3
            }
         }
         else {
            node x = inserted.parent.parent.left;
            if (x.color == 1) {
               //case 1
            }
            else {
               if (x == inserted.parent.left) {
                  //case 2
               }
               //case 3
            }
         }
      }
   }
   
   //fails if key corresponds to root
   void delete (int key) {
   }

   void print () {
      print_element(root);
   }

   void print_element (node element) {
      if (element == null) return;
      print_element(element.left);
      System.out.printf("%d\n", element.key);
      print_element(element.right);
   }
}

