#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME__H

#include <vector>
#include "../utils/utils.h"

enum class e_move_direction {
	UP, RIGHT, DOWN, LEFT
};

class c_snake {
private:
	e_move_direction m_move_direction { e_move_direction::RIGHT };

	coord_t m_snake_head { };
	std::vector<coord_t> m_snake_tail { };

public:
	void move_snake( );

	e_move_direction get_move_direction( ) { return m_move_direction; };
	void set_move_direction( e_move_direction move_direction ) { m_move_direction = move_direction; };

	coord_t get_snake_head( ) { return m_snake_head; };
	void set_snake_head( coord_t snake_head ) { m_snake_head = snake_head; };

	std::vector<coord_t>& get_snake_tail( ) { return m_snake_tail; };
	void set_snake_tail( std::vector<coord_t> snake_tail ) { m_snake_tail = snake_tail; };
};

#endif