#pragma once

#include <Formats/Resources/BYML/Nodes/FileData.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class FileData : public Formats::Resources::BYML::Nodes::FileData, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		FileData(Formats::Resources::BYML::Versions::V7::V7* parentBYML);
		~FileData();

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const override;

		virtual bool Parse(Formats::IO::Stream& bStream) override;
		virtual bool Serialize(Formats::IO::Stream& bStream) override;

		virtual F_U8* GetData() override;
		virtual F_U32 GetDataSize() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_U32 mDataSize;
		F_U32 mUkn0x4;
		F_U8* mData;
	};
}