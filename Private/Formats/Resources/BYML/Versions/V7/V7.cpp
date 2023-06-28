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

		F_U32 hashKeyTablePos = mBStream->ReadU32();
		if (hashKeyTablePos != 0) {
			mBStream->PushSeek(hashKeyTablePos);
			mHashKeyTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(this);
			assert(mHashKeyTable->Parse(*mBStream));
			mBStream->PopSeek();
		}

		F_U32 stringTablePos = mBStream->ReadU32();
		if (stringTablePos != 0) {
			mBStream->PushSeek(stringTablePos);
			mStringTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(this);
			assert(mStringTable->Parse(*mBStream));
			mBStream->PopSeek();
		}
		
		F_U32 rootNodePos = mBStream->ReadU32();
		if (rootNodePos != 0) {
			mBStream->PushSeek(rootNodePos);
			mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>(this);
			if (mRoot->Parse(*mBStream)) {
				mBStream->PopSeek();
				return true;
			}
			mBStream->Seek(rootNodePos);
			mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>(this);
			if (mRoot->Parse(*mBStream)) {
				mBStream->PopSeek();
				return true;
			}
			mBStream->Seek(rootNodePos);
			mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>(this);
			if (mRoot->Parse(*mBStream)) {
				mBStream->PopSeek();
				return true;
			}
			mBStream->Seek(rootNodePos);
			mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>(this);
			if (mRoot->Parse(*mBStream)) {
				mBStream->PopSeek();
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

		std::streampos offsetsPos = mBStream->GetSeek();
		mBStream->Seek(offsetsPos + (std::streampos)12);

		std::streampos hashKeyTablePos = 0;
		if (mHashKeyTable != nullptr) {
			hashKeyTablePos = mBStream->GetSeek();
			mHashKeyTable->Serialize(*mBStream);
		}
		std::streampos stringTablePos = 0;
		if (mStringTable != nullptr) {
			stringTablePos = mBStream->GetSeek();
			mStringTable->Serialize(*mBStream);
		}
		std::streampos rootPos = 0;
		if (mRoot != nullptr) {
			rootPos = mBStream->GetSeek();
			mRoot->Serialize(*mBStream);
		}

		mBStream->PushSeek(offsetsPos);
		mBStream->WriteU32(hashKeyTablePos);
		mBStream->WriteU32(stringTablePos);
		mBStream->WriteU32(rootPos);
		mBStream->PopSeek();

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
}