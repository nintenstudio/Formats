#pragma once

#include <Formats/Resources/BYML/Nodes/UInt64.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class UInt64 : public Formats::Resources::BYML::Nodes::UInt64, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		UInt64(Formats::Resources::BYML::Versions::V4::V4* parentBYML);

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual F_U64 GetValue() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_U64 mValue;
	};
}