#include "main.hpp"

#include <library/log.hpp>
#include "board.hpp"
#include "game.hpp"
#include "renderer.hpp"

/**
 * Tetris
 * 
 * Arrow keys to move the active piece
 * Space to rotate it
 * 
 * Escape (or close window) to exit
**/

using namespace library;

int main(void)
{
	logger << Log::INFO << "Tetris!" << Log::ENDL;
	
	/// initialize renderer & subsystems ///
	game::Renderer r;
	
	/// initialize game ///
	game::Game gameObject(r.getWindow());
	
	/// start game ///
	r.start(gameObject);
	
	logger << Log::INFO << "Bye!" << Log::ENDL;
	return 0;
}
