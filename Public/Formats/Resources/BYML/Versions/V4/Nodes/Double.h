#pragma once

#include <Formats/Resources/BYML/Nodes/Double.h>
#include <Formats/Resources/BYML/Versions/V4/V4.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class Double : public Formats::Resources::BYML::Nodes::Double, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		Double(Formats::Resources::BYML::Versions::V4::V4* parentBYML);

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual F_F64 GetValue() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_F64 mValue;
	};
}