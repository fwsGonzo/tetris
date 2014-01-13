#include "board.hpp"

#include <library/log.hpp>
#include <library/bitmap/bitmap.hpp>
#include "block.hpp"

using namespace library;

namespace game
{
	Board board;
	
	void Board::init()
	{
		// create board as initialized bitmap
		logger << Log::INFO << "Creating board" << Log::ENDL;
		
		// note: 0 is the same as ARGB(0, 0, 0, 0) which is invisible (a = 0) black
		board = Block(0, 0, Bitmap(Board::WIDTH, Board::HEIGHT, 0));
		
		// initialize shapes
		logger << Log::INFO << "Creating shapes" << Log::ENDL;
		Shapes::init();
		
	}
	
	void Board::render()
	{
		this->board.render();
	}
	
	unsigned int Board::operator () (int x, int y) const
	{
		return board(x, y);
	}
	
}

