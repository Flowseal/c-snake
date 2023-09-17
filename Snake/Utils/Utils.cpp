#include "Utils.h"

bool operator==( const Coord& lhs, const Coord& rhs )
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

Coord operator+( const Coord& lhs, const Coord& rhs )
{
	return Coord( lhs.x + rhs.x, lhs.y + rhs.y );
}

Coord operator-( const Coord& lhs, const Coord& rhs )
{
	return Coord( lhs.x - rhs.x, lhs.y - rhs.y );
}

Coord operator*( const Coord& lhs, const float rhs )
{
	return Coord( lhs.x * rhs, lhs.y * rhs );
}

Coord operator/( const Coord& lhs, const float rhs )
{
	return Coord( lhs.x / rhs, lhs.y / rhs );
}

Coord operator+( const Coord& lhs, const int rhs )
{
	return Coord( lhs.x + rhs, lhs.y + rhs );
}