#include "SupplyStack.hpp"

#include "Definitions.hpp"

// Std
#include <algorithm>
#include <iostream>
#include <ostream>
#include <ranges>

namespace Solutions::SupplyStacks {

template<size_t MaxNumStacks>
[[nodiscard]] auto
SupplyStack<MaxNumStacks>::getTops() const -> std::string
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

template<size_t MaxNumStacks>
[[nodiscard]] auto
SupplyStack<MaxNumStacks>::getTop(size_t index) const -> char
{
    if (MaxNumStacks <= index)
	{
	    std::cout << "getTop() : Invalid index: " << index << std::endl;
	    return 0;
    }

    const MyStack_t _stack = m_stacks.at(index);

    if (_stack.empty())
	{
	    std::cout << "Stack at index " << index << " is empty!" << std::endl;
	    return 0;
    }

    return _stack.front();
}

template<size_t MaxNumStacks>
auto
SupplyStack<MaxNumStacks>::popFromFrontOf(size_t index) -> char
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

template<size_t MaxNumStacks>
void
SupplyStack<MaxNumStacks>::pushToBackOf(char crateId, size_t index)
{
    if (MaxNumStacks <= index) [[unlikely]]
	{
	    std::cout << "pushToBackOf() : Invalid index: " << index << std::endl;
	    return;
    }
    MyStack_t& _stack = m_stacks.at(index);
    _stack.emplace_back(crateId);
}

template<size_t MaxNumStacks>
void
SupplyStack<MaxNumStacks>::pushToFrontOf(char crateId, size_t index)
{
    if (MaxNumStacks <= index) [[unlikely]]
	{
	    std::cout << "pushToFrontOf() : Invalid index: " << index << std::endl;
	    return;
    }
    MyStack_t& _stack = m_stacks.at(index);
    _stack.emplace_front(crateId);
}

template<size_t MaxNumStacks>
template<size_t OtherSize>
auto
SupplyStack<MaxNumStacks>::takeNFrom(SupplyStack<OtherSize>& other, size_t fromIndex, size_t toIndex,
				     long numItemsToTake) -> bool
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

template<size_t MaxNumStacks>
void
parseLine(Solutions::SupplyStacks::SupplyStack<MaxNumStacks>& _ret, const std::string_view& line)
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
parseSupplyStackInitialState(const std::string_view& data) -> Solutions::SupplyStacks::SupplyStack<MaxNumStacks>
{
    Solutions::SupplyStacks::SupplyStack<MaxNumStacks> _ret;
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

template struct SupplyStack<SupplyStacks::numStacksInDataSet>;
template struct SupplyStack<SupplyStacks::numStacksInTestDataSet>;

template auto parseSupplyStackInitialState<SupplyStacks::numStacksInTestDataSet>(const std::string_view& data)
  -> Solutions::SupplyStacks::SupplyStack<SupplyStacks::numStacksInTestDataSet>;

template auto parseSupplyStackInitialState<SupplyStacks::numStacksInDataSet>(const std::string_view& data)
  -> Solutions::SupplyStacks::SupplyStack<SupplyStacks::numStacksInDataSet>;
} // namespace Solutions::SupplyStacks