#include "board.hpp"

#include <library/log.hpp>
#include <library/bitmap/bitmap.hpp>
#include <library/bitmap/colortools.hpp>
#include "block.hpp"

using namespace library;

namespace game
{
	Board board;
	CurrentPiece piece;
	
	
	void Board::init()
	{
		// create board as initialized bitmap
		logger << Log::INFO << "Creating board" << Log::ENDL;
		
		// black background voxel wall
		background = Block(0, 0, Bitmap(Board::WIDTH, Board::HEIGHT, BGRA8(0, 0, 0, 255)));
		
		// note: 0 is the same as ARGB(0, 0, 0, 0) which is invisible (a = 0) black
		board = Block(0, 0, Bitmap(Board::WIDTH, Board::HEIGHT, 0));
		
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
	
	unsigned int Board::operator () (int x, int y) const
	{
		return board(x, y);
	}
	
	void Board::selectNewPiece()
	{
		piece.block = &Shapes::get(Shapes::randomShape(), 0);
		
		piece.x = getWidth() / 2 - piece.block->getWidth() / 2;
		piece.y = getHeight(); // + piece.block->getHeight();
		
	}
	
	void Board::burn()
	{
		this->board.maskedBlit(*piece.block, piece.x, piece.y);
	}
	
}

