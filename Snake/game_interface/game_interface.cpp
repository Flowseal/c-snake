#include <iostream>
#include <windows.h>
#include <string>
#include "game_interface.h"

void set_output_color( e_fg_color fg_color )
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), fg_color );
}

void reset_output_color( )
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FG_LIGHTGRAY );
}

void c_game_interface::draw_walls( )
{
	set_output_color( FG_WHITE );
	std::string long_wall( m_area_size + 2, 'X' );

	// top wall
	m_cursor_pos.X = 0;
	m_cursor_pos.Y = 0;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), m_cursor_pos );
	std::cout << long_wall;

	// bottom wall
	m_cursor_pos.X = 0;
	m_cursor_pos.Y = m_area_size + 1;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), m_cursor_pos );
	std::cout << long_wall;

	// left wall
	for ( int y = 0; y < m_area_size + 2; y++ )
	{
		m_cursor_pos.X = 0;
		m_cursor_pos.Y = y;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), m_cursor_pos );
		std::cout << 'X';
	}

	// right wall
	for ( int y = 0; y < m_area_size + 2; y++ )
	{
		m_cursor_pos.X = m_area_size + 2;
		m_cursor_pos.Y = y;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), m_cursor_pos );
		std::cout << 'X';
	}

	reset_output_color( );
}

void c_game_interface::draw_snake( coord_t snake_head, std::vector<coord_t> snake_tail )
{
	set_output_color( FG_LIGHTCYAN );

	m_cursor_pos.X = snake_head.x + 1;
	m_cursor_pos.Y = snake_head.y + 1;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), m_cursor_pos );
	std::cout << '*';

	set_output_color( FG_CYAN );

	for ( int i = 0; i < snake_tail.size( ); i++ )
	{
		m_cursor_pos.X = snake_tail.at( i ).x + 1;
		m_cursor_pos.Y = snake_tail.at( i ).y + 1;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), m_cursor_pos );
		std::cout << '*';
	}

	reset_output_color( );
}

void c_game_interface::draw_apple( coord_t coord )
{
	set_output_color( FG_LIGHTGREEN );

	m_cursor_pos.X = coord.x + 1;
	m_cursor_pos.Y = coord.y + 1;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), m_cursor_pos );
	std::cout << 'O';

	reset_output_color( );
}

void c_game_interface::hide_cursor( )
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cursorInfo );
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cursorInfo );
}

void c_game_interface::clear_area( )
{
	std::string empty_line( m_area_size, ' ' );

	for ( int y = 1; y < m_area_size + 1; y++ )
	{
		m_cursor_pos.X = 1;
		m_cursor_pos.Y = y;
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), m_cursor_pos );
		std::cout << empty_line;
	}
}
