#include <Formats/Resources/BYML/Versions/V7/Nodes/Int64.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Int64::Int64(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType Int64::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::Int64;
	}

	bool Int64::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadS64();

		return true;
	}
	bool Int64::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteS64(mValue);

		return true;
	}

	F_S64 Int64::GetValue() {
		return mValue;
	}

	void Int64::EmitYAML(YAML::Emitter& out) {
		out << mValue;
	}
}