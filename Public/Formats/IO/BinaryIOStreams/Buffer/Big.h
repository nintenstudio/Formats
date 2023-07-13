#pragma once

#include <Formats/IO/BinaryIOStreams/Buffer/Buffer.h>

#include <algorithm>

namespace Formats::IO::BinaryIOStreams::Buffer {
	class Big : public Formats::IO::BinaryIOStreams::Buffer::Buffer {
	public:
		Big(std::shared_ptr<F_U8[]> buffer, F_UT bufferSize) : Formats::IO::BinaryIOStreams::Buffer::Buffer(buffer, bufferSize) {

		}

	protected:
		virtual void ReadBytesWithEndian(void* out, F_UT length) override {
            ReadBytes(out, length);
#if (!FORMATS_BIGENDIAN)
			std::reverse(reinterpret_cast<F_U8*>(out), reinterpret_cast<F_U8*>(out) + length);
#endif
		}
		virtual void WriteBytesWithEndian(void* in, F_UT length) override {
#if (!FORMATS_BIGENDIAN)
			F_U8* reversed = new F_U8[length];
			memcpy(reversed, in, length);
			std::reverse(reinterpret_cast<F_U8*>(reversed), reinterpret_cast<F_U8*>(reversed) + length);
            WriteBytes(reversed, length);
#else
            WriteBytes(in, length);
#endif
		}
	};
}