#pragma once

#include <string>

namespace Formats::Resources::BYML::Nodes {
	class String {
	public:
		virtual std::string GetString() = 0;
		virtual void SetString(std::string value) = 0;
	};
}