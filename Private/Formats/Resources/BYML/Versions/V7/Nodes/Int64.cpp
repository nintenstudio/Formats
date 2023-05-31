#include <Formats/Resources/BYML/Versions/V7/Nodes/Int64.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Int64::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadS64();

		return true;
	}
	bool Int64::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteS64(mValue);

		return true;
	}
}