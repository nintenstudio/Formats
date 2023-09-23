#include <Formats/Resources/BYML/Versions/V7/Nodes/Float.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Float::Float(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType Float::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::Float;
	}

	bool Float::Parse(Formats::IO::Stream& bStream) {
		mValue = bStream.ReadF32();

		return true;
	}
	bool Float::Serialize(Formats::IO::Stream& bStream) {
		bStream.WriteF32(mValue);

		return true;
	}

	F_F32 Float::GetValue() {
		return mValue;
	}

	void Float::EmitYAML(YAML::Emitter& out) {
		out << mValue;
	}
}