#include <Formats/Resources/TXTG/TXTG.h>

#include <Formats/Resources/TXTG/Versions/V0x11/V0x11.h>

namespace Formats::Resources::TXTG {
	std::shared_ptr<TXTG> TXTG::Factory(std::shared_ptr<Formats::IO::Stream> stream) {
		std::shared_ptr<Formats::Resources::TXTG::Versions::V0x11::V0x11> v0x11 = std::make_shared<Formats::Resources::TXTG::Versions::V0x11::V0x11>();
		v0x11->SetStream(stream);
		if (v0x11->Parse())
			return v0x11;

		return nullptr;
	}

	void TXTG::SetStream(std::shared_ptr<Formats::IO::Stream> stream) {
		Formats::Resource::SetStream(stream);

		mStream->SetEndianness(Formats::IO::Endianness::LITTLE); // Unsure if endianess is specified in the format.
	}

	bool TXTG::ParseBaseInfo() {
		F_U16 headerSize;
		mStream->ReadBytes(&headerSize, 2);

		mStream->ReadBytes(&mVersion, 2);

		char signature[5];
		mStream->ReadBytes(&signature, 4);
		signature[4] = '\0';

		if (strcmp(signature, "6PK0") != 0)
			return false;

		mStream->SetEndianness(Formats::IO::Endianness::LITTLE); // Unsure if endianess is specified in the format.

		return true;
	}
	bool TXTG::WriteBaseInfo() {
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