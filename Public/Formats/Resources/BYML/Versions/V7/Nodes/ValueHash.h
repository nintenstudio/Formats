#pragma once

#include <Formats/Resources/BYML/Nodes/ValueHash.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>
#include <map>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class ValueHash : public Formats::Resources::BYML::Nodes::ValueHash, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		std::map<F_U32, std::shared_ptr<Formats::Resources::BYML::Versions::V7::Node>> mMap;
		F_U32 mUkn0x8;
	};
}