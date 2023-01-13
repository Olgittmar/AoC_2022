#include "NoSpace.hpp"

#include <algorithm>
#include <bits/ranges_algo.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

namespace {

template<typename SizeType> struct File;
template<typename SizeType> struct Directory;

template<typename SizeType>
void executeCommand(const std::string_view& line, std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory);

template<typename SizeType> class Command
{
    public:

	Command() = default;
	Command(const Command& other) = default;
	Command(Command&& other) noexcept = default;

	virtual ~Command() = default;

	auto operator=(const Command& other) -> Command& = default;
	auto operator=(Command&& other) noexcept -> Command& = default;

	static constexpr auto commandIdentifier = "$ ";

	virtual auto
	execute(std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory) -> bool
	{
	    return false;
	}

    protected:
    private:
};

template<typename SizeType> struct File
{
	File(std::string name, size_t size, const std::shared_ptr<Directory<SizeType>>& parent)
	  : m_name{std::move(name)}, m_size(size), m_parent(parent)
	{
	}

	[[nodiscard]] auto
	getSize() const -> SizeType
	{
	    return m_size;
	}

	auto
	getName() const -> std::string
	{
	    return m_name;
	}

	auto
	getParent() const -> std::shared_ptr<Directory<SizeType>>
	{
	    return m_parent.lock();
	}

    private:

	std::weak_ptr<Directory<SizeType>> m_parent;
	const std::string m_name;
	const SizeType m_size;
};

template<typename SizeType> struct Directory : public File<SizeType>
{
	Directory(const std::string& name, const std::shared_ptr<Directory>& parent) : File<SizeType>(name, 0UL, parent)
	{
	}

	[[nodiscard]] auto
	getSize() -> SizeType
	{
	    if (!sizeCalculated)
		{
		    uint32_t totalSize = 0;

		    for (const auto& item : files)
			{
			    totalSize += item.getSize();
			}

		    for (const auto& dir : dirs)
			{
			    totalSize += dir->getSize();
			}

		    m_totalSize = totalSize;
		    sizeCalculated = true;
	    }

	    return m_totalSize;
	}

	static void
	gatherDirsIf(std::deque<std::shared_ptr<Directory>>& dirsToCheck,
		     std::vector<std::shared_ptr<Directory>>& gatheredDirs, std::function<SizeType(SizeType)> compare)
	{
	    // Condition isApplicable;

	    const auto cwd = dirsToCheck.front();
	    const SizeType cwdSize = cwd->getSize();

	    if (compare(cwdSize))
		{
		    gatheredDirs.emplace_back(cwd);
	    }

	    for (const auto& dir : cwd->dirs)
		{
		    dirsToCheck.emplace_back(dir);
		}

	    dirsToCheck.pop_front();
	}

	// friend auto operator<<(std::ostream& out, const Directory& dir) -> std::ostream&;

	std::vector<File<SizeType>> files = {};
	std::vector<std::shared_ptr<Directory>> dirs = {};
	bool sizeCalculated = false;
	SizeType m_totalSize = 0;
};

template<typename SizeType> struct Root : public Directory<SizeType>
{
	// Should in principle be a "singleton" for the scope of the instance of the solution function call
	static constexpr auto name = "/";
	Root() : Directory<SizeType>(name, nullptr) {}

	[[nodiscard]] static auto
	makeRoot(const std::string_view& input) -> std::shared_ptr<Root>
	{
	    auto root = std::make_shared<Root>();
	    std::shared_ptr<Directory<SizeType>> currentWorkingDirectory = root;

	    // Find first command
	    size_t pos = 0;

	    pos = input.find(Command<SizeType>::commandIdentifier) + strlen(Command<SizeType>::commandIdentifier);

	    while (pos < input.size())
		{
		    const auto nextPos = input.find(Command<SizeType>::commandIdentifier, pos);
		    const auto commandData = input.substr(pos, nextPos - pos);
		    pos = nextPos + strlen(Command<SizeType>::commandIdentifier) * size_t(nextPos < input.size());

		    executeCommand(commandData, currentWorkingDirectory);
		}

	    return root;
	}
};

template<typename SizeType>
auto
operator<<(std::ostream& out, const Directory<SizeType>& dir) -> std::ostream&
{
    out << dir.getName() << ' ' << dir.m_totalSize << '\n';

    for (const auto& file : dir.files)
	{
	    out << "- " << file.getName() << ' ' << file.getSize() << '\n';
	}

    out << '\n';
    for (const auto& subDir : dir.dirs)
	{
	    out << std::setfill(' ') << *subDir;
	}

    return out;
}

template<typename SizeType> class List : public Command<SizeType>
{
    public:

	explicit List(const std::string_view& data) : m_data(data) {}

	auto
	execute(std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory) -> bool override
	{
	    parseData(currentWorkingDirectory);

	    SizeType cwdSize = 0;
	    for (const auto& file : m_filesToAdd)
		{
		    currentWorkingDirectory->files.emplace_back(file);
		}

	    for (const auto& dir : m_dirsToAdd)
		{
		    currentWorkingDirectory->dirs.emplace_back(dir);
		}

	    return true;

	    return false;
	}

    private:

	static constexpr auto lineDelimiter = '\n';
	static constexpr auto argDelimiter = ' ';
	static constexpr auto dirIdentifier = "dir ";

	void
	parseDir(const std::string_view& line, const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory)
	{
	    const auto dirName = std::string{line.substr(strlen(dirIdentifier))};
	    m_dirsToAdd.push_back(std::make_shared<Directory<SizeType>>(dirName, currentWorkingDirectory));
	}

	void
	parseRegularFile(const std::string_view& line,
			 const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory)
	{
	    const auto nameStart = line.rfind(argDelimiter);
	    const auto filename = std::string(line.substr(nameStart + 1));
	    const auto sizeStr = std::string(line.substr(0, nameStart));
	    const auto fileSize = std::stoul(sizeStr);

	    m_filesToAdd.emplace_back(filename, fileSize, currentWorkingDirectory);
	}

	void
	parseData(const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory)
	{
	    size_t pos = 0;
	    // TODO: Make a getLines() function to replace this while(pos < data.size()) pattern
	    while (pos < m_data.size())
		{
		    const auto nextPos = m_data.find(lineDelimiter, pos);
		    const auto line = m_data.substr(pos, nextPos - pos);
		    pos = nextPos + size_t(nextPos < m_data.size());

		    if (line.empty())
			{
			    break;
		    }

		    if (line.starts_with(dirIdentifier))
			{
			    parseDir(line, currentWorkingDirectory);
			    continue;
		    }

		    parseRegularFile(line, currentWorkingDirectory);
		}
	}

	std::string_view m_data;
	std::vector<File<SizeType>> m_filesToAdd;
	std::vector<std::shared_ptr<Directory<SizeType>>> m_dirsToAdd;
};

template<typename SizeType> class ChangeDirectory : public Command<SizeType>
{
    public:

	ChangeDirectory(const std::string_view& data) : m_destinationName{data} {}

	ChangeDirectory(const ChangeDirectory& other) = default;
	ChangeDirectory(ChangeDirectory&& other) noexcept = default;

	~ChangeDirectory() override = default;

	auto operator=(const ChangeDirectory& other) -> ChangeDirectory& = default;
	auto operator=(ChangeDirectory&& other) noexcept -> ChangeDirectory& = default;

	auto
	execute(std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory) -> bool override
	{
	    if (Root<SizeType>::name == m_destinationName)
		{
		    while (!!currentWorkingDirectory && Root<SizeType>::name != currentWorkingDirectory->getName())
			{
			    currentWorkingDirectory = currentWorkingDirectory->getParent();
			}
		    return true;
	    }

	    if (upOneDir == m_destinationName && currentWorkingDirectory->getParent())
		{
		    currentWorkingDirectory = currentWorkingDirectory->getParent();
		    return true;
	    }

	    auto destination = std::ranges::find_if(currentWorkingDirectory->dirs,
						    [this](const std::shared_ptr<Directory<SizeType>>& file)
						    { return m_destinationName == file->getName(); });

	    if (currentWorkingDirectory->dirs.end() != destination)
		{
		    currentWorkingDirectory = *destination;
		    return true;
	    }

	    return false;
	}

    private:

	static constexpr auto upOneDir = "..";
	std::string m_destinationName;
};

template<typename SizeType>
void
executeCommand(const std::string_view& line, std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory)
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

