#include "ChangeDir.hpp"

namespace Solutions::NoSpace {

template<typename SizeType>
auto
ChangeDirectory<SizeType>::execute(std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory) -> bool
{
    if (RootName == m_destinationName)
	{
	    while (!!currentWorkingDirectory && RootName != currentWorkingDirectory->getName())
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
      std::ranges::find_if(currentWorkingDirectory->dirs, [this](const std::shared_ptr<Directory<SizeType>>& file)
			   { return m_destinationName == file->getName(); });

    if (currentWorkingDirectory->dirs.end() != destination)
	{
	    currentWorkingDirectory = *destination;
	    return true;
    }

    return false;
}

template struct ChangeDirectory<size_t>;
} // namespace Solutions::NoSpace