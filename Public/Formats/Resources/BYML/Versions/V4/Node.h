#pragma once

namespace Formats::Resources::BYML::Versions::V4 {
	class V4;

	class Node {
	public:
		Node(V4* parentBYML) : mParentBYML(parentBYML) {
		
		}

		V4* mParentBYML;
	};
}