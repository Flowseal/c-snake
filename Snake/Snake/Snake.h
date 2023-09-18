#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include <vector>
#include "../Utils/Utils.h"

enum class MoveDirection {
	UP, RIGHT, DOWN, LEFT
};

extern std::map <MoveDirection, MoveDirection> OPPOSITE_DIRECTIONS;

class Snake {
private:
	MoveDirection mMoveDirection { MoveDirection::RIGHT };
	MoveDirection mNextMoveDirection { MoveDirection::RIGHT };

	Coord mSnakeHead { };
	std::vector<Coord> mSnakeTail { };

public:
	void moveSnake( );

	MoveDirection getMoveDirection( );
	void setMoveDirection( MoveDirection moveDirection );

	MoveDirection getNextMoveDirection( );
	void setNextMoveDirection( MoveDirection moveDirection );

	Coord getSnakeHead( );
	void setSnakeHead( Coord snakeHead );

	std::vector<Coord>& getSnakeTail( );
	void setSnakeTail( std::vector<Coord> snakeTail );
};

#endif