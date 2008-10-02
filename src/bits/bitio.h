#ifndef __BITIO_H__
#define __BITIO_H__

#include "integer.h"

#include <ostream>
#include <istream>

class BitOutputStream
{
public:
	BitOutputStream(std::ostream& out);
	~BitOutputStream();

	void Write(u32 bits, u32 count);

private:
	void Flush();

	std::ostream& out;
	u8 buffer;
	u8 bitCount;
};

class BitInputStream
{
public:
	BitInputStream(std::istream& in);

	u32 Read(u32 count);

private:
	std::istream& in;
	u8 buffer;
	u8 bitCount;
};

inline BitOutputStream::BitOutputStream(std::ostream& out)
: out(out), buffer(0), bitCount(0)
{
}

inline BitOutputStream::~BitOutputStream()
{
	Flush();
}

inline void BitOutputStream::Write(u32 bits, u32 count)
{
	while (count)
	{
		int bitsToCompleteByte = 8 - this->bitCount;
		int bitsToAdd = (std::min)(bitsToCompleteByte, int(count));
		this->buffer |= (((1 << bitsToAdd) - 1) & bits) << this->bitCount;
		bits >>= bitsToAdd;
		this->bitCount += bitsToAdd;
		count -= bitsToAdd;
		if (this->bitCount >= 8)
		{
			this->out.write(reinterpret_cast<char*>(&this->buffer), 1);
			this->bitCount -= 8;
			this->buffer = 0;
		}
	}
}

inline void BitOutputStream::Flush()
{
	if (this->bitCount)
	{
		this->out.write(reinterpret_cast<char*>(&this->buffer), 1);
		this->bitCount = 0;
		this->buffer = 0;
	}
}

inline BitInputStream::BitInputStream(std::istream& in)
: in(in), buffer(0), bitCount(0)
{
}

inline u32 BitInputStream::Read(u32 count)
{
	u32 bits = 0;
	int outSize = 0;
	while (count)
	{
		if (this->bitCount == 0)
		{
			this->in.read(reinterpret_cast<char*>(&this->buffer), 1);
			this->bitCount += 8;
		}

		int bitsToCopy = (std::min)(int(this->bitCount), int(count));
		bits |= (this->buffer & ((1 << bitsToCopy) - 1)) << outSize;
		outSize += bitsToCopy;
		this->bitCount -= bitsToCopy;
		count -= bitsToCopy;
		this->buffer >>= bitsToCopy;
	}

	return bits;
}

#endif //__BITIO_H__
