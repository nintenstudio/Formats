#pragma once

#include <Formats/IO/BinaryIOStream.h>

#include <bit>
#include <algorithm>

#if (FORMATS_BIGENDIAN)
#define READ_ENDIAN_CODE std::reverse(&res, (&res) + 1);
#else
#define READ_ENDIAN_CODE
#endif

#define READ(type, name) virtual inline type Read##name() override {\
		type res;\
		mStream.read(reinterpret_cast<char*>(&res), sizeof(type));\
		READ_ENDIAN_CODE\
		return res;\
	}

#if (FORMATS_BIGENDIAN)
#define WRITE_ENDIAN_CODE \
std::reverse(&swapped, (&swapped) + 1);\
mStream.write(reinterpret_cast<char*>(&swapped), sizeof(swapped));
#else
#define WRITE_ENDIAN_CODE mStream.write(reinterpret_cast<char*>(&value), sizeof(value));
#endif

#define WRITE(type, name) virtual inline void Write##name(type value) override { \
		type swapped = value;\
		WRITE_ENDIAN_CODE\
	}


namespace Formats::IO::BinaryIOStream_Versions {
	class Little : public Formats::IO::BinaryIOStream {
	public:
		Little(std::iostream& stream) : Formats::IO::BinaryIOStream(stream) {

		}

#pragma region READING

		READ(BYTE, Byte)
		READ(SHORT, Short)
		READ(INT24, Int24)
		READ(INT, Int)
		READ(LONG, Long)
		READ(UBYTE, UByte)
		READ(USHORT, UShort)
		READ(UINT24, UInt24)
		READ(UINT, UInt)
		READ(ULONG, ULong)
		READ(FLOAT, Float)
		READ(DOUBLE, Double)

#pragma endregion

#pragma region WRITING



		WRITE(BYTE, Byte)
		WRITE(SHORT, Short)
		WRITE(INT24, Int24)
		WRITE(INT, Int)
		WRITE(LONG, Long)
		WRITE(UBYTE, UByte)
		WRITE(USHORT, UShort)
		WRITE(UINT24, UInt24)
		WRITE(UINT, UInt)
		WRITE(ULONG, ULong)
		WRITE(FLOAT, Float)
		WRITE(DOUBLE, Double)
#pragma endregion
	};
}