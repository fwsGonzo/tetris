#ifndef BOARD_HPP
#define BOARD_HPP

#include "block.hpp"

namespace game
{
	struct CurrentPiece
	{
		int x, y;
		Block* block;
		
		void rotate()
		{
			block = &Shapes::get(block->getID(), (block->getRotation() + 1) % Shapes::ROTATIONS);
		}
	};
	
	class Board
	{
	public:
		Board();
		void renderBackground(int mode);
		void renderBoard(int mode);
		
		static const int WIDTH  = 10;
		static const int HEIGHT = 20;
		
		// board getters
		inline int getWidth() const
		{
			return WIDTH;
		}
		inline int getHeight() const
		{
			return HEIGHT;
		}
		
		// functions that affect the active piece
		inline CurrentPiece& getPiece()
		{
			return piece;
		}
		inline Block& getNextPiece()
		{
			return *nextPiece;
		}
		inline bool test(CurrentPiece& piece)
		{
			return board.testBlock(*piece.block, piece.x, piece.y);
		}
		// returns the number of rows removed
		int placeBlock();
		
	private:
		void selectNewPiece();
		int removeCompleteRows();
		
		Block background;
		Block board;
		CurrentPiece piece;
		Block* nextPiece;
	};
}

#endif // BOARD_HPP
