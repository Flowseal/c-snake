#include "Utils.h"

bool operator==( const Coord& lhs, const Coord& rhs )
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
