#pragma once

#include <Formats/Resources/BYML/Nodes/Array.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Resources/BYML/Versions/V7/NodeType.h>
#include <Formats/Aliases/Primitives.h>
#include <vector>
#include <memory>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class Array : public Formats::Resources::BYML::Nodes::Array, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		Array(Formats::Resources::BYML::Versions::V7::V7* parentBYML);

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::Stream& bStream) override;
		virtual bool Serialize(Formats::IO::Stream& bStream) override;

		virtual F_U32 GetNodeCount() override;
		virtual std::shared_ptr<Formats::Resources::BYML::Node> GetNode(F_U32 index) override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		std::vector<Formats::Resources::BYML::Versions::V7::NodeType::NodeType> mNodeTypes;
		std::vector<std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>> mNodes;
	};
}