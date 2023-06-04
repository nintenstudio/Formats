#pragma once

#include <Formats/Resources/BYML/Nodes/Array.h>
#include <Formats/Resources/BYML/Versions/V4/V4.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Resources/BYML/Versions/V4/NodeType.h>
#include <Formats/Aliases/Primitives.h>
#include <vector>
#include <memory>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class Array : public Formats::Resources::BYML::Nodes::Array, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		Array(Formats::Resources::BYML::Versions::V4::V4* parentBYML);

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual F_U32 GetNodeCount() override;
		virtual std::shared_ptr<Formats::Resources::BYML::Node> GetNode(F_U32 index) override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		std::vector<Formats::Resources::BYML::Versions::V4::NodeType::NodeType> mNodeTypes;
		std::vector<std::shared_ptr<Formats::Resources::BYML::Node>> mNodes;
	};
}