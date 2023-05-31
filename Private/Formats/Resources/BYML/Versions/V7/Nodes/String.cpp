#include <Formats/Resources/BYML/Versions/V7/Nodes/String.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool String::Parse(Formats::IO::BinaryIOStream& bStream) {
		mIndex = bStream.ReadU32();

		return true;
	}
	bool String::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(mIndex);

		return true;
	}
}