#include "scenerenderer.hpp"

#include <library/log.hpp>
#include <library/opengl/window.hpp>
#include "shaderman.hpp"
#include "board.hpp"

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
	
	void SceneRenderer::render(double time, double dtime)
	{
		Shader& shd = shaderman[Shaderman::BLOCK_SHADER];
		shd.bind();
		
		camera.setTranslation(-board.getWidth() / 2.0, -board.getHeight() / 2.0, -20);
		
		shd.sendMatrix("matview", camera.getViewMatrix());
		shd.sendFloat("time", time);
		
		board.render();
		
		/// render current piece ///
		Shapes::get(2, (int) time % 4).render();
		
	}
	
}
