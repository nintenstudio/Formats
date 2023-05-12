#include <Formats/Resources/BFRES.h>

namespace Formats::Resources {
	bool BFRES::Parse() {
		return false;
	}
	bool BFRES::Serialize() {
		return false;
	}
	bool BFRES::RequestParse(Formats::ResourceParsedCallback callback) {
		return false;
	}

	bool BFRES::ParseBaseInfo() {
		char signature[4];
		mStream->read(signature, 4);

		if (signature != "FRES")
			return false;

		unsigned int rawVersion;
		mStream->read((char*)&rawVersion, 4);

		mVersionMajor1 = rawVersion >> 24;
		mVersionMajor2 = rawVersion >> 16 & 0xFF;
		mVersionMinor1 = rawVersion >> 8 & 0xFF;
		mVersionMinor2 = rawVersion & 0xFF;

		return true;
	}
}