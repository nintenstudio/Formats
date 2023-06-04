#include <Formats/Resources/BYML/Versions/V4/Nodes/Bool.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	Bool::Bool(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

	}

	bool Bool::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadU32();

		return true;
	}
	bool Bool::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(mValue);

		return true;
	}

	bool Bool::GetValue() {
		return mValue;
	}

	void Bool::EmitYAML(YAML::Emitter& out) {
		out << mValue;
	}
}