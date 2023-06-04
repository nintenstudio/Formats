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

		mBStream->PushSeek(mBStream->ReadU32());
		mHashKeyTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(this);
		assert(mHashKeyTable->Parse(*mBStream));
		mBStream->PopSeek();

		mBStream->PushSeek(mBStream->ReadU32());
		mStringTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>(this);
		assert(mStringTable->Parse(*mBStream));
		mBStream->PopSeek();
		
		F_U32 rootNodePos = mBStream->ReadU32();
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
		
		return false;
	}
	bool V7::Serialize() {
		return false;
	}

	bool V7::RequestParse(Formats::Resources::ResourceParsedCallback callback) {
		return false;
	}

	std::string V7::ToYAML() {
		YAML::Emitter emitter;
		mRoot->EmitYAML(emitter);
		return emitter.c_str();
	}
}