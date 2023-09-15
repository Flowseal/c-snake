#include "FpsLock.h"

void FpsLock::waitForNextFrame( )
{
	const double frameTime = 1000 / mFps;

	mPreTime = std::chrono::system_clock::now( );
	std::chrono::duration<double, std::milli> workTime = mPreTime - mPostTime;

	if ( workTime.count( ) < frameTime )
	{
		std::chrono::duration<double, std::milli> msDelta( frameTime - workTime.count( ) );
		auto msDeltaDuration = std::chrono::duration_cast<std::chrono::milliseconds>(msDelta);
		std::this_thread::sleep_for( std::chrono::milliseconds( msDeltaDuration.count( ) ) );
	}

	mPostTime = std::chrono::system_clock::now( );
}