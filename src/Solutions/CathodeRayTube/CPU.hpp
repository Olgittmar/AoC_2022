#ifndef SOLUTIONS_CPU_CPU_HPP
#define SOLUTIONS_CPU_CPU_HPP

#include "Utils.hpp"

#include <cstddef>
#include <string_view>

namespace Solutions::CathodeRayTube {

template<size_t CycleOffset, size_t CycleStep, size_t CycleEnd> class CPU
{
    public:

	struct Command
	{
		size_t cycleCost;
		long value;
	};

	static auto makeCommand(std::string_view line) -> Command;

	void executeCommand(Command command);

	[[nodiscard]] auto
	GetTotalSum() const -> long
	{
	    return m_totalSum;
	}

    private:

	long m_totalSum = 0;
	size_t m_cycle = 1;
	long m_register = 1;
};

} // namespace Solutions::CathodeRayTube
#endif