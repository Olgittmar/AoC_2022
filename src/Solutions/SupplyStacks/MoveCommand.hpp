#ifndef SOLUTIONS_SUPPLYSTACKS_MOVECOMMAND_HPP
#define SOLUTIONS_SUPPLYSTACKS_MOVECOMMAND_HPP

#include <vector>

namespace Solutions::SupplyStacks {

class MoveCommand
{
    public:

	constexpr MoveCommand(long numCrates, size_t from,
			      size_t to) // NOLINT(readability-identifier-length)
	  : m_numCrates(numCrates), m_from(from), m_to(to)
	{
	}

	[[nodiscard]] static auto makeMoveCommand(std::string_view line) -> MoveCommand;

	[[nodiscard]] inline auto
	getNumCrates() const -> long
	{
	    return m_numCrates;
	}

	[[nodiscard]] inline auto
	fromPos() const -> size_t
	{
	    return m_from;
	}

	[[nodiscard]] inline auto
	toPos() const -> size_t
	{
	    return m_to;
	}

	friend auto operator<<(std::ostream& out, const MoveCommand& command) -> std::ostream&;

    private:

	long m_numCrates = 0;
	size_t m_from = 0;
	size_t m_to = 0;
};

[[nodiscard]] auto parseRearrangeCommands(std::string_view data) -> std::vector<Solutions::SupplyStacks::MoveCommand>;

auto operator<<(std::ostream& out, const MoveCommand& command) -> std::ostream&;

} // namespace Solutions::SupplyStacks
#endif