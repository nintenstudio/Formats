#pragma once

#include <Formats/Resources/BYML/Nodes/StringTable.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Aliases/Primitives.h>
#include <string>
#include <vector>


namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class StringTable : public Formats::Resources::BYML::Nodes::StringTable, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		StringTable(Formats::Resources::BYML::Versions::V7::V7* parentBYML);

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::Stream& bStream) override;
		virtual bool Serialize(Formats::IO::Stream& bStream) override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		std::vector<std::string> mStrings;
	};
}