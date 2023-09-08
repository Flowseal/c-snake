#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fps_lock/fps_lock.h"
#include "game_interface/game_interface.h"
#include "game_controller/game_controller.h"

void read_keys( c_game_controller& game_controller );

int main( )
{
	const int area_size = 10;
	const int frame_per_second = 3;
	srand( (unsigned int)time( NULL ) );

	c_fps_lock fps_lock( frame_per_second );
	c_game_interface game_interface( area_size );
	c_game_controller game_controller( area_size );

	std::thread key_reading( read_keys, std::ref( game_controller ) );

	while ( true )
	{
		system( "cls" );
		game_interface.draw_walls( );
		game_interface.hide_cursor( );
		game_controller.reset( );

		while ( game_controller.get_player_state( ) == e_player_state::ALIVE )
		{
			fps_lock.wait_next_frame( );

			game_controller.get_snake( ).move_snake( );
			game_controller.update_states( );

			game_interface.clear_area( );
			game_interface.draw_apple( game_controller.get_apple( ) );
			game_interface.draw_snake( game_controller.get_snake( ).get_snake_head( ), game_controller.get_snake( ).get_snake_tail( ) );
		}

		system( "cls" );

		if ( game_controller.get_player_state( ) == e_player_state::LOSE )
			std::cout << "You have lost :(" << std::endl << "Press SPACE to try again";
		else
			std::cout << "YOU WON!" << std::endl << "Press SPACE to try again";

		while ( game_controller.get_player_state( ) != e_player_state::ALIVE )
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
		}
	}
}

void read_keys( c_game_controller& game_controller )
{
	while ( true )
	{
		if ( game_controller.get_player_state( ) == e_player_state::ALIVE )
		{
			if ( GetKeyState( VK_UP ) & 0x8000 )
				game_controller.get_snake( ).set_move_direction( e_move_direction::UP );

			if ( GetKeyState( VK_RIGHT ) & 0x8000 )
				game_controller.get_snake( ).set_move_direction( e_move_direction::RIGHT );

			if ( GetKeyState( VK_DOWN ) & 0x8000 )
				game_controller.get_snake( ).set_move_direction( e_move_direction::DOWN );

			if ( GetKeyState( VK_LEFT ) & 0x8000 )
				game_controller.get_snake( ).set_move_direction( e_move_direction::LEFT );
		}
		else
		{
			if ( GetKeyState( VK_SPACE ) & 0x8000 )
				game_controller.set_player_state( e_player_state::ALIVE );
		}
	}
}