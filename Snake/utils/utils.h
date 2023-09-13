#ifndef SNAKEGAME__UTILS_H
#define SNAKEGAME__UTILS_H

struct Coord {
	int x, y;
};

bool operator==( const Coord& lhs, const Coord& rhs );

#endif