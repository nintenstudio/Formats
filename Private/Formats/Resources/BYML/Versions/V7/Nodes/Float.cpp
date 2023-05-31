#include <Formats/Resources/BYML/Versions/V7/Nodes/Float.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Float::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadF32();

		return true;
	}
	bool Float::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteF32(mValue);

		return true;
	}
}