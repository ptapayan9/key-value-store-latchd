#include "store.hpp"
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

int main() {

  Store store;
  std::string line;

  while (std::getline(std::cin, line)) {

    if (line == "QUIT") {
      break;
    }

    std::istringstream input{line};
    std::string command;

    if (!(input >> command)) {
      continue;
    }

    if (command == "GET") {

      std::string key, extra;
      if (!(input >> key)) {
        std::cout << "ERR expected GET key";
        continue;
      }

      if (input >> extra) {
        std::cout << "ERR expected SET key value \n";
        continue;
      }

      auto value = store.get(key);
      if (!(value.has_value())) {
        std::cout << "(nil)";
        continue;
      }

      std::cout << *value << "\n";
    }

    if (command == "SET") {

      std::string key, value, extra;
      if (!(input >> key >> value)) {
        std::cout << "ERR expected SET key value \n";
        continue;
      }

      if (input >> extra) {
        std::cout << "ERR expected SET key value \n";
        continue;
      }

      store.set(key, value);
      std::cout << "OK\n";
    } else {
      std::cout << "ER unkown command\n";
    }
  }

  return 0;
}
