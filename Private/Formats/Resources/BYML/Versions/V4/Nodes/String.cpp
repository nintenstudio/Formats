#include <Formats/Resources/BYML/Versions/V4/Nodes/String.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	String::String(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

	}

	bool String::Parse(Formats::IO::BinaryIOStream& bStream) {
		mIndex = bStream.ReadU32();

		return true;
	}
	bool String::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(mIndex);

		return true;
	}

	void String::EmitYAML(YAML::Emitter& out) {
		out << mParentBYML->mStringTable->mStrings.at(mIndex);
	}
}