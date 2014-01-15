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
		
		// chose next piece immediately
		nextPiece = &Shapes::randomShape();
		
		// choose random new piece at start of game
		selectNewPiece();
	}
	
	void Board::renderBackground(int mode)
	{
		this->background.render(mode);
	}
	void Board::renderBoard(int mode)
	{
		this->board.render(mode);
	}
	
	void Board::selectNewPiece()
	{
		piece.block = nextPiece;
		nextPiece   = &Shapes::randomShape();
		
		piece.x = getWidth() / 2 - piece.block->getWidth() / 2;
		piece.y = getHeight(); // + piece.block->getHeight();
	}
	
	int Board::placeBlock()
	{
		// combine the active piece with the current board (burn it into the board)
		// algorithmically, we are just adding each pixel of the active piece to the board,
		// with the exception of pixels with alpha=0
		this->board.maskedBlit(*piece.block, piece.x, piece.y);
		// select new piece automatically
		selectNewPiece();
		// remove any completed rows, to avoid annoying the player
		return removeCompleteRows();
	}
	
	int Board::removeCompleteRows()
	{
		int row, count = 0;
		
		while ((row = board.completeRow()) != -1)
		{
			board.removeRow(row);
			count++;
		}
		return count;
	}
	
}

