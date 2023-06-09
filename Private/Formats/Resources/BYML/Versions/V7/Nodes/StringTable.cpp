#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>
#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	StringTable::StringTable(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType StringTable::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::StringTable;
	}

	bool StringTable::Parse(Formats::IO::BinaryIOStream& bStream) {
		std::streampos nodeStart = bStream.GetSeek();

		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V7::NodeType::StringTable)
			return false;

		mStrings.clear();

		F_U24 numEntries = bStream.ReadU24();

		std::streampos stringsEnd;
		mStrings.reserve(numEntries + 1);
		for (F_U32 i = 0; i < numEntries + 1; i++) {
			std::streampos stringOffset = bStream.ReadU32();
			bStream.PushSeek(nodeStart + stringOffset);
			
			mStrings.push_back(bStream.ReadZeroTerminatedString());

			stringsEnd = bStream.GetSeek();
			bStream.PopSeek();
		}

		bStream.Seek(stringsEnd);
		return true;
	}
	bool StringTable::Serialize(Formats::IO::BinaryIOStream& bStream) {
		std::streampos nodeStart = bStream.GetSeek();

		bStream.WriteU8(Formats::Resources::BYML::Versions::V7::NodeType::StringTable);

		bStream.WriteU24(mStrings.size() - 1);
		
		std::streampos stringOffsetsStart = bStream.GetSeek();
		std::streampos stringsStart = stringOffsetsStart + (std::streampos)(sizeof(F_U32) * mStrings.size());
		std::streampos stringsEnd;
		bStream.PushSeek(stringsStart);
		for (F_U32 i = 0; i < mStrings.size(); i++) {
			std::streampos stringPos = bStream.GetSeek();
			bStream.WriteZeroTerminatedString(mStrings.at(i));
			bStream.PushSeek(stringOffsetsStart + (std::streampos)(sizeof(F_U32) * i));
			bStream.WriteU32(stringPos - nodeStart);
			bStream.PopSeek();
		}
		bStream.AlignSeek(4);
		stringsEnd = bStream.GetSeek();
		bStream.PopSeek();

		bStream.Seek(stringsEnd);
		return true;
	}

	void StringTable::EmitYAML(YAML::Emitter& out) {

	}
}