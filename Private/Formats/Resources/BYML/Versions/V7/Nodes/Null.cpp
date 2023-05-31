#include <Formats/Resources/BYML/Versions/V7/Nodes/Null.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Null::Parse(Formats::IO::BinaryIOStream& bStream) {
		bStream.ReadUInt();

		return true;
	}
	bool Null::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteUInt(0);

		return true;
	}
}