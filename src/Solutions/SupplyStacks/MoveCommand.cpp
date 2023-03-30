#include "MoveCommand.hpp"

#include <ostream>

namespace {
// Commands have the format 'move X from p to q'
constexpr auto _move = "move ";
constexpr auto _from = " from ";
constexpr auto _to = " to ";
} // namespace

namespace Solutions::SupplyStacks {

[[nodiscard]] auto
MoveCommand::makeMoveCommand(std::string_view line) -> MoveCommand
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

    return MoveCommand{numCrates, from - static_cast<unsigned long>(from != 0), to - static_cast<unsigned long>(from != 0)};
}

[[nodiscard]] auto
parseRearrangeCommands(std::string_view data) -> std::vector<MoveCommand>
{
    std::vector<MoveCommand> _ret;
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

	    const auto moveCommand = MoveCommand::makeMoveCommand(line);

	    _ret.emplace_back(moveCommand);
	    pos = nextPos + 1;
	}
    return _ret;
}

auto
operator<<(std::ostream& out, const MoveCommand& command) -> std::ostream&
{
    out << _move << command.m_numCrates << _from << command.m_from << _to << command.m_to;
    return out;
}

} // namespace Solutions::SupplyStacks