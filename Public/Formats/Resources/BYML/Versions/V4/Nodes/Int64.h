#pragma once

#include <Formats/Resources/BYML/Nodes/Int64.h>
#include <Formats/Resources/BYML/Versions/V4/V4.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class Int64 : public Formats::Resources::BYML::Nodes::Int64, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		Int64(Formats::Resources::BYML::Versions::V4::V4* parentBYML);

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual F_S64 GetValue() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_S64 mValue;
	};
}