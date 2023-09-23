#include <Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	BinaryData::BinaryData(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	BinaryData::~BinaryData() {
		delete mData;
	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType BinaryData::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::BinaryData;
	}

	bool BinaryData::Parse(Formats::IO::Stream& bStream) {
		delete mData;

		mDataSize = bStream.ReadU32();

		mData = new F_U8[mDataSize];
		bStream.ReadBytes(mData, mDataSize);

		return true;
	}
	bool BinaryData::Serialize(Formats::IO::Stream& bStream) {
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