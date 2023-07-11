#pragma once

#include <Formats/IO/BinaryIOStream.h>
#include <Formats/Aliases/Primitives.h>
#include <ios>
#include <vector>
#include <cassert>

#define FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(type, name) virtual type Read##name() override {\
		type res;\
		ReadBytesWithEndian(&res, sizeof(type));\
		return res;\
	}
#define FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(type, name) virtual void Write##name(type value) override {\
		WriteBytesWithEndian(&value, sizeof(type));\
	}

namespace Formats::IO::BinaryIOStreams::Buffer {
    class Buffer : public Formats::IO::BinaryIOStream {
    public:
        Buffer(std::shared_ptr<F_U8> buffer, F_UT bufferSize);

        virtual void Seek(std::streampos pos) override;
		virtual void PushSeek(std::streampos pos) override;
		virtual std::streampos PopSeek() override;
		virtual std::streampos GetSeek() override;
		virtual void AlignSeek(std::streampos alignment) override;

		virtual std::string ReadZeroTerminatedString(F_U32 allocation = FORMATS_IO_BINARYIOSTREAM_READ_STRING_DEFAULTALLOCATION) override;
		virtual void WriteZeroTerminatedString(std::string value) override;

		virtual F_U8 ReadU8() override {
			assert(mSeek < mBufferSize);

			F_U8 res;
			res = mBuffer.get()[mSeek];
            mSeek += 1;
			return res;
		}
		virtual F_S8 ReadS8() override {
			assert(mSeek < mBufferSize);

			F_S8 res;
			res = reinterpret_cast<F_S8*>(mBuffer.get())[mSeek];
            mSeek += 1;
			return res;
		}
		virtual void WriteU8(F_U8 value) override {
			assert(mSeek < mBufferSize);

			mBuffer.get()[mSeek] = value;
            mSeek += 1;
		}
		virtual void WriteS8(F_S8 value) override {
			assert(mSeek < mBufferSize);
			
			mBuffer.get()[mSeek] = *reinterpret_cast<F_U8*>(&value);
			mSeek += 1;
		}

		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_U16, U16)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_U24, U24)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_U32, U32)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_U64, U64)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_S16, S16)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_S24, S24)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_S32, S32)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_S64, S64)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_F32, F32)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_READ(F_F64, F64)

		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_U16, U16)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_U24, U24)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_U32, U32)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_U64, U64)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_S16, S16)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_S24, S24)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_S32, S32)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_S64, S64)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_F32, F32)
		FORMATS_IO_BINARYIOSTREAMS_BUFFER_WRITE(F_F64, F64)

		virtual void ReadBytes(void* out, F_U32 size) override;
		virtual void WriteBytes(const void* in, F_U32 size) override;

	protected:
		virtual void ReadBytesWithEndian(void* out, F_UT length) = 0;
		virtual void WriteBytesWithEndian(void* in, F_UT length) = 0;

		std::shared_ptr<F_U8> mBuffer;
		F_UT mBufferSize;
        std::streampos mSeek;
		std::vector<std::streampos> mSeekStack;
    };
}