#include "store.hpp"
#include <iostream>
#include <sstream>
#include <string>

enum class CommandType { Get, Set, Del, Exists, Quit, Unknown };

CommandType parse_command(const std::string &command) {
  if (command == "GET") {
    return CommandType::Get;
  }
  if (command == "SET") {
    return CommandType::Set;
  }
  if (command == "DEL") {
    return CommandType::Del;
  }
  if (command == "EXISTS") {
    return CommandType::Exists;
  }
  if (command == "QUIT") {
    return CommandType::Quit;
  }
  return CommandType::Unknown;
}

int main() {

  Store store;
  std::string line;

  while (std::getline(std::cin, line)) {

    std::istringstream input{line};
    std::string command;

    if (!(input >> command)) {
      continue;
    }

    switch (parse_command(command)) {
    case CommandType::Set: {
      std::string key, value, extra;
      if (!(input >> key >> value)) {
        std::cout << "ERR expected SET key value\n";
        break;
      }

      if (input >> extra) {
        std::cout << "ERR expected SET key value\n";
        break;
      }

      store.set(key, value);
      std::cout << "OK\n";
      break;
    }
    case CommandType::Get: {
      std::string key, extra;
      if (!(input >> key)) {
        std::cout << "ERR expected GET key\n";
        break;
      }

      if (input >> extra) {
        std::cout << "ERR expected GET key\n";
        break;
      }

      auto value = store.get(key);
      if (!(value.has_value())) {
        std::cout << "(nil)\n";
        break;
      }
      std::cout << *value << '\n';
      break;
    }
    case CommandType::Quit: {
      std::string extra;
      if (input >> extra) {
        std::cout << "ERR expected QUIT with no arguments\n";
        break;
      }
      return 0; // Exit main, not just the switch.
    }
    case CommandType::Del:
    case CommandType::Exists:
      std::cout << "ERR command not implemented yet\n";
      break;
    case CommandType::Unknown:
      std::cout << "ERR unknown command\n";
      break;
    }
  }

  return 0;
}
