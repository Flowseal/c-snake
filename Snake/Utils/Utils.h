#ifndef SNAKEGAME__UTILS_H
#define SNAKEGAME__UTILS_H

#include <SFML/Graphics.hpp>

struct Coord {
	float x, y;

	operator sf::Vector2f( ) const { return sf::Vector2f(x, y); }

	Coord( float x_, float y_ )
	{
		x = x_;
		y = y_;
	}

	Coord( int x_, int y_ )
	{
		x = x_;
		y = y_;
	}

	Coord( )
	{
		x = 0;
		y = 0;
	}
};

bool operator==( const Coord& lhs, const Coord& rhs );
Coord operator+=( Coord& lhs, const Coord& rhs );
Coord operator+( const Coord& lhs, const Coord& rhs );
Coord operator-( const Coord& lhs, const Coord& rhs );
Coord operator*( const Coord& lhs, const float rhs );
Coord operator/( const Coord& lhs, const float rhs );
Coord operator+( const Coord& lhs, const int rhs );

#endif