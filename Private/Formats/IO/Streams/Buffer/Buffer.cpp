#include <Formats/IO/Streams/Buffer/Buffer.h>

#include <Formats/IO/Streams/Buffer/EndianReaders/Little.h>
#include <Formats/IO/Streams/Buffer/EndianReaders/Big.h>

#include <cassert>

namespace Formats::IO::Streams::Buffer {
    Buffer::Buffer(std::shared_ptr<F_U8[]> buffer, F_UT bufferSize) : mBuffer(buffer), mBufferSize(bufferSize), mSeek(0), mSeekStack() {

    }

    void Buffer::Seek(std::streampos pos) {
        mSeek = pos;
    }
    void Buffer::PushSeek(std::streampos pos) {
        mSeekStack.push_back(mSeek);
        mSeek = pos;
    }
    std::streampos Buffer::PopSeek() {
        std::streampos res = mSeek;
        mSeek = mSeekStack.back();
        mSeekStack.pop_back();
        return res;
    }
    std::streampos Buffer::GetSeek() {
        return mSeek;
    }
    void Buffer::AlignSeek(std::streampos alignment) {
		mSeek = (mSeek % alignment == 0) ? mSeek : alignment - (mSeek % alignment) + mSeek;
	}

    std::string Buffer::ReadZeroTerminatedString(F_U32 allocation) {
		std::string res;
		res.reserve(allocation);

		char currentChar;
		while(ReadBytes(&currentChar, 1), currentChar != '\0') {
			res += currentChar;
		}

		return res;
	}
	void Buffer::WriteZeroTerminatedString(std::string value) {
		WriteBytes(reinterpret_cast<const void*>(value.c_str()), value.size() + 1);
	}

    void Buffer::SetEndianness(Formats::IO::Endianness endianness) {
        switch (endianness) {
            case Formats::IO::Endianness::LITTLE:
                mEndianReader = std::make_shared<Formats::IO::Streams::Buffer::EndianReaders::Little>(this);
                break;
            case Formats::IO::Endianness::BIG:
                mEndianReader = std::make_shared<Formats::IO::Streams::Buffer::EndianReaders::Big>(this);
                break;
            default:
                assert(false); // endianness is invalid!
        }
    }

    void Buffer::ReadBytes(void* out, F_U32 size) {
        assert(mSeek < (std::streampos)mBufferSize);

        memcpy(out, mBuffer.get() + mSeek, size);
        mSeek += size;
    }
    void Buffer::WriteBytes(const void* in, F_U32 size) {
        assert(mSeek < (std::streampos)mBufferSize);

        memcpy(mBuffer.get() + mSeek, in, size);
        mSeek += size;
    }

    std::shared_ptr<F_U8[]> Buffer::GetBuffer() {
        return mBuffer;
    }
    F_UT Buffer::GetBufferLength() {
        return mBufferSize;
    }
}