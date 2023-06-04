#include <Formats/Resources/BYML/Versions/V4/Nodes/StringHash.h>

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
#include <Formats/Resources/BYML/Versions/V4/Nodes/StringTable.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/UInt.h>
#include <Formats/Resources/BYML/Versions/V4/Nodes/UInt64.h>

#include <Formats/Resources/BYML/Versions/V4/NodeType.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	StringHash::StringHash(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

	}

	bool StringHash::Parse(Formats::IO::BinaryIOStream& bStream) {
		if (bStream.ReadU8() != Formats::Resources::BYML::Versions::V4::NodeType::StringHash)
			return false;

		F_U32 numEntries = bStream.ReadU24();

		for (F_U32 i = 0; i < numEntries; i++) {
			F_U32 keyIndex = bStream.ReadU24();
			Formats::Resources::BYML::Versions::V4::NodeType::NodeType nodeType = (Formats::Resources::BYML::Versions::V4::NodeType::NodeType)bStream.ReadU8();

			switch (nodeType) {
				case Formats::Resources::BYML::Versions::V4::NodeType::Array: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Array> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Array>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::BinaryData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::BinaryData> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::BinaryData>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Bool: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Bool> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Bool>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Double: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Double> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Double>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::FileData: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::FileData> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::FileData>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Float: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Float> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Float>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Int: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Int> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Int>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Int64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Int64> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Int64>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::Null: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::Null> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::Null>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::String: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::String> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::String>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::StringHash: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::StringHash> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::StringHash>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::StringTable: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::StringTable> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::StringTable>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::UInt: {
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::UInt> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::UInt>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					break;
				}
				case Formats::Resources::BYML::Versions::V4::NodeType::UInt64: {
					std::streampos offset = bStream.ReadU32();
					bStream.PushSeek(offset);
					std::shared_ptr<Formats::Resources::BYML::Versions::V4::Nodes::UInt64> node = std::make_shared<Formats::Resources::BYML::Versions::V4::Nodes::UInt64>(mParentBYML);
					node->Parse(bStream);
					mMap.emplace(keyIndex, node);
					bStream.PopSeek();
					break;
				}
			}
		}

		return true;
	}
	bool StringHash::Serialize(Formats::IO::BinaryIOStream& bStream) {

		return true;
	}

	std::vector<std::string> StringHash::GetKeys() {
		std::vector<std::string> res;
		res.reserve(mMap.size());
		for (std::map<F_U32, std::shared_ptr<Formats::Resources::BYML::Node>>::iterator it = mMap.begin(); it != mMap.end(); ++it) {
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
		for (const std::pair<F_U32, std::shared_ptr<Formats::Resources::BYML::Node>> pair : mMap) {
			out << YAML::Key;
			out << mParentBYML->mHashKeyTable->mStrings.at(pair.first);
			out << YAML::Value;
			pair.second->EmitYAML(out);
		}
		out << YAML::EndMap;
	}
}