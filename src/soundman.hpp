#ifndef SOUNDMAN_HPP
#define SOUNDMAN_HPP

namespace library
{
	class Sound;
	class Stream;
}

namespace game
{
	class Soundman
	{
	public:
		Soundman();
		~Soundman();
		
		enum sounds_t
		{
			PIECE_MOVE,
			PIECE_MOVE_F,
			
			PIECE_ROTATE,
			PIECE_ROTATE_F,
			
			PIECE_LAND,
			PIECE_DROP,
			
			ROW_COLLAPSE,
			
			NUM_SOUNDS
		};
		enum music_t
		{
			TETRIS_THEME
		};
		
		void play(sounds_t sound);
		
		void playMusic();
		void stopMusic();
		
	private:
		library::Stream* music;
		library::Sound*  sounds[NUM_SOUNDS];
	};
}

#endif // SOUNDMAN_HPP
