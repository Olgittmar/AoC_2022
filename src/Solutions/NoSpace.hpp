#ifndef SOLUTIONS_NOSPACE_HPP
#define SOLUTIONS_NOSPACE_HPP

#include <cstddef>
#include <string_view>

namespace Solutions {

constexpr size_t dirSizeLimit = 100000;
constexpr size_t availableSpaceOnFilesystem = 70000000;
constexpr size_t spaceOnFilesystemRequired = 30000000;

template<typename SizeType, SizeType MaxDirSize>
auto GetTotalSizeOfDirectories(const std::string_view& input, bool& success) -> std::uint64_t;

template<typename SizeType, SizeType TotalDiskSize, SizeType DiskSpaceNeeded>
auto GetSizeOfDirectoryToDelete(const std::string_view& input, bool& success) -> std::uint64_t;

} // namespace Solutions
#endif