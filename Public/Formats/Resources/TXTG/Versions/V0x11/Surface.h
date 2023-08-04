#pragma once

#include <Formats/Resources/TXTG/Surface.h>
#include <Formats/Aliases/Primitives.h>

#include <memory>

namespace Formats::Resources::TXTG::Versions::V0x11 {
	class Surface : public Formats::Resources::TXTG::Surface {
	public:
		Surface(F_U16 arrayIndex, F_U8 mipLevel, F_U8 surfaceCount) : mMipLevel(mipLevel), mArrayIndex(arrayIndex), mSurfaceCount(surfaceCount) {

		}

		virtual std::shared_ptr<F_U8[]> GetData() override {
			return mData;
		}

		F_U16 mArrayIndex;
		F_U8 mMipLevel;
		F_U8 mSurfaceCount;
		F_U32 mSize;
		F_U32 mUnk;
		std::shared_ptr<F_U8[]> mData;
	};
}