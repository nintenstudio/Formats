#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Nodes {
	class Double : public Formats::Resources::BYML::Node {
	public:
		virtual F_F64 GetValue() = 0;
	};
}