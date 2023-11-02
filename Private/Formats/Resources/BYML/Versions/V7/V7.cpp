#include <Formats/Resources/BYML/Versions/V7/V7.h>

#include <Formats/Resources/BYML/Versions/V7/Nodes/Array.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>
#include <Formats/Aliases/Primitives.h>
#include <yaml-cpp/yaml.h>

#include <cassert>

namespace Formats::Resources::BYML::Versions::V7 {
	bool V7::Parse() {
		if (!Formats::Resources::BYML::BYML::ParseBaseInfo())
			return false;

#if (FORMATS_RESOURCES_BYML_ACCEPTLESSERVERSIONS)
		if (mVersion > 7)
			return false;
#else
		if (mVersion != 7)
			return false;
#endif

		F_U32 hashKeyTablePos = mStream->ReadU32();
		if (hashKeyTablePos != 0) {
			mStream->PushSeek(hashKeyTablePos);
			mHashKeyTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(this);
			assert(mHashKeyTable->Parse(*mStream));
			mStream->PopSeek();
		}

		F_U32 stringTablePos = mStream->ReadU32();
		if (stringTablePos != 0) {
			mStream->PushSeek(stringTablePos);
			mStringTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(this);
			assert(mStringTable->Parse(*mStream));
			mStream->PopSeek();
		}
		
		F_U32 rootNodePos = mStream->ReadU32();
		if (rootNodePos != 0) {
			mStream->PushSeek(rootNodePos);
			mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>(this);
			if (mRoot->Parse(*mStream)) {
				mStream->PopSeek();
				return true;
			}
			mStream->Seek(rootNodePos);
			mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>(this);
			if (mRoot->Parse(*mStream)) {
				mStream->PopSeek();
				return true;
			}
			mStream->Seek(rootNodePos);
			mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>(this);
			if (mRoot->Parse(*mStream)) {
				mStream->PopSeek();
				return true;
			}
			mStream->Seek(rootNodePos);
			mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>(this);
			if (mRoot->Parse(*mStream)) {
				mStream->PopSeek();
				return true;
			}
		}
		else {
			return true;
		}
		
		return false;
	}
	bool V7::Serialize() {
		if (!Formats::Resources::BYML::BYML::WriteBaseInfo())
			return false;

		std::streampos offsetsPos = mStream->GetSeek();
		mStream->Seek(offsetsPos + (std::streampos)12);

		std::streampos hashKeyTablePos = 0;
		if (mHashKeyTable != nullptr) {
			hashKeyTablePos = mStream->GetSeek();
			mHashKeyTable->Serialize(*mStream);
		}
		std::streampos stringTablePos = 0;
		if (mStringTable != nullptr) {
			stringTablePos = mStream->GetSeek();
			mStringTable->Serialize(*mStream);
		}
		std::streampos rootPos = 0;
		if (mRoot != nullptr) {
			rootPos = mStream->GetSeek();
			mRoot->Serialize(*mStream);
		}

		mStream->PushSeek(offsetsPos);
		mStream->WriteU32(hashKeyTablePos);
		mStream->WriteU32(stringTablePos);
		mStream->WriteU32(rootPos);
		mStream->PopSeek();

		return true;
	}

	bool V7::RequestParse(Formats::ResourceParsedCallback callback) {
		return false;
	}

	std::string V7::ToYAML() {
		YAML::Emitter emitter;
		mRoot->EmitYAML(emitter);
		return emitter.c_str();
	}
	void V7::FromYAML(std::string text) {
		YAML::Node root = YAML::Load(text);
	}
}