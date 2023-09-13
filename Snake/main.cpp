#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fps_lock/fps_lock.h"
#include "game_interface/game_interface.h"
#include "game_controller/game_controller.h"

void readKeys( GameController& gameController );

int main( )
{
	const int areaSize = 10;
	const int fps = 3;
	srand( (unsigned int)time( NULL ) );

	FpsLock fpsLock( fps );
	GameInterface gameInterface( areaSize );
	GameController gameController( areaSize );

	std::thread keyReadingThread( readKeys, std::ref( gameController ) );

	while ( true )
	{
		system( "cls" );
		gameInterface.drawWalls( );
		gameInterface.hideCursor( );
		gameController.reset( );

		while ( gameController.getPlayerState( ) == PlayerState::ALIVE )
		{
			fpsLock.waitForNextFrame( );

			gameController.getSnake( ).moveSnake( );
			gameController.updateStates( );

			gameInterface.clearArea( );
			gameInterface.drawApple( gameController.getApple( ) );
			gameInterface.drawSnake( gameController.getSnake( ).getSnakeHead( ), gameController.getSnake( ).getSnakeTail( ) );
		}

		system( "cls" );

		if ( gameController.getPlayerState( ) == PlayerState::LOSE )
			std::cout << "You have lost :(" << std::endl << "Press SPACE to try again";
		else
			std::cout << "YOU WON!" << std::endl << "Press SPACE to try again";

		while ( gameController.getPlayerState( ) != PlayerState::ALIVE )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
		}
	}
}

void readKeys( GameController& gameController )
{
	while ( true )
	{
		if ( gameController.getPlayerState( ) == PlayerState::ALIVE )
		{
			if ( GetKeyState( VK_UP ) & 0x8000 )
				gameController.getSnake( ).setMoveDirection( MoveDirection::UP );

			if ( GetKeyState( VK_RIGHT ) & 0x8000 )
				gameController.getSnake( ).setMoveDirection( MoveDirection::RIGHT );

			if ( GetKeyState( VK_DOWN ) & 0x8000 )
				gameController.getSnake( ).setMoveDirection( MoveDirection::DOWN );

			if ( GetKeyState( VK_LEFT ) & 0x8000 )
				gameController.getSnake( ).setMoveDirection( MoveDirection::LEFT );
		}
		else
		{
			if ( GetKeyState( VK_SPACE ) & 0x8000 )
				gameController.setPlayerState( PlayerState::ALIVE );
		}
	}
}