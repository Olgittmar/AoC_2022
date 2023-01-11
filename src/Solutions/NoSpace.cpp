#include "NoSpace.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

struct File;
struct Directory;

struct File
{
	File(std::string name, size_t size, const std::shared_ptr<Directory>& parent)
	  : m_name{std::move(name)}, m_size(size), m_parent(parent)
	{
	}

	[[nodiscard]] auto
	getSize() const -> size_t
	{
	    return m_size;
	}

	auto
	getName() const -> std::string
	{
	    return m_name;
	}

	auto
	getParent() const -> std::shared_ptr<Directory>
	{
	    return m_parent.lock();
	}

    private:

	std::weak_ptr<Directory> m_parent;
	const std::string m_name;
	const size_t m_size;
};

struct Directory : public File
{
	Directory(const std::string& name, const std::shared_ptr<Directory>& parent) : File(name, 0UL, parent) {}

	[[nodiscard]] auto
	getSize() -> size_t
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

	template<size_t MaxSize>
	static void
	gatherDirsWithSizeLessThan(std::deque<std::shared_ptr<Directory>>& dirsToCheck,
				   std::vector<std::shared_ptr<Directory>>& gatheredDirs)
	{
	    const auto cwd = dirsToCheck.front();
	    const auto cwdSize = cwd->getSize();

	    if (MaxSize >= cwdSize && cwdSize > 0)
		{
		    gatheredDirs.emplace_back(cwd);
	    }

	    for (const auto& dir : cwd->dirs)
		{
		    dirsToCheck.emplace_back(dir);
		}

	    dirsToCheck.pop_front();
	}

	friend auto operator<<(std::ostream& out, const Directory& dir) -> std::ostream&;

	std::vector<File> files = {};
	std::vector<std::shared_ptr<Directory>> dirs = {};
	bool sizeCalculated = false;
	size_t m_totalSize = 0;
};

struct Root : public Directory
{
	// Should in principle be a "singleton" for the scope of the instance of the solution function call
	static constexpr auto name = "/";
	Root() : Directory(name, nullptr) {}
};

auto
operator<<(std::ostream& out, const Directory& dir) -> std::ostream&
{
    const auto dirSize = dir.m_totalSize;
    out << dir.getName() << ' ' << dir.m_totalSize << '\n';

    for (const auto& file : dir.files)
	{
	    out << "- " << file.getName() << ' ' << file.getSize() << '\n';
	}

    out << '\n';
    const auto oldW = out.width();
    out.width(oldW + 1);
    for (const auto& subDir : dir.dirs)
	{
	    out << std::right << std::setfill(' ') << *subDir;
	}
    out.width(oldW);

    return out;
}

class Command
{
    public:

	Command() = default;
	Command(const Command& other) = default;
	Command(Command&& other) = default;

	virtual ~Command() = default;

	auto operator=(const Command& other) -> Command& = default;
	auto operator=(Command&& other) -> Command& = default;

	static constexpr auto commandIdentifier = "$ ";

	virtual auto
	execute(std::shared_ptr<Directory>& currentWorkingDirectory) -> bool
	{
	    return false;
	}

    protected:
    private:
};

class List : public Command
{
    public:

	explicit List(const std::string_view& data) : m_data(data) {}

	auto
	execute(std::shared_ptr<Directory>& currentWorkingDirectory) -> bool override
	{
	    parseData(currentWorkingDirectory);

	    size_t cwdSize = 0;
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
	parseDir(const std::string_view& line, const std::shared_ptr<Directory>& currentWorkingDirectory)
	{
	    const auto dirName = std::string{line.substr(strlen(dirIdentifier))};
	    m_dirsToAdd.push_back(std::make_shared<Directory>(dirName, currentWorkingDirectory));
	}

	void
	parseRegularFile(const std::string_view& line, const std::shared_ptr<Directory>& currentWorkingDirectory)
	{
	    const auto nameStart = line.rfind(argDelimiter);
	    const auto filename = std::string(line.substr(nameStart + 1));
	    const auto sizeStr = std::string(line.substr(0, nameStart));
	    const auto fileSize = std::stoul(sizeStr);

	    m_filesToAdd.emplace_back(filename, fileSize, currentWorkingDirectory);
	}

	void
	parseData(const std::shared_ptr<Directory>& currentWorkingDirectory)
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
	std::vector<File> m_filesToAdd;
	std::vector<std::shared_ptr<Directory>> m_dirsToAdd;
};

class ChangeDirectory : public Command
{
    public:

