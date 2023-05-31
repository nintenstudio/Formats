#pragma once

#include <Formats/IO/BinaryIOStream.h>

#include <algorithm>

#if (FORMATS_BIGENDIAN)
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

#if (FORMATS_BIGENDIAN)
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
	class Little : public Formats::IO::BinaryIOStream {
	public:
		Little(std::iostream& stream) : Formats::IO::BinaryIOStream(stream) {

		}

#pragma region READING

		READ(F_S8, Byte)
		READ(F_S16, Short)
		READ(F_S24, Int24)
		READ(F_S32, Int)
		READ(F_S64, Long)
		READ(F_U8, UByte)
		READ(F_U16, UShort)
		READ(F_U24, UInt24)
		READ(F_U32, UInt)
		READ(F_U64, ULong)
		READ(F_F32, Float)
		READ(F_F64, Double)

#pragma endregion

#pragma region WRITING



		WRITE(F_S8, Byte)
		WRITE(F_S16, Short)
		WRITE(F_S24, Int24)
		WRITE(F_S32, Int)
		WRITE(F_S64, Long)
		WRITE(F_U8, UByte)
		WRITE(F_U16, UShort)
		WRITE(F_U24, UInt24)
		WRITE(F_U32, UInt)
		WRITE(F_U64, ULong)
		WRITE(F_F32, Float)
		WRITE(F_F64, Double)
#pragma endregion
	};
}

#undef READ
#undef READ_ENDIAN_CODE
#undef WRITE
#undef WRITE_ENDIAN_CODE