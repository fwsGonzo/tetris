#include "soundman.hpp"

#include <library/sound/sound.hpp>
#include <library/sound/stream.hpp>

using namespace library;

namespace game
{
	Soundman::Soundman()
	{
		sounds[PIECE_MOVE]   = new Sound("sound/SFX_PieceMoveLR.ogg");
		sounds[PIECE_ROTATE] = new Sound("sound/SFX_PieceRotateLR.ogg");
		
		music = new Stream("music/tetris.mp3");
		music->play();
	}
	Soundman::~Soundman()
	{
		delete sounds[PIECE_MOVE];
		delete sounds[PIECE_ROTATE];
		
		delete music;
	}
	
	void Soundman::play(sounds_t sound)
	{
		sounds[sound]->play();
	}
}
