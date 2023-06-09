#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>

namespace Formats::Resources::BYML::Versions::V7 {
	class V7;

	class Node : virtual public Formats::Resources::BYML::Node {
	public:
		Node(V7* parentBYML) : mParentBYML(parentBYML) {
		
		}

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const = 0;

		V7* mParentBYML;
	};
}