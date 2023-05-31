#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool UInt::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadU32();

		return true;
	}
	bool UInt::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(mValue);

		return true;
	}
}