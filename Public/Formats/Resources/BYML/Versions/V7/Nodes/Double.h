#pragma once

#include <Formats/Resources/BYML/Nodes/Double.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class Double : public Formats::Resources::BYML::Nodes::Double, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		Double(Formats::Resources::BYML::Versions::V7::V7* parentBYML);

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::Stream& bStream) override;
		virtual bool Serialize(Formats::IO::Stream& bStream) override;

		virtual F_F64 GetValue() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_F64 mValue;
	};
}