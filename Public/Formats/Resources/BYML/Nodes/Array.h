#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <Formats/Aliases/Primitives.h>
#include <vector>
#include <memory>

namespace Formats::Resources::BYML::Nodes {
	class Array : public Formats::Resources::BYML::Node {
	public:
		virtual F_U32 GetNodeCount() = 0;
		virtual std::shared_ptr<Formats::Resources::BYML::Node> GetNode(F_U32 index) = 0;
	};
}