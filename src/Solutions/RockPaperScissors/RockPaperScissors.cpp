#include "RockPaperScissors.hpp"

// Std
#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <vector>

// Internal
#include "Round.hpp"

namespace Solutions {

auto
GetScoreOfStrategyGuide(const std::string_view& input, bool& success) -> uint32_t
{
    uint32_t totalScore = 0;

    const auto rounds = RockPaperScissors::stringToRounds<RockPaperScissors::UnknownOutcome>(input);
    for (const auto& round : rounds)
	{
	    totalScore += round.getScore();
	}

    success = true;

    return totalScore;
}

auto
GetScoreOfDecryptedStrategyGuide(const std::string_view& input, bool& success) -> uint32_t
{
    uint32_t totalScore = 0;

    const auto rounds = RockPaperScissors::stringToRounds<RockPaperScissors::UnknownPlayerShape>(input);
    for (const auto& round : rounds)
	{
	    totalScore += round.getScore();
	}

    success = true;

    return totalScore;
}

} // namespace Solutions