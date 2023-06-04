#include <Formats/Resources/BYML/Versions/V4/Nodes/Int.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	Int::Int(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

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