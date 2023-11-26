#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	UInt64::UInt64(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType UInt64::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::UInt64;
	}

	bool UInt64::Parse(Formats::IO::Stream& bStream) {
		mValue = bStream.ReadU64();

		return true;
	}
	bool UInt64::Serialize(Formats::IO::Stream& bStream) {
		bStream.WriteU64(mValue);

		return true;
	}

	F_U64 UInt64::GetValue() {
		return mValue;
	}

	void UInt64::EmitYAML(YAML::Emitter& out) {
		out << YAML::LocalTag("uint64");
		out << mValue;
	}
	bool UInt64::LoadYAML(YAML::Node& node) {
		mValue = node.as<F_U64>();

		return true;
	}
}