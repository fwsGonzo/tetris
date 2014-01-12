#include "shaderman.hpp"

using namespace library;

namespace game
{
	Shaderman shaderman;
	
	void Shaderman::init()
	{
		std::vector<std::string> attr;
		
		// block shader
		attr.push_back("in_vertex");
		attr.push_back("in_normal");
		attr.push_back("in_color");
		
		shaders[Shaderman::BLOCK_SHADER] = Shader("shaders/block.glsl", attr);
		
	}
	
	Shader& Shaderman::operator [] (Shaderman::shaders_t shd)
	{
		return shaders[(int) shd];
	}
}

