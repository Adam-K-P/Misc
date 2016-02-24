#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename T>
class graph {

   private:
      std::unordered_map<T, std::unordered_set<T>*>* neighbors;
      std::unordered_map<T, T>* parent;
      std::vector<T>* level;

   public:
      graph () {
         neighbors = new std::unordered_map<T, std::unordered_set<T>*>;
         parent = new std::unordered_map<T, T>;
         level = new std::vector<T>;
      }

      ~graph () {
         delete neighbors;
         delete parent;
         delete level;
      }

      void add_vertex (T vertex) {
         std::unordered_set<T>* neighbors_ = new std::unordered_set<T>;
         neighbors->insert (vertex, neighbors_);
      }

      void add_arc (T vertex, T vertex_) {
         std::unordered_set<T>* neighbors_ = neighbors->at (vertex);
         neighbors_->insert (vertex_);
      }

      void bfs (T source) {
      }

};

#endif
