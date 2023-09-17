#include <iostream>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

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

	std::thread keyProcessingThread( &GameInterface::keysProcessing, std::ref(gameInterface), std::ref( gameController ) );

	while ( gameInterface.window.isOpen( ) )
	{
		sf::Event event;
		while ( gameInterface.window.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed )
			{
				gameInterface.window.close( );
				return 0;
			}
		}

		gameInterface.window.clear( sf::Color::Black );

		if ( gameController.getPlayerState( ) == PlayerState::ALIVE )
		{
			gameController.getSnake( ).moveSnake( );
			gameController.updateStates( );

			gameInterface.drawTiles( );
			gameInterface.drawApple( gameController.getApple( ) );
			gameInterface.drawSnake( gameController.getSnake( ) );
		}
		else
		{
			gameController.reset( );
		}

		gameInterface.window.display( );
		fpsLock.waitForNextFrame( );
	}

	return 0;
}