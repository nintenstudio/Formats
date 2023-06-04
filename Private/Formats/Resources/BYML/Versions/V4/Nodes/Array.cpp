#include <Formats/Resources/BYML/Versions/V4/Nodes/Array.h>

#include <Formats/Resources/BYML/Versions/V4/Nodes/BinaryData.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/Bool.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/Double.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/FileData.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/Float.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/Int.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/Int64.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/Null.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/String.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/StringHash.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/StringTable.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/UInt.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/UInt64.h>

#include <Formats/Resources/BYML/Versions/V4/NodeType.h>

#include <yaml-cpp/yaml.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	Array::Array(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

	}

	bool Array::Parse(Formats::IO::BinaryIOStream& bStream) {
		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V4::NodeType::Array)
			return false;

		F_U32 numEntries = bStream.ReadU24();

		for (F_U32 i = 0; i < numEntries; i++) {
			Formats::Resources::BYML::Versions::V4::NodeType::NodeType nodeType = (Formats::Resources::BYML::Versions::V4::NodeType::NodeType)bStream.ReadS8();

			mNodeTypes.push_back(nodeType);
		}

		bStream.AlignSeek(4);

		for (F_U32 i = 0; i < numEntries; i++) {
			Formats::Resources::BYML::Versions::V4::NodeType::NodeType nodeType = mNodeTypes.at(i);

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V4::NodeType::Array: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Array> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Array>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::BinaryData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::BinaryData> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::BinaryData>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Bool: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Bool> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Bool>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Double: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Double> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Double>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::FileData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::FileData> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::FileData>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Float: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Float> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Float>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Int: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Int> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Int>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Int64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Int64> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Int64>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Null: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Null> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Null>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::String: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::String> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::String>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::StringHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::StringHash> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::StringHash>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::StringTable: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::StringTable> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::StringTable>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::UInt: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::UInt> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::UInt>(mParentBYML);
					node->Parse(bStream);
					mNodes.push_back(node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::UInt64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::UInt64> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::UInt64>(mParentBYML);
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
		bStream.WriteS8(Formats::Resources::BYML::Versions::V4::NodeType::Array);


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