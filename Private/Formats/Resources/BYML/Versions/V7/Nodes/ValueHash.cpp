#include <Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h>

#include <Formats/Resources/BYML/Versions/V7/Nodes/Array.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Bool.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Double.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/FileData.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Float.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Int.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Int64.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/Null.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/String.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	ValueHash::ValueHash(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType ValueHash::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::ValueHash;
	}

	bool ValueHash::Parse(Formats::IO::Stream& bStream) {
		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V7::NodeType::ValueHash)
			return false;

		F_U32 numEntries = bStream.ReadU24();

		for (F_U32 i = 0; i < numEntries; i++) {
			bStream.PushSeek(bStream.GetSeek() + std::streampos(8 * numEntries));
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = (Formats::Resources::BYML::Versions::V7::NodeType::NodeType)bStream.ReadU8();
			bStream.PopSeek();

			bStream.PushSeek(bStream.GetSeek() + std::streampos(4)); // The hash is after the value, but for our purposes we get it first.
			F_U32 keyHash = bStream.ReadU32();
			bStream.PopSeek();

			std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node> node;

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V7::NodeType::Array: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Bool: {
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Bool>(mParentBYML);
					node->Parse(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Double: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Double>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::FileData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::FileData>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Float: {
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Float>(mParentBYML);
					node->Parse(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int: {
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int>(mParentBYML);
					node->Parse(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int64>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Null: {
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Null>(mParentBYML);
					node->Parse(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::PlainHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::String: {
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::String>(mParentBYML);
					node->Parse(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringTable: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt: {
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt>(mParentBYML);
					node->Parse(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt64>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::ValueHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>(mParentBYML);
					node->Parse(bStream);
					bStream.PopSeek();
					break;
				}
			}

			bStream.ReadU32(); // We already seeked here and got the hash
			mMap.emplace(keyHash, std::tuple(node, bStream.ReadU32()));
		}

		return true;
	}
	bool ValueHash::Serialize(Formats::IO::Stream& bStream) {
		bStream.WriteU8(Formats::Resources::BYML::Versions::V7::NodeType::ValueHash);

		bStream.WriteU24(mMap.size());

		std::streampos childNodeStart = bStream.GetSeek() + (std::streampos)(12 * mMap.size());

		for (std::pair<F_U32, std::tuple<std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>, F_U32>> pair : mMap) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = std::get<0>(pair.second)->GetNodeType();

			bStream.PushSeek(bStream.GetSeek() + std::streampos(8 * mMap.size()));
			bStream.WriteU8(std::get<0>(pair.second)->GetNodeType());
			bStream.PopSeek();

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V7::NodeType::Array: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Bool: {
					std::get<0>(pair.second)->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Double: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::FileData: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Float: {
					std::get<0>(pair.second)->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int: {
					std::get<0>(pair.second)->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int64: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Null: {
					std::get<0>(pair.second)->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::PlainHash: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::String: {
					std::get<0>(pair.second)->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringHash: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringTable: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt: {
					std::get<0>(pair.second)->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt64: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::ValueHash: {
					bStream.WriteU32(childNodeStart);
					bStream.PushSeek(childNodeStart);
					std::get<0>(pair.second)->Serialize(bStream);
					childNodeStart = bStream.PopSeek();
					break;
				}
			}

			bStream.WriteU32(pair.first);
			bStream.WriteU32(std::get<1>(pair.second));
		}

		return true;
	}

	std::vector<F_U32> ValueHash::GetKeys() {
		std::vector<F_U32> res;
		res.reserve(mMap.size());
		for (std::map<F_U32, std::tuple<std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>, F_U32>>::iterator it = mMap.begin(); it != mMap.end(); ++it) {
			res.push_back(it->first);
		}

		return res;
	}
	std::shared_ptr<Formats::Resources::BYML::Node> ValueHash::GetValue(F_U32 key) {
		if (mMap.count(key))
			return std::get<0>(mMap.at(key));

		return nullptr;
	}

	void ValueHash::EmitYAML(YAML::Emitter& out) {
		out << YAML::LocalTag("valuehash");
		out << YAML::BeginMap;
		for (const std::pair<F_U32, std::tuple<std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>, F_U32>> pair : mMap) {
			out << YAML::Key;
			out << YAML::LocalTag("uint32");
			out << pair.first;
			out << YAML::Value;
			out << YAML::BeginSeq;
			std::get<0>(pair.second)->EmitYAML(out);
			out << std::get<1>(pair.second);
			out << YAML::EndSeq;
		}
		out << YAML::EndMap;
	}
	bool ValueHash::LoadYAML(YAML::Node& node) {
		mMap.clear();
		for (YAML::iterator it = node.begin(); it != node.end(); it++) {
			std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node> newNode = Formats::Resources::BYML::Versions::V7::Node::Factory(mParentBYML, it->second);
			YAML::Node n = it->second[0];
			if (!newNode->LoadYAML(n))
				return false;

			F_U32 unk = it->second[1].as<F_U32>();

			mMap.emplace(it->first.as<F_U32>(), std::tuple(newNode, unk));
		}

		return true;
	}
}