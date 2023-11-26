#include <Formats/Resources/BYML/Versions/V7/Nodes/FileData.h>

#include <Formats/Utils/String.h>

#include <iomanip>
#include <sstream>
#include <string>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	FileData::FileData(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}
	FileData::~FileData() {
		delete mData;
	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType FileData::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::FileData;
	}

	bool FileData::Parse(Formats::IO::Stream& bStream) {
		delete mData;

		mDataSize = bStream.ReadU32();
		mUkn0x4 = bStream.ReadU32();

		mData = new F_U8[mDataSize];
		bStream.ReadBytes(mData, mDataSize);

		return true;
	}
	bool FileData::Serialize(Formats::IO::Stream& bStream) {
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
		out << YAML::LocalTag("filedata");

		std::stringstream stringstream;
		stringstream << std::hex;

		for (int i = 0; i < mDataSize; i++)
			stringstream << std::setw(2) << std::setfill('0') << (int)mData[i];

		out << stringstream.str();
		out << mData;
	}
	bool FileData::LoadYAML(YAML::Node& node) {
		delete mData;

		std::string hex = node.as<std::string>();
		if (hex.size() % 2 != 0)
			return false;
		mDataSize = hex.size() / 2;
		mData = new F_U8[mDataSize];

		for (F_U32 i = 0; i < hex.size() - 1; i += 2) {
			char upper = hex[i];
			char lower = hex[i + 1];

			mData[i / 2] = Formats::Utils::String::HexCharToByte(upper) * 16 + Formats::Utils::String::HexCharToByte(lower);
		}

		return true;
	}
}