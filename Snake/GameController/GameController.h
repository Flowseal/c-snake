#ifndef SNAKEGAME_GAME_CONTROLLER_H
#define SNAKEGAME_GAME_CONTROLLER_H

#include <vector>
#include "../Utils/Utils.h"
#include "../Snake/Snake.h"

enum class PlayerState {
	ALIVE, RESET, WIN
};

class GameController {
private:
	int mAreaSize { 0 };
	float mAnimationCycle { 0.f };
	Coord mApple { };
	Snake mSnake { };
	PlayerState mPlayerState { PlayerState::RESET };

public:
	int score { 0 };
	int highestScore { 0 };

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