#include <Formats/Resources/BFRES/BFRES.h>

namespace Formats::Resources::BFRES {
	std::shared_ptr<BFRES> BFRES::Factory(std::iostream* stream) {

		return nullptr;
	}

	bool BFRES::ParseBaseInfo() {
		char signature[4];
		mStream->ReadBytes(signature, 4);

		if (signature != "FRES")
			return false;

		unsigned int rawVersion;
		mStream->ReadBytes((char*)&rawVersion, 4);

		mVersionMajor1 = rawVersion >> 24;
		mVersionMajor2 = rawVersion >> 16 & 0xFF;
		mVersionMinor1 = rawVersion >> 8 & 0xFF;
		mVersionMinor2 = rawVersion & 0xFF;

		return true;
	}
}