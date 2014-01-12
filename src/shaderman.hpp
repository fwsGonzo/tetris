#ifndef SHADERMAN_HPP
#define SHADERMAN_HPP

#include <library/opengl/shader.hpp>

namespace game
{
	class Shaderman
	{
	public:
		enum shaders_t
		{
			BLOCK_SHADER,
			SCREEN_SHADER,
			
			NUM_SHADERS
		};
		
		void init();
		
		library::Shader& operator [] (shaders_t shd);
		
	private:
		library::Shader shaders[Shaderman::NUM_SHADERS];
		
	};
	extern Shaderman shaderman;
}

#endif // SHADERMAN_HPP
