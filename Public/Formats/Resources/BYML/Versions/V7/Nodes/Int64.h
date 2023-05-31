#pragma once

#include <Formats/Resources/BYML/Nodes/Int64.h>
#include <Formats/Resources/BYML/Versions/V7/V7.h>
#include <Formats/Resources/BYML/Versions/V7/Node.h>

#include <Formats/Resources/BYML/BYML.h>
#include <Formats/Aliases/Primitives.h>
#include <string>

namespace Formats::Resources::BYML::Versions::V7::Nodes {
	class Int64 : public Formats::Resources::BYML::Nodes::Int64, public Formats::Resources::BYML::Versions::V7::Node {
	public:
		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) override;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) override;

		F_S64 mValue;
	};
}