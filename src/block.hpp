#ifndef BLOCK_HPP
#define BLOCK_HPP

/**
 * Block is a container for a bitmap (pixel array), and a voxelmodel (opengl renderable)
 * 
 * The current masking convention is that a pixel value of 0 is invisible, whereas any other
 * is treated as if it was (when in fact it might not be). It's done to simplify algorithms:
 * 
 * if (bmp->getPixel(x, y))
 * 		// pixel should be treated as visible
 * else
 * 		// pixel value must be 0 (and evaluates to false)
 * 
**/

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
		
		void render(int mode);
		
		int getWidth() const;
		int getHeight() const;
		int getID() const { return id; }
		int getRotation() const { return rotation; }
		
		unsigned int operator () (int x, int y) const;
		
		void maskedBlit(const Block& block, int x, int y);
		bool testBlock(const Block& block, int x, int y);
		
		int  completeRow() const;
		void removeRow(int row);
		
	private:
		void updateVoxel();
		
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
			SHAPE_I = 0,
			SHAPE_J,
			SHAPE_L,
			SHAPE_O,
			SHAPE_S,
			SHAPE_T,
			SHAPE_Z,
			NUM_SHAPES,
			
			BACKGROUND,
			BOARD,
			TETRIS_TITLE,
			
		};
		static const int ROTATIONS = 4;
		
		static Block shapes[NUM_SHAPES][ROTATIONS];
		
		static void init();
		
		static void count();
		static Block& get(int index, int rotation);
		
		static Block& randomShape();
		
	};
	
}

#endif // BLOCK_HPP
