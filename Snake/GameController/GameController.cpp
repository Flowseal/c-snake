#include "GameController.h"

Coord GameController::generateNextAppleCoords( )
{
	std::vector<Coord> areaCoords;

	// Generate all area cell coords
	for ( int x = 0; x < mAreaSize; x++ )
		for ( int y = 0; y < mAreaSize; y++ )
			areaCoords.push_back( { x, y } );

	// Remove intersections with snake
	std::vector<Coord>::iterator snakeHead = std::find( areaCoords.begin( ), areaCoords.end( ), mSnake.getSnakeHead( ) );
	areaCoords.erase( snakeHead );

	for ( int i = 0; i < mSnake.getSnakeTail( ).size( ); i++ )
	{
		std::vector<Coord>::iterator snakeTail = std::find( areaCoords.begin( ), areaCoords.end( ), mSnake.getSnakeTail( ).at( i ) );
		if ( snakeTail != areaCoords.end( ) )
			areaCoords.erase( snakeTail );
	}

	// Return random free cell
	return areaCoords[ std::rand( ) % areaCoords.size( ) ];
}

void GameController::updateStates( )
{
	Coord snakeHead = mSnake.getSnakeHead( );
	std::vector<Coord>& snakeTail = mSnake.getSnakeTail( );

	// Ate apple
	if ( snakeHead == mApple )
	{
		snakeTail.push_back( snakeTail.at( snakeTail.size( ) - 1 ) );
		score += 1;

		if ( snakeTail.size( ) + 1 != mAreaSize * mAreaSize )
		{
			mApple = generateNextAppleCoords( );
		}
		else
		{
			mPlayerState = PlayerState::WIN;
			return;
		}
	}

	// Border hit
	if ( snakeHead.x < 0 || snakeHead.y < 0
		|| snakeHead.x >= mAreaSize || snakeHead.y >= mAreaSize )
	{
		mPlayerState = PlayerState::RESET;
		return;
	}

	// Self hit
	for ( int i = 0; i < snakeTail.size( ) - 1; i++ )
	{
		if ( snakeHead == snakeTail.at( i ) )
		{
			mPlayerState = PlayerState::RESET;
			return;
		}
	}
}

void GameController::reset( )
{
	highestScore = fmax( score, highestScore );
	score = 0;
	mPlayerState = PlayerState::ALIVE;

	mSnake = { };
	mSnake.setMoveDirection( MoveDirection::RIGHT );
	mSnake.setNextMoveDirection( MoveDirection::RIGHT );
	mSnake.setSnakeHead( Coord { 3, 1 } );
	mSnake.setSnakeTail( std::vector<Coord>{ { 2, 1 }, { 1, 1 }, { 0, 1 } } );

	mApple = generateNextAppleCoords( );
}

Snake& GameController::getSnake( )
{
	return mSnake;
}

Coord GameController::getApple( )
{
	return mApple;
}

PlayerState GameController::getPlayerState( )
{
	return mPlayerState;
}

void GameController::setPlayerState( PlayerState playerState )
{
	mPlayerState = playerState;
}