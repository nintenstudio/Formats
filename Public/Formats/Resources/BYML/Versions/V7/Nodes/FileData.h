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
		~FileData();

		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		F_U32 mDataSize;
		F_U32 mUkn0x4;
		F_U8* mData;
	};
}