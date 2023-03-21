#include "DataBroker/DataBroker.hpp"
#include "Definitions.hpp"
#include "SelectSolution/SelectSolution.hpp"

#include <RunSolution.hpp>
#include <Utils.hpp>
#include <benchmark/benchmark.h>
#include <tuple>

template<class... Args>
void
BM_Solution(::benchmark::State& state, Args&&... args)
{
    const auto args_tuple = std::make_tuple(std::move(args)...);
    const auto solutionId = static_cast<utils::SolutionId>(std::get<0>(args_tuple));
    const auto solutionDataId = utils::SelectSolutionData(solutionId);
    const auto data = utils::DataBroker::getSolutionData(solutionDataId);
    bool success = false;

    for (auto unused : state)
	{
	    benchmark::DoNotOptimize(Solutions::runSolution(solutionId, data, success));
	}
}

// The testdata for each solution represents a smaller data sample, which could potentially be much easier to generate
// Using this BM as a basis for experiments on possibility to automatically generate some data, for each solution.
template<class... Args>
void
BM_SolutionTest(::benchmark::State& state, Args&&... args)
{
    const auto args_tuple = std::make_tuple(std::move(args)...);
    const auto solutionId = static_cast<utils::SolutionId>(std::get<0>(args_tuple));
    const auto solutionDataId = utils::SelectSolutionData(solutionId);
    const auto testData = utils::DataBroker::getSolutionTestData(solutionDataId, 0);
    bool success = false;

    for (auto unused : state)
	{
	    benchmark::DoNotOptimize(Solutions::runSolution(solutionId, testData, success));
	}
}

// Actual real solutions
BENCHMARK_CAPTURE(BM_Solution, TopThreeFattestElfCalories, utils::SolutionId::TopThreeFattestElfCalories); // NOLINT
BENCHMARK_CAPTURE(BM_Solution, FattestElfCalories, utils::SolutionId::FattestElfCalories);                 // NOLINT
BENCHMARK_CAPTURE(BM_Solution, CampCleanup, utils::SolutionId::CampCleanup);                               // NOLINT
BENCHMARK_CAPTURE(BM_Solution, PartialCampCleanup, utils::SolutionId::PartialCampCleanup);                 // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RockPaperScissors, utils::SolutionId::RockPaperScissors);                   // NOLINT
BENCHMARK_CAPTURE(BM_Solution, DecryptedRockPaperScissors, utils::SolutionId::DecryptedRockPaperScissors); // NOLINT
BENCHMARK_CAPTURE(BM_Solution, TuningTrouble, utils::SolutionId::TuningTrouble);                           // NOLINT
BENCHMARK_CAPTURE(BM_Solution, MessageTuningTrouble, utils::SolutionId::MessageTuningTrouble);             // NOLINT
BENCHMARK_CAPTURE(BM_Solution, NoSpace, utils::SolutionId::NoSpace);                                       // NOLINT
BENCHMARK_CAPTURE(BM_Solution, YesSpace, utils::SolutionId::YesSpace);                                     // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RearrangeSupplyStacks, utils::SolutionId::RearrangeSupplyStacks);           // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RearrangeSupplyStacksWithAdvancedCrane,                                     // NOLINT
		  utils::SolutionId::RearrangeSupplyStacksWithAdvancedCrane);                              // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RucksackReorganization, utils::SolutionId::RucksackReorganization);         // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RucksackBadges, utils::SolutionId::RucksackBadges);                         // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RopeBridge, utils::SolutionId::RopeBridge);                                 // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RopeBridgeWithLongRopes, utils::SolutionId::RopeBridgeWithLongRopes);       // NOLINT
BENCHMARK_CAPTURE(BM_Solution, TreetopTreeHouse, utils::SolutionId::TreetopTreeHouse);                     // NOLINT
BENCHMARK_CAPTURE(BM_Solution, TreetopTreeHouseDist, utils::SolutionId::TreetopTreeHouseDist);             // NOLINT

// TODO: For now using testdata, investigate possibility of generating data for benchmarking.
// Since we don't care about the actual results here, we don't verify that the results are correct.
// (that should have already been done in tests)
BENCHMARK_CAPTURE(BM_SolutionTest, TopThreeFattestElfCalories, utils::SolutionId::TopThreeFattestElfCalories); // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, FattestElfCalories, utils::SolutionId::FattestElfCalories);                 // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, CampCleanup, utils::SolutionId::CampCleanup);                               // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, PartialCampCleanup, utils::SolutionId::PartialCampCleanup);                 // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, RockPaperScissors, utils::SolutionId::RockPaperScissors);                   // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, DecryptedRockPaperScissors, utils::SolutionId::DecryptedRockPaperScissors); // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, TuningTrouble, utils::SolutionId::TuningTrouble);                           // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, MessageTuningTrouble, utils::SolutionId::MessageTuningTrouble);             // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, NoSpace, utils::SolutionId::NoSpace);                                       // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, YesSpace, utils::SolutionId::YesSpace);                                     // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, RearrangeSupplyStacks, utils::SolutionId::RearrangeSupplyStacks);           // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, RearrangeSupplyStacksWithAdvancedCrane,                                     // NOLINT
		  utils::SolutionId::RearrangeSupplyStacksWithAdvancedCrane);                                  // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, RucksackReorganization, utils::SolutionId::RucksackReorganization);         // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, RucksackBadges, utils::SolutionId::RucksackBadges);                         // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, RopeBridge, utils::SolutionId::RopeBridge);                                 // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, RopeBridgeWithLongRopes, utils::SolutionId::RopeBridgeWithLongRopes);       // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, TreetopTreeHouse, utils::SolutionId::TreetopTreeHouse);                     // NOLINT
BENCHMARK_CAPTURE(BM_SolutionTest, TreetopTreeHouseDist, utils::SolutionId::TreetopTreeHouseDist);             // NOLINT

// BENCHMARK_MAIN(); // NOLINT