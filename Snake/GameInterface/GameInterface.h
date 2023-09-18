#ifndef SNAKEGAME_INTERFACE_H
#define SNAKEGAME_INTERFACE_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "../GameController/GameController.h"
#include "../Utils/Utils.h"

#define TILE_SIZE 32

enum class AnimationCycle {
	START = 0,
	IDLE = 1,
	END = 2
};

class GameInterface {
private:
	float mAnimationCycle { 0.f };
	int mAreaSize { 0 };

	void drawCircle( float radius, sf::Vector2f position, sf::Color color );

public:
	sf::RenderWindow window;
	
	void drawTiles( );
	void drawSnake( Snake snake );
	void drawApple( Coord coord );
	void keysProcessing( GameController& gameController );

	AnimationCycle getAnimationCycleType( );
	float getAnimationCycle( );
	void updateAnimationCycle( float cycleAmount );

	GameInterface( int areaSize )
	{
		mAreaSize = areaSize;

		sf::ContextSettings contextSettings;
		contextSettings.antialiasingLevel = 4;
		window.create(sf::VideoMode( TILE_SIZE * areaSize, TILE_SIZE * areaSize ), "Snake game", sf::Style::Default, contextSettings );
	}
};

#endif