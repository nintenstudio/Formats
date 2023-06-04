#pragma once

#include <Formats/Resources/BYML/Node.h>

namespace Formats::Resources::BYML::Nodes {
	class Bool : public Formats::Resources::BYML::Node {
	public:
		virtual bool GetValue() = 0;
	};
}