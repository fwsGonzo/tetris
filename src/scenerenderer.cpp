#include "scenerenderer.hpp"

#include <library/log.hpp>
#include <library/opengl/input.hpp>
#include <library/opengl/window.hpp>
#include "shaderman.hpp"
#include "board.hpp"

#include <GL/glfw3.h>

using namespace library;

namespace game
{
	double gravitySpeed, gravityTime;
	double movementSpeed, movementTime;
	
	void SceneRenderer::init(WindowClass& wnd)
	{
		/// create perspective camera ///
		camera = Camera(61, wnd.SA, 0.1, 100.0);
		
		/// load shaders ///
		logger << Log::INFO << "Loading shaders" << Log::ENDL;
		try
		{
			shaderman.init();
		}
		catch (std::string error)
		{
			throw std::string("Shader error: " + error);
		}
		
		/// initialize shader uniforms ///
		Shader& shd = shaderman[Shaderman::BLOCK_SHADER];
		shd.bind();
		shd.sendMatrix("matproj", camera.getProjection());
		
		/// initialize keyboard input ///
		input.init(wnd, true, false);
		
		// game speed
		gravitySpeed = 0.5;
		gravityTime = 0.0;
		
		movementSpeed = 0.05;
		movementTime = 0.0;
	}
	
	bool SceneRenderer::render(double time, double dtime)
	{
		Shader& shd = shaderman[Shaderman::BLOCK_SHADER];
		shd.bind();
		
		camera.setTranslation(-board.getWidth() / 2.0, -board.getHeight() / 2.0, -20);
		
		shd.sendMatrix("matview", camera.getViewMatrix());
		shd.sendFloat("time", time);
		
		board.renderBackground();
		
		// brick movement
		if (time > movementTime + movementSpeed)
		{
			movementTime = time;
			// move the piece left/right with arrow keys
			if (input.getKey(GLFW_KEY_LEFT))
				if (board.getPiece().x > 0) board.getPiece().x--;
			if (input.getKey(GLFW_KEY_RIGHT))
				if (board.getPiece().x < board.WIDTH-board.getPiece().block->getWidth()) board.getPiece().x++;
			// rotate the piece with Spacebar
			if (input.getKey(GLFW_KEY_SPACE)) board.getPiece().rotate();
		}
		// move piece down over time
		if (time > gravityTime + gravitySpeed)
		{
			gravityTime = time;
			if (board.getPiece().y == 0)
			{
				// burn into board
				board.burn();
				board.selectNewPiece();
			}
			else
			{
				board.getPiece().y--;
			}
		}
		
		// render board
		mat4 matview = camera.getViewMatrix();
		matview.translate(0, 0, 1);
		shd.sendMatrix("matview", matview);
		
		board.renderBoard();
		
		// render active piece
		matview.translate(board.getPiece().x, board.getPiece().y, 0);
		shd.sendMatrix("matview", matview);
		
		/// render current piece ///
		board.getPiece().block->render();
		
		// stop rendering when Escape key is pressed (effectively ending the game)
		return input.getKey(GLFW_KEY_ESCAPE) == Input::KEY_RELEASED;
	}
	
}
