#pragma once

#include <Formats/Aliases/Primitives.h>
#include <memory>

namespace Formats::Resources::TXTG {
	class Surface {
	public:
		virtual std::shared_ptr<F_U8[]> GetData() = 0;
		virtual F_UT GetDataSize() = 0;
		virtual F_U32 GetWidth() = 0;
		virtual F_U32 GetHeight() = 0;
	};
}