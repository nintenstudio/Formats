#pragma once

#include <Formats/IO/BinaryIOStreamBasic.h>

#include <ios>

namespace Formats::IO::BinaryIOStreamBasics::Buffer {
    class Buffer : public Formats::IO::BinaryIOStreamBasic {
    public:
        Buffer(std::shared_ptr<F_U8> buffer, F_UT bufferSize);
        Buffer(F_UT bufferSize);

        virtual std::shared_ptr<BinaryIOStream> Factory(Formats::IO::Endianness endianness) override;

        virtual void ReadBytes(void* out, F_U32 length) override;
		virtual void WriteBytes(const void* in, F_U32 length) override;

		virtual std::shared_ptr<F_U8> GetBuffer() override;
		virtual F_UT GetBufferLength() override;

    protected:
        std::shared_ptr<F_U8> mBuffer;
        F_UT mBufferSize;
        std::streampos mSeek;
    };
}