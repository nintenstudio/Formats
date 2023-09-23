#include <Formats/Resources/BYML/Versions/V7/Nodes/StringHash.h>

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
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	StringHash::StringHash(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType StringHash::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::StringHash;
	}

	bool StringHash::Parse(Formats::IO::Stream& bStream) {
		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V7::NodeType::StringHash)
			return false;

		F_U32 numEntries = bStream.ReadU24();

		for (F_U32 i = 0; i < numEntries; i++) {
			F_U32 keyIndex = bStream.ReadU24();
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = (Formats::Resources::BYML::Versions::V7::NodeType::NodeType)bStream.ReadU8();

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V7::NodeType::Array: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Array> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::BinaryData>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Bool: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Bool> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Bool>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Double: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Double> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Double>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::FileData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::FileData> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::FileData>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Float: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Float> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Float>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Int> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Int64> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Int64>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Null: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::Null> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Null>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::PlainHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::String: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::String> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::String>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::StringHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringTable: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::StringTable> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::UInt> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::UInt64> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::UInt64>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::ValueHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash> node = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
			}
		}

		return true;
	}
	bool StringHash::Serialize(Formats::IO::Stream& bStream) {
		bStream.WriteU8(Formats::Resources::BYML::Versions::V7::NodeType::StringHash);

		bStream.WriteU24(mMap.size());

		std::streampos nodeEnd = bStream.GetSeek() + (std::streampos)(8 * mMap.size());

		for (std::pair<F_U32, std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>> pair : mMap) {
			Formats::Resources::BYML::Versions::V7::NodeType::NodeType nodeType = pair.second->GetNodeType();

			bStream.WriteU24(pair.first);
			bStream.WriteU8(pair.second->GetNodeType());

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V7::NodeType::Array: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::BinaryData: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Bool: {
					pair.second->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Double: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::FileData: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Float: {
					pair.second->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int: {
					pair.second->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Int64: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::Null: {
					pair.second->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::PlainHash: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::String: {
					pair.second->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringHash: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::StringTable: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt: {
					pair.second->Serialize(bStream);
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::UInt64: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V7::NodeType::ValueHash: {
					bStream.WriteU32(nodeEnd);
					bStream.PushSeek(nodeEnd);
					pair.second->Serialize(bStream);
					nodeEnd = bStream.PopSeek();
					break;
				}
			}
		}

		bStream.Seek(nodeEnd);

		return true;
	}

	std::vector<std::string> StringHash::GetKeys() {
		std::vector<std::string> res;
		res.reserve(mMap.size());
		for (std::map<F_U32, std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>>::iterator it = mMap.begin(); it != mMap.end(); ++it) {
			res.push_back(mParentBYML->mHashKeyTable->mStrings.at(it->first));
		}

		return res;
	}

	std::shared_ptr<Formats::Resources::BYML::Node> StringHash::GetValue(std::string key) {
		F_U32 stringIndex = std::find(mParentBYML->mHashKeyTable->mStrings.begin(), mParentBYML->mHashKeyTable->mStrings.end(), key) - mParentBYML->mHashKeyTable->mStrings.begin();
		if (stringIndex == std::numeric_limits<F_U32>::max())
			return nullptr;

		if (mMap.count(stringIndex))
			return mMap.at(stringIndex);
		return nullptr;
	}

	void StringHash::EmitYAML(YAML::Emitter& out) {
		out << YAML::BeginMap;
		for (const std::pair<F_U32, std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>> pair : mMap) {
			out << YAML::Key;
			out << mParentBYML->mHashKeyTable->mStrings.at(pair.first);
			out << YAML::Value;
			pair.second->EmitYAML(out);
		}
		out << YAML::EndMap;
	}
}