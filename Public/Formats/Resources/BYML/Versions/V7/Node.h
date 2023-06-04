#pragma once

namespace Formats::Resources::BYML::Versions::V7 {
	class V7;

	class Node {
	public:
		Node(V7* parentBYML) : mParentBYML(parentBYML) {
		
		}

		V7* mParentBYML;
	};
}