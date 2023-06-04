#include <Formats/Resources/BYML/Versions/V7/Nodes/Bool.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Bool::Bool(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

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