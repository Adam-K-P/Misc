//Adam Pinarbasi
//Red-black tree implementation in Java

class red_black {

   class node {
      int key;
      int color; //0 is black, 1 is red
      Object value;
      node parent;
      node right;
      node left;
   }
   node nil  = new node ();
   node root = null;

   /* methods */

   //returns null if key not found
   node search (int key) {
      for (node curr = root; curr != null;) {
         if (key == curr.key) 
            return curr;
         if (key < curr.key) 
            curr = curr.left;
         if (key > curr.key) 
            curr = curr.right;
      }
      return null;
   }

   public void set (int key, Object value) {
      (search(key)).value = value;
   }

   public Object get (int key) {
      return (search(key)).value;
   }

   node maximum (node rooted) {
      node max = null;
      for (node curr = root; curr != nil; curr = curr.right) 
         max = curr;
      return max;
   }
   
   node minimum (node rooted) {
      node min = null;
      for (node curr = root; curr != nil; curr = curr.left)
         min = curr;
      return min;
   }

   node predecessor (node in) {
      if (in.left != nil) {
         node max = in.left;
         for (node curr = in.left; curr != nil; curr = curr.right)
            max = curr;
         return max;
      }
      else {
         for (node curr = in; curr.parent != null; curr = curr.parent) {
            if (curr == curr.parent.right)
               return curr.parent;
         }
      }
      return null; //predecessor not found
   }

   node successor (node in) {
      if (in.right != nil) {
         node min = in.right;
         for (node curr = in.right; curr != nil; curr = curr.left) 
            min = curr;
         return min;
      }
      else {
         for (node curr = in; curr.parent != null; curr = curr.parent) {
            if (curr == curr.parent.left)
               return curr.parent;
         }
      }
      return null; //successor not found
   }

   node btInsert (int key) {
      if (root == null) {
         node x   = new node();
         x.key    = key;
         x.color  = 0;
         x.parent = nil;
         x.right  = nil;
         x.left   = nil;
         root     = x;
         return root;
      }

      for (node curr = root; curr != nil;) {
         if (key == curr.key) return null;

         node x   = new node();
         x.key    = key;
         x.color  = 1;
         x.parent = nil;
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

   //precondition: element.right != nil
   void left_rotate (node rooted) {
      node pivot = rooted.right;
      rooted.right = pivot.left;
      if (pivot.left != nil) 
         pivot.left.parent = rooted;
      pivot.parent = rooted.parent;
      if (rooted.parent == nil) 
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
      if (rooted.parent == nil)
         root = pivot;
      else if (rooted == rooted.parent.right)
         rooted.parent.right = pivot;
      else
         rooted.parent.left = pivot;
      pivot.right = rooted;
      rooted.parent = pivot;
   }

   void insertCases (node inserted, boolean right) {
      node x = right ? inserted.parent.parent.right :
                       inserted.parent.parent.left;
      if (x.color == 1) {
         //case 1
         inserted.parent.color = 0;
         x.color = 0;
         inserted.parent.parent.color = 1;
         inserted = inserted.parent.parent;
      }
      else {
         if (inserted == (right ? inserted.parent.right :
                                  inserted.parent.left)) {
            //case 2
            inserted = inserted.parent;
            if (right) left_rotate(inserted);
            else right_rotate(inserted);
         }
         //case 3
         inserted.parent.color = 0;
         inserted.parent.parent.color = 1;
         if (right) right_rotate(inserted.parent.parent);
         else left_rotate(inserted.parent.parent);
      }
   }

   void insert (int key) {
      node inserted = btInsert(key);
      if (inserted == null) return;
      inserted.color = 1;
      while (inserted != root && inserted.parent.color == 1) {
         if (inserted.parent == inserted.parent.parent.left) 
            insertCases(inserted, true);
         else 
            insertCases(inserted, false);
      }
      root.color = 0;
   }
   
   void transplant (node thisNode, node thatNode) {
      if (thisNode.parent == nil)
         root = thatNode;
      else if (thisNode == thisNode.parent.left)
         thisNode.parent.left = thatNode;
      else 
         thisNode.parent.right = thatNode;
      thatNode.parent = thisNode.parent;
   }

   /*void delete_fixup (node thisNode) {
      node thatNode = null;
      while (thisNode != root && thisNode.color == 0) {
         if (thisNode == thisNode.parent.left) {
            thatNode = thisNode.parent.right;
            if (thatNode.color == 1) {
               thatNode.color = 0;
               thisNode.parent.color = 1;
               left_rotate(thisNode.parent);
               thatNode = thisNode.parent.right;
            }
            if (thatNode.left.color == 0 && thatNode.right.color == 0) {
               thatNode.color = 0;
               thisNode = thisNode.parent;
            }
            else {
               if (thatNode.right.color == 0) {
                  thatNode.left.color = 0;
                  thatNode.color = 1;
                  right_rotate(thatNode);
                  thatNode = thisNode.parent.right;
               }
               thatNode.color = thisNode.parent.color;
               thisNode.parent.color = 0; 
               thatNode.right.color = 0;
               left_rotate(thisNode.parent);
               thisNode = root;
            }
         }
         else*/

   void delete (int key) {
      node del = search(key);
      if (del == null) return;
      node thisNode = del, thatNode;
      int thisColor = thisNode.color;

      if (del.left == nil) {
         thatNode = del.right;
         transplant(del, del.right);
      }
      else if (del.right == nil) {
         thatNode = del.left;
         transplant(del, del.left);
      }
      else {
         thisNode = minimum(del.right);
         thisColor = thisNode.color;
         thatNode = thisNode.right;
         if (thisNode.parent == del) 
            thatNode.parent = thisNode;
         else {
            transplant(thisNode, thisNode.right);
            thisNode.right = del.right;
            thisNode.right.parent = thisNode;
         }
         transplant(del, thisNode);
         thisNode.left = del.left;
         thisNode.left.parent = thisNode;
         thisNode.color = del.color;
      }
      if (thisColor == 0);
   }

   void print () {
      print_element(root);
      System.out.printf("root:%d\n", root.key);
   }

   void print_element (node element) {
      if (element == nil) return;
      print_element(element.left);
      System.out.printf("%d\n%d\n\n", element.key, element.color);
      print_element(element.right);
   }
}

