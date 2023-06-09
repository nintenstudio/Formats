#include <Formats/Resources/BYML/Versions/V7/Nodes/Int.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Int::Int(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType Int::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::Int;
	}

	bool Int::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadS32();

		return true;
	}
	bool Int::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteS32(mValue);

		return true;
	}

	F_S32 Int::GetValue() {
		return mValue;
	}

	void Int::EmitYAML(YAML::Emitter& out) {
		out << mValue;
	}
}