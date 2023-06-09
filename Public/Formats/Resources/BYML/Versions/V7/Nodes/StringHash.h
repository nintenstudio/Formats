#pragma once

#include <Formats/Resources/BYML/Nodes/StringHash.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <memory>
#include <map>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class StringHash : public Formats::Resources::BYML::Nodes::StringHash, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		StringHash(Formats::Resources::BYML::Versions::V7::V7* parentBYML);

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual std::vector<std::string> GetKeys() override;
		virtual std::shared_ptr<Formats::Resources::BYML::Node> GetValue(std::string key) override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		std::map<F_U32, std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>> mMap;
	};
}