#ifndef SNAKE_GAME_CONTROLLER_H
#define SNAKE_GAME_CONTROLLER_H

#include <vector>
#include "coord.h"

enum class e_move_direction {
	UP, RIGHT, DOWN, LEFT
};

enum class e_player_state {
	ALIVE, LOSE, WIN
};

class c_game_controller {
private:
	int m_area_size { 20 };
	coord_t m_apple;

	e_player_state m_player_state { e_player_state::ALIVE };
	e_move_direction m_move_direction { e_move_direction::RIGHT };

	coord_t snake_head { 1, 1 };
	coord_t last_snake_tail_coord;
	std::vector<coord_t> snake_tail;
public:
	void move_snake( );
	void change_move_direction( e_move_direction move_direction );
	void update_states( );
	void reset( );

	coord_t next_apple_cords( );
	coord_t get_apple( ) { return m_apple; };
	coord_t get_snake_head( ) { return snake_head; };
	std::vector<coord_t> get_snake_tail( ) { return snake_tail; };

	e_player_state get_player_state( ) { return m_player_state; };
	void set_player_state( e_player_state new_player_state ) { m_player_state = new_player_state; };

	c_game_controller( int area_size )
	{
		this->m_area_size = area_size;
	}
};

#endif