	ChangeDirectory(const std::string_view& data) : m_destinationName{data} {}

	ChangeDirectory(const ChangeDirectory& other) = default;
	ChangeDirectory(ChangeDirectory&& other) = default;

	~ChangeDirectory() override = default;

	auto operator=(const ChangeDirectory& other) -> ChangeDirectory& = default;
	auto operator=(ChangeDirectory&& other) -> ChangeDirectory& = default;

	auto
	execute(std::shared_ptr<Directory>& currentWorkingDirectory) -> bool override
	{
	    if (Root::name == m_destinationName)
		{
		    while (!!currentWorkingDirectory && Root::name != currentWorkingDirectory->getName())
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

	    auto destination =
	      std::ranges::find_if(currentWorkingDirectory->dirs, [this](const std::shared_ptr<Directory>& file)
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

void
executeCommand(const std::string_view& line, std::shared_ptr<Directory>& currentWorkingDirectory)
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

	    ChangeDirectory cdCommand{cdData};
	    cdCommand.execute(currentWorkingDirectory);
    }

    const auto lsPos = line.find(listIdentifier);
    if (lsPos < line.size())
	{
	    const auto lsStartPos = lsPos + strlen(listIdentifier);
	    const auto lsEndPos = line.rfind(lineDelimiter);
	    const auto lsData = line.substr(lsStartPos, lsEndPos - lsStartPos);

	    List lsCommand{lsData};
	    lsCommand.execute(currentWorkingDirectory);
    }
}

[[nodiscard]] auto
parseInput(const std::string_view& input) -> std::shared_ptr<Root>
{
    auto root = std::make_shared<Root>();
    std::shared_ptr<Directory> currentWorkingDirectory = root;

    // Find first command
    size_t pos = input.find(Command::commandIdentifier) + strlen(Command::commandIdentifier);

    while (pos < input.size())
	{
	    const auto nextPos = input.find(Command::commandIdentifier, pos);
	    const auto commandData = input.substr(pos, nextPos - pos);
	    pos = nextPos + strlen(Command::commandIdentifier) * size_t(nextPos < input.size());

	    executeCommand(commandData, currentWorkingDirectory);
	}

    return root;
}

} // namespace

namespace Solutions {

template<size_t MaxDirSize>
auto
GetTotalSizeOfDirectories(const std::string_view& input, bool& success) -> std::uint64_t
{
    std::uint64_t _ret = 0;

    try
	{
	    auto root = parseInput(input);

	    std::deque<std::shared_ptr<Directory>> dirsToCheck{root};
	    std::vector<std::shared_ptr<Directory>> gatheredDirs{};

	    while (!dirsToCheck.empty())
		{
		    Directory::gatherDirsWithSizeLessThan<MaxDirSize>(dirsToCheck, gatheredDirs);
		}

	    for (const auto& dir : gatheredDirs)
		{
		    _ret += dir->getSize();
		}

	    success = true;
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    } catch (...)
	{
	    std::cout << "Unhandled exception!" << std::endl;
	    // throw std::logic_error("Unhandled exception"); // Bad idea?
    }

    return _ret;
}

template<size_t totalDiskSize, size_t diskSizeNeeded>
auto
GetSizeOfDirectoryToDelete(const std::string_view& input, bool& success) -> std::uint64_t
{
    std::uint64_t _ret = 0;

    try
	{
	    success = true;
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    } catch (...)
	{
	    std::cout << "Unhandled exception!" << std::endl;
    }

    return _ret;
}

} // namespace Solutions