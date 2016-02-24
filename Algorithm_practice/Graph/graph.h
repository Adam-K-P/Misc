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
      std::unordered_map<T, std::unordered_set<T>*>* parent;
      std::unordered_map<T, int>* level;

   public:
      graph () {
         neighbors = new std::unordered_map<T, std::unordered_set<T>*>;
         parent = new std::unordered_map<T, std::unordered_set<T>*>;
         level = new std::unordered_map<T, int>;
      }

      ~graph () {
         delete neighbors;
         delete parent;
         delete level;
      }

      //could sort if I wanted
      void print () {
         for (auto it = neighbors->begin (); it != neighbors->end (); ++it) {
            std::cout << "Vertex: " << it->first << std::endl;
            for (auto jt = it->second->begin (); 
                           jt != it->second->end (); 
                           ++jt) 
               std::cout << "     Neighbor: " << *jt << std::endl;
         }
      }

      void add_vertex (T vertex) {
         std::unordered_set<T>* neighbors_ = new std::unordered_set<T>;
         neighbors->emplace (vertex, neighbors_);
      }

      void add_arc (T vertex, T vertex_) {
         std::unordered_set<T>* neighbors_ = neighbors->at (vertex);
         neighbors_->emplace (vertex_);
      }

      void bfs (T source) {
         level->emplace (source, 0);
         int i = 1;
      }

};

#endif
