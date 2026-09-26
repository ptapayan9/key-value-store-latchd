#include "store.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("GET returns a previously stored value", "[store]") {
  // Arrange: each test owns a fresh store, independent of other tests.
  Store store;

  // Act: write a value, then read it through the public API.
  store.set("server:name", "latch");
  auto value = store.get("server:name");

  // Assert: REQUIRE stops this test on failure, protecting the dereference.
  REQUIRE(value.has_value());
  REQUIRE(*value == "latch");
}

TEST_CASE("SET replaces the value of an existing key", "[store]") {
  Store store;
  store.set("server:name", "latch");

  store.set("server:name", "latch-dev");
  auto value = store.get("server:name");

  REQUIRE(value.has_value());
  REQUIRE(*value == "latch-dev");
}

TEST_CASE("GET returns no value for a missing key", "[store]") {
  Store store;
  store.set("server:name", "latch");

  REQUIRE_FALSE(store.get("missing").has_value());
  // Repeated reads must not insert an empty string for the missing key.
  REQUIRE_FALSE(store.get("missing").has_value());
}

TEST_CASE("GET distinguishes an empty string from a missing key", "[store]") {
  Store store;
  store.set("empty", "");

  auto value = store.get("empty");

  REQUIRE(value.has_value());
  REQUIRE(value->empty());
  REQUIRE_FALSE(store.get("missing").has_value());
}

TEST_CASE("Updating one key leaves another key unchanged", "[store]") {
  Store store;
  store.set("server:name", "latch");
  store.set("environment", "development");

  store.set("server:name", "latch-dev");

  auto name = store.get("server:name");
  auto environment = store.get("environment");
  REQUIRE(name.has_value());
  REQUIRE(*name == "latch-dev");
  REQUIRE(environment.has_value());
  REQUIRE(*environment == "development");
}
