#ifndef SNAKEGAME_FPS_LOCK_H
#define SNAKEGAME_FPS_LOCK_H

#include <chrono>
#include <thread>

class c_fps_lock {
private:
	std::chrono::system_clock::time_point a = std::chrono::system_clock::now( );
	std::chrono::system_clock::time_point b = std::chrono::system_clock::now( );

	int m_fps { 1 };

public:
	c_fps_lock( int fps ) {
		this->m_fps = fps;
	}

	void wait_next_frame( );
};

#endif