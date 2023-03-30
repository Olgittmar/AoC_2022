
#include <RunSolution.hpp>
#include <Utils.hpp>
#include <benchmark/benchmark.h>

// The testdata for each solution represents a smaller data sample, which could potentially be much easier to generate
// Using this BM as a basis for experiments on possibility to automatically generate some data, for each solution.
template<class... Args>
void
BM_Solution(::benchmark::State& state, Args&&... args)
{
    const auto args_tuple = std::make_tuple(std::move(args)...);
    const auto solutionId = static_cast<utils::SolutionId>(std::get<0>(args_tuple));

    auto testDataGenerator = utils::DataBroker::getSolutionBenchmarkDataGenerator(solutionId);
    const auto testData = testDataGenerator();
    const auto solutionRunner = Solutions::getSolutionRunner<true>(solutionId);

    bool success = false;

    for (auto unused : state)
	{
	    benchmark::DoNotOptimize(solutionRunner(testData, success));
	}
}

// TODO: For now using testdata, investigate possibility of generating data for benchmarking.
// Since we don't care about the actual results here, we don't verify that the results are correct.
// (that should have already been done in tests)
BENCHMARK_CAPTURE(BM_Solution, TopThreeFattestElfCalories, utils::SolutionId::TopThreeFattestElfCalories);                         // NOLINT
BENCHMARK_CAPTURE(BM_Solution, FattestElfCalories, utils::SolutionId::FattestElfCalories);                                         // NOLINT
BENCHMARK_CAPTURE(BM_Solution, CampCleanup, utils::SolutionId::CampCleanup);                                                       // NOLINT
BENCHMARK_CAPTURE(BM_Solution, PartialCampCleanup, utils::SolutionId::PartialCampCleanup);                                         // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RockPaperScissors, utils::SolutionId::RockPaperScissors);                                           // NOLINT
BENCHMARK_CAPTURE(BM_Solution, DecryptedRockPaperScissors, utils::SolutionId::DecryptedRockPaperScissors);                         // NOLINT
BENCHMARK_CAPTURE(BM_Solution, TuningTrouble, utils::SolutionId::TuningTrouble);                                                   // NOLINT
BENCHMARK_CAPTURE(BM_Solution, MessageTuningTrouble, utils::SolutionId::MessageTuningTrouble);                                     // NOLINT
BENCHMARK_CAPTURE(BM_Solution, NoSpace, utils::SolutionId::NoSpace);                                                               // NOLINT
BENCHMARK_CAPTURE(BM_Solution, YesSpace, utils::SolutionId::YesSpace);                                                             // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RearrangeSupplyStacks, utils::SolutionId::RearrangeSupplyStacks);                                   // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RearrangeSupplyStacksWithAdvancedCrane, utils::SolutionId::RearrangeSupplyStacksWithAdvancedCrane); // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RucksackReorganization, utils::SolutionId::RucksackReorganization);                                 // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RucksackBadges, utils::SolutionId::RucksackBadges);                                                 // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RopeBridge, utils::SolutionId::RopeBridge);                                                         // NOLINT
BENCHMARK_CAPTURE(BM_Solution, RopeBridgeWithLongRopes, utils::SolutionId::RopeBridgeWithLongRopes);                               // NOLINT
BENCHMARK_CAPTURE(BM_Solution, TreetopTreeHouse, utils::SolutionId::TreetopTreeHouse);                                             // NOLINT
BENCHMARK_CAPTURE(BM_Solution, TreetopTreeHouseDist, utils::SolutionId::TreetopTreeHouseDist);                                     // NOLINT