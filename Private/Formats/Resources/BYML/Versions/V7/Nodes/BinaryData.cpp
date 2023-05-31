#include <Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	BinaryData::~BinaryData() {
		delete mData;
	}

	bool BinaryData::Parse(Formats::IO::BinaryIOStream& bStream) {
		mDataSize = bStream.ReadU32();


		return true;
	}
	bool BinaryData::Serialize(Formats::IO::BinaryIOStream& bStream) {

		return true;
	}
}