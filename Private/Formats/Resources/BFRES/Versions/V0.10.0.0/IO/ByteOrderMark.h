#pragma once

#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BFRES::Versions::V0_10_0_0::IO {
	enum class ByteOrderMark : F_U32 {
		LITTLE = 0xFFFE,
		BIG = 0xFEFF
	};
}