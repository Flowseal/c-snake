#include "game_controller.h"

bool operator==( const coord_t& lhs, const coord_t& rhs )
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

void c_game_controller::move_snake( )
{
	// Move tail for snake's head
	for ( int i = snake_tail.size( ) - 1; i >= 0; i-- )
	{
		if ( i == 0 )
			snake_tail.at( i ) = snake_head;
		else
			snake_tail.at( i ) = snake_tail.at( i - 1 );
	}

	// Move snake's head
	switch ( m_move_direction )
	{
	case e_move_direction::UP:
		snake_head.y -= 1; break;
	case e_move_direction::RIGHT:
		snake_head.x += 1; break;
	case e_move_direction::DOWN:
		snake_head.y += 1; break;
	case e_move_direction::LEFT:
		snake_head.x -= 1; break;
	}

	last_snake_tail_coord = snake_tail.at( snake_tail.size( ) - 1 );
}

void c_game_controller::change_move_direction( e_move_direction new_move_direction )
{
	m_move_direction = new_move_direction;
}

coord_t c_game_controller::next_apple_cords( )
{
	std::vector<coord_t> area_coords;

	// Generate all area cell coords
	for ( int x = 0; x < m_area_size; x++ )
		for ( int y = 0; y < m_area_size; y++ )
			area_coords.push_back( { x, y } );

	// Remove intersections with snake
	std::vector<coord_t>::iterator snake_head_cell = std::find( area_coords.begin( ), area_coords.end( ), snake_head );
	area_coords.erase( snake_head_cell );

	for ( int i = 0; i < snake_tail.size( ); i++ )
	{
		std::vector<coord_t>::iterator snake_tail_cell = std::find( area_coords.begin( ), area_coords.end( ), snake_tail.at( i ) );
		if ( snake_tail_cell != area_coords.end() )
			area_coords.erase( snake_tail_cell );
	}

	// Return random free cell
	return area_coords[ std::rand( ) % area_coords.size( ) ];
}

void c_game_controller::update_states( )
{
	if ( snake_head == m_apple )
	{
		snake_tail.push_back( last_snake_tail_coord );

		if ( snake_tail.size( ) + 1 != m_area_size * m_area_size )
		{
			m_apple = next_apple_cords( );
		}
		else
		{
			m_player_state = e_player_state::WIN;
			return;
		}
	}

	if ( snake_head.x == -1 || snake_head.y == -1
		|| snake_head.x == m_area_size || snake_head.y == m_area_size )
	{
		m_player_state = e_player_state::LOSE;
		return;
	}

	for ( int i = 0; i < snake_tail.size( ); i++ )
	{
		if ( snake_head == snake_tail.at( i ) )
		{
			m_player_state = e_player_state::LOSE;
			return;
		}
	}
}

void c_game_controller::reset( )
{
	m_player_state = e_player_state::ALIVE;
	m_move_direction = e_move_direction::RIGHT;
	snake_head = { 4, 1 };
	snake_tail = { { 3, 1 }, { 2, 1 }, { 1, 1 } };
	m_apple = next_apple_cords( );
}