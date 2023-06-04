#pragma once

#include <Formats/Resources/BYML/Nodes/Float.h>
#include <Formats/Resources/BYML/Versions/V4/V4.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class Float : public Formats::Resources::BYML::Nodes::Float, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		Float(Formats::Resources::BYML::Versions::V4::V4* parentBYML);

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual F_F32 GetValue() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_F32 mValue;
	};
}