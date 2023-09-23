#include <Formats/IO/Streams/Buffer/EndianReaders/Big.h>

#include <algorithm>

namespace Formats::IO::Streams::Buffer::EndianReaders {
    void Big::ReadBytesWithEndian(void* out, F_UT length) {
        mParentStream->ReadBytes(out, length);
#if (FORMATS_BIGENDIAN)
			std::reverse(reinterpret_cast<F_U8*>(out), reinterpret_cast<F_U8*>(out) + length);
#endif
    }
    void Big::WriteBytesWithEndian(void* in, F_UT length) {
#if (FORMATS_BIGENDIAN)
			F_U8* reversed = new F_U8[length];
			memcpy(reversed, in, length);
			std::reverse(reinterpret_cast<F_U8*>(reversed), reinterpret_cast<F_U8*>(reversed) + length);
            mParentStream->WriteBytes(reversed, length);
#else
            mParentStream->WriteBytes(in, length);
#endif
    }
}