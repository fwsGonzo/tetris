#include "game.hpp"

#include <library/log.hpp>
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
		//soundman->playMusic();
		
		/// initialize game board ///
		board = new Board();
		
		/// initialize keyboard input ///
		input.init(wnd, true, false);
		
		// input & gameplay timers
		gravitySpeed = 0.5;
		gravityTime = 0.0;
		
		movementSpeed = 0.08;
		movementTime = 0.0;
		
		rotationSpeed = 0.2;
		rotationTime = 0.0;
		
		gameSpeed = 0.01;
		gameTime  = 0.0;
		
		// current dropping
		droppingDown = false;
	}
	
	Game::~Game()
	{
		delete soundman;
		delete board;
	}
	
	bool Game::gameHandler(double time, double dtime)
	{
		bool tick = false;
		
		// increase game speed over time
		if (time > gameTime + gameSpeed)
		{
			gameTime = time;
			gravitySpeed -= 0.00001;
			tick = true;
		}
		
		if (droppingDown == false)
		{
			// brick movement
			if (time > movementTime + movementSpeed)
			{
				movementTime = time;
				
				// move the piece left/right with arrow keys
				if (input.getKey(GLFW_KEY_LEFT))
				{
					CurrentPiece piece = board->getPiece();
					piece.move(-1, 0); // create new active piece that we have already moved left
					
					if (board->test(piece)) // test that the new piece is in a valid position
					{
						board->getPiece().move(-1, 0);
						soundman->play(Soundman::PIECE_MOVE);
					}
					else soundman->play(Soundman::PIECE_MOVE_F);
				}
				if (input.getKey(GLFW_KEY_RIGHT))
				{
					CurrentPiece piece = board->getPiece();
					piece.move(1, 0);
					
					if (board->test(piece))
					{
						board->getPiece().move(1, 0);
						soundman->play(Soundman::PIECE_MOVE);
					}
					else soundman->play(Soundman::PIECE_MOVE_F);
				}
			}
			// conditional timing
			if (time > rotationTime + rotationSpeed)
			{
				// rotate the piece with Spacebar
				if (input.getKey(GLFW_KEY_SPACE))
				{
					rotationTime = time;
					
					CurrentPiece piece = board->getPiece();
					piece.rotate();
					
					if (board->test(piece))
					{
						board->getPiece().rotate();
						soundman->play(Soundman::PIECE_ROTATE);
					}
					else soundman->play(Soundman::PIECE_ROTATE_F);
				}
				// drop piece down with Down key
				if (input.getKey(GLFW_KEY_DOWN))
				{
					rotationTime = time;
					
					soundman->play(Soundman::PIECE_DROP);
					droppingDown = true;
				}
			}
		}
		// move piece down over time (or when dropping)
		if (time > gravityTime + gravitySpeed || (droppingDown && tick))
		{
			gravityTime = time;
			
			// create clone of active piece, and move it down
			CurrentPiece piece = board->getPiece();
			piece.move(0, -1);
			
			if (board->getPiece().getY()+piece.getBlock().getHeight() >= board->getHeight())
			{
				// the piece is currently above the board itself, so we can't burn
				// instead the game is over if it hits something
				if (board->test(piece) == false)
				{
					/// GAME OVER ///
					logger << Log::WARN << "Game over!" << Log::ENDL;
					return false;
				}
				else // move the piece into the board (over time)
				{
					board->getPiece().move(0, -1);
				}
			}
			else
			{
				// piece is inside board, do regular testing
				if (board->test(piece))
				{
					// we can continue moving the piece down, since it hit nothing
					board->getPiece().move(0, -1);
				}
				else
				{
					// the piece would hit something if it moved down, so instead place
					// the function returns the number of rows removed as a result of the placement
					int rowsRemoved = board->placeBlock();
					
					if (rowsRemoved)
					{
						// play amazing sounds and use legendary fx here
						soundman->play(Soundman::ROW_COLLAPSE);
					}
					else
					{	// play standard sound, just because
						soundman->play(Soundman::PIECE_LAND);
					}
					
					// no longer dropping down
					droppingDown = false;
				}
			}
		}
		
		// stop rendering when Escape key is pressed (effectively ending the game)
		return (input.getKey(GLFW_KEY_ESCAPE) == Input::KEY_RELEASED);
	}
	
}

