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

		READ(F_S8, S8)
		READ(F_S16, S16)
		READ(F_S24, S24)
		READ(F_S32, S32)
		READ(F_S64, S64)
		READ(F_U8, U8)
		READ(F_U16, U16)
		READ(F_U24, U24)
		READ(F_U32, U32)
		READ(F_U64, U64)
		READ(F_F32, F32)
		READ(F_F64, F64)

#pragma endregion

#pragma region WRITING



		WRITE(F_S8, S8)
		WRITE(F_S16, S16)
		WRITE(F_S24, S24)
		WRITE(F_S32, S32)
		WRITE(F_S64, S64)
		WRITE(F_U8, U8)
		WRITE(F_U16, U16)
		WRITE(F_U24, U24)
		WRITE(F_U32, U32)
		WRITE(F_U64, U64)
		WRITE(F_F32, F32)
		WRITE(F_F64, F64)
#pragma endregion
	};
}

#undef READ
#undef READ_ENDIAN_CODE
#undef WRITE
#undef WRITE_ENDIAN_CODE