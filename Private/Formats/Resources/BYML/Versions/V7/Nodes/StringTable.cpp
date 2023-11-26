#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>
#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	StringTable::StringTable(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType StringTable::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::StringTable;
	}

	bool StringTable::Parse(Formats::IO::Stream& stream) {
		std::streampos nodeStart = stream.GetSeek();

		if (stream.ReadU8() != Formats::Resources::BYML::Versions::V7::NodeType::StringTable)
			return false;

		mStrings.clear();

		F_U24 numEntries = stream.ReadU24();

		std::streampos stringsEnd;
		mStrings.reserve(numEntries);
		for (F_U32 i = 0; i < numEntries; i++) {
			std::streampos stringOffset = stream.ReadU32();
			stream.PushSeek(nodeStart + stringOffset);
			
			mStrings.push_back(stream.ReadZeroTerminatedString());

			stringsEnd = stream.GetSeek();
			stream.PopSeek();
		}
		stream.ReadU32(); // The end-of-list pointer

		stream.Seek(stringsEnd);
		return true;
	}
	bool StringTable::Serialize(Formats::IO::Stream& stream) {
		std::streampos nodeStart = stream.GetSeek();

		stream.WriteU8(Formats::Resources::BYML::Versions::V7::NodeType::StringTable);

		stream.WriteU24(mStrings.size());
		
		std::streampos stringOffsetsStart = stream.GetSeek();
		std::streampos stringsStart = stringOffsetsStart + (std::streampos)(sizeof(F_U32) * (mStrings.size() + 1));
		std::streampos stringsEnd;
		stream.PushSeek(stringsStart);
		for (F_U32 i = 0; i < mStrings.size(); i++) {
			std::streampos stringPos = stream.GetSeek();
			stream.WriteZeroTerminatedString(mStrings.at(i));
			stream.PushSeek(stringOffsetsStart + (std::streampos)(sizeof(F_U32) * i));
			stream.WriteU32(stringPos - nodeStart);
			stream.PopSeek();
		}
		stream.AlignSeek(4);
		stringsEnd = stream.GetSeek();
		stream.PushSeek(stringOffsetsStart + (std::streampos)(sizeof(F_U32) * mStrings.size()));
		stream.WriteU32(stringsEnd - nodeStart);
		stream.PopSeek();
		stream.PopSeek();

		stream.Seek(stringsEnd);
		return true;
	}

	std::string StringTable::GetString(F_U32 index) {
		return mStrings.at(index);
	}
	F_U32 StringTable::AddString(std::string string) {
		F_U32 index = GetStringIndex(string);
		if (index != std::numeric_limits<F_U32>::max())
			return index;

		mStrings.push_back(string);
		return mStrings.size() - 1;
	}
	F_U32 StringTable::GetStringIndex(std::string string) {
		std::vector<std::string>::iterator it = std::find(mStrings.begin(), mStrings.end(), string);

		return it != mStrings.end() ? it - mStrings.begin() : std::numeric_limits<F_U32>::max();
	}

	void StringTable::EmitYAML(YAML::Emitter& out) {

	}
	bool StringTable::LoadYAML(YAML::Node& node) {
		return true;
	}
}