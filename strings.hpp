#ifndef CPPSAK_STRINGS_HPP
#define CPPSAK_STRINGS_HPP

#include <string>
#include <string_view>
#include <vector>

namespace cppsak {
namespace strings {
std::string Join(std::vector<std::string> s, std::string_view sep);

std::string_view TrimPrefix(std::string_view s, char c);

std::string_view TrimSuffix(std::string_view s, char c);

std::vector<std::string_view> Split(std::string_view s, char sep);

std::string Enclose(std::string_view s);
}  // namespace strings
}  // namespace cppsak

#endif
