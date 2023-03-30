#ifndef SOLUTIONS_NOSPACE_NOSPACE_HPP
#define SOLUTIONS_NOSPACE_NOSPACE_HPP

// std
#include <cstddef>
#include <string_view>

// internal
#include "ChangeDir.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "List.hpp"

namespace Solutions {

template<typename SizeType, SizeType MaxDirSize> auto GetTotalSizeOfDirectories(std::string_view input, bool& success) -> std::uint64_t;

template<typename SizeType, SizeType TotalDiskSize, SizeType DiskSpaceNeeded>
auto GetSizeOfDirectoryToDelete(std::string_view input, bool& success) -> std::uint64_t;

} // namespace Solutions
#endif