#define CATCH_CONFIG_MAIN
#include "../test.hpp"

#include "../src/lib/lib.hpp"

TEST_CASE("Sample test") {
  MyClass c;
  REQUIRE(c.main() == 0);
}
