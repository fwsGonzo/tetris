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
		void renderBackground();
		void renderBoard();
		
		static const int WIDTH  = 10;
		static const int HEIGHT = 20;
		
		// board operations
		inline unsigned int operator () (int x, int y) const
		{
			return board(x, y);
		}
		
		// board getters
		int getWidth() const
		{
			return WIDTH;
		}
		int getHeight() const
		{
			return HEIGHT;
		}
		
		// functions that affect the active piece
		CurrentPiece& getPiece()
		{
			return piece;
		}
		void selectNewPiece();
		void burn();
		
	private:
		Block background;
		Block board;
		CurrentPiece piece;
		
	};
}

#endif // BOARD_HPP
