#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME__H

#include <vector>
#include "../Utils/Utils.h"

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

	MoveDirection getMoveDirection( );
	void setMoveDirection( MoveDirection moveDirection );

	Coord getSnakeHead( );
	void setSnakeHead( Coord snakeHead );

	std::vector<Coord>& getSnakeTail( );
	void setSnakeTail( std::vector<Coord> snakeTail );
};

#endif