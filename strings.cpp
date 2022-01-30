
#include "strings.hpp"

namespace enums {
namespace strings {
std::string Join(std::vector<std::string> s, std::string_view sep) {
  std::string r;
  for (size_t i = 0; i < s.size(); ++i) {
    r += s[i];
    if (i != s.size() - 1) r += std::string(sep);
  }
  return r;
}

std::string_view TrimPrefix(std::string_view s, char c) {
  for (size_t i = 0; s[i] == c && i < s.size(); ++i) {
    s.remove_prefix(1);
  }
  return s;
}

std::string_view TrimSuffix(std::string_view s, char c) {
  for (auto i = s.size() - 1; s[i] == c && i >= 0; --i) {
    s.remove_suffix(1);
  }
  return s;
}

std::vector<std::string_view> Split(std::string_view s, char sep) {
  std::vector<std::string_view> r;
  s = TrimPrefix(s, ' ');
  while (true) {
    auto p = s.find_first_of(sep);
    if (p == std::string_view::npos) break;
    r.emplace_back(s.substr(0, p));
    s.remove_prefix(p + 1);
  }
  r.emplace_back(s);
  return r;
}

std::string Enclose(std::string_view s) {
  if (s.find_first_of(',') == std::string::npos) {
    return std::string{s};
  }
  std::string r{s};
  r = "(" + r;
  r.push_back(')');
  return r;
}

}  // namespace strings
}  // namespace enums
