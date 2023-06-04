#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>
#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	StringTable::StringTable(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	bool StringTable::Parse(Formats::IO::BinaryIOStream& bStream) {
		std::streampos nodeStart = bStream.GetSeek();

		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V7::NodeType::StringTable)
			return false;

		mStrings.clear();

		F_U24 numEntries = bStream.ReadU24();
		mStrings.reserve(numEntries);
		for (F_U32 i = 0; i < numEntries + 1; i++) {
			std::streampos stringOffset = bStream.ReadU32();
			bStream.PushSeek(nodeStart + stringOffset);
			
			mStrings.push_back(bStream.ReadZeroTerminatedString());

			bStream.PopSeek();
		}

		return true;
	}
	bool StringTable::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteS8(Formats::Resources::BYML::Versions::V7::NodeType::StringTable);
		
		std::streampos stringOffsetsStart = bStream.GetSeek();
		std::streampos stringsStart = stringOffsetsStart + (std::streampos)(sizeof(F_U32) * mStrings.size() + 1);
		bStream.PushSeek(stringsStart);
		for (F_U32 i = 0; i < mStrings.size() + 1; i++) {
			std::streampos stringPos = bStream.GetSeek();
			bStream.WriteZeroTerminatedString(mStrings.at(i));
			bStream.PushSeek(stringOffsetsStart + (std::streampos)(sizeof(F_U32) * i));
			bStream.WriteU32(stringPos);
			bStream.PopSeek();
		}
		bStream.PopSeek();

		return true;
	}

	void StringTable::EmitYAML(YAML::Emitter& out) {

	}
}