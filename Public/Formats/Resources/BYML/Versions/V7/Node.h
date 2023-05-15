#pragma once

#include <Formats/IO/BinaryIOStream.h>
#include <memory>

namespace Formats::Resources::BYML::Versions::V7 {
	class Node {
	public:
		virtual bool Parse(Formats::IO::BinaryIOStream& bStream) = 0;
		virtual bool Serialize(Formats::IO::BinaryIOStream& bStream) = 0;
	};
}