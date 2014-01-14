#include "block.hpp"

#include <library/log.hpp>
#include <library/bitmap/bitmap.hpp>
#include <library/bitmap/colortools.hpp>
#include <library/math/toolbox.hpp>
#include <library/math/vector.hpp>
#include <library/voxels/voxelmodel.hpp>
#include <library/voxels/voxelizer.hpp>
#include <cstdint>

using namespace library;

namespace game
{
	Block Shapes::shapes[Shapes::NUM_SHAPES][Shapes::ROTATIONS];
	
	Block::Block()
	{
		this->id = 0;
		this->bmp   = nullptr;
		this->voxel = nullptr;
	}
	Block::Block(int id, int rot, const Bitmap& bmp) : Block()
	{
		this->id = id;
		this->rotation = rot;
		this->bmp = new Bitmap(bmp);
		this->voxel = new VoxelModel();
		updateVoxel();
	}
	Block& Block::operator = (const Block& block)
	{
		this->id = block.id;
		this->rotation = block.rotation;
		this->bmp = new Bitmap(*block.bmp);
		this->voxel = new VoxelModel(*block.voxel);
		return *this;
	}
	Block::~Block()
	{
		delete bmp;
		delete voxel;
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
	
	void Block::render()
	{
		if (voxel->isGood()) voxel->render();
	}
	
	void Block::updateVoxel()
	{
		XModel xm;
		xm.extrude(*bmp, vec3(0.0), vec3(1.0));
		voxel->create(xm.vertices(), xm.data());
	}
	
	void Block::maskedBlit(const Block& block, int x, int y)
	{
		for (int dx = 0; dx < block.getWidth(); dx++)
		for (int dy = 0; dy < block.getHeight(); dy++)
		{
			Bitmap::rgba8_t C = block.bmp->getPixel(dx, dy);
			
			if (C) bmp->setPixel(x + dx, y + dy, C);
		}
		updateVoxel();
	}
	
	void createShape(int index, Bitmap bmp)
	{
		for (int i = 0; i < Shapes::ROTATIONS; i++)
		{
			Shapes::shapes[index][i] = Block(index, i, bmp);
			bmp = bmp.rotate90();
		}
	}
	
	void Shapes::init()
	{
		Bitmap::rgba8_t C;
		/// http://en.wikipedia.org/wiki/Tetris ///
		
		// I shape
		Bitmap bmp(4, 1);
		C = BGRA8(0, 255, 255, 255); // cyan
		bmp.clear(C);
		
		createShape(SHAPE_I, bmp);
		
		// J shape
		bmp = Bitmap(3, 2);
		C = BGRA8(0, 0, 255, 255); // blue
		bmp.setPixel(0, 1, C); bmp.setPixel(1, 1, C); bmp.setPixel(2, 1, C);
		bmp.setPixel(0, 0, 0); bmp.setPixel(1, 0, 0); bmp.setPixel(2, 0, C);
		
		createShape(SHAPE_J, bmp);
		
		// L shape
		bmp = Bitmap(3, 2);
		C = BGRA8(255, 164, 0, 255); // orange
		bmp.setPixel(0, 1, C); bmp.setPixel(1, 1, C); bmp.setPixel(2, 1, C);
		bmp.setPixel(0, 0, C); bmp.setPixel(1, 0, 0); bmp.setPixel(2, 0, 0);
		
		createShape(SHAPE_L, bmp);
		
		// O shape
		bmp = Bitmap(2, 2);
		C = BGRA8(255, 255, 0, 255); // yellow
		bmp.clear(C);
		
		createShape(SHAPE_O, bmp);
		
		// S shape
		bmp = Bitmap(3, 2);
		C = BGRA8(0, 255, 0, 255); // green
		bmp.setPixel(0, 1, 0); bmp.setPixel(1, 1, C); bmp.setPixel(2, 1, C);
		bmp.setPixel(0, 0, C); bmp.setPixel(1, 0, C); bmp.setPixel(2, 0, 0);
		
		createShape(SHAPE_S, bmp);
		
		// T shape
		bmp = Bitmap(3, 2);
		C = BGRA8(255, 0, 255, 255); // magenta
		bmp.setPixel(0, 1, C); bmp.setPixel(1, 1, C); bmp.setPixel(2, 1, C);
		bmp.setPixel(0, 0, 0); bmp.setPixel(1, 0, C); bmp.setPixel(2, 0, 0);
		
		createShape(SHAPE_T, bmp);
		
		// Z shape
		bmp = Bitmap(3, 2);
		C = BGRA8(255, 0, 0, 255); // red
		bmp.setPixel(0, 1, C); bmp.setPixel(1, 1, C); bmp.setPixel(2, 1, 0);
		bmp.setPixel(0, 0, 0); bmp.setPixel(1, 0, C); bmp.setPixel(2, 0, C);
		
		createShape(SHAPE_Z, bmp);
		
	}
	
	Block& Shapes::get(int index, int rotation)
	{
		return shapes[index][rotation];
	}
	
	int Shapes::randomShape()
	{
		return toolbox::rnd((int)Shapes::NUM_SHAPES);
	}
	
}
