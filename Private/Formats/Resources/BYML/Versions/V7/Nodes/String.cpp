#include <Formats/Resources/BYML/Versions/V7/Nodes/String.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	String::String(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType String::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::String;
	}

	bool String::Parse(Formats::IO::Stream& stream) {
		mIndex = stream.ReadU32();

		return true;
	}
	bool String::Serialize(Formats::IO::Stream& stream) {
		stream.WriteU32(mIndex);

		return true;
	}

	void String::EmitYAML(YAML::Emitter& out) {
		out << mParentBYML->mStringTable->mStrings.at(mIndex);
	}
}