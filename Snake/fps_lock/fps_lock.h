#ifndef SNAKEGAME_FPS_LOCK_H
#define SNAKEGAME_FPS_LOCK_H

#include <chrono>
#include <thread>

class FpsLock {
private:
	std::chrono::system_clock::time_point mPreTime = std::chrono::system_clock::now( );
	std::chrono::system_clock::time_point mPostTime = std::chrono::system_clock::now( );

	int mFps { 1 };

public:
	FpsLock( int fps ) {
		mFps = fps;
	}

	void waitForNextFrame( );
};

#endif