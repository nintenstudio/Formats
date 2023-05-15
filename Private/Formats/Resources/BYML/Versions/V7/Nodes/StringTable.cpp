#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>
#include <Formats/Aliases/Primitives.h>

#include <cassert>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool StringTable::Parse(Formats::IO::BinaryIOStream& bStream) {
		mStrings.clear();

		std::streampos nodeStart = bStream.GetSeek();
		assert(bStream.ReadByte() == Formats::Resources::BYML::Versions::V7::NodeType::StringTable);

		UINT24 numEntries = bStream.ReadUInt24();
		mStrings.resize(numEntries);
		for (UINT i = 0; i < numEntries + 1; i++) {
			std::streampos stringOffset = bStream.ReadUInt();
			bStream.PushSeek(nodeStart + stringOffset);
			
			mStrings.push_back(bStream.ReadZeroTerminatedString());

			bStream.PopSeek();
		}

		return true;
	}
	bool StringTable::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteByte(Formats::Resources::BYML::Versions::V7::NodeType::StringTable);
		
		std::streampos stringOffsetsStart = bStream.GetSeek();
		std::streampos stringsStart = stringOffsetsStart + (std::streampos)(sizeof(UINT) * mStrings.size() + 1);
		bStream.PushSeek(stringsStart);
		for (UINT i = 0; i < mStrings.size() + 1; i++) {
			std::streampos stringPos = bStream.GetSeek();
			bStream.WriteZeroTerminatedString(mStrings.at(i));
			bStream.PushSeek(stringOffsetsStart + (std::streampos)(sizeof(UINT) * i));
			bStream.WriteUInt(stringPos);
			bStream.PopSeek();
		}
		bStream.PopSeek();

		return true;
	}
}