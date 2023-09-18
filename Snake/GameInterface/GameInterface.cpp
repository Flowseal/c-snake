#include <iostream>
#include <string>

#define NOMINMAX
#include <Windows.h>
#include "GameInterface.h"

sf::Color DARK_TILE_COLOR = sf::Color( 162, 209, 73, 255 );
sf::Color LIGHT_TILE_COLOR = sf::Color( 170, 215, 81, 255 );
sf::Color SNAKE_HEAD_COLOR = sf::Color( 83, 130, 255, 255 );
sf::Color SNAKE_FIRST_TAIL_COLOR = sf::Color( 75, 124, 246, 255 );
sf::Color SNAKE_LAST_TAIL_COLOR = sf::Color( 33, 78, 176, 255 );

sf::Color colorBlend( sf::Color firstCol, sf::Color secondCol, float percentage )
{
	int r = firstCol.r - abs( firstCol.r - secondCol.r ) * percentage;
	int g = firstCol.g - abs( firstCol.g - secondCol.g ) * percentage;
	int b = firstCol.b - abs( firstCol.b - secondCol.b ) * percentage;

	return sf::Color( r, g, b, 255 );
}

void GameInterface::drawTiles( )
{
	const sf::Color tileColors[ 2 ] = { LIGHT_TILE_COLOR, DARK_TILE_COLOR };

	for ( int x = 0; x < mAreaSize; x++ )
		for ( int y = 0; y < mAreaSize; y++ )
		{
			sf::RectangleShape tile( sf::Vector2f( TILE_SIZE, TILE_SIZE ) );
			tile.setFillColor( tileColors[ (x + y) % 2 ] );
			tile.setPosition( sf::Vector2f( x * TILE_SIZE, y * TILE_SIZE ) );
			window.draw( tile );
		}
}

void GameInterface::drawSnake( Snake snake )
{
	// Push head to the tail's array to connect first tail part with the head
	std::vector<Coord> snakeTail = snake.getSnakeTail( );
	snakeTail.insert( snakeTail.begin( ), snake.getSnakeHead( ) );

	// Track previous data to connect with next tail's part
	Coord prevSnakeTail = snakeTail.at( snakeTail.size( ) - 1 );
	int prevDirection = 0;

	// Draw Snake's tail
	for ( int i = static_cast<int>(snakeTail.size( )) - 2; i >= 0; i-- )
	{
		Coord currSnakeTail = snakeTail.at( i );

		Coord prevSnakeTailCenter = prevSnakeTail * TILE_SIZE + (TILE_SIZE / 2);
		Coord currSnakeTailCenter = currSnakeTail * TILE_SIZE + (TILE_SIZE / 2);

		if ( i == 0 )
		{
			currSnakeTailCenter = prevSnakeTailCenter + (currSnakeTailCenter - prevSnakeTailCenter) * getAnimationCycle();
		}
		
		else if ( i == static_cast<int>(snakeTail.size( )) - 2 )
		{
			prevSnakeTailCenter = prevSnakeTailCenter + (currSnakeTailCenter - prevSnakeTailCenter) * getAnimationCycle( );

			//Draw rounded Snake's end
			sf::CircleShape snakeRoundedEnd( TILE_SIZE / 4, 30 );
			snakeRoundedEnd.setFillColor( SNAKE_LAST_TAIL_COLOR );
			snakeRoundedEnd.setPosition( sf::Vector2f( prevSnakeTailCenter.x - TILE_SIZE / 4, prevSnakeTailCenter.y - TILE_SIZE / 4 ) );
			window.draw( snakeRoundedEnd );
		}
		

		int widthDelta = abs( currSnakeTail.x - prevSnakeTail.x ) * (TILE_SIZE / 4);
		int heightDelta = abs( currSnakeTail.y - prevSnakeTail.y ) * (TILE_SIZE / 4);

		// If snake have changed a direction, we need to smooth out the angle
		if ( prevDirection != 0 && (widthDelta - heightDelta) != prevDirection )
		{
			sf::CircleShape edgeCircle( TILE_SIZE / 4, 30 );
			edgeCircle.setFillColor( colorBlend( SNAKE_FIRST_TAIL_COLOR, SNAKE_LAST_TAIL_COLOR, static_cast<float>(i + 2) / snakeTail.size( ) ) );
			edgeCircle.setPosition( sf::Vector2f( prevSnakeTailCenter.x - TILE_SIZE / 4, prevSnakeTailCenter.y - TILE_SIZE / 4 ) );
			window.draw( edgeCircle );
		}

		sf::ConvexShape snakePath;
		snakePath.setFillColor( colorBlend( SNAKE_FIRST_TAIL_COLOR, SNAKE_LAST_TAIL_COLOR, static_cast<float>(i + 2) / snakeTail.size( ) ) );
		snakePath.setPointCount( 4 );
		snakePath.setPoint( 0, sf::Vector2f( prevSnakeTailCenter.x - heightDelta, prevSnakeTailCenter.y - widthDelta ) );
		snakePath.setPoint( 1, sf::Vector2f( prevSnakeTailCenter.x + heightDelta, prevSnakeTailCenter.y + widthDelta ) );
		snakePath.setPoint( 2, sf::Vector2f( currSnakeTailCenter.x + heightDelta, currSnakeTailCenter.y + widthDelta ) );
		snakePath.setPoint( 3, sf::Vector2f( currSnakeTailCenter.x - heightDelta, currSnakeTailCenter.y - widthDelta ) );
		window.draw( snakePath );

		// Draw Snake's head
		if ( i == 0 )
		{
			sf::CircleShape snakeHead( TILE_SIZE / 2, 60 );
			snakeHead.setFillColor( SNAKE_HEAD_COLOR );
			snakeHead.setPosition( sf::Vector2f( currSnakeTailCenter.x - TILE_SIZE / 2, currSnakeTailCenter.y - TILE_SIZE / 2 ) );
			window.draw( snakeHead );
		}

		prevSnakeTail = currSnakeTail;
		prevDirection = widthDelta - heightDelta;
	}
}

