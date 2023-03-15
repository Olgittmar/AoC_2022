#ifndef PRETTYPRINT_PRETTYPRINT_HPP
#define PRETTYPRINT_PRETTYPRINT_HPP

#include <experimental/source_location>
#include <filesystem>
#include <iostream>

namespace utils {

constexpr inline auto
log(const std::experimental::source_location location, auto... vals) -> std::ostream&
{
    // Not a fan of this string usage, but it's prettier than what I had previously
    std::cout << std::filesystem::path(location.file_name()).filename().c_str() << "::" << location.line()
	      << "::" << location.function_name() << ":\n";
    return ((std::cout << vals), ...);
}

constexpr inline auto
log_error(const std::experimental::source_location location, auto... vals) -> std::ostream&
{
    // Just replacing cout with cerr for now, need to read up on how to do logging properly and figure out how to
    // properly log to a file
    std::cerr << std::filesystem::path(location.file_name()).filename().c_str() << "::" << location.line()
	      << "::" << location.function_name() << ":\n";
    return ((std::cerr << vals), ...);
}

} // namespace utils
#endif