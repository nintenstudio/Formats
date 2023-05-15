#pragma once

#include <cstring>

namespace Formats::Primitives {
	class UInt24 {
	public:
		UInt24() {

		}
		UInt24(unsigned int value) {
			std::memcpy(&mData, &value, (size_t)3);
		}

		operator unsigned int() const {
			int res = 0;
			std::memcpy(&res, mData, 3);
			return res;
		}

	private:
		char mData[3];
	};
}