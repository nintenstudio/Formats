#pragma once

#include <Formats/Resources/BYML/Node.h>

namespace Formats::Resources::BYML::Nodes {
	class BinaryData : public Formats::Resources::BYML::Node {
	public:
		virtual F_U8* GetData() = 0;
		virtual F_U32 GetDataSize() = 0;
	};
}