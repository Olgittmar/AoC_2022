#include "RockPaperScissors.hpp"

// Std
#include <algorithm>
#include <exception>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string_view>
#include <vector>

// Internal
#include "Round.hpp"

namespace Solutions {

auto
GetScoreOfStrategyGuide(std::string_view input, bool& success) -> int32_t
{
    const auto rounds = RockPaperScissors::stringToRounds<RockPaperScissors::UnknownOutcome>(input);
    const auto totalScore = std::accumulate(rounds.cbegin(), rounds.cend(), 0,
					    [](int32_t sum, const RockPaperScissors::Round& round) { return sum + round.getScore(); });

    success = true;

    return totalScore;
}

auto
GetScoreOfDecryptedStrategyGuide(std::string_view input, bool& success) -> uint32_t
{
    const auto rounds = RockPaperScissors::stringToRounds<RockPaperScissors::UnknownPlayerShape>(input);
    const auto totalScore = std::accumulate(rounds.cbegin(), rounds.cend(), 0U,
					    [](uint32_t sum, const RockPaperScissors::Round& round) { return sum + round.getScore(); });

    success = true;

    return totalScore;
}

} // namespace Solutions