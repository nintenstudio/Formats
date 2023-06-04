#include <Formats/Resources/BYML/Versions/V7/Nodes/FileData.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	FileData::FileData(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}
	FileData::~FileData() {
		delete mData;
	}

	bool FileData::Parse(Formats::IO::BinaryIOStream& bStream) {
		delete mData;

		mDataSize = bStream.ReadU32();
		mUkn0x4 = bStream.ReadU32();

		mData = new F_U8[mDataSize];
		bStream.ReadBytes(mData, mDataSize);

		return true;
	}
	bool FileData::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(mDataSize);
		bStream.WriteU32(mUkn0x4);

		bStream.WriteBytes(mData, mDataSize);

		return true;
	}

	F_U8* FileData::GetData() {
		return mData;
	}
	F_U32 FileData::GetDataSize() {
		return mDataSize;
	}

	void FileData::EmitYAML(YAML::Emitter& out) {
		out << "FileData!";
	}
}