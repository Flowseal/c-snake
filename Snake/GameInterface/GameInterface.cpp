#include <iostream>
#include <windows.h>
#include <string>

#include "GameInterface.h"

void GameInterface::drawTiles( )
{
	const sf::Color tileColors[ 2 ] = { sf::Color( 170, 215, 81, 255 ), sf::Color( 162, 209, 73, 255 ) };

	for ( int x = 0; x < mAreaSize; x++ )
		for ( int y = 0; y < mAreaSize; y++ )
		{
			sf::RectangleShape tile( sf::Vector2f( TILE_SIZE, TILE_SIZE ) );
			tile.setFillColor( tileColors[ (x + y) % 2 ] );
			tile.setPosition( x * TILE_SIZE, y * TILE_SIZE );
			window.draw( tile );
		}
}

void GameInterface::drawSnake( Coord snakeHead, std::vector<Coord> snakeTail )
{
	printPositionedString( { snakeHead.x + 1, snakeHead.y + 1 }, "*", FG_LIGHTCYAN );

	for ( int i = 0; i < snakeTail.size( ); i++ )
		printPositionedString( { snakeTail.at( i ).x + 1, snakeTail.at( i ).y + 1 }, "*", FG_CYAN );
}

void GameInterface::drawApple( Coord coord )
{
	printPositionedString( { coord.x + 1, coord.y + 1 }, "O", FG_LIGHTGREEN );
}

void GameInterface::keysProcessing( GameController& gameController )
{
	while ( true )
	{
		if ( gameController.getPlayerState( ) == PlayerState::ALIVE )
		{
			if ( GetKeyState( VK_UP ) & 0x8000 && gameController.getSnake( ).getMoveDirection( ) != MoveDirection::DOWN )
				gameController.getSnake( ).setMoveDirection( MoveDirection::UP );

			if ( GetKeyState( VK_RIGHT ) & 0x8000 && gameController.getSnake( ).getMoveDirection( ) != MoveDirection::LEFT )
				gameController.getSnake( ).setMoveDirection( MoveDirection::RIGHT );

			if ( GetKeyState( VK_DOWN ) & 0x8000 && gameController.getSnake( ).getMoveDirection( ) != MoveDirection::UP )
				gameController.getSnake( ).setMoveDirection( MoveDirection::DOWN );

			if ( GetKeyState( VK_LEFT ) & 0x8000 && gameController.getSnake( ).getMoveDirection( ) != MoveDirection::RIGHT )
				gameController.getSnake( ).setMoveDirection( MoveDirection::LEFT );
		}
		else
		{
			if ( GetKeyState( VK_SPACE ) & 0x8000 )
				gameController.setPlayerState( PlayerState::ALIVE );
		}
	}
}