#include <Formats/Resources/BYML/Versions/V7/Nodes/UInt.h>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	UInt::UInt(Formats::Resources::BYML::Versions::V7::V7* parentBYML) : Formats::Resources::BYML::Versions::V7::Node::Node(parentBYML) {

	}

	Formats::Resources::BYML::Versions::V7::NodeType::NodeType UInt::GetNodeType() const {
		return Formats::Resources::BYML::Versions::V7::NodeType::UInt;
	}

	bool UInt::Parse(Formats::IO::Stream& bStream) {
		mValue = bStream.ReadU32();

		return true;
	}
	bool UInt::Serialize(Formats::IO::Stream& bStream) {
		bStream.WriteU32(mValue);

		return true;
	}

	F_U32 UInt::GetValue() {
		return mValue;
	}

	void UInt::EmitYAML(YAML::Emitter& out) {
		out << YAML::LocalTag("uint32");
		out << mValue;
	}
	bool UInt::LoadYAML(YAML::Node& node) {
		mValue = node.as<F_U32>();

		return true;
	}
}