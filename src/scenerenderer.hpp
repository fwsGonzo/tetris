#ifndef SCENE_RENDERER_HPP
#define SCENE_RENDERER_HPP

#include <library/opengl/camera.hpp>
namespace library
{
	class WindowClass;
}

namespace game
{
	class SceneRenderer
	{
	public:
		
		void init(library::WindowClass& wnd);
		
		bool render(double time, double dtime);
		
		library::Camera camera;
		library::WindowClass* window;
		
	};

}

#endif // SCENE_RENDERER_HPP
