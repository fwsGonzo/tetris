#ifndef BLOCK_HPP
#define BLOCK_HPP

namespace library
{
	class Bitmap;
	class VoxelModel;
}

namespace game
{
	class Block
	{
	public:
		Block();
		Block(int id, int rot, const library::Bitmap& bmp);
		Block& operator= (const Block& block);
		~Block();
		
		void render();
		
		int getWidth() const;
		int getHeight() const;
		
		unsigned int operator () (int x, int y) const;
		
	private:
		library::Bitmap* bmp;
		library::VoxelModel* voxel;
		
		int id;
		int rotation; // 0, 1, 2, 3 (cw)
		
		friend class Board;
	};
	
	class Shapes
	{
	public:
		/// http://en.wikipedia.org/wiki/Tetris ///
		enum shapes_t
		{
			BOARD = 0,
			SHAPE_I,
			SHAPE_J,
			SHAPE_L,
			SHAPE_O,
			SHAPE_S,
			SHAPE_T,
			SHAPE_Z,
			
			NUM_SHAPES
		};
		static const int ROTATIONS = 4;
		
		static Block shapes[NUM_SHAPES][ROTATIONS];
		
		static void init();
		
		static void count();
		static Block& get(int index, int rotation);
		
	};
	
}

#endif // BLOCK_HPP
