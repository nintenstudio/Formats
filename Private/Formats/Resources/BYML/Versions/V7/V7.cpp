#include <Formats/Resources/BYML/Versions/V7/V7.h>

#include <Formats/Resources/BYML/Versions/V7/Nodes/StringTable.h>
#include <Formats/Aliases/Primitives.h>	

namespace Formats::Resources::BYML::Versions::V7 {
	bool V7::Parse() {
		if (!Formats::Resources::BYML::BYML::ParseBaseInfo())
			return false;

		if (mVersion != 7)
			return false;

		mBStream->PushSeek(mBStream->ReadUInt());
		mHashKeyTable = std::make_shared<Formats::Resources::BYML::Versions::V7::Nodes::StringTable>();
		mHashKeyTable->Parse(*mBStream);
		mBStream->PopSeek();
		return false;
	}
	bool V7::Serialize() {
		return false;
	}

	bool V7::RequestParse(Formats::ResourceParsedCallback callback) {
		return false;
	}
}