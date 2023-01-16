#include "List.hpp"

namespace Solutions::NoSpace {

template<typename SizeType>
auto
List<SizeType>::execute(std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory) -> bool
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

template<typename SizeType>
void
List<SizeType>::parseDir(const std::string_view& line,
			 const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory)
{
    const auto dirName = std::string{line.substr(strlen(dirIdentifier))};
    m_dirsToAdd.push_back(std::make_shared<Directory<SizeType>>(dirName, currentWorkingDirectory));
}

template<typename SizeType>
void
List<SizeType>::parseRegularFile(const std::string_view& line,
				 const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory)
{
    const auto nameStart = line.rfind(argDelimiter);
    const auto filename = std::string(line.substr(nameStart + 1));
    const auto sizeStr = std::string(line.substr(0, nameStart));
    const auto fileSize = std::stoul(sizeStr);

    m_filesToAdd.emplace_back(filename, fileSize, currentWorkingDirectory);
}

template<typename SizeType>
void
List<SizeType>::parseData(const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory)
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

template struct List<size_t>;

} // namespace Solutions::NoSpace