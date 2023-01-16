#ifndef SOLLUTIONS_NOSPACE_NOSPACE_COMMAND_HPP
#define SOLLUTIONS_NOSPACE_NOSPACE_COMMAND_HPP

#include <cstring>
#include <memory>
namespace Solutions::NoSpace {

template<typename SizeType> struct Directory;

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

template struct Command<size_t>;

} // namespace Solutions::NoSpace
#endif