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
  REQUIRE(!n.linked(2, 1));
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

TEST_CASE("add does not unlink nodes") {
  nodes::Nodes n;
  link_two(n);
  n.add(2);
  REQUIRE(n.linked(1, 2));
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

TEST_CASE("no path found case, non existent nodes") {
  nodes::Nodes n;
  link_four(n);
  auto path = n.find_path(8, 10);
  REQUIRE(path.size() == 0);
}

TEST_CASE("no path found case, existend nodes") {
  nodes::Nodes n;
  link_four(n);
  auto path = n.find_path(1, 4);
  REQUIRE(path.size() == 0);
}

TEST_CASE("path found on a single link") {
  nodes::Nodes n;
  link_four(n);
  auto path = n.find_path(1, 2);
  list<int> expected = {1, 2};
  REQUIRE(path == expected);
}

TEST_CASE("no path found inverse") {
  nodes::Nodes n;
  link_four(n);
  auto path = n.find_path(2, 1);
  REQUIRE(path.size() == 0);
}


void link_four_connected(nodes::Nodes& n) {
  n.add(1);
  n.add(2);
  n.add(3);
  n.add(4);
  n.link(1, 2);
  n.link(2, 1);
  n.link(2, 3);
  n.link(3, 4);
}

TEST_CASE("path found on a double step link") {
  nodes::Nodes n;
  link_four_connected(n);
  auto path = n.find_path(1, 4);
  list<int> expected = {1, 2, 3, 4};
  REQUIRE(path == expected);
}

// link(pair, weight)
// type of nodes, identifiers
// path type (list of nodes in a sequence)
