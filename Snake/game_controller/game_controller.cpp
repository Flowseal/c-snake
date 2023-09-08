#include "game_controller.h"

coord_t c_game_controller::next_apple_coords( )
{
	std::vector<coord_t> area_coords;

	// Generate all area cell coords
	for ( int x = 0; x < m_area_size; x++ )
		for ( int y = 0; y < m_area_size; y++ )
			area_coords.push_back( { x, y } );

	// Remove intersections with snake
	std::vector<coord_t>::iterator snake_head_cell = std::find( area_coords.begin( ), area_coords.end( ), m_snake.get_snake_head( ) );
	area_coords.erase( snake_head_cell );

	for ( int i = 0; i < m_snake.get_snake_tail( ).size( ); i++ )
	{
		std::vector<coord_t>::iterator snake_tail_cell = std::find( area_coords.begin( ), area_coords.end( ), m_snake.get_snake_tail( ).at( i ) );
		if ( snake_tail_cell != area_coords.end( ) )
			area_coords.erase( snake_tail_cell );
	}

	// Return random free cell
	return area_coords[ std::rand( ) % area_coords.size( ) ];
}

void c_game_controller::update_states( )
{
	coord_t snake_head = m_snake.get_snake_head( );
	std::vector<coord_t>& snake_tail = m_snake.get_snake_tail( );

	// Ate apple
	if ( snake_head == m_apple )
	{
		snake_tail.push_back( snake_tail.at( snake_tail.size( ) - 1 ) );

		if ( snake_tail.size( ) + 1 != m_area_size * m_area_size )
		{
			m_apple = next_apple_coords( );
		}
		else
		{
			m_player_state = e_player_state::WIN;
			return;
		}
	}

	// Border hit
	if ( snake_head.x < 0 || snake_head.y < 0
		|| snake_head.x >= m_area_size || snake_head.y >= m_area_size )
	{
		m_player_state = e_player_state::LOSE;
		return;
	}

	// Self hit
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

	m_snake = { };
	m_snake.set_move_direction( e_move_direction::RIGHT );
	m_snake.set_snake_head( coord_t { 3, 1 } );
	m_snake.set_snake_tail( std::vector<coord_t>{ { 2, 1 }, { 1, 1 }} );

	m_apple = next_apple_coords( );
}