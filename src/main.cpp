#include "main.hpp"

#include <library/log.hpp>
#include "renderer.hpp"

using namespace library;
using namespace game;

int main(void)
{
	logger << Log::INFO << "Tetris!" << Log::ENDL;
	
	Renderer r;
	r.startRender();
	return 0;
}
