#include <Formats/Resources/MeshCodec/Versions/V1.1.0.0/V1.1.0.0.h>

#include <Formats/Resources/ZSTD/ZSTDBackend.h>
#include <Formats/IO/Stream.h>
#include <Formats/IO/PartialStream.h>
#include <memory>

namespace Formats::Resources::MeshCodec::Versions::V1_1_0_0 {
	bool V1_1_0_0::Parse() {
		F_UT mcStart = mStream->GetSeek();

		if (!Formats::Resources::MeshCodec::MeshCodec::ParseBaseInfo())
			return false;

		if (mVersion[0] != 1 || mVersion[1] != 1 || mVersion[2] != 0 || mVersion[3] != 0)
			return false;

		mFlags = mStream->ReadU32();
		F_UT decompressedSize = (mFlags >> 5) << (mFlags & 0xf);

		mStream->Seek(mcStart + 0xc);

		std::shared_ptr<Formats::IO::Stream> decompressed = ZSTD::ZSTDBackend::DecompressMeshCodec(std::make_shared<Formats::IO::PartialStream>(mStream, mStream->GetSeek(), mStream->GetBufferLength() - 1));
		
		

		return false;
	}
	bool V1_1_0_0::Serialize() {
		return false;
	}
}