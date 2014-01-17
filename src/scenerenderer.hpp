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
		
		void render(Game&, double time, double dtime);
		
	private:
		library::Camera camera;
		library::WindowClass* window;
	};

}

#endif // SCENE_RENDERER_HPP
