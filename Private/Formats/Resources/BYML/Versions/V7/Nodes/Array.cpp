#include <Formats/Resources/BYML/Versions/V7/Nodes/Array.h>

#include <cassert>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Array::Parse(Formats::IO::BinaryIOStream& bStream) {
		assert(bStream.ReadByte() == Formats::Resources::BYML::Versions::V7::NodeType::StringTable);
		UINT numEntries = bStream.ReadUInt24();

		for (UINT i = 0; i < numEntries; i++) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = (Formats::Resources::BYML::Versions::V7::NodeType::NodeType)bStream.ReadByte();

			mNodeTypes.push_back(nodeType);
		}

		bStream.AlignSeek(4);

		for (UINT i = 0; i < numEntries; i++) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = mNodeTypes.at(i);

			switch (nodeType) {
			case Formats::Resources::BYML::Versions::V7::NodeType::Array:
				std::streampos offset = bStream.ReadUInt();
				bStream.PushSeek(offset);
				Formats::Resources::BYML::Versions::V7::Nodes::Array* node = new Formats::Resources::BYML::Versions::V7::Nodes::Array();
				node->Parse(bStream);
				mNodes.push_back(node);
				bStream.PopSeek();
			case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData:
				std::streampos offset = bStream.ReadUInt();
				bStream.PushSeek(offset);
				Formats::Resources::BYML::Versions::V7::Nodes::BinaryData* node = new Formats::Resources::BYML::Versions::V7::Nodes::BinaryData();
				node->Parse(bStream);
				mNodes.push_back(node);
				bStream.PopSeek();
			}
		}

		return true;
	}
	bool Array::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteByte(Formats::Resources::BYML::Versions::V7::NodeType::StringTable);


		return true;
	}
}