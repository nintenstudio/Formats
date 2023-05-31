#include <Formats/Resources/BYML/Versions/V7/Nodes/Int64.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Int64::Parse(Formats::IO::BinaryIOStream& bStream) {

		return false;
	}
	bool Int64::Serialize(Formats::IO::BinaryIOStream& bStream) {

		return true;
	}
}