#include <Formats/Resources/BYML/Versions/V7/Nodes/Double.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Double::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadF64();

		return true;
	}
	bool Double::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteF64(mValue);

		return true;
	}
}