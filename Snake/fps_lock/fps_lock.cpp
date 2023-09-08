#include "fps_lock.h"

void c_fps_lock::wait_next_frame( )
{
	double frame_time = 1000 / m_fps;

	a = std::chrono::system_clock::now( );
	std::chrono::duration<double, std::milli> work_time = a - b;

	if ( work_time.count( ) < frame_time )
	{
		std::chrono::duration<double, std::milli> delta_ms( frame_time - work_time.count( ) );
		auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
		std::this_thread::sleep_for( std::chrono::milliseconds( delta_ms_duration.count( ) ) );
	}

	b = std::chrono::system_clock::now( );
}