void GameInterface::drawApple( Coord coord )
{
	sf::CircleShape apple( TILE_SIZE / 2 );
	apple.setFillColor( sf::Color( 231, 71, 29, 255 ) );
	apple.setPosition( sf::Vector2f( coord.x * TILE_SIZE, coord.y * TILE_SIZE ) );
	window.draw( apple );
}

void GameInterface::keysProcessing( GameController& gameController )
{
	while ( true )
	{
		if ( gameController.getPlayerState( ) == PlayerState::ALIVE )
		{
			if ( GetKeyState( VK_UP ) & 0x8000 )
				gameController.getSnake( ).setNextMoveDirection( MoveDirection::UP );

			if ( GetKeyState( VK_RIGHT ) & 0x8000 )
				gameController.getSnake( ).setNextMoveDirection( MoveDirection::RIGHT );

			if ( GetKeyState( VK_DOWN ) & 0x8000 )
				gameController.getSnake( ).setNextMoveDirection( MoveDirection::DOWN );

			if ( GetKeyState( VK_LEFT ) & 0x8000 )
				gameController.getSnake( ).setNextMoveDirection( MoveDirection::LEFT );
		}
		else
		{
			if ( GetKeyState( VK_SPACE ) & 0x8000 )
				gameController.setPlayerState( PlayerState::ALIVE );
		}
	}
}

AnimationCycle GameInterface::getAnimationCycleType( )
{
	if ( mAnimationCycle == 0.f )
		return AnimationCycle::START;

	if ( mAnimationCycle == 1.f )
		return AnimationCycle::END;

	return AnimationCycle::IDLE;
}

float GameInterface::getAnimationCycle( )
{
	return mAnimationCycle;
}

void GameInterface::updateAnimationCycle( float cycleAmount )
{
	if ( mAnimationCycle == 1.f )
	{
		mAnimationCycle = 0.f;
		return;
	}

	mAnimationCycle += cycleAmount;

	if ( mAnimationCycle > 1.f )
		mAnimationCycle = 1.f;
}