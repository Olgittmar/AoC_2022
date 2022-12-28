
#include "SupplyStacks.hpp"

#include "Definitions.hpp"

// Std
#include <algorithm>
#include <array>
#include <bits/ranges_algo.h>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <numeric>
#include <ostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>

namespace {

class MoveCommand
{
    public:

	constexpr MoveCommand(long numCrates, size_t from,
			      size_t to) // NOLINT(readability-identifier-length)
	  : m_numCrates(numCrates), m_from(from), m_to(to)
	{
	}

	[[nodiscard]] static auto
	makeMoveCommand(const std::string_view& line) -> MoveCommand
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

	// Commands have the format 'move X from p to q'
	static constexpr auto _move = "move ";
	static constexpr auto _from = " from ";
	static constexpr auto _to = " to ";

	long m_numCrates = 0;
	size_t m_from = 0;
	size_t m_to = 0;
};

auto
operator<<(std::ostream& out, const MoveCommand& command) -> std::ostream&
{
    out << MoveCommand::_move << command.m_numCrates << MoveCommand::_from << command.m_from << MoveCommand::_to
	<< command.m_to;
    return out;
}

template<size_t MaxNumStacks> class SupplyStack
{
    public:

	[[nodiscard]] auto
	getTops() const -> std::string
	{
	    std::string _ret;
	    std::ranges::for_each(m_stacks,
				  [&_ret](const MyStack_t& _stack)
				  {
				      if (!_stack.empty())
					  {
					      _ret += _stack.back();
				      }
				  });
	    return _ret;
	}

	[[nodiscard]] auto
	getTop(size_t index) const -> char
	{
	    // Why can this check be constexpr when the ones below can't?
	    if constexpr (MaxNumStacks <= index)
		{
		    std::cout << "getTop() : Invalid index: " << index << std::endl;
		    return 0;
	    }
	    MyStack_t& _stack = m_stacks.at(index);

	    if (_stack.empty())
		{
		    std::cout << "Stack at index " << index << " is empty!" << std::endl;
		    return 0;
	    }

	    return _stack.front();
	}

	auto
	popFromFrontOf(size_t index) -> char
	{
	    if (MaxNumStacks <= index) [[unlikely]]
		{
		    std::cout << "popFromFrontOf() : Invalid index: " << index << std::endl;
		    return 0;
	    }
	    MyStack_t& _stack = m_stacks.at(index);

	    if (_stack.empty())
		{
		    std::cout << "popFromFrontOf() : Stack at index " << index << " is empty!" << std::endl;
		    return 0;
	    }

	    const auto _ret = _stack.front();
	    _stack.pop_front();
	    return _ret;
	}

	void
	pushToBackOf(char crateId, size_t index)
	{
	    if (MaxNumStacks <= index) [[unlikely]]
		{
		    std::cout << "pushToBackOf() : Invalid index: " << index << std::endl;
		    return;
	    }
	    MyStack_t& _stack = m_stacks.at(index);
	    _stack.emplace_back(crateId);
	}

	void
	pushToFrontOf(char crateId, size_t index)
	{
	    if (MaxNumStacks <= index) [[unlikely]]
		{
		    std::cout << "pushToFrontOf() : Invalid index: " << index << std::endl;
		    return;
	    }
	    MyStack_t& _stack = m_stacks.at(index);
	    _stack.emplace_front(crateId);
	}

	template<size_t OtherSize>
	auto
	takeNFrom(SupplyStack<OtherSize>& other, size_t fromIndex, size_t toIndex, long numItemsToTake) -> bool
	{
	    try
		{
		    MyStack_t& fromStack = other.m_stacks.at(fromIndex);
		    MyStack_t& toStack = m_stacks.at(toIndex);

		    if (numItemsToTake > fromStack.size())
			{
			    throw std::invalid_argument("NumItemsToTake is larger than source stack size: " +
							std::to_string(numItemsToTake));
		    }

		    const auto pos = std::prev(fromStack.end(), numItemsToTake);
		    toStack.splice(toStack.end(), fromStack, pos, fromStack.end());
	    } catch (const std::exception& errc)
		{
		    std::cout << errc.what() << std::endl;
		    return false;
	    } catch (...)
		{
		    std::cout << "Unhandled exception!" << std::endl;
		    return false;
	    }
	    return true;
	}

	constexpr auto
	moveN(size_t fromIndex, size_t toIndex, long numItemsToTake) -> bool
	{
	    return takeNFrom<MaxNumStacks>(*this, fromIndex, toIndex, numItemsToTake);
	}

	template<size_t SupplyStackSize>
	friend auto operator<<(std::ostream& out, const SupplyStack<SupplyStackSize>& supplyStack) -> std::ostream&;

    private:

	using MyStack_t = std::list<char>;
	std::array<MyStack_t, MaxNumStacks> m_stacks; // misnomer?
};

template<size_t MaxNumStacks>
auto
operator<<(std::ostream& out, const SupplyStack<MaxNumStacks>& supplyStack) -> std::ostream&
{
    for (const auto& stack : supplyStack.m_stacks)
	{
	    for (const auto& crateId : stack)
		{
		    out << "[" << crateId << "] ";
		}
	    out << "\n";
	}
    return out;
}

// This pattern keeps recurring, create some kind of
// 'template<class T> charsToType(const std::string_view& data) -> T'
template<size_t MaxNumStacks>
void
parseLine(SupplyStack<MaxNumStacks>& _ret, const std::string_view& line)
{
    constexpr auto crateBegin = '[';
    constexpr auto crateEnd = ']';
    constexpr size_t spaceBetweenCrates = 1UL;
    constexpr size_t widthFromCrateToNext = 4UL;

    size_t linePos = 0;
    size_t stackIndex = 0;
    while (line.size() > linePos)
	{
	    const auto crateIdBegin = line.find(crateBegin, linePos);
	    if (line.size() < crateIdBegin)
		{
		    break;
	    }

	    const auto diffFromLastCrate = crateIdBegin - linePos;
	    const auto crateIdEnd = line.find(crateEnd, crateIdBegin + 1);
	    linePos = crateIdEnd + 1;

	    if (diffFromLastCrate > spaceBetweenCrates)
		{
		    stackIndex += diffFromLastCrate / widthFromCrateToNext;
	    }

	    const auto crateIdStr = std::string{line.substr(crateIdBegin + 1, crateIdEnd - (crateIdBegin + 1))};
	    const auto crateId = crateIdStr.front();

	    //! The values are being pushed in reverse order from what we're reading
	    _ret.pushToFrontOf(crateId, stackIndex);
	    ++stackIndex;
	}
};

template<size_t MaxNumStacks>
[[nodiscard]] auto
parseSupplyStackInitialState(const std::string_view& data) -> SupplyStack<MaxNumStacks>
{
    SupplyStack<MaxNumStacks> _ret;
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
	    pos = nextPos + 1;
	    parseLine<MaxNumStacks>(_ret, line);
	}

