#ifndef BOARD_HPP
#define BOARD_HPP

#include "block.hpp"

namespace game
{
	class Board
	{
	public:
		void init();
		void render();
		
		const int WIDTH  = 10;
		const int HEIGHT = 20;
		
		unsigned int operator () (int x, int y) const;
		
		int getWidth() const
		{
			return WIDTH;
		}
		int getHeight() const
		{
			return HEIGHT;
		}
		
	private:
		Block board;
		
	};
	extern Board board;
}

#endif // BOARD_HPP
