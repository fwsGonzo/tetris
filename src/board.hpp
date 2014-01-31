#ifndef BOARD_HPP
#define BOARD_HPP

#include "block.hpp"

namespace game
{
	class CurrentPiece
	{
	public:
		CurrentPiece()
		{
			block = nullptr;
		}
		CurrentPiece(const CurrentPiece& cp)
		{
			*this = cp;
		}
		inline CurrentPiece& operator = (const CurrentPiece& cp)
		{
			block = cp.block;
			x = cp.x; y = cp.y;
			return *this;
		}
		
		inline int getX() const { return x; }
		inline int getY() const { return y; }
		
		inline Block& getBlock()
		{
			return *block;
		}
		inline void setBlock(Block* b)
		{
			this->block = b;
		}
		
		inline void rotate()
		{
			block = &Shapes::get(block->getID(), (block->getRotation() + 1) % Shapes::ROTATIONS);
		}
		inline void setPosition(int X, int Y)
		{
			this->x = X;
			this->y = Y;
		}
		void move(int X, int Y)
		{
			// move to relatively by (X, Y)
			this->x += X; this->y += Y;
		}
		
	private:
		Block* block;
		int x, y;
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
			return board.testBlock(piece.getBlock(), piece.getX(), piece.getY());
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
