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

#include <yaml-cpp/yaml.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Array::Array(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType Array::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::Array;
	}

	bool Array::Parse(Formats::IO::BinaryIOStream& bStream) {
		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V7::NodeType::Array)
			return false;

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
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Array> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Bool: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Bool> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Bool>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Double: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Double> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Double>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::FileData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::FileData> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::FileData>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Float: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Float> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Float>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Int> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Int64> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int64>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Null: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Null> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Null>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::PlainHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::String: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::String> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::String>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::StringHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringTable: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::StringTable> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::UInt> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::UInt64> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt64>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::ValueHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>(mParentBYML);
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

		bStream.WriteU24(mNodes.size());

		for (std::vector<std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>>::iterator it = mNodes.begin(); it != mNodes.end(); ++it) {
			bStream.WriteU8(it->get()->GetNodeType());
		}

		bStream.AlignSeek(4);

		std::streampos nodeEnd = bStream.GetSeek() + (std::streampos)(0x4 * mNodes.size());

		for (std::vector<std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>>::iterator it = mNodes.begin(); it != mNodes.end(); ++it) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = it->get()->GetNodeType();

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V7::NodeType::Array: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Bool: {
					it->get()->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Double: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::FileData: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Float: {
					it->get()->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int: {
					it->get()->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int64: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Null: {
					it->get()->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::PlainHash: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::String: {
					it->get()->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringHash: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringTable: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt: {
					it->get()->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt64: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::ValueHash: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					it->get()->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
			}
		}

		bStream.Seek(nodeEnd);

		return true;
	}

	F_U32 Array::GetNodeCount() {
		return mNodes.size();
	}
	std::shared_ptr<Formats::Resources::BYML::Node> Array::GetNode(F_U32 index) {
		return mNodes.at(index);
	}

	void Array::EmitYAML(YAML::Emitter& out) {
		out << YAML::BeginSeq;

		for (std::shared_ptr<Formats::Resources::BYML::Node> node : mNodes) {
			node->EmitYAML(out);
		}

		out << YAML::EndSeq;
	}
}