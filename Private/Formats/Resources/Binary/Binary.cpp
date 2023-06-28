#include <Formats/Resources/Binary/Binary.h>

namespace Formats::Resources::Binary {
	bool Binary::Parse() {
		return true;
	}
	bool Binary::Serialize() {
		return true;
	}

	bool Binary::RequestParse(Formats::ResourceParsedCallback callback) {
		return false;
	}
}