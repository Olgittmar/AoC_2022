#include "RockPaperScissors.hpp"

#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace {

// Enums and structs
// ---------------------------------------------------------------------------------------------------------
enum class Shape : int32_t
{
    Rock = 1,
    Paper = 2,
    Scissors = 3,
    Unknown
};

enum class Outcome : uint32_t
{
    Loss = 0,
    Draw = 3,
    Win = 6,
    Unknown
};

struct Scenario;
struct UnknownOutcome;
struct UnknownPlayerShape;

// Converters from input data to appropriate struct
// ---------------------------------------------------------------------------------------------------------
auto
charToShape(char shapeChar) -> Shape
{
    using enum Shape;
    switch (shapeChar) {
	    case 'A':
	    case 'X':
	    case 'a':
	    case 'x':
		return Rock;
	    case 'B':
	    case 'Y':
	    case 'b':
	    case 'y':
		return Paper;
	    case 'C':
	    case 'Z':
	    case 'c':
	    case 'z':
		return Scissors;
	    default:
		throw std::invalid_argument(std::string("No known conversion rule from ") + shapeChar + " to Shape.");
	}
};

auto
charToOutcome(char outcomeChar) -> Outcome
{
    using enum Outcome;
    switch (outcomeChar) {
	    case 'X':
	    case 'x':
		return Loss;
	    case 'Y':
	    case 'y':
		return Draw;
	    case 'Z':
	    case 'z':
		return Win;
	    default:
		throw std::invalid_argument(std::string("No known conversion rule from ") + outcomeChar +
					    " to Outcome.");
	}
};

// Class representing the variables of a single round
// ---------------------------------------------------------------------------------------------------------
class Round
{
    public:

	explicit Round(Shape opponentShape, Outcome outcome) // NOLINT(bugprone-easily-swappable-parameters)
	  : m_opponentShape(opponentShape), m_outcome(outcome)
	{
	    updatePlayerhand();
	}

	explicit Round(Shape playerShape, Shape opponentShape) // NOLINT(bugprone-easily-swappable-parameters)
	  : m_playerShape(playerShape), m_opponentShape(opponentShape)
	{
	    updateOutcome();
	}

	[[nodiscard]] auto
	getOutcome() const -> Outcome
	{
	    return m_outcome;
	}

	[[nodiscard]] auto
	getScore() const -> uint32_t
	{
	    return uint32_t(m_outcome) + uint32_t(m_playerShape);
	}

	void
	setPlayerShape(Shape playerShape)
	{
	    m_playerShape = playerShape;
	}

	void
	setOpponentShape(Shape opponentShape)
	{
	    m_opponentShape = opponentShape;
	}

	void
	setOutcome(Outcome outcome)
	{
	    m_outcome = outcome;
	}

    private:

	void
	updateOutcome()
	{
	    using enum Outcome;

	    const auto difference = int32_t(m_playerShape) - int32_t(m_opponentShape);

	    if (difference == 0) {
		    m_outcome = Draw;
		    return;
		}

	    if (difference == -1 || difference == 2) {
		    m_outcome = Loss;
		    return;
		}

	    if (difference == 1 || difference == -2) {
		    m_outcome = Win;
		    return;
		}
	}

	void
	updatePlayerhand()
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
		}
	}

	Shape m_playerShape = Shape::Unknown;
	Shape m_opponentShape = Shape::Unknown;
	Outcome m_outcome = Outcome::Unknown;
};

// Specialized input parsers
// ---------------------------------------------------------------------------------------------------------
template<class Scenario> [[nodiscard]] auto parseInput(const std::string_view& input) -> std::vector<Round>;

template<>
[[nodiscard]] auto
parseInput<UnknownOutcome>(const std::string_view& input) -> std::vector<Round>
{
    constexpr auto delimiter = '\n';
    std::vector<Round> _ret;
    // _ret.reserve(input.count(delimiter));
    size_t pos = 0;

    while (pos < input.size()) {
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
parseInput<UnknownPlayerShape>(const std::string_view& input) -> std::vector<Round>
{
    constexpr auto delimiter = '\n';
    std::vector<Round> _ret{};
    // _ret.reserve(input.count(delimiter));
    size_t pos = 0;

    while (pos < input.size()) {
	    const auto nextPos = input.find(delimiter, pos);
	    const auto roundStr = input.substr(pos, nextPos - pos);
	    pos = nextPos + size_t(nextPos != std::string_view::npos);

	    const auto opponentShape = charToShape(roundStr.front());
	    const auto outcome = charToOutcome(roundStr.back());

	    _ret.emplace_back(opponentShape, outcome);
	}

    return _ret;
}

} // namespace

namespace Solutions {

auto
GetScoreOfStrategyGuide(const std::string_view& input, bool& success) -> uint32_t
{
    uint32_t totalScore = 0;
    try {
	    const auto rounds = parseInput<UnknownOutcome>(input);

	    for (const auto& round : rounds) {
		    totalScore += round.getScore();
		}

	    success = true;
    } catch (const std::invalid_argument& errc) {
	    std::cout << errc.what() << std::endl;
    } catch (const std::exception& errc) {
	    std::cout << errc.what() << std::endl;
    }

    return totalScore;
}

auto
GetScoreOfDecryptedStrategyGuide(const std::string_view& input, bool& success) -> uint32_t
{
    uint32_t totalScore = 0;
    try {
	    const auto rounds = parseInput<UnknownPlayerShape>(input);

	    for (const auto& round : rounds) {
		    totalScore += round.getScore();
		}

	    success = true;
    } catch (const std::invalid_argument& errc) {
	    std::cout << errc.what() << std::endl;
    } catch (const std::exception& errc) {
	    std::cout << errc.what() << std::endl;
    }

    return totalScore;
}

} // namespace Solutions