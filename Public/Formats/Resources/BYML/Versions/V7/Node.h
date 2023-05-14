#pragma once

#include <Formats/Resources/BYML/BYML.h>

#include <memory>

namespace Formats::Resources::BYML::Versions::V7 {
	class Node {
	public:
		Node(std::shared_ptr<Formats::Resources::BYML::BYML> parent) : mParent(parent) {

		}

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;

	protected:
		std::shared_ptr<Formats::Resources::BYML::BYML> mParent;
	};
}