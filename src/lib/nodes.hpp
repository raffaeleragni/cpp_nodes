#ifndef NODES_HPP_
#define NODES_HPP_

#include <memory>

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
  private:
    class Pimpl;
    std::unique_ptr<Pimpl> pimpl;
  };

}

#endif
