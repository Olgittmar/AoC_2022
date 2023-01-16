#include "NoSpace.hpp"

#include "Definitions.hpp"

// Internal

// Std
#include <algorithm>
#include <cstddef>
#include <ranges>

namespace {

template<typename SizeType>
void
executeCommand(const std::string_view& line,
	       std::shared_ptr<Solutions::NoSpace::Directory<SizeType>>& currentWorkingDirectory)
{
    constexpr auto changeDirIdentifier = "cd ";
    constexpr auto listIdentifier = "ls\n";
    constexpr auto lineDelimiter = '\n';

    const auto cdPos = line.find(changeDirIdentifier);
    if (cdPos < line.size())
	{
	    const auto cdStartPos = cdPos + strlen(changeDirIdentifier);
	    const auto cdEndPos = line.find(lineDelimiter, cdStartPos);
	    const auto cdData = line.substr(cdStartPos, cdEndPos - cdStartPos);

	    Solutions::NoSpace::ChangeDirectory<SizeType> cdCommand{cdData};
	    cdCommand.execute(currentWorkingDirectory);
    }

    const auto lsPos = line.find(listIdentifier);
    if (lsPos < line.size())
	{
	    const auto lsStartPos = lsPos + strlen(listIdentifier);
	    const auto lsEndPos = line.rfind(lineDelimiter);
	    const auto lsData = line.substr(lsStartPos, lsEndPos - lsStartPos);

	    Solutions::NoSpace::List<SizeType> lsCommand{lsData};
	    lsCommand.execute(currentWorkingDirectory);
    }
}

template<typename SizeType> struct Root : public Solutions::NoSpace::Directory<SizeType>
{
	// Should in principle be a "singleton" for the scope of the instance of the solution function call
	static constexpr auto name = Solutions::NoSpace::RootName;
	Root() : Solutions::NoSpace::Directory<SizeType>(name, nullptr) {}

	[[nodiscard]] static auto makeRoot(const std::string_view& input) -> std::shared_ptr<Root>;
};

template<typename SizeType>
[[nodiscard]] auto
Root<SizeType>::makeRoot(const std::string_view& input) -> std::shared_ptr<Root<SizeType>>
{
    using Command = Solutions::NoSpace::Command<SizeType>;
    using Directory = Solutions::NoSpace::Directory<SizeType>;

    auto root = std::make_shared<Root>();
    std::shared_ptr<Directory> currentWorkingDirectory = root;

    // Find first command
    size_t pos = 0;

    pos = input.find(Command::commandIdentifier) + strlen(Command::commandIdentifier);

    while (pos < input.size())
	{
	    const auto nextPos = input.find(Command::commandIdentifier, pos);
	    const auto commandData = input.substr(pos, nextPos - pos);
	    pos = nextPos + strlen(Command::commandIdentifier) * size_t(nextPos < input.size());

	    executeCommand(commandData, currentWorkingDirectory);
	}

    return root;
}

template struct Root<size_t>;
} // namespace

namespace Solutions {

template<typename SizeType, SizeType MaxDirSize>
auto
GetTotalSizeOfDirectories(const std::string_view& input, bool& success) -> std::uint64_t
{
    std::uint64_t _ret = 0;
    auto isSmallEnough = [](SizeType dirSize) -> bool { return dirSize <= MaxDirSize; };

    auto root = Root<SizeType>::makeRoot(input);

    std::deque<std::shared_ptr<NoSpace::Directory<SizeType>>> dirsToCheck{root};
    std::vector<std::shared_ptr<NoSpace::Directory<SizeType>>> gatheredDirs{};

    while (!dirsToCheck.empty())
	{
	    NoSpace::Directory<SizeType>::gatherDirsIf(dirsToCheck, gatheredDirs, isSmallEnough);
	}

    for (const auto& dir : gatheredDirs)
	{
	    _ret += dir->getSize();
	}

    success = true;
    return _ret;
}

template<typename SizeType, SizeType TotalDiskSize, SizeType DiskSpaceNeeded>
auto
GetSizeOfDirectoryToDelete(const std::string_view& input, bool& success) -> std::uint64_t
{
    std::uint64_t _ret = 0;

    auto root = Root<SizeType>::makeRoot(input);
    const SizeType usedDiskSpace = root->getSize();

    auto largeEnoughToDelete = [&usedDiskSpace](SizeType dirSize) -> bool
    {
	const auto availableSpace = TotalDiskSize - usedDiskSpace;
	const auto requiredFolderSize = (DiskSpaceNeeded - availableSpace);
	return dirSize >= requiredFolderSize;
    };

    std::deque<std::shared_ptr<NoSpace::Directory<SizeType>>> dirsToCheck{root};
    std::vector<std::shared_ptr<NoSpace::Directory<SizeType>>> gatheredDirs{};

    while (!dirsToCheck.empty())
	{
	    NoSpace::Directory<SizeType>::gatherDirsIf(dirsToCheck, gatheredDirs, largeEnoughToDelete);
	}

    if (gatheredDirs.empty())
	{
	    return _ret;
    }

    auto smallestDir = std::ranges::min_element(
      gatheredDirs.cbegin(), gatheredDirs.cend(),
      [](const auto& dir1, const auto& dir2) constexpr { return dir1->getSize() < dir2->getSize(); });

    _ret = (*smallestDir)->getSize(); // ew

    success = true;
    return _ret;
}

template auto GetTotalSizeOfDirectories<size_t, NoSpace::dirSizeLimit>(const std::string_view& input, bool& success)
  -> std::uint64_t;

template auto
GetSizeOfDirectoryToDelete<size_t, NoSpace::availableSpaceOnFilesystem, NoSpace::spaceOnFilesystemRequired>(
  const std::string_view& input, bool& success) -> std::uint64_t;

} // namespace Solutions