#include <Formats/Resources/BYML/Versions/V4/Nodes/Null.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	Null::Null(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

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