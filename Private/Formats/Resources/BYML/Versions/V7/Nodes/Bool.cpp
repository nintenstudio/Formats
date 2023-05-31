#include <Formats/Resources/BYML/Versions/V7/Nodes/Bool.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Bool::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadUInt();

		return true;
	}
	bool Bool::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteUInt(mValue);

		return true;
	}
}