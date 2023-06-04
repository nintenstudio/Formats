#include <Formats/Resources/BYML/Versions/V4/Nodes/Int64.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	Int64::Int64(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

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