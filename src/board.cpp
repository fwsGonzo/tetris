#include "board.hpp"

#include <library/bitmap/bitmap.hpp>

using namespace library;

namespace game
{
	Board::Board()
	{
		board = Block(0, Bitmap(WIDTH, HEIGHT, 32));
	}
	
	unsigned int Board::operator () (int x, int y) const
	{
		return board(x, y);
	}
	
}

