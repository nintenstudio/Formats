#include <Formats/Resources/BYML/Versions/V7/Nodes/Bool.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Bool::Bool(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType Bool::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::Bool;
	}

	bool Bool::Parse(Formats::IO::Stream& bStream) {
		mValue = bStream.ReadU32();

		return true;
	}
	bool Bool::Serialize(Formats::IO::Stream& bStream) {
		bStream.WriteU32(mValue);

		return true;
	}

	bool Bool::GetValue() {
		return mValue;
	}

	void Bool::EmitYAML(YAML::Emitter& out) {
		out << YAML::LocalTag("bool");
		out << mValue;
	}
	bool Bool::LoadYAML(YAML::Node& node) {
		mValue = node.as<bool>();

		return true;
	}
}