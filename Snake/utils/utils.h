#pragma once

struct coord_t {
	int x, y;
};

bool operator==( const coord_t& lhs, const coord_t& rhs );