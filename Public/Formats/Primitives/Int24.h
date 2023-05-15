#pragma once

#include <cstring>

namespace Formats::Primitives {
	class Int24 {
	public:
		Int24() {

		}
		Int24(int value) {
			std::memcpy(&mData, &value, (size_t)3);
		}

		operator int() const {
			int res = 0;
			std::memcpy(&res, mData, 3);
			// Sign extend:
			if (res & 0x00800000)
				res |= 0xFF000000;
			return res;
		}

	private:
		char mData[3];
	};
}