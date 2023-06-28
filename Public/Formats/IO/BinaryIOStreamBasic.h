#pragma once

#include <Formats/IO/BinaryIOStream.h>
#include <Formats/IO/Endianness.h>
#include <Formats/Aliases/Primitives.h>
#include <memory>

namespace Formats::IO {
	class BinaryIOStreamBasic {
	public:
		virtual std::shared_ptr<BinaryIOStream> Factory(Formats::IO::Endianness endianness) = 0;

		virtual void ReadBytes(void* out, F_U32 length) = 0;
		virtual void WriteBytes(const void* in, F_U32 length) = 0;

		virtual F_U8* GetBuffer() = 0;
		virtual F_U64 GetBufferLength() = 0;
	};
}