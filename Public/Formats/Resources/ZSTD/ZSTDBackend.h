#pragma once

#include <Formats/IO/Stream.h>
#include <memory>

namespace Formats::Resources::ZSTD {
	class ZSTDBackend {
	public:
		static std::shared_ptr<Formats::IO::Stream> Decompress(std::shared_ptr<Formats::IO::Stream> stream);
		static std::shared_ptr<Formats::IO::Stream> Compress(std::shared_ptr<Formats::IO::Stream> stream);
		static std::shared_ptr<Formats::IO::Stream> DecompressMeshCodec(std::shared_ptr<Formats::IO::Stream> stream);
		static std::shared_ptr<Formats::IO::Stream> CompressMeshCodec(std::shared_ptr<Formats::IO::Stream> stream);

		static bool AddDict(std::shared_ptr<Formats::IO::Stream> stream, F_U32 compressionLevel = 5);

	protected:
		static void InitThread();
	};
}