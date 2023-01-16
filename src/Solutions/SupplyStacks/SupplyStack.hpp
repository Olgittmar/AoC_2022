#ifndef SOLUTIONS_SUPPLYSTACKS_SUPPLYSTACK_HPP
#define SOLUTIONS_SUPPLYSTACKS_SUPPLYSTACK_HPP

// Std
#include "Definitions.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <list>
#include <ostream>
#include <ranges>

namespace Solutions::SupplyStacks {

template<size_t MaxNumStacks> class SupplyStack
{
    public:

	[[nodiscard]] auto getTops() const -> std::string;
	[[nodiscard]] auto getTop(size_t index) const -> char;
	auto popFromFrontOf(size_t index) -> char;
	void pushToBackOf(char crateId, size_t index);
	void pushToFrontOf(char crateId, size_t index);

	template<size_t OtherSize>
	auto takeNFrom(SupplyStack<OtherSize>& other, size_t fromIndex, size_t toIndex, long numItemsToTake) -> bool;

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
auto operator<<(std::ostream& out, const SupplyStack<MaxNumStacks>& supplyStack) -> std::ostream&;

template<size_t MaxNumStacks>
void parseLine(Solutions::SupplyStacks::SupplyStack<MaxNumStacks>& _ret, const std::string_view& line);

template<size_t MaxNumStacks>
[[nodiscard]] auto parseSupplyStackInitialState(const std::string_view& data)
  -> Solutions::SupplyStacks::SupplyStack<MaxNumStacks>;

} // namespace Solutions::SupplyStacks
#endif