#include "store.hpp"
#include <iostream>

int main() {

  Store store;
  store.set("server:name", "latch");

  auto value = store.get("server:name");

  if (value.has_value()) {
    std::cout << *value << '\n';
  } else {
    std::cout << "(nil)\n";
  }

  store.set("server:name", "Latch-overwrite");
  value = store.get("server:name");
  std::cout << *value << '\n';

  return 0;
}
