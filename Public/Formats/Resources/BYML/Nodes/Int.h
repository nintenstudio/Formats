#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Nodes {
	class Int : public Formats::Resources::BYML::Node {
	public:
		virtual F_S32 GetValue() = 0;
	};
}