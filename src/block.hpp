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
		Block(int id, const library::Bitmap& bmp);
		~Block();
		
		library::VoxelModel& getModel();
		
		int getWidth() const;
		int getHeight() const;
		
		unsigned int operator () (int x, int y) const;
		
	private:
		library::Bitmap* bmp;
		library::VoxelModel* voxel;
		
		int id;
		int rotation; // 0, 1, 2, 3 (cw)
	};
	
	class Shapes
	{
	public:
		static void init();
		
		static void count();
		static Block& get(int index);
		
	};
	
}

#endif // BLOCK_HPP
