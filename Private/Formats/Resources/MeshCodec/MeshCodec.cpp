#include <Formats/Resources/MeshCodec/MeshCodec.h>

#include <Formats/Resources/MeshCodec/Versions/V1.1.0.0/V1.1.0.0.h>

namespace Formats::Resources::MeshCodec {
	std::shared_ptr<MeshCodec> MeshCodec::Factory(std::shared_ptr<Formats::IO::Stream> stream) {
		std::shared_ptr<Formats::Resources::MeshCodec::Versions::V1_1_0_0::V1_1_0_0> v1_1_0_0 = std::make_shared<Formats::Resources::MeshCodec::Versions::V1_1_0_0::V1_1_0_0>();
		v1_1_0_0->SetStream(stream);
		if (v1_1_0_0->Parse())
			return v1_1_0_0;

		return nullptr;
	}

	void MeshCodec::SetStream(std::shared_ptr<Formats::IO::Stream> stream) {
		Formats::Resource::SetStream(stream);

		mStream->SetEndianness(Formats::IO::Endianness::LITTLE); // Unsure if endianess is specified in the format.
	}

	bool MeshCodec::ParseBaseInfo() {
		char signature[5];
		mStream->ReadBytes(&signature, 4);
		signature[4] = '\0';

		if (strcmp(signature, "MCPK") != 0)
			return false;

		mStream->ReadBytes(&mVersion, 4);

		mStream->SetEndianness(Formats::IO::Endianness::LITTLE); // Unsure if endianess is specified in the format.

		return true;
	}
	bool MeshCodec::WriteBaseInfo() {
		F_U16 headerSize = 0x50;
		mStream->WriteBytes(&headerSize, 2);

		mStream->WriteBytes(&mVersion, 2);

		char signature[5] = "6PK0";
		mStream->WriteBytes(&signature, 4);
		signature[4] = '\0';

		mStream->SetEndianness(Formats::IO::Endianness::LITTLE); // Unsure if endianess is specified in the format.

		return true;
	}
}