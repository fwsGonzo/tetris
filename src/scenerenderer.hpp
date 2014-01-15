#ifndef SCENE_RENDERER_HPP
#define SCENE_RENDERER_HPP

#include <library/opengl/camera.hpp>
namespace library
{
	class WindowClass;
}

namespace game
{
	class Game;
	
	class SceneRenderer
	{
	public:
		
		void init(library::WindowClass& wnd);
		void attachGame(Game& game)
		{
			this->game = &game;
		}
		
		bool render(double time, double dtime);
		
	private:
		library::Camera camera;
		library::WindowClass* window;
		Game* game;
		
	};

}

#endif // SCENE_RENDERER_HPP
