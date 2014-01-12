#include "block.hpp"

#include <library/bitmap/bitmap.hpp>
#include <library/voxels/voxelmodel.hpp>

using namespace library;

namespace game
{
	/// http://en.wikipedia.org/wiki/Tetris
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
	Block shapes[NUM_SHAPES];
	
	Block::Block()
	{
		this->id = 0;
		this->bmp   = new Bitmap();
		this->voxel = new VoxelModel();
	}
	Block::Block(int id, const Bitmap& bmp) : Block()
	{
		this->id = id;
		this->bmp[0] = bmp;
	}
	Block::~Block()
	{
		delete bmp; delete voxel;
	}
	
	int Block::getWidth() const
	{
		return bmp->getWidth();
	}
	int Block::getHeight() const
	{
		return bmp->getHeight();
	}
	
	unsigned int Block::operator () (int x, int y) const
	{
		return bmp->getPixel(x, y);
	}
	
	VoxelModel& Block::getModel()
	{
		return this->voxel[0];
	}
	
	void Shapes::init()
	{
		Bitmap bmp(4, 1, 32);
		Bitmap::rgba8_t C;
		
		// set entire block to red
		C = bmp.makeColor(255, 0, 0, 255);
		bmp.clear(C);
		
		shapes[SHAPE_I] = Block(SHAPE_I, bmp);
		
		
	}
	
}

