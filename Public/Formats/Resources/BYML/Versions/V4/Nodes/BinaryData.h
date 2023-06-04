#pragma once

#include <Formats/Resources/BYML/Nodes/BinaryData.h>
#include <Formats/Resources/BYML/Versions/V4/V4.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class BinaryData : public Formats::Resources::BYML::Nodes::BinaryData, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		BinaryData(Formats::Resources::BYML::Versions::V4::V4* parentBYML);
		~BinaryData();

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual F_U8* GetData() override;
		virtual F_U32 GetDataSize() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_U32 mDataSize;
		F_U8* mData;
	};
}