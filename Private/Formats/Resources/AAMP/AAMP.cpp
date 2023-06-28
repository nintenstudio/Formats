#include <Formats/Resources/AAMP/AAMP.h>

namespace Formats::Resources::AAMP {
	std::shared_ptr<AAMP> AAMP::Factory(std::iostream* stream) {

		return nullptr;
	}

	bool AAMP::Parse() {
		return false;
	}
	bool AAMP::Serialize() {
		return false;
	}
	bool AAMP::RequestParse(Formats::ResourceParsedCallback callback) {
		return false;
	}
}