#include "snake.h"

void c_snake::move_snake( )
{
	// Move tail for snake's head
	for ( int i = m_snake_tail.size( ) - 1; i >= 0; i-- )
	{
		if ( i == 0 )
			m_snake_tail.at( i ) = m_snake_head;
		else
			m_snake_tail.at( i ) = m_snake_tail.at( i - 1 );
	}

	// Move snake's head
	switch ( m_move_direction )
	{
		case e_move_direction::UP:
			m_snake_head.y -= 1; break;

		case e_move_direction::RIGHT:
			m_snake_head.x += 1; break;

		case e_move_direction::DOWN:
			m_snake_head.y += 1; break;

		case e_move_direction::LEFT:
			m_snake_head.x -= 1; break;
	}
}