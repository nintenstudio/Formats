#include <Formats/IO/BinaryIOStreamBasics/Buffer/Buffer.h>

#include <Formats/IO/BinaryIOStreams/Buffer/Little.h>
#include <Formats/IO/BinaryIOStreams/Buffer/Big.h>
#include <cassert>

namespace Formats::IO::BinaryIOStreamBasics::Buffer {
    Buffer::Buffer(std::shared_ptr<F_U8> buffer, F_UT bufferSize) : mBuffer(buffer), mBufferSize(bufferSize), mSeek(0) {
        
    }
    Buffer::Buffer(F_UT bufferSize) : mBuffer(new F_U8[bufferSize]), mBufferSize(bufferSize), mSeek(0) {

    }

    std::shared_ptr<Formats::IO::BinaryIOStream> Buffer::Factory(Formats::IO::Endianness endianness) {
        assert(endianness == Formats::IO::Endianness::LITTLE || endianness == Formats::IO::Endianness::BIG);

        if (endianness == Formats::IO::Endianness::LITTLE)
            return std::make_shared<Formats::IO::BinaryIOStreams::Buffer::Little>(mBuffer, mBufferSize);
        else
            return std::make_shared<Formats::IO::BinaryIOStreams::Buffer::Big>(mBuffer, mBufferSize);
    }

    void Buffer::ReadBytes(void* out, F_U32 length) {
        assert(mSeek < mBufferSize);

        memcpy(out, mBuffer.get() + mSeek, length);
        mSeek += length;
    }
    void Buffer::WriteBytes(const void* in, F_U32 length) {
        assert(mSeek < mBufferSize);

        memcpy(mBuffer.get() + mSeek, in, length);
        mSeek += length;
    }

    std::shared_ptr<F_U8> Buffer::GetBuffer() {
        return mBuffer;
    }
    F_UT Buffer::GetBufferLength() {
        return mBufferSize;
    }
}