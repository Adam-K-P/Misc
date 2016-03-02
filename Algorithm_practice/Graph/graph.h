#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template<typename T>
class graph {

   using adj = std::unordered_set<T>;

   private:
      /* T in all of these is the vertex and the second element in the 
       * pair is whatever is being mapped to that vertex */
      std::unordered_map<T, adj*>* neighbors;
      std::unordered_map<T, T>* parent;
      std::unordered_map<T, int>* level;

      void dfs_visit (T source) {
         for (auto it = neighbors->at(source)->begin ();
                   it != neighbors->at(source)->end ();
                   ++it) {
            if (parent->find (*it) == parent->end ()) {
               parent->emplace (*it, source);
               dfs_visit (*it);
            }
         }
      }

   public:
      graph () {
         neighbors = new std::unordered_map<T, adj*>;
         parent = new std::unordered_map<T,T>;
         level = new std::unordered_map<T, int>;
      }

      ~graph () {
         delete neighbors;
         delete parent;
         delete level;
      }

      void print () {
         for (auto it = neighbors->begin (); it != neighbors->end (); ++it) {
            std::cout << "Vertex: " << it->first << std::endl;
            if (parent->find (it->first) != parent->end ()) 
               std::cout << "   Parent: " << parent->at (it->first) 
                         << std::endl;
         }
      }

      void add_vertex (T vertex) {
         adj* neighbors_ = new adj;
         neighbors->emplace (vertex, neighbors_);
      }

      //for adding unweighted edges
      void add_arc (T vertex, T vertex_) {
         if (neighbors->find (vertex) != neighbors->end () and
             neighbors->find (vertex_) != neighbors->end ()) {
            adj* neighbors_ = neighbors->at (vertex);
            neighbors_->insert (vertex_);
         }
         else {
            std::cout << "Vertex: " << vertex << " and Vertex: " << vertex_ 
                      << " are not in the graph; continuing with execution" 
                      << std::endl;
         }
      }

      void dfs () {
         for (auto it = neighbors->begin ();
                   it != neighbors->end ();
                   ++it) 
            if (parent->find (it->first) == parent->end ()) 
               dfs_visit (it->first);
      }

      void bfs (T source) {
         level->emplace (source, 0);
         std::deque<T> frontier;
         int i = 1;
         for (frontier.push_back (source); 
              not frontier.empty ();
              frontier.pop_front (), ++i) {
            for (auto it = frontier.begin (); it != frontier.end (); ++it) {
               for (auto jt = neighbors->at(*it)->begin ();
                         jt != neighbors->at(*it)->end ();
                         ++jt) {
                  if (level->find (*jt) == level->end ()) {
                     level->emplace (*jt, i);
                     parent->emplace (*jt, *it);
                     frontier.push_back (*jt);
                  }
               }
            }
         }
      }

};

template<typename T>
class directed_graph {

   using adj = std::unordered_set<int>;

   private:
      //maps key to value (which is of type T)
      std::unordered_map<int, T> vertex;
      //maps key to distance associated with key
      std::unordered_map<int, int> distance;
      //maps (key, key) pair to weight of edge
      std::unordered_map<std::pair<int, int>*, int> weight;
      //maps key to adjacency list
      std::unordered_map<int, adj> neighbors;

   public:
      directed_graph () { 
         /*vertex = new std::unordered_map<int, T>;
         distance = new std::unordered_map<int, int>;
         weight = new std::unordered_map<std::pair<int, int>*, int>;
         neighbors = new std::unordered_map<int, adj*>;*/
      }
};

#endif
