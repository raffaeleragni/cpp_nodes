#ifndef NODES_HPP_
#define NODES_HPP_

#include <memory>
#include <list>

namespace nodes {

  class Nodes {
  public:
    Nodes();
    ~Nodes();
  public:
    size_t size();
    void add(long id);
    void remove(long id);
    void link(long id1, long id2);
    void unlink(long id1, long id2);
    bool linked(long id1, long id2);
    std::list<int> find_path(long id_start, long id_end);
  private:
    class Pimpl;
    std::unique_ptr<Pimpl> pimpl;
  };

}

#endif
