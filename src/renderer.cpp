#include "renderer.hpp"

#include <library/log.hpp>
#include <library/opengl/opengl.hpp>
#include <library/opengl/window.hpp>
#include "scenerenderer.hpp"

using namespace library;

namespace game
{
	SceneRenderer scene;
	
	Renderer::Renderer()
	{
		this->window = new WindowClass();
		if (window == nullptr) throw std::string("Failed to open OpenGL context window");
		
		logger << Log::INFO << "Opening window" << Log::ENDL;
		// set window configuration
		WindowConfig wndconf("Tetris", 800, 600);
		wndconf.vsync = true;
		// open window
		window->open(wndconf);
		
		/// initialize scene renderer ///
		scene.init(*window);
	}
	
	Renderer::~Renderer()
	{
		if (window) delete window;
	}
	
	bool renderTetris(WindowClass& wnd, double dtime, double timeElapsed);
	
	void Renderer::start(Game& game)
	{
		/// start game ///
		logger << Log::INFO << "Game started" << Log::ENDL;
		scene.attachGame(game);
		
		window->startRenderingLoop(renderTetris, 1.0);
		// close window after renderloop
		window->close();
	}
	
	bool renderTetris(WindowClass& wnd, double dtime, double timeElapsed)
	{
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glEnable(GL_DEPTH_TEST);
		
		bool ret = scene.render(timeElapsed, dtime);
		
		glfwSwapBuffers(wnd.window());
		return ret;
	}
	
}

