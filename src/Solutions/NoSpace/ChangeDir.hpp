#ifndef SOLLUTIONS_NOSPACE_NOSPACE_CHANGEDIR_HPP
#define SOLLUTIONS_NOSPACE_NOSPACE_CHANGEDIR_HPP

#include "Command.hpp"
#include "Directory.hpp"

namespace Solutions::NoSpace {

template<typename SizeType> class ChangeDirectory : public Command<SizeType>
{
    public:

	ChangeDirectory(std::string_view data) : m_destinationName{data} {}

	ChangeDirectory(const ChangeDirectory& other) = default;
	ChangeDirectory(ChangeDirectory&& other) noexcept = default;

	~ChangeDirectory() override = default;

	auto operator=(const ChangeDirectory& other) -> ChangeDirectory& = default;
	auto operator=(ChangeDirectory&& other) noexcept -> ChangeDirectory& = default;

	auto execute(std::shared_ptr<Directory<SizeType>>& currentWorkingDirectory) -> bool override;

    private:

	static constexpr auto upOneDir = "..";
	std::string m_destinationName;
};

} // namespace Solutions::NoSpace
#endif