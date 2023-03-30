#ifndef SOLUTIONS_ROCKPAPERSCISSORS_ROUND_HPP
#define SOLUTIONS_ROCKPAPERSCISSORS_ROUND_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace Solutions::RockPaperScissors {
// --------------------------------------------------------------------
// Shape
// --------------------------------------------------------------------
enum class Shape : int32_t
{
    Rock = 1,
    Paper = 2,
    Scissors = 3,
    Unknown
};

constexpr auto
charToShape(char shapeChar) -> Shape
{
    using enum Shape;
    switch (shapeChar)
	{
	    case 'A':
	    case 'X':
		{
		    return Rock;
		}
	    case 'B':
	    case 'Y':
		{
		    return Paper;
		}
	    case 'C':
	    case 'Z':
		{
		    return Scissors;
		}
	    default:
		{
		    throw std::invalid_argument(std::string("No known conversion rule from ") + shapeChar + " to Shape.");
		}
	}
};

// --------------------------------------------------------------------
// Outcome
// --------------------------------------------------------------------
enum class Outcome : int32_t
{
    Loss = 0,
    Draw = 3,
    Win = 6,
    Unknown
};

constexpr auto
charToOutcome(char outcomeChar) -> Outcome
{
    using enum Outcome;
    switch (outcomeChar)
	{
	    case 'X':
		{
		    return Loss;
		}
	    case 'Y':
		{
		    return Draw;
		}
	    case 'Z':
		{
		    return Win;
		}
	    default:
		{
		    throw std::invalid_argument(std::string("No known conversion rule from ") + outcomeChar + " to Outcome.");
		}
	}
};

// --------------------------------------------------------------------
// Round
// --------------------------------------------------------------------
class Round
{
    public:

	explicit constexpr Round(Shape playerShape, Shape opponentShape)
	  : m_playerShape(playerShape), m_opponentShape(opponentShape), m_outcome(Outcome::Unknown)
	{
	}

	explicit constexpr Round(Shape opponentShape, Outcome outcome)
	  : m_opponentShape(opponentShape), m_outcome(outcome), m_playerShape(Shape::Unknown)
	{
	}

	[[nodiscard]] inline auto
	getScore() const -> int32_t
	{
	    return static_cast<int32_t>(m_outcome) + static_cast<int32_t>(m_playerShape);
	}

	void updateOutcome();
	void updatePlayerhand();

    private:

	static constexpr int64_t intWidth = 32;

	static constexpr inline auto
	roundHash(int64_t lhs, int64_t rhs) -> int64_t
	{
	    return (lhs << intWidth) + rhs;
	}

	static constexpr inline auto
	roundHash(Shape lhs, Shape rhs) -> int64_t
	{
	    return roundHash(static_cast<int64_t>(lhs), static_cast<int64_t>(rhs));
	}

	static constexpr inline auto
	roundHash(Shape lhs, Outcome rhs) -> int64_t
	{
	    return roundHash(static_cast<int64_t>(lhs), static_cast<int64_t>(rhs));
	}

	Shape m_playerShape;
	Shape m_opponentShape;
	Outcome m_outcome;
};

// Parser scenarios
enum Scenario
{
    UnknownOutcome,
    UnknownPlayerShape
};

// Parsers
template<Scenario scenario> [[nodiscard]] auto stringToRounds(std::string_view input) -> std::vector<Round>;
template<> [[nodiscard]] auto stringToRounds<UnknownOutcome>(std::string_view input) -> std::vector<Round>;
template<> [[nodiscard]] auto stringToRounds<UnknownPlayerShape>(std::string_view input) -> std::vector<Round>;

} // namespace Solutions::RockPaperScissors
#endif