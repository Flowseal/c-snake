#ifndef SNAKEGAME_INTERFACE_H
#define SNAKEGAME_INTERFACE_H

#include <Windows.h>
#include <vector>
#include "../utils/utils.h"

enum FgColor
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

class GameInterface {
private:
	int mAreaSize { 20 };
	COORD mCursorPos { 0, 0 };

public:
	void drawWalls( );
	void drawSnake( Coord snakeHead, std::vector<Coord> snakeTail );
	void drawApple( Coord coord );
	void hideCursor( );
	void clearArea( );

	GameInterface( int areaSize )
	{
		mAreaSize = areaSize;
	}
};

#endif