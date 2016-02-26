#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename T>
class graph {

   using adj = std::unordered_set<T>;

   private:
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

      //maybe sort before printing?
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

      void add_arc (T vertex, T vertex_) {
         if (neighbors != nullptr and 
            neighbors->find (vertex) != neighbors->end ()) {
            adj* neighbors_ = neighbors->at (vertex);
            neighbors_->insert (vertex_);
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

#endif
