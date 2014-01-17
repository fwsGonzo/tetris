#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <library/opengl/window.hpp>

namespace game
{
	class Game;
	
	class Renderer : public library::RenderClass
	{
	public:
		Renderer();
		~Renderer();
		
		void start(Game& game);
		
		library::WindowClass& getWindow()
		{
			return *window;
		}
		
	private:
		bool render(library::WindowClass& wnd, double dtime, double timeElapsed);
		
		library::WindowClass* window;
		Game* game;
	};
	
}

#endif // RENDERER_HPP
