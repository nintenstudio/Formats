#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool UInt64::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadU64();

		return true;
	}
	bool UInt64::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU64(mValue);

		return true;
	}
}