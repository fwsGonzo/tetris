#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace library
{
	class WindowClass;
}

namespace game
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		
		void start();
		
	private:
		library::WindowClass* window;
		
	};
	
}

#endif // RENDERER_HPP
