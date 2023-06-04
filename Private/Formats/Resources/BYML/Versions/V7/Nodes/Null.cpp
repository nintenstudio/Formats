#include <Formats/Resources/BYML/Versions/V7/Nodes/Null.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Null::Null(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	bool Null::Parse(Formats::IO::BinaryIOStream& bStream) {
		bStream.ReadU32();

		return true;
	}
	bool Null::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(0);

		return true;
	}

	void Null::EmitYAML(YAML::Emitter& out) {
		out << "null";
	}
}