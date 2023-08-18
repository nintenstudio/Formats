#pragma once

#include <Formats/IO/BinaryIOStreamBasic.h>
#include <memory>

namespace Formats::Resources::ZSTD {
	class ZSTDBackend {
	public:
		static std::shared_ptr<Formats::IO::BinaryIOStreamBasic> Decompress(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream);
		static std::shared_ptr<Formats::IO::BinaryIOStreamBasic> Compress(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream);

		static bool AddDict(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream, F_U32 compressionLevel = 5);

	protected:
		static void InitThread();
	};
}