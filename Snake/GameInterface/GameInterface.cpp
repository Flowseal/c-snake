#include <iostream>
#include <windows.h>
#include <string>

#include "GameInterface.h"

void GameInterface::printPositionedString( Coord coord, std::string string, FgColor fgColor )
{
	if ( fgColor != FG_LIGHTGRAY )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), fgColor );

	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), { short( coord.x ), short( coord.y ) } );
	std::cout << string;

	if ( fgColor != FG_LIGHTGRAY )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FG_LIGHTGRAY );
}

void GameInterface::drawWalls( )
{
	const std::string longWall( mAreaSize + 2, 'X' );

	// top wall
	printPositionedString( { 0, 0 }, longWall, FG_WHITE );

	// bottom wall
	printPositionedString( { 0, mAreaSize + 1 }, longWall, FG_WHITE );

	// left wall
	for ( int y = 0; y < mAreaSize + 2; y++ )
		printPositionedString( { 0, y }, "X", FG_WHITE );

	// right wall
	for ( int y = 0; y < mAreaSize + 2; y++ )
		printPositionedString( { mAreaSize + 1, y }, "X", FG_WHITE );
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

void GameInterface::hideCursor( )
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cursorInfo );
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cursorInfo );
}

void GameInterface::clearArea( )
{
	const std::string emptyLine( mAreaSize, ' ' );

	for ( int y = 1; y < mAreaSize + 1; y++ )
	{
		printPositionedString( { 1, y }, emptyLine );
	}
}
