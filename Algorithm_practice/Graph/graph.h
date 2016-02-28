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
   using tpair = std::pair<T, T>;

   private:
      /* T in all of these is the vertex and the second element in the 
       * pair is whatever is being mapped to that vertex */
      std::unordered_map<T, adj*>* neighbors;
      std::unordered_map<T, T>* parent;
      std::unordered_map<T, int>* level;
      std::unordered_map<T, int>* distance;
      std::unordered_map<tpair*, int>* weight;
      std::unordered_map<T, T>* predecessor;

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

      std::unordered_map<T, int>* init_weight () {
         std::unordered_map<T, int>* weight = new std::unordered_map<T, int>;
         for (auto it = neighbors->begin ();
                   it != neighbors->end ();
                   ++it) 
            weight->emplace (it->first, INFINITY);
         return weight;
      }

      void relax (T vertex, T vertex_, int wgt) {
         (void) vertex;
         (void) vertex_;
         (void) wgt;
      }

      void dijkstra_loop
            (std::priority_queue<T, std::vector<T>, std::greater<T>> vertices) {
      }

   public:
      graph () {
         neighbors = new std::unordered_map<T, adj*>;
         parent = new std::unordered_map<T,T>;
         level = new std::unordered_map<T, int>;
         distance = new std::unordered_map<T, int>;
         weight = new std::unordered_map<tpair*, int>;
         predecessor = new std::unordered_map<T, T>;
      }

      ~graph () {
         delete neighbors;
         delete parent;
         delete level;
         delete distance;
         delete weight;
         delete predecessor;
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

      //for adding weighted edges
      void add_arc (T vertex, T vertex_, int wgt) {
         if (neighbors->find (vertex) != neighbors->end () and
             neighbors->find (vertex_) != neighbors->end ()) {
            add_arc (vertex, vertex_);
            tpair* this_pair = new tpair;
            this_pair->first = vertex;
            this_pair->second = vertex_;
            weight->emplace (this_pair, wgt);
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

      // Dijkstra's algorithm
      void dijkstra (T source) {
         std::unordered_map<T, int>* weight = init_weight ();
         distance->emplace (source, 0);
         std::priority_queue<T, std::vector<T>, std::greater<T>> vertices;
         for (auto it = neighbors->begin ();
                   it != neighbors->end ();
                   ++it) 
            vertices.push (it->first);
         dijkstra_loop (vertices);
         while (not vertices.empty ()) {
            T tval = vertices.top ();
            vertices.pop ();
            for (auto it = neighbors->at(tval)->begin ();
                      it != neighbors->at(tval)->end ();
                      ++it) {
               std::cout << "ya I'm pretty bored lol" << std::endl;
            }
         }
      }

};

#endif
