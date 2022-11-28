#include "nodes.hpp"

#include <map>
#include <unordered_set>
#include <deque>

using namespace std;

namespace nodes {
  class Nodes::Pimpl {
  public:
    map<int, unique_ptr<unordered_set<int>>> nodes;

    size_t size() {
      return nodes.size();
    }

    void add(long id) {
      nodes.insert({id, make_unique<unordered_set<int>>()});
    }

    void remove(long id) {
      nodes.erase(id);
    }

    bool has_pair(long id1, long id2) {
      return nodes.contains(id1) && nodes.contains(id2);
    }

    void link(long id1, long id2) {
      if (!has_pair(id1, id2))
        return;
      nodes.find(id1)->second->insert(id2);
    }

    void unlink(long id1, long id2) {
      if (!linked(id1, id2))
        return;
      nodes.find(id1)->second->erase(id2);
    }

    bool linked(long id1, long id2) {
      if (!has_pair(id1, id2))
        return false;
      return nodes.find(id1)->second->contains(id2);
    }

    list<int> find_path(long id_start, long id_end) {
      if (!has_pair(id_start, id_end))
        return list<int>{};
      return find_path_bfs(id_start, id_end);
    }
    
    list<int> find_path_bfs(long start, long end) {
      deque<int> q;
      unordered_set<int> visited;
      map<int, list<int>> paths;
      q.push_back(start);
      paths.insert({start, list<int>{start}});
      while (!q.empty()) {
        int element = q.front();
        q.pop_front();

        list<int> path_to_here = paths.find(element)->second;
        
        if (element == end)
          return path_to_here;

        for (auto child = nodes.find(element)->second->begin(); child != nodes.find(element)->second->end(); ++child)
          if (!visited.contains(*child)) {
            list<int> new_path = path_to_here;
            new_path.push_back(*child);
            paths.insert({*child, new_path});
            q.push_back(*child);
          }

        visited.insert(element);
      }
      return list<int>{};
    }
  };

  Nodes::Nodes():
    pimpl(std::make_unique<Pimpl>()) {
  }

  Nodes::~Nodes() {
  }

  size_t Nodes::size() {
    return pimpl->size();
  }

  void Nodes::add(long id) {
    pimpl->add(id);
  }

  void Nodes::remove(long id) {
    pimpl->remove(id);
  }

  void Nodes::link(long id1, long id2) {
    pimpl->link(id1, id2);
  }

  void Nodes::unlink(long id1, long id2) {
    pimpl->unlink(id1, id2);
  }

  bool Nodes::linked(long id1, long id2) {
    return pimpl->linked(id1, id2);
  }

  list<int> Nodes::find_path(long id_start, long id_end) {
    return pimpl->find_path(id_start, id_end);
  }
}
