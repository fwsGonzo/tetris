#ifndef BOARD_HPP
#define BOARD_HPP

#include "block.hpp"

namespace game
{
	class Board
	{
	public:
		Board();
		
		const int WIDTH = 10;
		const int HEIGHT = 20;
		
		unsigned int operator () (int x, int y) const;
		
	private:
		Block board;
		
	};
}

#endif // BOARD_HPP
