#define CATCH_CONFIG_MAIN
#include "test.hpp"

#include "../src/lib/nodes.hpp"

using namespace std;
using namespace nodes;



TEST_CASE("new nodes with size 0") {
  nodes::Nodes n;
  REQUIRE(n.size() == 0);
}

TEST_CASE("add item increases size") {
  nodes::Nodes n;
  n.add(1);
  REQUIRE(n.size() == 1);
  n.add(2);
  REQUIRE(n.size() == 2);
}

TEST_CASE("remove decreases size") {
  nodes::Nodes n;
  n.add(1);
  n.add(2);
  REQUIRE(n.size() == 2);

  n.remove(1);
  REQUIRE(n.size() == 1);
  n.remove(2);
  REQUIRE(n.size() == 0);
  n.remove(1);
  REQUIRE(n.size() == 0);
}

TEST_CASE("unlinked nodes") {
  nodes::Nodes n;
  REQUIRE(!n.linked(1, 2));
}



void link_two(nodes::Nodes& n) {
  n.add(1);
  n.add(2);
  n.link(1, 2);
}

TEST_CASE("link two nodes") {
  nodes::Nodes n;
  link_two(n);
  REQUIRE(n.linked(1, 2));
  REQUIRE(n.linked(2, 1));
}

TEST_CASE("unlink nodes") {
  nodes::Nodes n;
  link_two(n);
  REQUIRE(n.linked(1, 2));

  n.unlink(3, 4);
  REQUIRE(n.linked(1, 2));

  n.unlink(1, 2);
  REQUIRE(!n.linked(1, 2));
}



void link_four(nodes::Nodes& n) {
  n.add(1);
  n.add(2);
  n.add(3);
  n.add(4);
  n.link(1, 2);
  n.link(3, 4);
}

TEST_CASE("link more than two nodes") {
  nodes::Nodes n;
  link_four(n);
  REQUIRE(n.size() == 4);
  REQUIRE(n.linked(1, 2));
  REQUIRE(n.linked(3, 4));
}


// link(pair, weight)
// type of nodes, identifiers
// path type (list of nodes in a sequence)
