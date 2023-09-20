#include <iostream>
#include <string>

#define NOMINMAX
#include <Windows.h>

#include "../resource.h"
#include "GameInterface.h"

sf::Color DARK_TILE_COLOR = sf::Color( 162, 209, 73, 255 );
sf::Color LIGHT_TILE_COLOR = sf::Color( 170, 215, 81, 255 );
sf::Color SNAKE_HEAD_COLOR = sf::Color( 83, 130, 255, 255 );
sf::Color SNAKE_FIRST_TAIL_COLOR = sf::Color( 75, 124, 246, 255 );
sf::Color SNAKE_LAST_TAIL_COLOR = sf::Color( 33, 78, 176, 255 );

sf::Color colorBlend( sf::Color firstCol, sf::Color secondCol, float percentage )
{
	int r = firstCol.r - abs( firstCol.r - secondCol.r ) * percentage;
	int g = firstCol.g - abs( firstCol.g - secondCol.g ) * percentage;
	int b = firstCol.b - abs( firstCol.b - secondCol.b ) * percentage;

	return sf::Color( r, g, b, 255 );
}

void GameInterface::createTextures( )
{
	HMODULE hModule = GetModuleHandle( NULL );

	HRSRC hResource = FindResource( hModule, MAKEINTRESOURCE( IDB_PNG2 ), L"PNG" );
	HGLOBAL hMemory = LoadResource( hModule, hResource );
	DWORD dwSize = SizeofResource( hModule, hResource );
	LPVOID lpAddress = LockResource( hMemory );

	char* bytes = new char[ dwSize ];
	memcpy( bytes, lpAddress, dwSize );

	mAppleTexture.loadFromMemory( bytes, dwSize );
	mAppleTexture.setSmooth( true );
}

void GameInterface::drawCircle( float radius, sf::Vector2f position, sf::Color color )
{
	sf::CircleShape circle( radius, 60 );
	circle.setPosition( position );
	circle.setFillColor( color );
	window.draw( circle );
}

void GameInterface::drawTiles( )
{
	const sf::Color tileColors[ 2 ] = { LIGHT_TILE_COLOR, DARK_TILE_COLOR };

	for ( int x = 0; x < mAreaSize; x++ )
		for ( int y = 0; y < mAreaSize; y++ )
		{
			sf::RectangleShape tile( sf::Vector2f( TILE_SIZE, TILE_SIZE ) );
			tile.setFillColor( tileColors[ (x + y) % 2 ] );
			tile.setPosition( sf::Vector2f( x * TILE_SIZE, y * TILE_SIZE ) );
			window.draw( tile );
		}
}

