#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME__H

#include <vector>
#include "../utils/utils.h"

enum class MoveDirection {
	UP, RIGHT, DOWN, LEFT
};

class Snake {
private:
	MoveDirection mMoveDirection { MoveDirection::RIGHT };

	Coord mSnakeHead { };
	std::vector<Coord> mSnakeTail { };

public:
	void moveSnake( );

	MoveDirection getMoveDirection( ) { return mMoveDirection; };
	void setMoveDirection( MoveDirection moveDirection ) { mMoveDirection = moveDirection; };

	Coord getSnakeHead( ) { return mSnakeHead; };
	void setSnakeHead( Coord snakeHead ) { mSnakeHead = snakeHead; };

	std::vector<Coord>& getSnakeTail( ) { return mSnakeTail; };
	void setSnakeTail( std::vector<Coord> snakeTail ) { mSnakeTail = snakeTail; };
};

#endif