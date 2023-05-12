#pragma once

#include <Formats/IO/BinaryIOStream.h>

#include <bit>

namespace Formats::IO::BinaryIOStream_Versions {
	class Little : public Formats::IO::BinaryIOStream {
		Little(std::iostream stream) : Formats::IO::BinaryIOStream(stream) {

		}

#pragma region READING
#define READ(type, name) virtual inline type ReadByte() override {     \
		type res;                                                      \
		mStream.read(&res, sizeof(type));                              \
#if (FORMATS_BIGENDIAN)
		return std::byteswap(res);                                     \
#endif
		return res;                                                    \
	}                                                                  \

READ(BYTE, Byte)
READ(SHORT, Short)
READ(INT, Int)
READ(LONG, Long)
READ(UBYTE, UByte)
READ(USHORT, UShort)
READ(UINT, UInt)
READ(ULONG, ULong)
READ(FLOAT, Float)
READ(DOUBLE, Double)

#pragma endregion

#pragma region WRITING
#define WRITE(type, name) virtual inline void ReadByte(type value) override { \
#if (FORMATS_BIGENDIAN)
		type swapped = std::byteswap(value);                                  \
		mStream.write(&swapped, sizeof(type))                                 \
#endif
		mStream.write(&value, sizeof(type));                                  \
	}                                                                         \

		WRITE(BYTE, Byte)
		WRITE(SHORT, Short)
		WRITE(INT, Int)
		WRITE(LONG, Long)
		WRITE(UBYTE, UByte)
		WRITE(USHORT, UShort)
		WRITE(UINT, UInt)
		WRITE(ULONG, ULong)
		WRITE(FLOAT, Float)
		WRITE(DOUBLE, Double)
#pragma endregion
	};
}