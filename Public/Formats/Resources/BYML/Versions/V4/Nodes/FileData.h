#pragma once

#include <Formats/Resources/BYML/Nodes/FileData.h>
#include <Formats/Resources/BYML/Versions/V4/V4.h>
#include <Formats/Resources/BYML/Versions/V4/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V4::Nodes {
	class FileData : public Formats::Resources::BYML::Nodes::FileData, public Formats::Resources::BYML::Versions::V4::Node {
	public:
		FileData(Formats::Resources::BYML::Versions::V4::V4* parentBYML);
		~FileData();

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		virtual F_U8* GetData() override;
		virtual F_U32 GetDataSize() override;

		virtual void EmitYAML(YAML::Emitter& out) override;

		F_U32 mDataSize;
		F_U32 mUkn0x4;
		F_U8* mData;
	};
}