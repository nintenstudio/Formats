#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <Formats/Resources/BYML/Versions/V7/NodeType.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V7 {
	class V7;

	class Node : virtual public Formats::Resources::BYML::Node {
	public:
		Node(V7* parentBYML) : mParentBYML(parentBYML) {
		
		}
		static std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node> Factory(Formats::Resources::BYML::Versions::V7::V7* parentBYML, YAML::Node& node);

		virtual Formats::Resources::BYML::Versions::V7::NodeType::NodeType GetNodeType() const = 0;

		V7* mParentBYML;
	};
}