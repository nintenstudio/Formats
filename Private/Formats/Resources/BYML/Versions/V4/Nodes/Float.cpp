#include <Formats/Resources/BYML/Versions/V4/Nodes/Float.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	Float::Float(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

	}
	bool Float::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadF32();

		return true;
	}
	bool Float::Serialize(Formats::IO::BinaryIOStream& bStream) {
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