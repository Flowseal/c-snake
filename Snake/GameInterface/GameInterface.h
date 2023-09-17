#ifndef SNAKEGAME_INTERFACE_H
#define SNAKEGAME_INTERFACE_H

#include <Windows.h>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../GameController/GameController.h"
#include "../Utils/Utils.h"

#define TILE_SIZE 32

class GameInterface {
private:
	int mAreaSize { 0 };

public:
	sf::RenderWindow window { sf::VideoMode( ), "Snake game" };
	
	void drawTiles( );
	void drawSnake( Coord snakeHead, std::vector<Coord> snakeTail );
	void drawApple( Coord coord );
	void keysProcessing( GameController& gameController );

	GameInterface( int areaSize )
	{
		mAreaSize = areaSize;
		window.setSize( { TILE_SIZE * areaSize, TILE_SIZE * areaSize } );
	}
};

#endif