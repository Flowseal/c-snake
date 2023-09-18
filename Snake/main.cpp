#include <iostream>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "FpsLock/FpsLock.h"
#include "GameInterface/GameInterface.h"
#include "GameController/GameController.h"

int main( )
{
	const int areaSize = 15;
	const int fps = 100;
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
			if ( gameInterface.getAnimationCycleType( ) == AnimationCycle::START )
				gameController.getSnake( ).moveSnake( );

			if ( gameInterface.getAnimationCycleType( ) == AnimationCycle::END )
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
		gameInterface.updateAnimationCycle( 10.f / fps );
		fpsLock.waitForNextFrame( );
	}

	return 0;
}