    return _ret;
}

[[nodiscard]] auto
parseRearrangeCommands(const std::string_view& data) -> std::vector<MoveCommand>
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

template<size_t MaxNumStacks>
[[nodiscard]] auto
parseInput(const std::string_view& data)
{
    constexpr auto endOfSupplyStackDelimiter = "\n\n";

    // Parse Supply stack initial state
    const auto endOfSupplyStackPos = data.find(endOfSupplyStackDelimiter);
    const auto supplyStackStr = data.substr(0, endOfSupplyStackPos);

    const auto moveCommandsStartPos = endOfSupplyStackPos + strlen(endOfSupplyStackDelimiter);
    const auto moveCommandsStr = data.substr(moveCommandsStartPos);

    struct
    {
	    const SupplyStack<MaxNumStacks> supplyStackInitialState;
	    const std::vector<MoveCommand> moveCommands;
    } _ret{// Force Linebreak
	   parseSupplyStackInitialState<MaxNumStacks>(supplyStackStr), parseRearrangeCommands(moveCommandsStr)};

    return _ret;
}

} // namespace

namespace Solutions {

template<size_t NumStacksInSupply>
auto
GetCratesAtTopOfStacksAfterMoveOperations(const std::string_view& input, bool& success) -> std::string
{
    std::string _ret;

    try
	{
	    const auto [supplyStackInitialState, moveCommands] = parseInput<NumStacksInSupply>(input);
	    auto supplyStack = supplyStackInitialState;

	    std::ranges::for_each(
	      moveCommands,
	      [&supplyStack](const MoveCommand& command)
	      {
		  // What is up with clang-format and lambdas?
		  for (int numCratesMoved = 0; numCratesMoved < command.getNumCrates(); ++numCratesMoved)
		      {
			  if (!supplyStack.moveN(command.fromPos(), command.toPos(), 1))
			      {
				  auto sstrm = std::stringstream();
				  sstrm << command;
				  throw std::out_of_range("Failed to execute move command: " + sstrm.str());
			  }
		      }
	      });

	    _ret = supplyStack.getTops();

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

template<size_t NumStacksInSupply>
auto
GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane(const std::string_view& input, bool& success) -> std::string
{
    std::string _ret;

    try
	{
	    const auto [supplyStackInitialState, moveCommands] = parseInput<NumStacksInSupply>(input);
	    auto supplyStack = supplyStackInitialState;

	    std::ranges::for_each(
	      moveCommands,
	      [&supplyStack](const MoveCommand& command)
	      {
		  if (!supplyStack.moveN(command.fromPos(), command.toPos(), command.getNumCrates()))
		      {
			  auto sstrm = std::stringstream();
			  sstrm << command;
			  throw std::out_of_range("Failed to execute move command: " + sstrm.str());
		  }
	      });

	    _ret = supplyStack.getTops();

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