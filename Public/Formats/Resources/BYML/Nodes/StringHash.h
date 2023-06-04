#pragma once

#include <Formats/Resources/BYML/Node.h>

#include <vector>
#include <string>
#include <memory>

namespace Formats::Resources::BYML::Nodes {
	class StringHash : public Formats::Resources::BYML::Node {
	public:
		virtual std::vector<std::string> GetKeys() = 0;
		virtual std::shared_ptr<Formats::Resources::BYML::Node> GetValue(std::string key) = 0;
	};
}