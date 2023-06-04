#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	UInt64::UInt64(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	bool UInt64::Parse(Formats::IO::BinaryIOStream& bStream) {
		mValue = bStream.ReadU64();

		return true;
	}
	bool UInt64::Serialize(Formats::IO::BinaryIOStream& bStream) {
		bStream.WriteU64(mValue);

		return true;
	}

	F_U64 UInt64::GetValue() {
		return mValue;
	}

	void UInt64::EmitYAML(YAML::Emitter& out) {
		out << mValue;
	}
}