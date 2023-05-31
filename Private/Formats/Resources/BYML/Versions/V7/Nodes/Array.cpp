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

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool Array::Parse(Formats::IO::BinaryIOStream& bStream) {
		std::streampos nodeStart = bStream.GetSeek();

		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V7::NodeType::Array) {
			bStream.Seek(nodeStart);
			return false;
		}

		F_U32 numEntries = bStream.ReadU24();

		for (F_U32 i = 0; i < numEntries; i++) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = (Formats::Resources::BYML::Versions::V7::NodeType::NodeType)bStream.ReadS8();

			mNodeTypes.push_back(nodeType);
		}

		bStream.AlignSeek(4);

		for (F_U32 i = 0; i < numEntries; i++) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = mNodeTypes.at(i);

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V7::NodeType::Array: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Array> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Bool: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Bool> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Bool>();
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Double: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Double> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Double>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::FileData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::FileData> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::FileData>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Float: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Float> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Float>();
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Int> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int>();
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Int64> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int64>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Null: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Null> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Null>();
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::PlainHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::String: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::String> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::String>();
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::StringHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringTable: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::StringTable> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::UInt> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt>();
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::UInt64> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt64>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::ValueHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>();
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
			}
		}

		return true;
	}
	bool Array::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteS8(Formats::Resources::BYML::Versions::V7::NodeType::Array);


		return true;
	}
}