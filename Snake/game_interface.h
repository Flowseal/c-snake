#ifndef SNAKE_INTERFACE_H
#define SNAKE_INTERFACE_H

#include <Windows.h>
#include <vector>
#include "coord.h"

enum e_fg_color
{
	FG_BLACK = 0,
	FG_BLUE = 1,
	FG_GREEN = 2,
	FG_CYAN = 3,
	FG_RED = 4,
	FG_MAGENTA = 5,
	FG_BROWN = 6,
	FG_LIGHTGRAY = 7,
	FG_GRAY = 8,
	FG_LIGHTBLUE = 9,
	FG_LIGHTGREEN = 10,
	FG_LIGHTCYAN = 11,
	FG_LIGHTRED = 12,
	FG_LIGHTMAGENTA = 13,
	FG_YELLOW = 14,
	FG_WHITE = 15
};

class c_game_interface {
private:
	int m_area_size { 20 };
	COORD m_cursor_pos { 0, 0 };

public:
	void draw_walls( );
	void draw_snake( coord_t snake_head, std::vector<coord_t> snake_tail );
	void draw_apple( coord_t coord );
	void hide_cursor( );
	void clear_area( );

	c_game_interface( int area_size )
	{
		this->m_area_size = area_size;
	}
};

#endif