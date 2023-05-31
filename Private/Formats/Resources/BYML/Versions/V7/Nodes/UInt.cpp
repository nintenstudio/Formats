#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool UInt::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadUInt();

		return true;
	}
	bool UInt::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteUInt(mValue);

		return true;
	}
}