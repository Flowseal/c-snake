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
	const int fps = 100;
	srand( (unsigned int)time( NULL ) );

	FpsLock fpsLock( fps );
	GameInterface gameInterface( areaSize );
	GameController gameController( areaSize );

	gameInterface.createResources( );

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

			gameInterface.renderFrame( gameController );
			gameInterface.updateAnimationCycle( 10.f / fps );
		}
		else if ( gameController.getPlayerState( ) == PlayerState::RESET )
		{
			gameController.reset( );
		}
		else if ( gameController.getPlayerState( ) == PlayerState::WIN )
		{
			gameInterface.renderFrame( gameController );
			gameInterface.renderWinScreen( );
		}

		gameInterface.window.display( );
		fpsLock.waitForNextFrame( );
	}

	return 0;
}