	    ChangeDirectory<SizeType> cdCommand{cdData};
	    cdCommand.execute(currentWorkingDirectory);
    }

    const auto lsPos = line.find(listIdentifier);
    if (lsPos < line.size())
	{
	    const auto lsStartPos = lsPos + strlen(listIdentifier);
	    const auto lsEndPos = line.rfind(lineDelimiter);
	    const auto lsData = line.substr(lsStartPos, lsEndPos - lsStartPos);

	    List<SizeType> lsCommand{lsData};
	    lsCommand.execute(currentWorkingDirectory);
    }
}

} // namespace

namespace Solutions {

template<typename SizeType, SizeType MaxDirSize>
auto
GetTotalSizeOfDirectories(const std::string_view& input, bool& success) -> std::uint64_t
{
    std::uint64_t _ret = 0;
    auto isSmallEnough = [](SizeType dirSize) -> bool { return dirSize <= MaxDirSize; };

    auto root = Root<SizeType>::makeRoot(input);

    std::deque<std::shared_ptr<Directory<SizeType>>> dirsToCheck{root};
    std::vector<std::shared_ptr<Directory<SizeType>>> gatheredDirs{};

    while (!dirsToCheck.empty())
	{
	    Directory<SizeType>::gatherDirsIf(dirsToCheck, gatheredDirs, isSmallEnough);
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

    std::deque<std::shared_ptr<Directory<SizeType>>> dirsToCheck{root};
    std::vector<std::shared_ptr<Directory<SizeType>>> gatheredDirs{};

    while (!dirsToCheck.empty())
	{
	    Directory<SizeType>::gatherDirsIf(dirsToCheck, gatheredDirs, largeEnoughToDelete);
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

template auto GetTotalSizeOfDirectories<size_t, dirSizeLimit>(const std::string_view& input, bool& success)
  -> std::uint64_t;

template auto GetSizeOfDirectoryToDelete<size_t, availableSpaceOnFilesystem, spaceOnFilesystemRequired>(
  const std::string_view& input, bool& success) -> std::uint64_t;

} // namespace Solutions