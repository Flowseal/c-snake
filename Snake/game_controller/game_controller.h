#ifndef SNAKEGAME_GAME_CONTROLLER_H
#define SNAKEGAME_GAME_CONTROLLER_H

#include <vector>
#include "../utils/utils.h"
#include "../snake/snake.h"

enum class e_player_state {
	ALIVE, LOSE, WIN
};

class c_game_controller {
private:
	int m_area_size { 20 };
	coord_t m_apple { };
	c_snake m_snake { };
	e_player_state m_player_state { e_player_state::ALIVE };

public:
	void update_states( );
	void reset( );

	c_snake& get_snake( ) { return m_snake; };

	coord_t next_apple_coords( );
	coord_t get_apple( ) { return m_apple; };

	e_player_state get_player_state( ) { return m_player_state; };
	void set_player_state( e_player_state new_player_state ) { m_player_state = new_player_state; };

	c_game_controller( int area_size )
	{
		this->m_area_size = area_size;
	}
};

#endif