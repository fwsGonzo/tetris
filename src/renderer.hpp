#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace library
{
	class WindowClass;
}

namespace game
{
	class Game;
	
	class Renderer
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
		library::WindowClass* window;
		
	};
	
}

#endif // RENDERER_HPP
