#include <Formats/Resources/BYML/Versions/V7/Nodes/Array.h>

#include <Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Bool.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Double.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/FileData.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Float.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Int.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Int64.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Null.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/String.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Array::Parse(Formats::IO::BinaryIOStream& bStream) {
		std::streampos nodeStart = bStream.GetSeek();

		if (bStream.ReadUByte() != Formats::Resources::BYML::Versions::V7::NodeType::Array) {
			bStream.Seek(nodeStart);
			return false;
		}

		F_UINT numEntries = bStream.ReadUInt24();

		for (F_UINT i = 0; i < numEntries; i++) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = (Formats::Resources::BYML::Versions::V7::NodeType::NodeType)bStream.ReadByte();

			mNodeTypes.push_back(nodeType);
		}

		bStream.AlignSeek(4);

		for (F_UINT i = 0; i < numEntries; i++) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = mNodeTypes.at(i);

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V7::NodeType::Array: {
					std::streampos offset = bStream.ReadUInt();
					bStream.PushSeek(offset);
					Formats::Resources::BYML::Versions::V7::Nodes::Array* node = new Formats::Resources::BYML::Versions::V7::Nodes::Array();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					std::streampos offset = bStream.ReadUInt();
					bStream.PushSeek(offset);
					Formats::Resources::BYML::Versions::V7::Nodes::BinaryData* node = new Formats::Resources::BYML::Versions::V7::Nodes::BinaryData();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
				}
			}
		}

		return true;
	}
	bool Array::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteByte(Formats::Resources::BYML::Versions::V7::NodeType::StringTable);


		return true;
	}
}