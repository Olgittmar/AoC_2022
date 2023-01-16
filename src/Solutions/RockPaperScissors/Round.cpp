#include "Round.hpp"

// Std

// Internal

namespace Solutions::RockPaperScissors {

Round::Round(Shape opponentShape, Outcome outcome) // NOLINT(bugprone-easily-swappable-parameters)
  : m_opponentShape(opponentShape), m_outcome(outcome)
{
    updatePlayerhand();
}

Round::Round(Shape playerShape, Shape opponentShape) // NOLINT(bugprone-easily-swappable-parameters)
  : m_playerShape(playerShape), m_opponentShape(opponentShape)
{
    updateOutcome();
}

void
Round::updateOutcome()
{
    using enum Outcome;

    const auto difference = int32_t(m_playerShape) - int32_t(m_opponentShape);

    if (difference == 0)
	{
	    m_outcome = Draw;
	    return;
    }

    if (difference == -1 || difference == 2)
	{
	    m_outcome = Loss;
	    return;
    }

    if (difference == 1 || difference == -2)
	{
	    m_outcome = Win;
	    return;
    }
}

void
Round::updatePlayerhand()
{
    // How to do this nicer? Unique sum?
    if ((m_opponentShape == Shape::Rock && m_outcome == Outcome::Loss) ||
	(m_opponentShape == Shape::Paper && m_outcome == Outcome::Win) ||
	(m_opponentShape == Shape::Scissors && m_outcome == Outcome::Draw))
	{
	    // Sum 1, 8, 6
	    m_playerShape = Shape::Scissors;
	    return;
    }

    if ((m_opponentShape == Shape::Rock && m_outcome == Outcome::Draw) ||
	(m_opponentShape == Shape::Paper && m_outcome == Outcome::Loss) ||
	(m_opponentShape == Shape::Scissors && m_outcome == Outcome::Win))
	{
	    // Sum 4, 2, 9
	    m_playerShape = Shape::Rock;
	    return;
    }

    if ((m_opponentShape == Shape::Rock && m_outcome == Outcome::Win) ||
	(m_opponentShape == Shape::Paper && m_outcome == Outcome::Draw) ||
	(m_opponentShape == Shape::Scissors && m_outcome == Outcome::Loss))
	{
	    // Sum 7, 5, 3
	    m_playerShape = Shape::Paper;
	    return;
    }
}

template<>
[[nodiscard]] auto
stringToRounds<UnknownOutcome>(const std::string_view& input) -> std::vector<Round>
{
    constexpr auto delimiter = '\n';
    const auto numLines = std::count(input.cbegin(), input.cend(), delimiter) + 1;
    std::vector<Round> _ret;
    _ret.reserve(numLines);
    size_t pos = 0;

    while (pos < input.size())
	{
	    const auto nextPos = input.find(delimiter, pos);
	    const auto roundStr = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    const auto opponentShape = charToShape(roundStr.front());
	    const auto playerShape = charToShape(roundStr.back());

	    _ret.emplace_back(playerShape, opponentShape);
	}

    return _ret;
}

template<>
[[nodiscard]] auto
stringToRounds<UnknownPlayerShape>(const std::string_view& input) -> std::vector<Round>
{
    constexpr auto delimiter = '\n';
    const auto numLines = std::count(input.cbegin(), input.cend(), delimiter) + 1;
    std::vector<Round> _ret{};
    _ret.reserve(numLines);
    size_t pos = 0;

    while (pos < input.size())
	{
	    const auto nextPos = input.find(delimiter, pos);
	    const auto roundStr = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    const auto opponentShape = charToShape(roundStr.front());
	    const auto outcome = charToOutcome(roundStr.back());

	    _ret.emplace_back(opponentShape, outcome);
	}

    return _ret;
}

} // namespace Solutions::RockPaperScissors