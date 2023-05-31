#include <Formats/Resources/BYML/BYML.h>

#include <Formats/Resources/BYML/Versions/V7/V7.h>

#include <Formats/IO/BinaryIOStream_Versions/Little.h>
#include <Formats/IO/BinaryIOStream_Versions/Big.h>

namespace Formats::Resources::BYML {
	std::shared_ptr<BYML> BYML::Factory(std::iostream* stream) {
		std::streampos startGPos = stream->tellg();
		std::streampos startPPos = stream->tellp();


		std::shared_ptr<Formats::Resources::BYML::Versions::V7::V7> v7 = std::make_shared<Formats::Resources::BYML::Versions::V7::V7>();
		v7->SetStream(stream);
		if (v7->Parse())
			return v7;
		stream->seekg(startGPos);
		stream->seekp(startPPos);

		return nullptr;
	}

	bool BYML::ParseBaseInfo() {
		char signature[3];
		mStream->read(signature, 2);
		signature[2] = '\0';

		if (strcmp(signature, "YB") == 0) {
			mEndianness = Formats::IO::Endianness::LITTLE;
			mBStream = std::make_shared<Formats::IO::BinaryIOStream_Versions::Little>(*mStream);
		}
		else if (strcmp(signature, "BY") == 0) {
			mEndianness = Formats::IO::Endianness::BIG;
			mBStream = std::make_shared<Formats::IO::BinaryIOStream_Versions::Big>(*mStream);
		}
		else
			return false;

		mVersion = mBStream->ReadU16();

		return true;
	}
}