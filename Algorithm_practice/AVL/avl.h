#ifndef __AVL_H__
#define __AVL_H__

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

            node (const T& data_) {
               data = up_T (new T (data_));
               right = sp_node (nullptr);
               left = sp_node (nullptr);
            }

            ~node () {}

            const T& get_data () const {
               return *data;
            }

      };

      using sp_node = std::shared_ptr<node>;

      sp_node root;

      static bool handle_insert (sp_node& this_node, const T& data) {
         if (this_node.get () == nullptr) {
            this_node = sp_node (new node (data));
            return true;
         }
         return false;
      }

      void bst_insert (const T& data) {
         if (handle_insert (root, data))
            return;

         node* curr = root.get ();
         while (curr != nullptr) {
            if (curr->get_data () == data)
               return;
            if (data < curr->get_data ()) {
               if (handle_insert (curr->left, data))
                  return;
               else
                  curr = curr->left.get ();
            }
            else {
               if (handle_insert (curr->right, data))
                  return;
               else
                  curr = curr->right.get ();
            }
         }
      }

      void bst_remove (const T& data) {
      }

      //in-order traversal
      void print_ (sp_node this_node) const {
         if (this_node.get () == nullptr) return;
         print_ (this_node->left);
         std::cout << this_node->get_data () << std::endl;
         print_ (this_node->right);
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
      }

      void remove (const T& data) {
         bst_remove (data);
      }

      void print () const {
         print_ (root);
      }

};

#endif
