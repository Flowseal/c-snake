#ifndef SNAKEGAME_INTERFACE_H
#define SNAKEGAME_INTERFACE_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "../GameController/GameController.h"
#include "../Utils/Utils.h"

#define TILE_SIZE 32

class GameInterface {
private:
	int mAreaSize { 0 };

public:
	sf::RenderWindow window;
	
	void drawTiles( );
	void drawSnake( Snake snake );
	void drawApple( Coord coord );
	void keysProcessing( GameController& gameController );

	GameInterface( int areaSize )
	{
		mAreaSize = areaSize;

		sf::ContextSettings contextSettings;
		contextSettings.antialiasingLevel = 4;
		window.create(sf::VideoMode( TILE_SIZE * areaSize, TILE_SIZE * areaSize ), "Snake game", sf::Style::Default, contextSettings );
	}
};

#endif