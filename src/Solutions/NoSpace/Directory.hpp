#ifndef SOLLUTIONS_NOSPACE_NOSPACE_DIRECTORY_HPP
#define SOLLUTIONS_NOSPACE_NOSPACE_DIRECTORY_HPP

#include "File.hpp"

#include <deque>
#include <functional>
#include <iomanip>
#include <vector>

namespace Solutions::NoSpace {

template<typename SizeType> struct Directory : public File<SizeType>
{
	Directory(const std::string& name, const std::shared_ptr<Directory>& parent) : File<SizeType>(name, 0UL, parent) {}

	[[nodiscard]] auto getSize() -> SizeType;

	static void gatherDirsIf(std::deque<std::shared_ptr<Directory>>& dirsToCheck, std::vector<std::shared_ptr<Directory>>& gatheredDirs,
				 std::function<SizeType(SizeType)> compare);

	std::vector<File<SizeType>> files = {};
	std::vector<std::shared_ptr<Directory>> dirs = {};
	bool sizeCalculated = false;
	SizeType m_totalSize = 0;
};

} // namespace Solutions::NoSpace
#endif