

#include "SupplyStacks.hpp"

#include "Definitions.hpp"
#include "MoveCommand.hpp"
#include "SupplyStack.hpp"

// Std
#include <cstring>
#include <sstream>

namespace {

template<size_t MaxNumStacks>
[[nodiscard]] auto
parseInput(std::string_view data)
{
    constexpr auto endOfSupplyStackDelimiter = "\n\n";

    // Parse Supply stack initial state
    const auto endOfSupplyStackPos = data.find(endOfSupplyStackDelimiter);
    const auto supplyStackStr = data.substr(0, endOfSupplyStackPos);

    const auto moveCommandsStartPos = endOfSupplyStackPos + strlen(endOfSupplyStackDelimiter);
    const auto moveCommandsStr = data.substr(moveCommandsStartPos);

    struct
    {
	    Solutions::SupplyStacks::SupplyStack<MaxNumStacks> supplyStackInitialState;
	    std::vector<Solutions::SupplyStacks::MoveCommand> moveCommands;
    } _ret{// Force Linebreak
	   Solutions::SupplyStacks::parseSupplyStackInitialState<MaxNumStacks>(supplyStackStr),
	   Solutions::SupplyStacks::parseRearrangeCommands(moveCommandsStr)};

    return _ret;
}

} // namespace

namespace Solutions {

template<size_t NumStacksInSupply>
auto
GetCratesAtTopOfStacksAfterMoveOperations(std::string_view input, bool& success) -> std::string
{
    std::string _ret;

    const auto [supplyStackInitialState, moveCommands] = parseInput<NumStacksInSupply>(input);
    auto supplyStack = supplyStackInitialState;

    std::ranges::for_each(moveCommands,
			  [&supplyStack](const SupplyStacks::MoveCommand& command)
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

    return _ret;
}

template<size_t NumStacksInSupply>
auto
GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane(std::string_view input, bool& success) -> std::string
{
    std::string _ret;

    const auto [supplyStackInitialState, moveCommands] = parseInput<NumStacksInSupply>(input);
    auto supplyStack = supplyStackInitialState;

    std::ranges::for_each(moveCommands,
			  [&supplyStack](const SupplyStacks::MoveCommand& command)
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

    return _ret;
}

// Template instantiations
template auto GetCratesAtTopOfStacksAfterMoveOperations<SupplyStacks::numStacksInDataSet>(std::string_view input, bool& success) -> std::string;
template auto GetCratesAtTopOfStacksAfterMoveOperations<SupplyStacks::numStacksInTestDataSet>(std::string_view input, bool& success) -> std::string;

template auto GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<SupplyStacks::numStacksInTestDataSet>(std::string_view input, bool& success)
  -> std::string;

template auto GetCratesAtTopOfStacksAfterMoveOperationsWithAdvancedCrane<SupplyStacks::numStacksInDataSet>(std::string_view input, bool& success)
  -> std::string;

} // namespace Solutions