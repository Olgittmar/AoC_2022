#ifndef SOLLUTIONS_NOSPACE_NOSPACE_LIST_HPP
#define SOLLUTIONS_NOSPACE_NOSPACE_LIST_HPP

#include "Command.hpp"
#include "Directory.hpp"
#include "File.hpp"

#include <cstddef>
#include <cstring>
#include <vector>

namespace Solutions::NoSpace {

template<typename SizeType> class List : public Command<SizeType>
{
    public:

	explicit List(const std::string_view& data) : m_data(data) {}

	auto execute(std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory) -> bool override;

    private:

	static constexpr auto lineDelimiter = '\n';
	static constexpr auto argDelimiter = ' ';
	static constexpr auto dirIdentifier = "dir ";

	void parseDir(const std::string_view& line,
		      const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory);

	void parseRegularFile(const std::string_view& line,
			      const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory);

	void parseData(const std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory);

	std::string_view m_data;
	std::vector<File<SizeType>> m_filesToAdd;
	std::vector<std::shared_ptr<Directory<SizeType>>> m_dirsToAdd;
};

} // namespace Solutions::NoSpace
#endif