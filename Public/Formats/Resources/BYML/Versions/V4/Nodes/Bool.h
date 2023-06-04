#pragma once

#include <Formats/Resources/BYML/Nodes/Bool.h>
#include <Formats/Resources/BYML/Versions/V4/V4.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class Bool : public Formats::Resources::BYML::Nodes::Bool, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		Bool(Formats::Resources::BYML::Versions::V4::V4* parentBYML);

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual bool GetValue() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		bool mValue;
	};
}