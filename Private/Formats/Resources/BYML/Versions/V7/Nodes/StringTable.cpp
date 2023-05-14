#include <Formats/Resources/BYML/Versions/7/Nodes/StringTable.h>

#include <Formats/Resources/BYML/Versions/7/NodeType.h>

#include <cassert>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool StringTable::Parse() {
		assert(mParent->mBStream->ReadByte() == Formats::Resources::BYML::Versions::V7::NodeType::StringTable);

		mNumEntries = mParent->mBStream->ReadUInt() << 8 >> 8;
	}
	bool StringTable::Serialize() {
		mParent->mBStream->WriteByte(Formats::Resources::BYML::Versions::V7::NodeType::StringTable);
	}
}