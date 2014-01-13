#include "main.hpp"

#include <library/log.hpp>
#include "board.hpp"
#include "renderer.hpp"

using namespace library;

int main(void)
{
	logger << Log::INFO << "Tetris!" << Log::ENDL;
	
	/// initialize renderer & subsystems ///
	game::Renderer r;
	
	/// initialize game ///
	game::board.init();
	
	/// start game ///
	r.start();
	
	logger << Log::INFO << "Bye!" << Log::ENDL;
	return 0;
}
