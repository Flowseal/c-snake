#include "Snake.h"

void Snake::moveSnake( )
{
	// Move tail for snake's head
	for ( int i = mSnakeTail.size( ) - 1; i >= 0; i-- )
	{
		if ( i == 0 )
			mSnakeTail.at( i ) = mSnakeHead;
		else
			mSnakeTail.at( i ) = mSnakeTail.at( i - 1 );
	}

	// Move snake's head
	switch ( mMoveDirection )
	{
		case MoveDirection::UP:
			mSnakeHead.y -= 1; break;

		case MoveDirection::RIGHT:
			mSnakeHead.x += 1; break;

		case MoveDirection::DOWN:
			mSnakeHead.y += 1; break;

		case MoveDirection::LEFT:
			mSnakeHead.x -= 1; break;
	}
}

MoveDirection Snake::getMoveDirection( )
{
	return mMoveDirection; 
}

void Snake::setMoveDirection( MoveDirection moveDirection ) 
{ 
	mMoveDirection = moveDirection;
}

Coord Snake::getSnakeHead( ) 
{ 
	return mSnakeHead; 
}

void Snake::setSnakeHead( Coord snakeHead ) 
{ 
	mSnakeHead = snakeHead; 
}

std::vector<Coord>& Snake::getSnakeTail( ) 
{ 
	return mSnakeTail; 
}

void Snake::setSnakeTail( std::vector<Coord> snakeTail ) 
{
	mSnakeTail = snakeTail; 
}