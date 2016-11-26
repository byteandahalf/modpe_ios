#ifndef __MCPE_COMMON_H
#define __MCPE_COMMON_H

#include <stdint.h>

typedef uint_fast8_t DataID;
typedef uint_fast8_t FacingID;

struct BlockID
{
	unsigned char value;

	BlockID()
	{
		this->value = 1;
	}

	BlockID(unsigned char val)
	{
		this->value = val;
	}

	BlockID(BlockID const& other)
	{
		this->value = other.value;
	}

	bool operator==(char v)
	{
		return this->value == v;
	}

	bool operator==(int v)
	{
		return this->value == v;
	}

	bool operator==(BlockID v)
	{
		return this->value == v.value;
	}

	BlockID& operator=(const unsigned char& v)
	{
		this->value = v;
		return *this;
	}

	operator unsigned char()
	{
		return this->value;
	}
};

struct FullBlock
{
	BlockID blockId;
	DataID data;
};

struct BlockPos
{
	int x, y, z;
};

struct Vec3
{
	float x, y, z;
};

#endif
