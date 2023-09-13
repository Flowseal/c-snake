#ifndef SNAKEGAME_GAME_CONTROLLER_H
#define SNAKEGAME_GAME_CONTROLLER_H

#include <vector>
#include "../utils/utils.h"
#include "../snake/snake.h"

enum class PlayerState {
	ALIVE, LOSE, WIN
};

class GameController {
private:
	int mAreaSize { 20 };
	Coord mApple { };
	Snake mSnake { };
	PlayerState mPlayerState { PlayerState::ALIVE };

public:
	void updateStates( );
	void reset( );

	Snake& getSnake( );

	Coord generateNextAppleCoords( );
	Coord getApple( );

	PlayerState getPlayerState( );
	void setPlayerState( PlayerState playerState );

	GameController( int areaSize )
	{
		mAreaSize = areaSize;
	}
};

#endif