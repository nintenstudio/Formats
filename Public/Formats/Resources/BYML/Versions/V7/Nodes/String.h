#pragma once

#include <Formats/Resources/BYML/Nodes/String.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class String : public Formats::Resources::BYML::Nodes::String, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		String(Formats::Resources::BYML::Versions::V7::V7* parentBYML);

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::Stream& bStream) override;
		virtual bool Serialize(Formats::IO::Stream& bStream) override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_U32 mIndex;
	};
}