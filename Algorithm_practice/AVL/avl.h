#ifndef __AVL_H__
#define __AVL_H__

#include <cassert>
#include <memory>

template <typename T>
class avl {

   private:

      class node {

         private:

            using up_int = std::unique_ptr<const int>;
            using up_T = std::unique_ptr<const T>;
            using sp_node = std::shared_ptr<node>;
            using wp_node = std::weak_ptr<node>;

            up_T data;
            up_int key;

         public:

            sp_node right;
            sp_node left;
            sp_node parent;
            signed int balance_factor;

            node (const int key_, const T& data_) {
               data = up_T (new T (data_));
               key = up_int (new int (key_));
               right = sp_node (nullptr);
               left = sp_node (nullptr);
               parent = sp_node (nullptr);
               balance_factor = 0;
            }

            ~node () {}

            const int& get_key () const {
               return *key;
            }

            const T& get_data () const {
               return *data;
            }

      };

      using sp_node = std::shared_ptr<node>;

      sp_node root = sp_node (nullptr);
      sp_node nil = sp_node (nullptr); //root's parent

      static int height (const sp_node& this_node) {
         if (this_node.get () == nullptr)
            return 0;
         int rheight = height (this_node->right);
         int lheight = height (this_node->left);
         return 1 + (rheight > lheight ? rheight : lheight);
      }

      /*static const sp_node& check_violations (const sp_node& this_node) {
         return this_node;
      }

      const sp_node& check_violations () const {
         return check_violations (root);
      }*/

      //true -> violations
      //the heights of the right and left subtree may differ by at most 1
      static bool check_violations (const sp_node& this_node) {
         int lheight = height (this_node->left);
         int rheight = height (this_node->right);
         if ( (lheight > rheight and lheight - rheight > 1) or
              (rheight > lheight and rheight - lheight > 1) )
            return true;
         return false;
      }

      void cleanup (sp_node& this_node) const {
         if (this_node.get () == nullptr) 
            return;
         check_violations (this_node); 
         cleanup (this_node->parent);
      }

      //TODO: update balance_factor
      //precondition: this_node must have a left child
      static void right_rotate (sp_node& old_root) {
         assert (old_root->left.get () != nullptr);
         sp_node new_root = old_root->left;
         old_root->left = new_root->right;
         new_root->right = old_root;
         old_root = new_root;
      }

      //TODO: update balance_factor
      //precondition: this_node must have a right child
      static void left_rotate (sp_node& old_root) {
         assert (old_root->right.get () != nullptr);
         sp_node new_root = old_root->right;
         old_root->right = new_root->left;
         new_root->left = old_root;
         old_root = new_root;
      }

      static bool handle_bst_insert (sp_node& this_node, 
                                     sp_node& parent,
                                     const int key,
                                     const T& data) {
         if (this_node.get () == nullptr) {
            this_node = sp_node (new node (key, data)); 
            this_node->parent = parent; //this is causing the memory leak!!!
            return true;
         }
         return false;
      }

      sp_node bst_insert (const int key, const T& data) {
         if (handle_bst_insert (root, nil, key, data))
            return root;
         sp_node curr = root;
         while (true) {
            if (curr->get_key () == key)
               return curr;
            if (key < curr->get_key ()) {
               if (handle_bst_insert (curr->left, curr, key, data)) {
                  --(curr->balance_factor);
                  if (curr->parent.get () != nullptr)
                     --(curr->parent->balance_factor);
                  return curr->left;
               }
               curr = curr->left;
            }
            else {
               if (handle_bst_insert (curr->right, curr, key, data)) {
                  ++(curr->balance_factor);
                  if (curr->parent.get () != nullptr)
                     ++(curr->parent->balance_factor);
                  return curr->right;
               }
               curr = curr->right;
            }
         }
      }

      void bst_remove (const T& data) {
      }

      //in-order traversal
      static void print_ (const sp_node& this_node) {
         if (this_node.get () == nullptr) 
            return;
         print_ (this_node->left);
         std::cout << this_node->get_data () << std::endl;
         print_ (this_node->right);
      }

      //pre-order traversal
      //shows hierarchy of the tree
      static void print__ (const sp_node& this_node) {
         if (this_node.get () == nullptr) 
            return;

         std::cout << std::endl;
         std::cout << "key: " << this_node->get_key () << std::endl 
                   << "data: " << this_node->get_data () << std::endl;
         
         if (this_node->left.get () != nullptr) 
            std::cout << "left_key: " << this_node->left->get_key () 
                      << std::endl
                      << "left_data: " << this_node->left->get_data ()
                      << std::endl;

         if (this_node->right.get () != nullptr)
            std::cout << "right_key: " << this_node->right->get_key () 
                      << std::endl
                      << "right_data: " << this_node->right->get_data ()
                      << std::endl;
         std::cout << std::endl;

         print__ (this_node->left);
         print__ (this_node->right);
      }

   public:

      avl () {}

      ~avl () {}

      void insert (const int key, const T& data) {
         sp_node inserted = bst_insert (key, data);
         cleanup (inserted);
      }

      void remove (const T& data) {
         bst_remove (data);
      }

      void test () {
         std::cout << std::endl;
         std::cout << "original structure\nheight: " << height (root)
                   << std::endl;
         print__ (root);

         left_rotate (root);
         std::cout << "after left_rotate (root)\nheight: " << height (root)
                   << std::endl;
         print__ (root);

         right_rotate (root);
         std::cout << "after right_rotate (root)\nheight: " << height (root)
                   << std::endl;
         print__ (root);
      }

      void print () const {
         print_ (root);
      }

};

#endif
