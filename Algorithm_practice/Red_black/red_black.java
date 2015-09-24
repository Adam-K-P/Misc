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
            if (curr.left == nil) {
               x.parent  = curr;
               curr.left = x;
               return x;
            }
            else curr = curr.left;
         }
         else {
            if (curr.right == nil) {
               x.parent   = curr;
               curr.right = x;
               return x;
            }
            else curr = curr.right;
         }
      }
      return null;
   }

   //temporary test function
   void do_left (int key) { 
      for (node curr = root; curr != nil; ) {
         if (curr.key == key) {
            right_rotate(curr);
            break;
         }
         else if (key < curr.key)
            curr = curr.left;
         else
            curr = curr.right;
      }
      System.out.printf("%d\n%d\n", root.key, root.right.key);
   }

   //precondition: element.right != nil
   void left_rotate (node rooted) {
      node pivot = rooted.right;
      rooted.right = pivot.left;
      if (pivot.left != nil) 
         pivot.left.parent = rooted;
      pivot.parent = rooted.parent;
      if (rooted.parent == null) 
         root = pivot;
      else if (rooted == rooted.parent.left)
         rooted.parent.left = pivot;
      else 
         rooted.parent.right = pivot;
      pivot.left = rooted;
      rooted.parent = pivot;
   }

   //precondition: element.left != nil
   void right_rotate (node rooted) {
      node pivot = rooted.left;
      rooted.left = pivot.right;
      if (pivot.right != nil) 
         pivot.right.parent = rooted;
      pivot.parent = rooted.parent;
      if (rooted.parent == null)
         root = pivot;
      else if (rooted == rooted.parent.right)
         rooted.parent.right = pivot;
      else
         rooted.parent.left = pivot;
      pivot.right = rooted;
      rooted.parent = pivot;
   }

   void insert (int key) {
      node inserted = bt_insert(key);
      if (inserted == null) return;
      inserted.color = 1;
      while (inserted != root && inserted.parent.color == 1) {
         if (inserted.parent == inserted.parent.parent.left) {
            node x = inserted.parent.parent.right;
            if (x.color == 1) { 
               //case 1
               inserted.parent.color = 0;
               x.color = 0;
               inserted.parent.parent.color = 1;
               inserted = inserted.parent.parent;
            }
            else {
               if (inserted == inserted.parent.right) {
                  //case 2
                  inserted = inserted.parent;
                  left_rotate(inserted);
               }
               //case 3
               inserted.parent.color = 0;
               inserted.parent.parent.color = 1;
               right_rotate(inserted.parent.parent);
            }
         }
         else {
            node x = inserted.parent.parent.left;
            if (x.color == 1) {
               //case 4
               inserted.parent.color = 0;
               x.color = 0;
               inserted.parent.parent.color = 1;
               inserted = inserted.parent.parent;
            }
            else {
               if (inserted == inserted.parent.left) {
                  //case 5
                  inserted = inserted.parent;
                  right_rotate(inserted);
               }
               //case 6
               inserted.parent.color = 0;
               inserted.parent.parent.color = 1;
               left_rotate(inserted.parent.parent);
            }
         }
      }
      root.color = 0;
   }
   
   void delete (int key) {
   }

   void print () {
      print_element(root);
   }

   void print_element (node element) {
      if (element == nil) return;
      print_element(element.left);
      System.out.printf("%d\n", element.key);
      print_element(element.right);
   }
}

