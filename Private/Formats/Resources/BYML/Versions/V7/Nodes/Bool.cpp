#include <Formats/Resources/BYML/Versions/V7/Nodes/Bool.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Bool::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadU32();

		return true;
	}
	bool Bool::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(mValue);

		return true;
	}
}