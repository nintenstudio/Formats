#pragma once

#include <Formats/IO/BinaryIOStream.h>

#include <algorithm>

#if (!FORMATS_BIGENDIAN)
#define READ_ENDIAN_CODE(size) std::reverse(reinterpret_cast<char*>(&res), reinterpret_cast<char*>(&res) + size);
#else
#define READ_ENDIAN_CODE(size)
#endif

#define READ(type, name) virtual inline type Read##name() override {\
		type res;\
		mStream.read(reinterpret_cast<char*>(&res), sizeof(type));\
		READ_ENDIAN_CODE(sizeof(type))\
		return res;\
	}

#if (!FORMATS_BIGENDIAN)
#define WRITE_ENDIAN_CODE(size) \
std::reverse(reinterpret_cast<char*>(&swapped), reinterpret_cast<char*>(&swapped) + size);\
mStream.write(reinterpret_cast<char*>(&swapped), sizeof(swapped));
#else
#define WRITE_ENDIAN_CODE(size) mStream.write(reinterpret_cast<char*>(&value), size);
#endif

#define WRITE(type, name) virtual inline void Write##name(type value) override { \
		type swapped = value;\
		WRITE_ENDIAN_CODE(sizeof(type))\
	}


namespace Formats::IO::BinaryIOStream_Versions {
	class Big : public Formats::IO::BinaryIOStream {
public:
		Big(std::iostream& stream) : Formats::IO::BinaryIOStream(stream) {

		}

#pragma region READING

		READ(F_BYTE, Byte)
		READ(F_SHORT, Short)
		READ(F_INT24, Int24)
		READ(F_INT, Int)
		READ(F_LONG, Long)
		READ(F_UBYTE, UByte)
		READ(F_USHORT, UShort)
		READ(F_UINT24, UInt24)
		READ(F_UINT, UInt)
		READ(F_ULONG, ULong)
		READ(F_FLOAT, Float)
		READ(F_DOUBLE, Double)

#pragma endregion

#pragma region WRITING



		WRITE(F_BYTE, Byte)
		WRITE(F_SHORT, Short)
		WRITE(F_INT24, Int24)
		WRITE(F_INT, Int)
		WRITE(F_LONG, Long)
		WRITE(F_UBYTE, UByte)
		WRITE(F_USHORT, UShort)
		WRITE(F_UINT24, UInt24)
		WRITE(F_UINT, UInt)
		WRITE(F_ULONG, ULong)
		WRITE(F_FLOAT, Float)
		WRITE(F_DOUBLE, Double)
#pragma endregion
	};
}

#undef READ
#undef READ_ENDIAN_CODE
#undef WRITE
#undef WRITE_ENDIAN_CODE