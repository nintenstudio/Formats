#include <Formats/Resources/BYML/Versions/V7/Nodes/Int.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Int::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadS32();

		return true;
	}
	bool Int::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteS32(mValue);

		return true;
	}
}