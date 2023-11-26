#pragma once

#include <Formats/Resources/BYML/Nodes/ValueHash.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>
#include <map>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class ValueHash : public Formats::Resources::BYML::Nodes::ValueHash, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		ValueHash(Formats::Resources::BYML::Versions::V7::V7* parentBYML);

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::Stream& bStream) override;
		virtual bool Serialize(Formats::IO::Stream& bStream) override;

		virtual std::vector<F_U32> GetKeys() override;
		virtual std::shared_ptr<Formats::Resources::BYML::Node> GetValue(F_U32 key) override;

		virtual void EmitYAML(YAML::Emitter& out) override;
		virtual bool LoadYAML(YAML::Node& node) override;

		std::map<F_U32, std::tuple<std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>, F_U32>> mMap;
	};
}