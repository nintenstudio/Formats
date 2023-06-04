#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Nodes {
	class Int64 : public Formats::Resources::BYML::Node {
	public:
		virtual F_S64 GetValue() = 0;
	};
}