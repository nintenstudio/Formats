#include <Formats/Resources/BYML/Versions/V4/Nodes/BinaryData.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	BinaryData::BinaryData(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

	}

	BinaryData::~BinaryData() {
		delete mData;
	}

	bool BinaryData::Parse(Formats::IO::BinaryIOStream& bStream) {
		delete mData;

		mDataSize = bStream.ReadU32();

		mData = new F_U8[mDataSize];
		bStream.ReadBytes(mData, mDataSize);

		return true;
	}
	bool BinaryData::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(mDataSize);

		bStream.WriteBytes(mData, mDataSize);

		return true;
	}

	F_U8* BinaryData::GetData() {
		return mData;
	}
	F_U32 BinaryData::GetDataSize() {
		return mDataSize;
	}

	void BinaryData::EmitYAML(YAML::Emitter& out) {
		out << "BinaryData!";
	}
}