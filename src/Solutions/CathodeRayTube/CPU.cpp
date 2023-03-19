#include "CPU.hpp"

#include <cstddef>
#include <string>

namespace Solutions::CathodeRayTube {

template<size_t CycleOffset, size_t CycleStep, size_t CycleEnd>
auto
CPU<CycleOffset, CycleStep, CycleEnd>::makeCommand(std::string_view line) -> Command
{
    constexpr auto addStr = "addx ";
    constexpr auto noopStr = "noop";

    const auto isNoop = line.starts_with(noopStr);
    const auto isAdd = line.starts_with(addStr);

    const auto cycleCost = static_cast<size_t>(isNoop) + static_cast<size_t>(isAdd);

    long val = 0;
    if (isAdd)
	{
	    const auto valStart = line.find_first_not_of(addStr);
	    const std::string valStr{line.substr(valStart)};
	    val = std::stol(valStr);
    }

    return {.cycleCost = cycleCost, .value = val};
}

template<size_t CycleOffset, size_t CycleStep, size_t CycleEnd>
void
CPU<CycleOffset, CycleStep, CycleEnd>::executeCommand(Command command)
{
    for (size_t cycleCounter = 0; cycleCounter < command.cycleCost; ++cycleCounter)
	{
	    if (m_cycle > CycleOffset && (((m_cycle - CycleOffset) % CycleStep) == 0U))
		{
		    m_totalSum += long(m_cycle) * m_register;
	    }
	}
    m_register += command.value;
}

template class CPU<CycleOffset, CycleStep, CycleEnd>;

} // namespace Solutions::CathodeRayTube