#include <Formats/Resources/BYML.h>

namespace Formats::Resources {
	bool BYML::Parse() {
		return false;
	}
	bool BYML::Serialize() {
		return false;
	}
	bool BYML::RequestParse(Formats::ResourceParsedCallback callback) {
		return false;
	}

	bool BYML::ParseBaseInfo() {
		char signature[4];
		mStream->read(signature, 4);

		if (signature == "YB")
			mEndianness = Formats::IO::Endianness::LITTLE;
		else if (signature == "BY")
			mEndianness = Formats::IO::Endianness::BIG;
		else
			return false;

		// FORMATS_TODO_FUNCTIONAL Implement.

		return false;
	}
}