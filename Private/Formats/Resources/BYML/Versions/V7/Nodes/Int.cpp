#include <Formats/Resources/BYML/Versions/V7/Nodes/Int.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Int::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadInt();

		return true;
	}
	bool Int::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteInt(mValue);

		return true;
	}
}