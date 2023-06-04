#pragma once

#include <Formats/Resources/BYML/Nodes/String.h>
#include <Formats/Resources/BYML/Versions/V4/V4.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class String : public Formats::Resources::BYML::Nodes::String, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		String(Formats::Resources::BYML::Versions::V4::V4* parentBYML);

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_U32 mIndex;
	};
}