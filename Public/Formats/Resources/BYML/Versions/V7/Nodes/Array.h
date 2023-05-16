#pragma once

#include <Formats/Resources/BYML/Nodes/Array.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Resources/BYML/Versions/V7/NodeType.h>
#include <Formats/Aliases/Primitives.h>
#include <vector>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class Array : public Formats::Resources::BYML::Nodes::Array, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		std::vector<Formats::Resources::BYML::Versions::V7::NodeType::NodeType> mNodeTypes;
		std::vector<Formats::Resources::BYML::Versions::V7::Node*> mNodes;
	};
}