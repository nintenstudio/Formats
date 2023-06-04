#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Nodes {
	class UInt : public Formats::Resources::BYML::Node {
	public:
		virtual F_U32 GetValue() = 0;
	};
}