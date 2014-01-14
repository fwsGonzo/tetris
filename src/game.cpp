#include "game.hpp"

#include <library/opengl/input.hpp>
#include <library/opengl/window.hpp>
#include "board.hpp"
#include "soundman.hpp"

// we need this for GLFW_KEY_***
#include <GL/glfw3.h>

using namespace library;

namespace game
{
	Game::Game(WindowClass& wnd)
	{
		/// initialize sound & music ///
		soundman = new Soundman();
		
		/// initialize game board ///
		board = new Board();
		
		/// initialize keyboard input ///
		input.init(wnd, true, false);
		
		// game speed
		gravitySpeed = 0.5;
		gravityTime = 0.0;
		
		movementSpeed = 0.05;
		movementTime = 0.0;
		
	}
	
	Game::~Game()
	{
		delete soundman;
		delete board;
	}
	
	bool Game::gameHandler(double time, double dtime)
	{
		
		// brick movement
		if (time > movementTime + movementSpeed)
		{
			movementTime = time;
			// move the piece left/right with arrow keys
			if (input.getKey(GLFW_KEY_LEFT))
				if (board->getPiece().x > 0) board->getPiece().x--;
			if (input.getKey(GLFW_KEY_RIGHT))
				if (board->getPiece().x < board->getWidth() - board->getPiece().block->getWidth()) board->getPiece().x++;
			// rotate the piece with Spacebar
			if (input.getKey(GLFW_KEY_SPACE)) board->getPiece().rotate();
		}
		// move piece down over time
		if (time > gravityTime + gravitySpeed)
		{
			gravityTime = time;
			if (board->getPiece().y == 0)
			{
				// burn into board
				board->burn();
				board->selectNewPiece();
			}
			else
			{
				board->getPiece().y--;
			}
		}
		
		// stop rendering when Escape key is pressed (effectively ending the game)
		return (input.getKey(GLFW_KEY_ESCAPE) == Input::KEY_RELEASED);
	}
	
}

