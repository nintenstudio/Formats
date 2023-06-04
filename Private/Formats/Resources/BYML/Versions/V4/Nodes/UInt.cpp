#include <Formats/Resources/BYML/Versions/V4/Nodes/UInt.h>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	UInt::UInt(Formats::Resources::BYML::Versions::V4::V4* parentBYML) : Formats::Resources::BYML::Versions::V4::Node::Node(parentBYML) {

	}

	bool UInt::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadU32();

		return true;
	}
	bool UInt::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU32(mValue);

		return true;
	}

	F_U32 UInt::GetValue() {
		return mValue;
	}

	void UInt::EmitYAML(YAML::Emitter& out) {
		out << mValue;
	}
}