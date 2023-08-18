#include <Formats/Resources/TXTG/Versions/V0x11/V0x11.h>

#include <Formats/Resources/ZSTD/ZSTDBackend.h>
#include <Formats/IO/BinaryIOStreamBasics/Buffer/Buffer.h>

#include <tegra_swizzle/lib.h>
#include <algorithm>
#include <memory>
#include <cassert>
#include <cmath>

#include <fstream>

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
		mDepth = mBStream->ReadU16();
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

		mSurfaces.reserve(mMipCount * mDepth);
		for (F_U32 i = 0; i < mMipCount * mDepth; i++) {
			F_U16 arrayIndex = mBStream->ReadU16();
			F_U8 mipLevel = mBStream->ReadU8();
			F_U8 surfaceCount = mBStream->ReadU8();
			mSurfaces.push_back(std::make_shared<Formats::Resources::TXTG::Versions::V0x11::Surface>(arrayIndex, mipLevel, surfaceCount));
		}
		for (F_U32 i = 0; i < mMipCount * mDepth; i++) {
			mSurfaces.at(i)->mZSTDCompressedSize = mBStream->ReadU32();
			mSurfaces.at(i)->mUnk = mBStream->ReadU32();
		}

		Formats::Texture::Format format = GetFormat();
		F_UT blockWidth = Formats::Texture::GetFormatBlockWidth(format);
		F_UT blockHeight = Formats::Texture::GetFormatBlockHeight(format);
		F_UT blockDepth = Formats::Texture::GetFormatBlockDepth(format);
		F_UT bytesPerBlock = Formats::Texture::GetFormatBytesPerBlock(format);
		BlockHeight blockHeightMip0 = block_height_mip0(div_round_up(mHeight, blockHeight));

		for (F_U32 i = 0; i < mMipCount * mDepth; i++) {
			std::shared_ptr<F_U8[]> compressedSurface = std::shared_ptr<F_U8[]>(new F_U8[mSurfaces.at(i)->mZSTDCompressedSize]);
			mBStream->ReadBytes(compressedSurface.get(), mSurfaces.at(i)->mZSTDCompressedSize);

			std::shared_ptr<Formats::IO::BinaryIOStreamBasics::Buffer::Buffer> compressedSurfaceStream = std::make_shared<Formats::IO::BinaryIOStreamBasics::Buffer::Buffer>(compressedSurface, mSurfaces.at(i)->mZSTDCompressedSize);

			std::shared_ptr<Formats::IO::BinaryIOStreamBasic> swizzledSurfaceDataStream = Formats::Resources::ZSTD::ZSTDBackend::Decompress(compressedSurfaceStream);
			std::shared_ptr<F_U8[]> swizzledSurfaceData = swizzledSurfaceDataStream->GetBuffer();

			F_UT mipWidth = std::max(1, mWidth >> mSurfaces.at(i)->mMipLevel);
			F_UT mipHeight = std::max(1, mHeight >> mSurfaces.at(i)->mMipLevel);
			F_UT mipDepth = std::max(1, mDepth >> mSurfaces.at(i)->mMipLevel);
			BlockHeight mipBlockHeight = mip_block_height(div_round_up(mipHeight, blockHeight), blockHeightMip0);

			mSurfaces.at(i)->mWidth = mipWidth;
			mSurfaces.at(i)->mHeight = mipHeight;

			// When swizzled data takes up less than a block height, tegra_swizzle gets mad.
			// Here just allocate what it expects to find into a new array and copy to that.
			// There's likely a better solution than this, but none that I've found.
			F_UT swizzledSurfaceDataExpandedSize = swizzled_mip_size(div_round_up(mipWidth, blockWidth), div_round_up(mipHeight, blockHeight), div_round_up(mipDepth, blockDepth), mipBlockHeight, bytesPerBlock);
			std::shared_ptr<F_U8[]> swizzledSurfaceDataExpanded = std::shared_ptr<F_U8[]>(new F_U8[swizzledSurfaceDataExpandedSize]);
			std::memcpy(swizzledSurfaceDataExpanded.get(), swizzledSurfaceData.get(), swizzledSurfaceDataExpandedSize);

			F_U8* deswizzledSurfaceData;
			F_UT deswizzledSurfaceDataSize;
			deswizzle_block_linear(div_round_up(mipWidth, blockWidth), div_round_up(mipHeight, blockHeight), div_round_up(mipDepth, blockDepth), swizzledSurfaceDataExpanded.get(), swizzledSurfaceDataExpandedSize, mipBlockHeight, bytesPerBlock, &deswizzledSurfaceData, &deswizzledSurfaceDataSize);
			mSurfaces.at(i)->mData = std::shared_ptr<F_U8[]>(deswizzledSurfaceData);
			mSurfaces.at(i)->mDataSize = deswizzled_mip_size(div_round_up(mipWidth, blockWidth), div_round_up(mipHeight, blockHeight), div_round_up(mipDepth, blockDepth), bytesPerBlock);
			
			std::ofstream outfile("TEST.bin", std::ios::out | std::ios::binary);
			outfile.write((const char*)&deswizzledSurfaceData[0], deswizzledSurfaceDataSize);
		
		}

		return true;
	}
	bool V0x11::Serialize() {
		if (!Formats::Resources::TXTG::TXTG::WriteBaseInfo())
			return false;

		return true;
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

	F_U16 V0x11::GetDepth() {
		return mDepth;
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

	Formats::Texture::Format V0x11::GetFormat() {
		switch (mFormat) {
		case 0x101:
			return Formats::Texture::Format::ASTC_4x4_UNORM;
		case 0x102:
			return Formats::Texture::Format::ASTC_8x8_UNORM;
		case 0x105:
			return Formats::Texture::Format::ASTC_8x8_SRGB;
		case 0x109:
			return Formats::Texture::Format::ASTC_4x4_SRGB;
		case 0x202:
			return Formats::Texture::Format::BC1_UNORM;
		case 0x203:
			return Formats::Texture::Format::BC1_UNORM_SRGB;
		case 0x302:
			return Formats::Texture::Format::BC1_UNORM;

		case 0x505:
			return Formats::Texture::Format::BC3_UNORM_SRGB;
		case 0x602:
			return Formats::Texture::Format::BC4_UNORM;
		case 0x606:
			return Formats::Texture::Format::BC4_UNORM;
		case 0x607:
			return Formats::Texture::Format::BC4_UNORM;
		case 0x702:
			return Formats::Texture::Format::BC5_UNORM;
		case 0x703:
			return Formats::Texture::Format::BC5_UNORM;
		case 0x707:
			return Formats::Texture::Format::BC5_UNORM;
		case 0x901:
			return Formats::Texture::Format::BC7_UNORM;

		default:
			return Formats::Texture::Format::UNKNOWN;
		}
	}
}