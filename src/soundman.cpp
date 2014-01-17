#include "soundman.hpp"

#include <library/sound/sound.hpp>
#include <library/sound/stream.hpp>

using namespace library;

namespace game
{
	Soundman::Soundman()
	{
		sounds[PIECE_MOVE]   = new Sound("sound/SFX_PieceMoveLR.ogg");
		sounds[PIECE_MOVE_F] = new Sound("sound/SFX_PieceTouchLR.ogg");
		sounds[PIECE_ROTATE] = new Sound("sound/SFX_PieceRotateLR.ogg");
		sounds[PIECE_ROTATE_F] = new Sound("sound/SFX_PieceRotateFail.ogg");
		
		sounds[PIECE_LAND] = new Sound("sound/SFX_PieceSoftDrop.ogg");
		sounds[PIECE_DROP] = new Sound("sound/SFX_PieceHardDrop.ogg");
		
		sounds[ROW_COLLAPSE] = new Sound("sound/bang.ogg");
		
		music = new Stream("music/tetris.mp3");
	}
	Soundman::~Soundman()
	{
		for (int i = 0; i < (int) NUM_SOUNDS; i++)
			delete sounds[i];
		
		delete music;
	}
	
	void Soundman::play(sounds_t sound)
	{
		sounds[sound]->play();
	}
	
	void Soundman::playMusic()
	{
		music->play();
	}
	void Soundman::stopMusic()
	{
		music->stop();
	}
	
}
