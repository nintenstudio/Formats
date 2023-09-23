#pragma once

#include <Formats/IO/EndianReader.h>

namespace Formats::IO::Streams::Buffer::EndianReaders {
    class Little : public Formats::IO::EndianReader {
    public:
		Little(Formats::IO::Stream* parentStream) : Formats::IO::EndianReader::EndianReader(parentStream) {

		}

        virtual void ReadBytesWithEndian(void* out, F_UT length) override;
		virtual void WriteBytesWithEndian(void* in, F_UT length) override;
    };
}