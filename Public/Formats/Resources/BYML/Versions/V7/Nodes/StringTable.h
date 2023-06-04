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

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		std::vector<std::string> mStrings;
	};
}