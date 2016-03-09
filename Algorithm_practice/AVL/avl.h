#ifndef __AVL_H__
#define __AVL_H__

#include <cassert>
#include <memory>
#include <utility>

constexpr bool right_heavy = true;
constexpr bool left_heavy = false;

template <typename T>
class avl {

   private:

      class node {

         private:

            using up_int = std::unique_ptr<const int>;
            using up_T = std::unique_ptr<const T>;
            using sp_node = std::shared_ptr<node>;

            up_T data;
            up_int key;

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
      using p_bool = std::pair<bool, bool>;
      using violation = std::unique_ptr<p_bool>;

      sp_node root;
      const sp_node nil = sp_node (nullptr); //root's parent

      static int height (const sp_node& this_node) {
         if (this_node.get () == nullptr)
            return 0;
         int rheight = height (this_node->right);
         int lheight = height (this_node->left);
         return 1 + (rheight > lheight ? rheight : lheight);
      }

      //true -> violations
      //the heights of the right and left subtree may differ by at most 1
      static violation check_violations (const sp_node& this_node) {
         violation this_violation = violation (new p_bool);
         int lheight = height (this_node->left);
         int rheight = height (this_node->right);
         if (lheight > rheight and lheight - rheight > 1) {
            this_violation->first = true;
            this_violation->second = left_heavy;
         }
         else if (rheight > lheight and rheight - lheight > 1) {
            this_violation->first = true;
            this_violation->second = right_heavy;
         }
         else {
            this_violation->first = false;
            this_violation->second = false; //doesn't matter
         }
         return this_violation;
      }

      static void cleanup (sp_node& this_node) {
         if (this_node.get () == nullptr) 
            return;
         violation this_violation = check_violations (this_node);
         if (this_violation->first) 
            std::cout << "violation at: " << this_node->get_data ()
                      << (this_violation->second == right_heavy ?
                          " right heavy" : " left heavy") << std::endl;
         else
            cleanup (this_node->parent);
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
                                     const sp_node& parent,
                                     const T& data) {
         if (this_node.get () == nullptr) {
            this_node = sp_node (new node (data));
            this_node->parent = parent;
            return true;
         }
         return false;
      }

      void bst_insert (const T& data) {
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
      static void print_ (const sp_node& this_node) {
         if (this_node.get () == nullptr) return;
         print_ (this_node->left);
         std::cout << this_node->get_data () << std::endl;
         print_ (this_node->right);
      }

      //shows hierarchy of the tree as well
      static void print__ (const sp_node& this_node) {
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
         bst_insert (data);
         cleanup (root);
      }

      void remove (const T& data) {
         bst_remove (data);
      }

      void test () {
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
