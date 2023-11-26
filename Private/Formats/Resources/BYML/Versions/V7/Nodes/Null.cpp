#include <Formats/Resources/BYML/Versions/V7/Nodes/Null.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Null::Null(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType Null::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::Null;
	}

	bool Null::Parse(Formats::IO::Stream& bStream) {
		bStream.ReadU32();

		return true;
	}
	bool Null::Serialize(Formats::IO::Stream& bStream) {
		bStream.WriteU32(0);

		return true;
	}

	void Null::EmitYAML(YAML::Emitter& out) {
		out << "null";
	}
	bool Null::LoadYAML(YAML::Node& node) {
		return true;
	}
}