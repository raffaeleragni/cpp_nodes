#include "nodes.hpp"

#include <map>
#include <unordered_set>

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
      nodes.find(id2)->second->insert(id1);
    }

    void unlink(long id1, long id2) {
      if (!linked(id1, id2))
        return;
      nodes.find(id1)->second->erase(id2);
      nodes.find(id2)->second->erase(id1);
    }

    bool linked(long id1, long id2) {
      if (!has_pair(id1, id2))
        return false;
      return nodes.find(id1)->second->contains(id2) && nodes.find(id2)->second->contains(id1);
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
}
