#ifndef UTILS_GETUSERNAME_GETUSERNAME_HPP
#define UTILS_GETUSERNAME_GETUSERNAME_HPP

#include <string>

namespace utils {

auto GetUserName(std::ostream& out, std::istream& input) -> std::string;

} // namespace utils
#endif