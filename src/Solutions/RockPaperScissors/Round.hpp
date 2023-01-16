#ifndef SOLUTIONS_ROCKPAPERSCISSORS_ROUND_HPP
#define SOLUTIONS_ROCKPAPERSCISSORS_ROUND_HPP

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
	    case 'a':
	    case 'x':
		{
		    return Rock;
		}
	    case 'B':
	    case 'Y':
	    case 'b':
	    case 'y':
		{
		    return Paper;
		}
	    case 'C':
	    case 'Z':
	    case 'c':
	    case 'z':
		{
		    return Scissors;
		}
	    default:
		{
		    throw std::invalid_argument(std::string("No known conversion rule from ") + shapeChar +
						" to Shape.");
		}
	}
};

// --------------------------------------------------------------------
// Outcome
// --------------------------------------------------------------------
enum class Outcome : uint32_t
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
	    case 'x':
		{
		    return Loss;
		}
	    case 'Y':
	    case 'y':
		{
		    return Draw;
		}
	    case 'Z':
	    case 'z':
		{
		    return Win;
		}
	    default:
		{
		    throw std::invalid_argument(std::string("No known conversion rule from ") + outcomeChar +
						" to Outcome.");
		}
	}
};

// --------------------------------------------------------------------
// Round
// --------------------------------------------------------------------
class Round
{
    public:

	explicit Round(Shape opponentShape, Outcome outcome);
	explicit Round(Shape playerShape, Shape opponentShape);

	[[nodiscard]] inline auto
	getOutcome() const -> Outcome
	{
	    return m_outcome;
	}

	[[nodiscard]] inline auto
	getScore() const -> uint32_t
	{
	    return uint32_t(m_outcome) + uint32_t(m_playerShape);
	}

	inline void
	setPlayerShape(Shape playerShape)
	{
	    m_playerShape = playerShape;
	}

	inline void
	setOpponentShape(Shape opponentShape)
	{
	    m_opponentShape = opponentShape;
	}

	inline void
	setOutcome(Outcome outcome)
	{
	    m_outcome = outcome;
	}

    private:

	void updateOutcome();

	void updatePlayerhand();

	Shape m_playerShape = Shape::Unknown;
	Shape m_opponentShape = Shape::Unknown;
	Outcome m_outcome = Outcome::Unknown;
};

// Parsers
template<class Scenario> [[nodiscard]] auto stringToRounds(const std::string_view& input) -> std::vector<Round>;

// Parser scenarios
struct UnknownOutcome;
struct UnknownPlayerShape;

} // namespace Solutions::RockPaperScissors
#endif