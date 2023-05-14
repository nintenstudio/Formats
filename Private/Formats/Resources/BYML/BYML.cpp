#include <Formats/Resources/BYML/BYML.h>

#include <Formats/IO/BinaryIOStream_Versions/Little.h>
#include <Formats/IO/BinaryIOStream_Versions/Big.h>

namespace Formats::Resources::BYML {
	bool BYML::ParseBaseInfo() {
		char signature[4];
		mStream->read(signature, 4);

		if (signature == "YB") {
			mEndianness = Formats::IO::Endianness::LITTLE;
			mBStream = std::make_shared<Formats::IO::BinaryIOStream_Versions::Little>(*mStream);
		}
		else if (signature == "BY") {
			mEndianness = Formats::IO::Endianness::BIG;
			mBStream = std::make_shared<Formats::IO::BinaryIOStream_Versions::Big>(*mStream);
		}
		else
			return false;

		mVersion = mBStream->ReadUShort();

		return false;
	}
}