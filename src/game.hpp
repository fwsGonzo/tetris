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
		inline bool getDroppingDown() const
		{
			return droppingDown;
		}
		
	private:
		Board*    board;
		Soundman* soundman;
		
		double gravitySpeed, gravityTime;
		double movementSpeed, movementTime;
		double rotationSpeed, rotationTime;
		double gameSpeed, gameTime;
		
		bool droppingDown = false;
	};
}

#endif // GAME_HPP