void GameInterface::drawSnake( Snake snake )
{
	// Push head to the tail's array since we will render all the snake in one loop
	std::vector<Coord> fullSnake = snake.getSnakeTail( );
	fullSnake.insert( fullSnake.begin( ), snake.getSnakeHead( ) );
	int fullSnakeSize = static_cast<int>(fullSnake.size( ));

	// Track previous data to connect with the next snake's part
	Coord prevSnakePart = fullSnake.at( fullSnake.size( ) - 1 );
	int prevDirection = 0;

	for ( int i = fullSnakeSize - 2; i >= 0; i-- )
	{
		Coord currSnakePart = fullSnake.at( i );

		Coord prevSnakePartScreen = prevSnakePart * TILE_SIZE + (TILE_SIZE / 2);
		Coord currSnakePartScreen = currSnakePart * TILE_SIZE + (TILE_SIZE / 2);

		// Adjust screen positions of first and last snake parts for animation
		if ( i == 0 )
		{
			currSnakePartScreen = prevSnakePartScreen + (currSnakePartScreen - prevSnakePartScreen) * getAnimationCycle( );
		}
		else if ( i == fullSnakeSize - 2 )
		{
			prevSnakePartScreen = prevSnakePartScreen + (currSnakePartScreen - prevSnakePartScreen) * getAnimationCycle( );
		}

		int convexWidth = abs( currSnakePart.x - prevSnakePart.x ) * (TILE_SIZE / 4);
		int convexHeight = abs( currSnakePart.y - prevSnakePart.y ) * (TILE_SIZE / 4);
		bool snakeChangedDirection = prevDirection != 0 && (convexWidth - convexHeight) != prevDirection;

		sf::ConvexShape snakePath;
		snakePath.setPointCount( 4 );
		snakePath.setPoint( 0, sf::Vector2f( prevSnakePartScreen.x - convexHeight, prevSnakePartScreen.y - convexWidth ) );
		snakePath.setPoint( 1, sf::Vector2f( prevSnakePartScreen.x + convexHeight, prevSnakePartScreen.y + convexWidth ) );
		snakePath.setPoint( 2, sf::Vector2f( currSnakePartScreen.x + convexHeight, currSnakePartScreen.y + convexWidth ) );
		snakePath.setPoint( 3, sf::Vector2f( currSnakePartScreen.x - convexHeight, currSnakePartScreen.y - convexWidth ) );
		snakePath.setFillColor( colorBlend( SNAKE_FIRST_TAIL_COLOR, SNAKE_LAST_TAIL_COLOR, (i + 2.f) / fullSnakeSize ) );
		window.draw( snakePath );

		// If snake have changed a direction, we need to smooth out the angle
		if ( snakeChangedDirection )
		{
			drawCircle(
				TILE_SIZE / 4,
				sf::Vector2f( prevSnakePartScreen ) - sf::Vector2f( TILE_SIZE / 4, TILE_SIZE / 4 ),
				colorBlend( SNAKE_FIRST_TAIL_COLOR, SNAKE_LAST_TAIL_COLOR, (i + 2.f) / fullSnakeSize )
			);
		}

		// Draw Snake's head
		if ( i == 0 )
		{
			drawCircle(
				TILE_SIZE / 2,
				sf::Vector2f( currSnakePartScreen ) - sf::Vector2f( TILE_SIZE / 2, TILE_SIZE / 2 ),
				SNAKE_HEAD_COLOR
			);
		}

		// Draw rounded Snake's end
		else if ( i == fullSnakeSize - 2 )
		{
			drawCircle(
				TILE_SIZE / 4,
				sf::Vector2f( prevSnakePartScreen ) - sf::Vector2f( TILE_SIZE / 4, TILE_SIZE / 4 ),
				SNAKE_LAST_TAIL_COLOR
			);
		}

		prevSnakePart = currSnakePart;
		prevDirection = convexWidth - convexHeight;
	}
}

void GameInterface::drawApple( Coord coord )
{
	float scaleX = float( TILE_SIZE ) / float( mAppleTexture.getSize( ).x );
	float scaleY = float( TILE_SIZE ) / float( mAppleTexture.getSize( ).y );

	sf::Sprite appleSprite;
	appleSprite.setTexture( mAppleTexture );
	appleSprite.setScale( sf::Vector2f( scaleX, scaleY ) );
	appleSprite.setPosition( sf::Vector2f( coord.x * TILE_SIZE, coord.y * TILE_SIZE ) );
	window.draw( appleSprite );
}

void GameInterface::keysProcessing( GameController& gameController )
{
	while ( true )
	{
		if ( gameController.getPlayerState( ) == PlayerState::ALIVE )
		{
			if ( GetKeyState( VK_UP ) & 0x8000 )
				gameController.getSnake( ).setNextMoveDirection( MoveDirection::UP );

			if ( GetKeyState( VK_RIGHT ) & 0x8000 )
				gameController.getSnake( ).setNextMoveDirection( MoveDirection::RIGHT );

			if ( GetKeyState( VK_DOWN ) & 0x8000 )
				gameController.getSnake( ).setNextMoveDirection( MoveDirection::DOWN );

			if ( GetKeyState( VK_LEFT ) & 0x8000 )
				gameController.getSnake( ).setNextMoveDirection( MoveDirection::LEFT );
		}
		else
		{
			if ( GetKeyState( VK_SPACE ) & 0x8000 )
				gameController.setPlayerState( PlayerState::ALIVE );
		}
	}
}

float GameInterface::getAnimationCycle( )
{
	return mAnimationCycle;
}

AnimationCycle GameInterface::getAnimationCycleType( )
{
	if ( mAnimationCycle == 0.f )
		return AnimationCycle::START;

	if ( mAnimationCycle == 1.f )
		return AnimationCycle::END;

	return AnimationCycle::IDLE;
}

void GameInterface::updateAnimationCycle( float cycleAmount )
{
	if ( mAnimationCycle == 1.f )
	{
		mAnimationCycle = 0.f;
		return;
	}

	mAnimationCycle += cycleAmount;

	if ( mAnimationCycle > 1.f )
		mAnimationCycle = 1.f;
}