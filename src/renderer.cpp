#include "renderer.hpp"

#include <library/log.hpp>
#include <library/opengl/opengl.hpp>
#include <library/opengl/window.hpp>
#include "shaderman.hpp"

using namespace library;

namespace game
{
	Renderer::Renderer()
	{
		this->window = new WindowClass();
		if (window == nullptr) throw "";
	}
	
	Renderer::~Renderer()
	{
		if (window) delete window;
	}
	
	bool renderTetris(WindowClass& wnd, double dtime, double timeElapsed);
	
	void Renderer::startRender()
	{
		logger << Log::INFO << "Opening window" << Log::ENDL;
		// set window configuration
		WindowConfig wndconf("Tetris", 800, 600);
		wndconf.vsync = true;
		// open window
		window->open(wndconf);
		
		logger << Log::INFO << "Loading shaders" << Log::ENDL;
		try
		{
			shaderman.init();
		}
		catch (std::string error)
		{
			logger << Log::ERR << "Shader error: " << error << Log::ENDL;
			return;
		}
		logger << Log::INFO << "Game started" << Log::ENDL;
		window->startRenderingLoop(renderTetris, 1.0);
		window->close();
		
		logger << Log::INFO << "Ending game" << Log::ENDL;
	}
	
	bool renderTetris(WindowClass& wnd, double dtime, double timeElapsed)
	{
		glClearColor(0.0, 1.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		
		glfwSwapBuffers(wnd.window());
		return true;
	}
	
}

