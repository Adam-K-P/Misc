#ifndef __AVL_H__
#define __AVL_H__

#include <memory>

template <typename T>
class avl {

   private:

      struct node {

         const T& data;
         std::shared_ptr<node> right;
         std::shared_ptr<node> left;

         node (const T& data_) : data(data_) {
            right = std::shared_ptr<node> (nullptr);
            left = std::shared_ptr<node> (nullptr);
         }
         ~node () {}

      };

      using sp_node = std::shared_ptr<node>;

      sp_node root;

      void bst_insert (const T& data) {
         if (root.get () == nullptr) {
            std::cout << "root changed to " << data << std::endl;
            root = sp_node (new node (data));
            return;
         }
         sp_node curr = root;
         while (curr.get () != nullptr) {
            std::cout << "sanity check" << std::endl;
            if (curr->data == data)
               return;
            if (data < curr->data)
               curr.swap (curr->left);
            else 
               curr.swap (curr->right);
         }
         //curr.reset (new node (data));
      }

      void bst_remove (const T& data) {
      }

      //in-order traversal
      void print_ (sp_node this_node) const {
         if (this_node.get () == nullptr) return;
         print_ (this_node->left);
         std::cout << this_node->data << std::endl;
         print_ (this_node->right);
      }

   public:
      avl () {
         root = sp_node (nullptr);
      }

      ~avl () {}

      void insert (const T& data) {
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
