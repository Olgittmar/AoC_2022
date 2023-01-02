#include "NoSpace.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>

namespace Solutions {

auto
GetTotalSizeOfDirectories(const std::string_view& input, bool& success) -> std::uint32_t
{
    uint32_t _ret = 0;

    try
	{
	    success = true;
    } catch (const std::exception& err)
	{
	    std::cout << err.what() << std::endl;
    } catch (...)
	{
	    std::cout << "Unhandled exception!" << std::endl;
	    // throw std::logic_error("Unhandled exception"); // Bad idea?
    }

    return _ret;
}

} // namespace Solutions