#include "Round.hpp"

// Std
#include <algorithm>
#include <iterator>
#include <ranges>
// Internal

namespace Solutions::RockPaperScissors {

void
Round::updateOutcome()
{
    using enum Outcome;

    const auto difference = static_cast<int32_t>(m_playerShape) - static_cast<int32_t>(m_opponentShape);
    switch (difference)
	{
	    case 0:
		{
		    m_outcome = Draw;
		    return;
		}
	    case -1:
	    case 2:
		{
		    m_outcome = Loss;
		    return;
		}
	    case 1:
	    case -2:
		{
		    m_outcome = Win;
		    return;
		}
	}
}

void
Round::updatePlayerhand()
{
    const auto identifier = roundHash(m_opponentShape, m_outcome);

    switch (identifier)
	{
	    case roundHash(Shape::Rock, Outcome::Loss):
	    case roundHash(Shape::Paper, Outcome::Win):
	    case roundHash(Shape::Scissors, Outcome::Draw):
		{
		    m_playerShape = Shape::Scissors;
		    return;
		}
	    case roundHash(Shape::Rock, Outcome::Draw):
	    case roundHash(Shape::Paper, Outcome::Loss):
	    case roundHash(Shape::Scissors, Outcome::Win):
		{
		    m_playerShape = Shape::Rock;
		    return;
		}
	    case roundHash(Shape::Rock, Outcome::Win):
	    case roundHash(Shape::Paper, Outcome::Draw):
	    case roundHash(Shape::Scissors, Outcome::Loss):
		{
		    m_playerShape = Shape::Paper;
		    return;
		}
	}
}

template<>
[[nodiscard]] auto
stringToRounds<UnknownOutcome>(std::string_view input) -> std::vector<Round>
{
    constexpr auto delimiter = '\n';
    const auto numLines = std::ranges::count(input, delimiter) + 1;
    std::vector<Round> _ret;
    _ret.reserve(numLines);

    auto lineToRound = [&](const auto line)
    {
	const auto opponentShape = charToShape(line.front());
	// drop_view ?
	const auto opponentPart = std::ranges::subrange(std::next(line.begin(), 2), line.end());
	const auto playerShape = charToShape(opponentPart.front());

	_ret.emplace_back(playerShape, opponentShape).updateOutcome();
    };

    std::ranges::for_each(std::views::split(input, delimiter), lineToRound);

    return _ret;
}

template<>
[[nodiscard]] auto
stringToRounds<UnknownPlayerShape>(std::string_view input) -> std::vector<Round>
{
    constexpr auto delimiter = '\n';
    const auto numLines = std::ranges::count(input, delimiter) + 1;

    std::vector<Round> _ret;
    _ret.reserve(numLines);
    size_t pos = 0;

    while (pos < input.size())
	{
	    const auto nextPos = input.find(delimiter, pos);
	    const auto roundStr = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    const auto opponentShape = charToShape(roundStr.front());
	    const auto outcome = charToOutcome(roundStr.back());

	    auto& round = _ret.emplace_back(opponentShape, outcome);
	    round.updatePlayerhand();
	}

    return _ret;
}

} // namespace Solutions::RockPaperScissors