#include <Formats/Resources/BYML/Versions/V7/Nodes/Float.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Float::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadFloat();

		return true;
	}
	bool Float::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteFloat(mValue);

		return true;
	}
}