#pragma once

#include <Formats/Resources/BYML/Nodes/Float.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class Float : public Formats::Resources::BYML::Nodes::Float, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		Float(Formats::Resources::BYML::Versions::V7::V7* parentBYML);

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual F_F32 GetValue() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_F32 mValue;
	};
}