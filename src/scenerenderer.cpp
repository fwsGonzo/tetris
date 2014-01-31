#include "scenerenderer.hpp"

#include <library/log.hpp>
#include <library/opengl/window.hpp>
#include "board.hpp"
#include "game.hpp"
#include "shaderman.hpp"
#include "soundman.hpp"

using namespace library;

namespace game
{
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
	}
	
	void SceneRenderer::render(Game& game, double time, double dtime)
	{
		Shader& shd = shaderman[Shaderman::BLOCK_SHADER];
		shd.bind();
		
		Board& board = game.getBoard();
		
		camera.setTranslation(-board.getWidth() / 2.0, -board.getHeight() / 2.0, -20);
		
		shd.sendMatrix("matview", camera.getViewMatrix());
		shd.sendFloat("time", time);
		
		glEnable(GL_LINE_SMOOTH);
		board.renderBackground(GL_LINES);
		
		/**
		 * All renderable objects start at (0, 0) and go outwards positively
		 * This means we need to translate the objects using matrices to the intended position,
		 * and that simplifies alot of the internal math, such as collisions. All we need to do
		 * is keep adding offsets such as + (dx, dy) to each test.
		 * 
		 * Visually, the background is drawn at (0, 0, 0), and the board is at (0, 0, 1); meaning
		 * the board is actually ahead of the background, by 1 voxel unit.
		 * The active piece is translated to (piece.x, piece.y, 1) so that it is on the same Z as
		 * the board, but has its own (x, y) position.
		 * 
		**/
		
		// render next piece
		mat4 matnext = camera.getViewMatrix();
		matnext.translate(board.getWidth() + 2, board.getHeight() - 4, 0);
		shd.sendMatrix("matview", matnext);
		
		board.getNextPiece().render(GL_QUADS);
		
		// render board
		mat4 matview = camera.getViewMatrix();
		matview.translate(0, 0, 1);
		shd.sendMatrix("matview", matview);
		
		board.renderBoard(GL_QUADS);
		
		CurrentPiece& activePiece = board.getPiece();
		
		if (game.getDroppingDown())
		{
			glEnable(GL_BLEND);
			const int TRAIL = 5;
			
			for (int i = 0; i < TRAIL; i++)
			{
				float fade = 1.0 - (float)i / TRAIL;
				//fade *= fade;
				
				// render active piece (last position)
				mat4 mv = matview;
				mv.translate_xy(activePiece.getX(), activePiece.getY() + (i + 1) * 0.5);
				shd.sendMatrix("matview", mv);
				shd.sendFloat("visibility", fade);
				
				/// render current piece (last position) ///
				activePiece.getBlock().render(GL_QUADS);
			}
			
			glDisable(GL_BLEND);
		}
		
		// render active piece
		matview.translate_xy(activePiece.getX(), activePiece.getY());
		shd.sendMatrix("matview", matview);
		shd.sendFloat("visibility", 1.0);
		
		/// render current piece ///
		activePiece.getBlock().render(GL_QUADS);
	}
	
}
