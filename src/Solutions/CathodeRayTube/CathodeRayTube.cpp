#include "CathodeRayTube.hpp"

#include "CPU.hpp"
#include "Definitions.hpp"

#include <cstddef>

namespace Solutions {

template<size_t CycleOffset, size_t CycleStep, size_t CycleEnd>
auto
GetSumOfSignalStrengths(std::string_view input, bool& success) -> long
{
    using Cpu = CathodeRayTube::CPU<CycleOffset, CycleStep, CycleEnd>;

    constexpr auto lineDelim = '\n';
    size_t pos = 0;
    Cpu cpu;

    while (pos < input.size())
	{
	    const auto endPos = input.find(lineDelim, pos);
	    const auto line = input.substr(pos, endPos - pos);
	    const auto command = Cpu::makeCommand(line);
	    pos = endPos + 1;

	    cpu.executeCommand(command);
	}

    success = true;
    return cpu.GetTotalSum();
}

template auto GetSumOfSignalStrengths<CathodeRayTube::CycleOffset, CathodeRayTube::CycleStep, CathodeRayTube::CycleEnd>(std::string_view input, bool& success)
  -> long;

} // namespace Solutions