#include <iostream>
#include <cstdlib>
#include <ctime>

#include "FpsLock/FpsLock.h"
#include "GameInterface/GameInterface.h"
#include "GameController/GameController.h"

int main( )
{
	const int areaSize = 10;
	const int fps = 4;
	srand( (unsigned int)time( NULL ) );

	FpsLock fpsLock( fps );
	GameInterface gameInterface( areaSize );
	GameController gameController( areaSize );

	std::thread keyProcessingThread( &GameInterface::keysProcessing, gameInterface, std::ref( gameController ) );

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