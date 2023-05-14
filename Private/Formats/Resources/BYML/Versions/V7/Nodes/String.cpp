#include <Formats/Resources/BYML/Versions/7/Nodes/String.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	bool String::Parse() {
		mIndex = mParent->mBStream->ReadUInt();
	}
	bool String::Serialize() {
		mParent->mBStream->WriteUInt(mIndex);
	}

	std::string String::GetString() {
		// FORMATS_TODO: Implement.
		return "";
	}
	void String::SetString(std::string value) {
		// FORMATS_TODO: Implement.
	}
}