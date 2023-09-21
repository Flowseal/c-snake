#ifndef SNAKEGAME_INTERFACE_H
#define SNAKEGAME_INTERFACE_H

#define NOMINMAX
#include <Windows.h>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../GameController/GameController.h"
#include "../Utils/Utils.h"

#define TILE_SIZE 64

enum class AnimationCycle {
	START = 0,
	IDLE = 1,
	END = 2
};

struct ResourceFile {
	char* bytes;
	int dwSize;
};

class GameInterface {
private:
	float mAnimationCycle { 0.f };
	int mAreaSize { 0 };

	sf::Texture mAppleTexture, mTropheyTexture;
	sf::Font mMontserratFont;

	ResourceFile resourceToBytes( LPCWSTR lpName, LPCWSTR lpType );

	void drawCircle( float radius, sf::Vector2f position, sf::Color color );
	void drawSprite( sf::Texture texture, Coord coord );

	void renderInfobar( int score, int highestScore );
	void renderTiles( );
	void renderSnake( Snake snake );

public:
	sf::RenderWindow window;
	
	void renderFrame( GameController gameController );
	void keysProcessing( GameController& gameController );
	void createResources( );

	AnimationCycle getAnimationCycleType( );
	float getAnimationCycle( );
	void updateAnimationCycle( float cycleAmount );

	GameInterface( int areaSize )
	{
		mAreaSize = areaSize;

		sf::ContextSettings contextSettings;
		contextSettings.antialiasingLevel = 4;
		window.create(sf::VideoMode( TILE_SIZE * (areaSize + 2), TILE_SIZE * areaSize ), "Snake game", sf::Style::Default, contextSettings );
	}
};

#endif