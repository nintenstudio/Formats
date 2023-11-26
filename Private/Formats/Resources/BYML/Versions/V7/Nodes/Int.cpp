#include <Formats/Resources/BYML/Versions/V7/Nodes/Int.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Int::Int(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType Int::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::Int;
	}

	bool Int::Parse(Formats::IO::Stream& bStream) {
		mValue = bStream.ReadS32();

		return true;
	}
	bool Int::Serialize(Formats::IO::Stream& bStream) {
		bStream.WriteS32(mValue);

		return true;
	}

	F_S32 Int::GetValue() {
		return mValue;
	}

	void Int::EmitYAML(YAML::Emitter& out) {
		out << YAML::LocalTag("sint32");
		out << mValue;
	}
	bool Int::LoadYAML(YAML::Node& node) {
		mValue = node.as<F_S32>();

		return true;
	}
}