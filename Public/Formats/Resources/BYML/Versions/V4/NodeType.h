#pragma once

#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BYML::Versions::V4::NodeType {
	enum NodeType : F_U8 {
		String = 0xA0,
		BinaryData = 0xA1,
		FileData = 0xA2,
		Array = 0xC0,
		StringHash = 0xC1,
		StringTable = 0xC2,
		Bool = 0xD0,
		Int = 0xD1,
		Float = 0xD2,
		UInt = 0xD3,
		Int64 = 0xD4,
		UInt64 = 0xD5,
		Double = 0xD6,
		Null = 0xFF
	};
}
