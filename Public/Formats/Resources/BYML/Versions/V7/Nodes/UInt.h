#pragma once

#include <Formats/Resources/BYML/Nodes/UInt.h>
#include <Formats/Resources/BYML/Versions/7/7.h>
#include <Formats/Resources/BYML/Versions/7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class UInt : public Formats::Resources::BYML::Nodes::UInt, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		UInt(std::shared_ptr<Formats::Resources::BYML::Versions::V7::V7> parent) : Formats::Resources::BYML::Versions::V7::Node(parent) {

		}

		virtual bool Parse() override;
		virtual bool Serialize() override;
	};
}