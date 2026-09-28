#include "store.hpp"
#include <optional>

void Store::set(const std::string &key, const std::string &value) {
  data_.insert_or_assign(key, value);
}

std::optional<std::string> Store::get(const std::string &key) const {

  auto result = data_.find(key);
  if (result != data_.end()) {
    return result->second;
  }
  return std::nullopt;
}
