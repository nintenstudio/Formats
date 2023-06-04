#include <Formats/Resources/BYML/Versions/V7/Nodes/Double.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	Double::Double(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	bool Double::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadF64();

		return true;
	}
	bool Double::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteF64(mValue);

		return true;
	}

	F_F64 Double::GetValue() {
		return mValue;
	}

	void Double::EmitYAML(YAML::Emitter& out) {
		out << mValue;
	}
}