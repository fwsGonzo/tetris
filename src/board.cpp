#include "board.hpp"

#include <library/log.hpp>
#include <library/bitmap/bitmap.hpp>
#include <library/bitmap/colortools.hpp>
#include "block.hpp"

using namespace library;

namespace game
{
	Board::Board()
	{
		// create board as initialized bitmap
		logger << Log::INFO << "Creating board" << Log::ENDL;
		
		// black background voxel wall
		background = Block(0, 0, Bitmap(getWidth(), getHeight(), BGRA8(0, 0, 0, 255)));
		
		// note: 0 is the same as ARGB(0, 0, 0, 0) which is invisible (a = 0) black
		board = Block(0, 0, Bitmap(getWidth(), getHeight(), 0));
		
		// initialize shapes
		logger << Log::INFO << "Creating shapes" << Log::ENDL;
		Shapes::init();
		
		// choose random new piece at start of game
		selectNewPiece();
	}
	
	void Board::renderBackground()
	{
		this->background.render();
	}
	void Board::renderBoard()
	{
		this->board.render();
	}
	
	void Board::selectNewPiece()
	{
		piece.block = &Shapes::randomShape();
		
		piece.x = getWidth() / 2 - piece.block->getWidth() / 2;
		piece.y = getHeight(); // + piece.block->getHeight();
	}
	
	// combine the active piece with the current board (burn it into the board)
	// algorithmically, we are just adding each pixel of the active piece to the board,
	// with the exception of pixels with alpha=0
	void Board::burn()
	{
		this->board.maskedBlit(*piece.block, piece.x, piece.y);
	}
	
}

