#include <Formats/Resources/BYML/Versions/V7/V7.h>

#include <Formats/Resources/BYML/Versions/V7/Nodes/Array.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringHash.h>
#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>
#include <Formats/Aliases/Primitives.h>	

#include <cassert>

namespace Formats::Resources::BYML::Versions::V7 {
	bool V7::Parse() {
		if (!Formats::Resources::BYML::BYML::ParseBaseInfo())
			return false;

		if (mVersion != 7)
			return false;

		mBStream->PushSeek(mBStream->ReadU32());
		mHashKeyTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>();
		assert(mHashKeyTable->Parse(*mBStream));
		mBStream->PopSeek();

		mBStream->PushSeek(mBStream->ReadU32());
		mStringTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>();
		assert(mStringTable->Parse(*mBStream));
		mBStream->PopSeek();
		
		mBStream->PushSeek(mBStream->ReadU32());
		mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::Array>();
		if (mRoot->Parse(*mBStream)) {
			mBStream->PopSeek();
			return true;
		}
		mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::PlainHash>();
		if (mRoot->Parse(*mBStream)) {
			mBStream->PopSeek();
			return true;
		}
		mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::ValueHash>();
		if (mRoot->Parse(*mBStream)) {
			mBStream->PopSeek();
			return true;
		}
		mRoot = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringHash>();
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
}