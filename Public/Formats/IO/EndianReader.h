#pragma once

#include <Formats/IO/Stream.h>
#include <Formats/Aliases/Primitives.h>

namespace Formats::IO {
    class EndianReader {
    public:
        EndianReader(Formats::IO::Stream* parentStream) : mParentStream(parentStream) {

        }

        virtual void ReadBytesWithEndian(void* out, F_UT length) = 0;
		virtual void WriteBytesWithEndian(void* in, F_UT length) = 0;

    protected:
        Formats::IO::Stream* mParentStream;
    };
}