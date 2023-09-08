#include "utils.h"

bool operator==( const coord_t& lhs, const coord_t& rhs )
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
