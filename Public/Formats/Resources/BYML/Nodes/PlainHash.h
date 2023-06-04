#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Nodes {
	class PlainHash : public Formats::Resources::BYML::Node {
	public:
		virtual std::vector<F_U32> GetKeys() = 0;
		virtual std::shared_ptr<Formats::Resources::BYML::Node> GetValue(F_U32 key) = 0;
	};
}