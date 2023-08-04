#include <Formats/Resources/TXTG/Versions/V0x11/V0x11.h>

#include <Formats/Resources/ZSTD/ZSTDBackend.h>
#include <Formats/IO/BinaryIOStreamBasics/Buffer/Buffer.h>

#include <memory>
#include <cassert>

namespace Formats::Resources::TXTG::Versions::V0x11 {
	bool V0x11::Parse() {
		if (!Formats::Resources::TXTG::TXTG::ParseBaseInfo())
			return false;

#if (FORMATS_RESOURCES_BYML_ACCEPTLESSERVERSIONS)
		if (mVersion > 0x11)
			return false;
#else
		if (mVersion != 0x11)
			return false;
#endif

		mWidth = mBStream->ReadU16();
		mHeight = mBStream->ReadU16();
		mArrayCount = mBStream->ReadU16();
		mMipCount = mBStream->ReadU8();
		mUnk1 = mBStream->ReadU8();
		mUnk2 = mBStream->ReadU8();
		mBStream->ReadU16(); // Padding

		mFormatFlag = mBStream->ReadU8();
		mFormatSetting = mBStream->ReadU32();

		mCompSelectR = mBStream->ReadU8();
		mCompSelectG = mBStream->ReadU8();
		mCompSelectB = mBStream->ReadU8();
		mCompSelectA = mBStream->ReadU8();

		mBStream->ReadBytes(&mHash[0], 32);

		mFormat = mBStream->ReadU16();
		mUnk3 = mBStream->ReadU16();

		mTextureSetting1 = mBStream->ReadU32();
		mTextureSetting2 = mBStream->ReadU32();
		mTextureSetting3 = mBStream->ReadU32();
		mTextureSetting4 = mBStream->ReadU32();

		mSurfaces.reserve(mMipCount * mArrayCount);
		for (F_U32 i = 0; i < mMipCount * mArrayCount; i++) {
			F_U16 arrayIndex = mBStream->ReadU16();
			F_U8 mipLevel = mBStream->ReadU8();
			F_U8 surfaceCount = mBStream->ReadU8();
			mSurfaces.push_back(std::make_shared<Formats::Resources::TXTG::Versions::V0x11::Surface>(arrayIndex, mipLevel, surfaceCount));
		}
		for (F_U32 i = 0; i < mMipCount * mArrayCount; i++) {
			mSurfaces.at(i)->mSize = mBStream->ReadU32();
			mSurfaces.at(i)->mUnk = mBStream->ReadU32();
		}
		for (F_U32 i = 0; i < mMipCount * mArrayCount; i++) {
			std::shared_ptr<F_U8[]> compressedSurface = std::make_shared<F_U8[]>(mSurfaces.at(i)->mSize);
			mBStream->ReadBytes(compressedSurface.get(), mSurfaces.at(i)->mSize);
			std::shared_ptr<Formats::IO::BinaryIOStreamBasics::Buffer::Buffer> compressedSurfaceStream = std::make_shared<Formats::IO::BinaryIOStreamBasics::Buffer::Buffer>(compressedSurface, mSurfaces.at(i)->mSize);

			mSurfaces.at(i)->mData = Formats::Resources::ZSTD::ZSTDBackend::Decompress(compressedSurfaceStream)->GetBuffer();
		}
	}
	bool V0x11::Serialize() {
		if (!Formats::Resources::TXTG::TXTG::WriteBaseInfo())
			return false;


	}

	bool V0x11::RequestParse(Formats::ResourceParsedCallback callback) {
		return false;
	}

	F_U16 V0x11::GetWidth() {
		return mWidth;
	}

	F_U16 V0x11::GetHeight() {
		return mHeight;
	}

	F_U16 V0x11::GetArrayCount() {
		return mArrayCount;
	}

	F_U8 V0x11::GetMipCount() {
		return mMipCount;
	}

	std::shared_ptr<Formats::Resources::TXTG::Surface> V0x11::GetSurface(F_U16 arrayIndex, F_U8 mipLevel) {
		for (std::shared_ptr<Formats::Resources::TXTG::Versions::V0x11::Surface> surface : mSurfaces) {
			if (surface->mArrayIndex == arrayIndex && surface->mMipLevel == mipLevel)
				return static_pointer_cast<Formats::Resources::TXTG::Surface>(surface);
		}

		return nullptr;
	}
}