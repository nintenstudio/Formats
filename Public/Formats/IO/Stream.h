#pragma once

#include <Formats/Aliases/Primitives.h>
#include <Formats/IO/Endianness.h>
#include <memory>

// The size to allocate to a string by default when loading.
// May have an impact on performance in some cases.
#define FORMATS_IO_STREAM_READ_STRING_DEFAULTALLOCATION 32

namespace Formats::IO {
    class Stream {
    public:
        virtual void Seek(std::streampos pos) = 0;
		virtual void PushSeek(std::streampos pos) = 0;
		virtual std::streampos PopSeek() = 0;
		virtual std::streampos GetSeek() = 0;
		virtual void AlignSeek(std::streampos alignment) = 0;

        virtual std::string ReadZeroTerminatedString(F_U32 allocation = FORMATS_IO_STREAM_READ_STRING_DEFAULTALLOCATION) = 0;
		virtual void WriteZeroTerminatedString(std::string value) = 0;

        virtual void SetEndianness(Formats::IO::Endianness endianness) = 0;

        virtual F_S8 ReadS8() = 0;
		virtual F_S16 ReadS16() = 0;
		virtual F_S24 ReadS24() = 0;
		virtual F_S32 ReadS32() = 0;
		virtual F_S64 ReadS64() = 0;

		virtual F_U8 ReadU8() = 0;
		virtual F_U16 ReadU16() = 0;
		virtual F_U24 ReadU24() = 0;
		virtual F_U32 ReadU32() = 0;
		virtual F_U64 ReadU64() = 0;

		virtual F_F32 ReadF32() = 0;
		virtual F_F64 ReadF64() = 0;

		virtual void WriteS8(F_S8 value) = 0;
		virtual void WriteS16(F_S16 value) = 0;
		virtual void WriteS24(F_S24 value) = 0;
		virtual void WriteS32(F_S32 value) = 0;
		virtual void WriteS64(F_S64 value) = 0;

		virtual void WriteU8(F_U8 value) = 0;
		virtual void WriteU16(F_U16 value) = 0;
		virtual void WriteU24(F_U24 value) = 0;
		virtual void WriteU32(F_U32 value) = 0;
		virtual void WriteU64(F_U64 value) = 0;

		virtual void WriteF32(F_F32 value) = 0;
		virtual void WriteF64(F_F64 value) = 0;

        virtual void ReadBytes(void* out, F_U32 length) = 0;
		virtual void WriteBytes(const void* in, F_U32 length) = 0;

        virtual std::shared_ptr<F_U8[]> GetBuffer() = 0;
		virtual F_UT GetBufferLength() = 0;
    };
}