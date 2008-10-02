#ifndef __ARITH_H__
#define __ARITH_H__

#include "integer.h"
#include "bitio.h"

#include <assert.h>

class ArithmeticEncoder
{
public:
	ArithmeticEncoder(BitOutputStream& out);
	~ArithmeticEncoder();
	template <typename M> void Encode(M& model, typename M::Value value);

private:
	void EncodeRange(u32 rangeLow, u32 rangeSize, u32 spaceSize);

	u32 windowMin;
	u32 windowMax;
	int underflowBitsPending;
	BitOutputStream& out;
	char value;
	FILE* f;
};

class ArithmeticDecoder
{
public:
	ArithmeticDecoder(BitInputStream& in);
	~ArithmeticDecoder();
	template <typename M> typename M::Value Decode(M& model);

private:
	FILE* f;
	u32 windowMin;
	u32 windowMax;
	u32 code;
	BitInputStream& in;
};

inline ArithmeticEncoder::ArithmeticEncoder(BitOutputStream& out)
: out(out), windowMin(0), windowMax(~0), underflowBitsPending(0)
{
	f = fopen("e:\\e.txt", "w");
}

inline ArithmeticEncoder::~ArithmeticEncoder()
{
	this->out.Write(this->windowMin >> (31), 1);
	while (this->underflowBitsPending)
	{
		this->out.Write((~this->windowMin >> 31), 1);
		--this->underflowBitsPending;
	}
	for (int i = 1; i < 32; ++i)
		this->out.Write((this->windowMin >> (31 - i)) & 1, 1);
	fclose(f);
}

template <typename M> inline void ArithmeticEncoder::Encode(M& model, typename M::Value value)
{
	this->value = value;
	u32 spaceSize = model.GetSpaceSize();
	u32 rangeLow = model.GetRangeLow(value);
	u32 rangeSize = model.GetRangeSize(value);
	this->EncodeRange(rangeLow, rangeSize, spaceSize);
}

inline void ArithmeticEncoder::EncodeRange(u32 rangeLow, u32 rangeSize, u32 spaceSize)
{
	fprintf(f, "Encode: %d/%d/%d (%c)\n", rangeLow, rangeSize, spaceSize, this->value);

	fprintf(f, "%.8X %.8X\n", this->windowMin, this->windowMax);

	u64 windowSize = u64(this->windowMax) - this->windowMin + 1;
	this->windowMax = u32(this->windowMin + (rangeLow + rangeSize) * windowSize / spaceSize) - 1;
	this->windowMin = u32(this->windowMin + rangeLow * windowSize / spaceSize);

	for (;;)
	{
		fprintf(f, "  %.8X %.8X\n", this->windowMin, this->windowMax);
		assert(this->windowMin <= this->windowMax);

		if ((this->windowMin >> 31) == (this->windowMax >> 31))
		{
			this->out.Write(this->windowMin >> 31, 1);
			while (this->underflowBitsPending)
			{
				this->out.Write((~this->windowMin >> 31), 1);
				--this->underflowBitsPending;
			}
			this->windowMin <<= 1;
			this->windowMax = (this->windowMax << 1) | 1;
		}
		else if (((this->windowMin >> 30) & 0x1) == 1 && ((this->windowMax >> 30) & 0x1) == 0)
		{
			assert((this->windowMin >> 31) == 0);
			assert((this->windowMax >> 31) == 1);
			++this->underflowBitsPending;
			this->windowMin = ~(1 << 31) & (this->windowMin << 1);
			this->windowMax = (1 << 31) | (this->windowMax << 1) | 1;
		}
		else
		{
			break;
		}
	}
}

inline ArithmeticDecoder::ArithmeticDecoder(BitInputStream& in)
: in(in), windowMin(0), windowMax(~0)
{
	f = fopen("e:\\d.txt", "w");

	this->code = 0;
	for (int i = 0; i < 32; ++i)
		this->code |= in.Read(1) << (31 - i);
}

ArithmeticDecoder::~ArithmeticDecoder()
{
	fclose(f);
}

template <typename M> inline typename M::Value ArithmeticDecoder::Decode(M& model)
{
	typedef typename M::Value Value;

	u64 windowSize = u64(this->windowMax) - this->windowMin + 1;
	u32 spaceSize = model.GetSpaceSize();
	u32 position = u32(((u64(this->code) - this->windowMin + 1) * spaceSize - 1) / windowSize);
	Value value = model.FindValue(position);
	u32 rangeLow = model.GetRangeLow(value);
	u32 rangeSize = model.GetRangeSize(value);
	
	fprintf(f, "Decode: %d/%d/%d (%c)\n", rangeLow, rangeSize, spaceSize, value);

	fprintf(f, "%.8X %.8X %.8X\n", this->windowMin, this->windowMax, this->code);

	this->windowMax = u32(this->windowMin + (rangeLow + rangeSize) * windowSize / spaceSize) - 1;
	this->windowMin = u32(this->windowMin + rangeLow * windowSize / spaceSize);

	for (;;)
	{
		fprintf(f, "  %.8X %.8X %.8X\n", this->windowMin, this->windowMax, this->code);

		assert(this->windowMin <= this->windowMax);
		assert(this->code <= this->windowMax);
		assert(this->code >= this->windowMin);

		if ((this->windowMin >> 31) == (this->windowMax >> 31))
		{
			this->windowMin <<= 1;
			this->windowMax = (this->windowMax << 1) | 1;
			this->code = (this->code << 1) | this->in.Read(1);
		}
		else if (((this->windowMin >> 30) & 0x1) == 1 && ((this->windowMax >> 30) & 0x1) == 0)
		{
			assert((this->windowMin >> 31) == 0);
			assert((this->windowMax >> 31) == 1);
			this->windowMin = ~(1 << 31) & (this->windowMin << 1);
			this->windowMax = (1 << 31) | (this->windowMax << 1) | 1;
			this->code = ((this->code << 1) ^ (1 << 31)) | this->in.Read(1);
		}
		else
		{
			break;
		}
	}

	return value;
}

#endif //__ARITH_H__
