#pragma once

#include <Formats/Resources/BYML/Nodes/BinaryData.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class BinaryData : public Formats::Resources::BYML::Nodes::BinaryData, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		BinaryData(Formats::Resources::BYML::Versions::V7::V7* parentBYML);
		~BinaryData();

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::Stream& bStream) override;
		virtual bool Serialize(Formats::IO::Stream& bStream) override;

		virtual F_U8* GetData() override;
		virtual F_U32 GetDataSize() override;

		virtual void EmitYAML(YAML::Emitter& out) override;
		virtual bool LoadYAML(YAML::Node& node) override;

		F_U32 mDataSize;
		F_U8* mData;
	};
}