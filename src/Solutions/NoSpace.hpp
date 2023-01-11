#ifndef SOLUTIONS_NOSPACE_HPP
#define SOLUTIONS_NOSPACE_HPP

#include <cstddef>
#include <string_view>

namespace Solutions {

constexpr size_t dirSizeLimit = 100000;
constexpr size_t availableSpaceOnFilesystem = 70000000;
constexpr size_t spaceOnFilesystemRequired = 30000000;

template<size_t MaxDirSize>
auto GetTotalSizeOfDirectories(const std::string_view& input, bool& success) -> std::uint64_t;

template<> auto GetTotalSizeOfDirectories<dirSizeLimit>(const std::string_view& input, bool& success) -> std::uint64_t;

template<size_t totalDiskSize, size_t diskSizeNeeded>
auto GetSizeOfDirectoryToDelete(const std::string_view& input, bool& success) -> std::uint64_t;

template<>
auto GetSizeOfDirectoryToDelete<availableSpaceOnFilesystem, spaceOnFilesystemRequired>(const std::string_view& input,
										       bool& success) -> std::uint64_t;

} // namespace Solutions
#endif