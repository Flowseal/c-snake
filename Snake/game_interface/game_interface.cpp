#include <iostream>
#include <windows.h>
#include <string>
#include "game_interface.h"

void setOutputColor( FgColor fgColor )
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), fgColor );
}

void resetOutputColor( )
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FG_LIGHTGRAY );
}

void GameInterface::drawWalls( )
{
	setOutputColor( FG_WHITE );
	std::string longWall( mAreaSize + 2, 'X' );

	// top wall
	mCursorPos.X = 0;
	mCursorPos.Y = 0;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mCursorPos );
	std::cout << longWall;

	// bottom wall
	mCursorPos.X = 0;
	mCursorPos.Y = mAreaSize + 1;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mCursorPos );
	std::cout << longWall;

	// left wall
	for ( int y = 0; y < mAreaSize + 2; y++ )
	{
		mCursorPos.X = 0;
		mCursorPos.Y = y;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mCursorPos );
		std::cout << 'X';
	}

	// right wall
	for ( int y = 0; y < mAreaSize + 2; y++ )
	{
		mCursorPos.X = mAreaSize + 2;
		mCursorPos.Y = y;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mCursorPos );
		std::cout << 'X';
	}

	resetOutputColor( );
}

void GameInterface::drawSnake( Coord snakeHead, std::vector<Coord> snakeTail )
{
	setOutputColor( FG_LIGHTCYAN );

	mCursorPos.X = snakeHead.x + 1;
	mCursorPos.Y = snakeHead.y + 1;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mCursorPos );
	std::cout << '*';

	setOutputColor( FG_CYAN );

	for ( int i = 0; i < snakeTail.size( ); i++ )
	{
		mCursorPos.X = snakeTail.at( i ).x + 1;
		mCursorPos.Y = snakeTail.at( i ).y + 1;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mCursorPos );
		std::cout << '*';
	}

	resetOutputColor( );
}

void GameInterface::drawApple( Coord coord )
{
	setOutputColor( FG_LIGHTGREEN );

	mCursorPos.X = coord.x + 1;
	mCursorPos.Y = coord.y + 1;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mCursorPos );
	std::cout << 'O';

	resetOutputColor( );
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
	std::string emptyLine( mAreaSize, ' ' );

	for ( int y = 1; y < mAreaSize + 1; y++ )
	{
		mCursorPos.X = 1;
		mCursorPos.Y = y;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mCursorPos );
		std::cout << emptyLine;
	}
}
