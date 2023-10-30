#pragma once

#include <Formats/IO/Stream.h>
#include <ios>
#include <memory>

namespace Formats::IO {
    class PartialStream : public Formats::IO::Stream {
    public:
        PartialStream(std::shared_ptr<Formats::IO::Stream> stream, std::streampos start, std::streampos end) : mStream(stream), mStart(start), mEnd(end) {

        }

        virtual void Seek(std::streampos pos) override { mStream->Seek(pos + mStart); }
		virtual void PushSeek(std::streampos pos) override { mStream->PushSeek(pos + mStart); }
		virtual std::streampos PopSeek() override { return mStream->PopSeek() - mStart; }
		virtual std::streampos GetSeek() override { return mStream->GetSeek() - mStart; }
		virtual void AlignSeek(std::streampos alignment) { mStream->Seek(GetSeek() = (GetSeek() % alignment == 0) ? GetSeek() : alignment - (GetSeek() % alignment) + GetSeek()); }

        virtual std::string ReadZeroTerminatedString(F_U32 allocation = FORMATS_IO_STREAM_READ_STRING_DEFAULTALLOCATION) override { return mStream->ReadZeroTerminatedString(allocation); }
		virtual void WriteZeroTerminatedString(std::string value) override { mStream->WriteZeroTerminatedString(value); }

        virtual void SetEndianness(Formats::IO::Endianness endianness) override { mStream->SetEndianness(endianness); }

        virtual F_S8 ReadS8() override { return mStream->ReadS8(); }
		virtual F_S16 ReadS16() override { return mStream->ReadS16(); }
		virtual F_S24 ReadS24() override { return mStream->ReadS24(); }
		virtual F_S32 ReadS32() override { return mStream->ReadS32(); }
		virtual F_S64 ReadS64() override { return mStream->ReadS64(); }

		virtual F_U8 ReadU8() override { return mStream->ReadU8(); }
		virtual F_U16 ReadU16() override { return mStream->ReadU16(); }
		virtual F_U24 ReadU24() override { return mStream->ReadU24(); }
		virtual F_U32 ReadU32() override { return mStream->ReadU32(); }
		virtual F_U64 ReadU64() override { return mStream->ReadU64(); }

		virtual F_F32 ReadF32() override { return mStream->ReadF32(); }
		virtual F_F64 ReadF64() override { return mStream->ReadF64(); }

		virtual void WriteS8(F_S8 value) override { mStream->WriteS8(value); }
		virtual void WriteS16(F_S16 value) override { mStream->WriteS16(value); }
		virtual void WriteS24(F_S24 value) override { mStream->WriteS24(value); }
		virtual void WriteS32(F_S32 value) override { mStream->WriteS32(value); }
		virtual void WriteS64(F_S64 value) override { mStream->WriteS64(value); }

		virtual void WriteU8(F_U8 value) override { mStream->WriteU8(value); }
		virtual void WriteU16(F_U16 value) override { mStream->WriteU16(value); }
		virtual void WriteU24(F_U24 value) override { mStream->WriteU24(value); }
		virtual void WriteU32(F_U32 value) override { mStream->WriteU32(value); }
		virtual void WriteU64(F_U64 value) override { mStream->WriteU64(value); }

		virtual void WriteF32(F_F32 value) override { mStream->WriteF32(value); }
		virtual void WriteF64(F_F64 value) override { mStream->WriteF64(value); }

        virtual void ReadBytes(void* out, F_U32 length) override { mStream->ReadBytes(out, length); }
		virtual void WriteBytes(const void* in, F_U32 length) override { mStream->WriteBytes(in, length); }

        virtual std::shared_ptr<F_U8[]> GetBuffer() override
        {
            mStream->PushSeek(mStart);

            F_UT bufferLength = GetBufferLength();
            F_U8* buffer = new F_U8[bufferLength];
            mStream->ReadBytes(buffer, bufferLength);

            mStream->PopSeek();

			return std::shared_ptr<F_U8[]>(buffer);
        }
		virtual F_UT GetBufferLength() override
        {
            return mEnd - mStart;
        }

    protected:
        std::shared_ptr<Formats::IO::Stream> mStream;
        std::streampos mStart;
        std::streampos mEnd;
    };
}