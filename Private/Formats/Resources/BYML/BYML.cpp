#include <Formats/Resources/BYML/BYML.h>

#include <Formats/Resources/BYML/Versions/V7/V7.h>

namespace Formats::Resources::BYML {
	std::shared_ptr<BYML> BYML::Factory(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		std::shared_ptr<Formats::Resources::BYML::Versions::V7::V7> v7 = std::make_shared<Formats::Resources::BYML::Versions::V7::V7>();
		v7->SetStream(stream);
		if (v7->Parse())
			return v7;

		return nullptr;
	}

	void BYML::SetStream(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		Formats::Resource::SetStream(stream);
		
		mBStream = stream->Factory(mEndianness);
	}

	bool BYML::ParseBaseInfo() {
		char signature[3];
		mStream->ReadBytes(&signature, 2);
		signature[2] = '\0';

		if (strcmp(signature, "YB") == 0)
			mEndianness = Formats::IO::Endianness::LITTLE;
		else if (strcmp(signature, "BY") == 0)
			mEndianness = Formats::IO::Endianness::BIG;
		else
			return false;

		mBStream = mStream->Factory(mEndianness);

		mVersion = mBStream->ReadU16();

		return true;
	}
	bool BYML::WriteBaseInfo() {
		if (mEndianness == Formats::IO::Endianness::LITTLE) {
			mStream->WriteBytes("YB", 2);
		}
		else {
			mStream->WriteBytes("BY", 2);
		}

		mBStream->WriteU16(mVersion);

		return true;
	}
}