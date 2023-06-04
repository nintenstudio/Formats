#include <Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.h>

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
#include <Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	PlainHash::PlainHash(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	bool PlainHash::Parse(Formats::IO::BinaryIOStream& bStream) {
		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V7::NodeType::PlainHash)
			return false;

		F_U32 numEntries = bStream.ReadU24();

		for (F_U32 i = 0; i < numEntries; i++) {
			bStream.PushSeek(bStream.GetSeek() + std::streampos(8 * numEntries));
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = (Formats::Resources::BYML::Versions::V7::NodeType::NodeType)bStream.ReadU8();
			bStream.PopSeek();

			F_U32 keyHash = bStream.ReadU32();

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V7::NodeType::Array: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Array> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Bool: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Bool> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Bool>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Double: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Double> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Double>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::FileData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::FileData> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::FileData>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Float: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Float> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Float>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Int> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Int64> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int64>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Null: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Null> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Null>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::PlainHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::String: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::String> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::String>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::StringHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringTable: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::StringTable> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::UInt> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::UInt64> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt64>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::ValueHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyHash, node);
					bStream.PopSeek();
					break;
				}
			}
		}

		return true;
	}
	bool PlainHash::Serialize(Formats::IO::BinaryIOStream& bStream) {

		return true;
	}

	std::vector<F_U32> PlainHash::GetKeys() {
		std::vector<F_U32> res;
		res.reserve(mMap.size());
		for (std::map<F_U32, std::shared_ptr<Formats::Resources::BYML::Node>>::iterator it = mMap.begin(); it != mMap.end(); ++it) {
			res.push_back(it->first);
		}

		return res;
	}
	std::shared_ptr<Formats::Resources::BYML::Node> PlainHash::GetValue(F_U32 key) {
		if (mMap.count(key))
			return mMap.at(key);

		return nullptr;
	}

	void PlainHash::EmitYAML(YAML::Emitter& out) {
		out << YAML::BeginMap;
		for (const std::pair<F_U32, std::shared_ptr<Formats::Resources::BYML::Node>> pair : mMap) {
			out << YAML::Key;
			out << pair.first;
			out << YAML::Value;
			pair.second->EmitYAML(out);
		}
		out << YAML::EndMap;
	}
}