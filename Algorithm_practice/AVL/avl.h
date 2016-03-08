#ifndef __AVL_H__
#define __AVL_H__

#include <cassert>
#include <memory>

template <typename T>
class avl {

   private:

      class node {

         private:

            using up_T = std::unique_ptr<T>;
            using sp_node = std::shared_ptr<node>;

            up_T data;

         public:

            sp_node right;
            sp_node left;
            sp_node parent;

            node (const T& data_) {
               data = up_T (new T (data_));
               right = sp_node (nullptr);
               left = sp_node (nullptr);
               parent = sp_node (nullptr);
            }

            ~node () {}

            const T& get_data () const {
               return *data;
            }

      };

      using sp_node = std::shared_ptr<node>;

      sp_node root;
      sp_node nil = sp_node (nullptr); //root's parent

      void cleanup (sp_node& this_node) {
      }

      //precondition: this_node must have a left child
      static void right_rotate (sp_node& old_root) {
         assert (old_root->left.get () != nullptr);
         sp_node new_root = old_root->left;
         old_root->left = new_root->right;
         new_root->right = old_root;
         old_root = new_root;
      }

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
                                     const T& data) {
         if (this_node.get () == nullptr) {
            this_node = sp_node (new node (data));
            this_node->parent = parent;
            return true;
         }
         return false;
      }

      void bst_insert_ (const T& data) {
         if (handle_bst_insert (root, nil, data))
            return;
         sp_node curr = root;
         while (true) {
            if (curr->get_data () == data)
               return;
            if (data < curr->get_data ()) {
               if (handle_bst_insert (curr->left, curr, data))
                  return;
               curr = curr->left;
            }
            else {
               if (handle_bst_insert (curr->right, curr, data))
                  return;
               curr = curr->right;
            }
         }
      }

      void bst_remove (const T& data) {
      }

      //in-order traversal
      void print_ (const sp_node& this_node) const {
         if (this_node.get () == nullptr) return;
         print_ (this_node->left);
         std::cout << this_node->get_data () << std::endl;
         print_ (this_node->right);
      }

      //shows hierarchy of the tree as well
      void print__ (const sp_node& this_node) const {
         if (this_node.get () == nullptr) return;
         print__ (this_node->left);
         std::cout << "data: " << this_node->get_data () << std::endl;
         if (this_node->left.get () != nullptr) 
            std::cout << "left: " << this_node->left->get_data () << std::endl;
         if (this_node->right.get () != nullptr)
            std::cout << "right: " << this_node->right->get_data () 
                      << std::endl;
         print__ (this_node->right);
      }

   public:

      avl () {
         root = sp_node (nullptr);
      }

      ~avl () {}

      void insert (const T& data) {
         /*if (root.get() != nullptr) 
            std::cout << "in insert, root is: " << root->data << std::endl;*/
         bst_insert_ (data);
      }

      void remove (const T& data) {
         bst_remove (data);
      }

      void test () {
         std::cout << "original structure\n";
         print__ (root);
         left_rotate (root);
         std::cout << "after left_rotate (root)\n";
         print__ (root);
         right_rotate (root);
         std::cout << "after right_rotate (root)\n";
         print__ (root);
      }

      void print () const {
         print_ (root);
      }

};

#endif
