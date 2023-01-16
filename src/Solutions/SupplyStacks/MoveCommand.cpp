#include "MoveCommand.hpp"

#include <ostream>

namespace Solutions::SupplyStacks {

[[nodiscard]] auto
MoveCommand::makeMoveCommand(const std::string_view& line) -> MoveCommand
{
    const auto afterMove = line.find_first_not_of(_move);

    const auto beforeFrom = line.find(_from);
    const auto afterFrom = line.find_first_not_of(_from, beforeFrom);

    const auto beforeTo = line.find(_to);
    const auto afterTo = line.find_first_not_of(_to, beforeTo);

    // TODO: implement fromChars generator for constexpr?
    const std::string numCratesStr{line.substr(afterMove, beforeFrom - afterMove)};
    const std::string fromStr{line.substr(afterFrom, beforeTo - afterFrom)};
    const std::string toStr{line.substr(afterTo)};

    const long numCrates = std::stol(numCratesStr);
    const size_t from = std::stoul(fromStr);
    const size_t to = std::stoul(toStr); // NOLINT(readability-identifier-length)

    return MoveCommand{numCrates, from - 1UL * static_cast<unsigned long>(from != 0),
		       to - 1UL * static_cast<unsigned long>(from != 0)};
}

[[nodiscard]] auto
parseRearrangeCommands(const std::string_view& data) -> std::vector<Solutions::SupplyStacks::MoveCommand>
{
    std::vector<Solutions::SupplyStacks::MoveCommand> _ret;
    constexpr auto lineDelimiter = '\n';

    uint32_t pos = 0;
    while (pos < data.size())
	{
	    const auto nextPos = data.find(lineDelimiter, pos);
	    if (nextPos > data.size())
		{
		    break;
	    }
	    const auto line = data.substr(pos, nextPos - pos);

	    const auto moveCommand = Solutions::SupplyStacks::MoveCommand::makeMoveCommand(line);

	    _ret.emplace_back(moveCommand);
	    pos = nextPos + 1;
	}
    return _ret;
}

auto
operator<<(std::ostream& out, const MoveCommand& command) -> std::ostream&
{
    out << MoveCommand::_move << command.m_numCrates << MoveCommand::_from << command.m_from << MoveCommand::_to
	<< command.m_to;
    return out;
}

} // namespace Solutions::SupplyStacks