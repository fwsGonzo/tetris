#ifndef GAME_HPP
#define GAME_HPP

namespace library
{
	class WindowClass;
}

namespace game
{
	class Soundman;
	class Board;
	
	class Game
	{
	public:
		Game(library::WindowClass& wnd);
		~Game();
		
		bool gameHandler(double time, double dtime);
		
		Board& getBoard()
		{
			return *board;
		}
		
	private:
		Board*    board;
		Soundman* soundman;
		
		double gravitySpeed, gravityTime;
		double movementSpeed, movementTime;
		double rotationSpeed, rotationTime;
		
		bool droppingDown = false;
	};
}

#endif // GAME_HPP
