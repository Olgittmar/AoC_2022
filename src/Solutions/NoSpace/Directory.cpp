#include "Directory.hpp"

#include "Command.hpp"

namespace Solutions::NoSpace {

template<typename SizeType>
[[nodiscard]] auto
Directory<SizeType>::getSize() -> SizeType
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

template<typename SizeType>
void
Directory<SizeType>::gatherDirsIf(std::deque<std::shared_ptr<Directory>>& dirsToCheck,
				  std::vector<std::shared_ptr<Directory>>& gatheredDirs,
				  std::function<SizeType(SizeType)> compare)
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

template struct Directory<size_t>;

} // namespace Solutions::NoSpace