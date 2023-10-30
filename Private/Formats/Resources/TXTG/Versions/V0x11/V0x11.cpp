#include <Formats/Resources/TXTG/Versions/V0x11/V0x11.h>

#include <Formats/Resources/ZSTD/ZSTDBackend.h>
#include <Formats/IO/Streams/Buffer/Buffer.h>

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

		mWidth = mStream->ReadU16();
		mHeight = mStream->ReadU16();
		mDepth = mStream->ReadU16();
		mMipCount = mStream->ReadU8();
		mUnk1 = mStream->ReadU8();
		mUnk2 = mStream->ReadU8();
		mStream->ReadU16(); // Padding

		mFormatFlag = mStream->ReadU8();
		mFormatSetting = mStream->ReadU32();

		mCompSelectR = mStream->ReadU8();
		mCompSelectG = mStream->ReadU8();
		mCompSelectB = mStream->ReadU8();
		mCompSelectA = mStream->ReadU8();

		mStream->ReadBytes(&mHash[0], 32);

		mFormat = mStream->ReadU16();
		mUnk3 = mStream->ReadU16();

		mTextureSetting1 = mStream->ReadU32();
		mTextureSetting2 = mStream->ReadU32();
		mTextureSetting3 = mStream->ReadU32();
		mTextureSetting4 = mStream->ReadU32();

		mSurfaces.reserve(mMipCount * mDepth);
		for (F_U32 i = 0; i < mMipCount * mDepth; i++) {
			F_U16 arrayIndex = mStream->ReadU16();
			F_U8 mipLevel = mStream->ReadU8();
			F_U8 surfaceCount = mStream->ReadU8();
			mSurfaces.push_back(std::make_shared<Formats::Resources::TXTG::Versions::V0x11::Surface>(arrayIndex, mipLevel, surfaceCount));
		}
		for (F_U32 i = 0; i < mMipCount * mDepth; i++) {
			mSurfaces.at(i)->mZSTDCompressedSize = mStream->ReadU32();
			mSurfaces.at(i)->mUnk = mStream->ReadU32();
		}

		Formats::Texture::Format format = GetFormat();
		if (format == Formats::Texture::Format::UNKNOWN)
			return false;
		F_UT blockWidth = Formats::Texture::GetFormatBlockWidth(format);
		F_UT blockHeight = Formats::Texture::GetFormatBlockHeight(format);
		F_UT blockDepth = Formats::Texture::GetFormatBlockDepth(format);
		F_UT bytesPerBlock = Formats::Texture::GetFormatBytesPerBlock(format);
		BlockHeight blockHeightMip0 = block_height_mip0(div_round_up(mHeight, blockHeight));

		for (F_U32 i = 0; i < mMipCount * mDepth; i++) {
			std::shared_ptr<F_U8[]> compressedSurface = std::shared_ptr<F_U8[]>(new F_U8[mSurfaces.at(i)->mZSTDCompressedSize]);
			mStream->ReadBytes(compressedSurface.get(), mSurfaces.at(i)->mZSTDCompressedSize);

			std::shared_ptr<Formats::IO::Streams::Buffer::Buffer> compressedSurfaceStream = std::make_shared<Formats::IO::Streams::Buffer::Buffer>(compressedSurface, mSurfaces.at(i)->mZSTDCompressedSize);

			std::shared_ptr<Formats::IO::Stream> swizzledSurfaceDataStream = Formats::Resources::ZSTD::ZSTDBackend::Decompress(compressedSurfaceStream);
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
		}

		return true;
	}
	bool V0x11::Serialize() {
		if (!Formats::Resources::TXTG::TXTG::WriteBaseInfo())
			return false;

		mStream->WriteU16(mWidth);
		mStream->WriteU16(mHeight);
		mStream->WriteU16(mDepth);
		mStream->WriteU8(mMipCount);
		mStream->WriteU8(mUnk1);
		mStream->WriteU8(mUnk2);
		mStream->WriteU16(0); // Padding

		mStream->WriteU8(mFormatFlag);
		mStream->WriteU32(mFormatSetting);

		mStream->WriteU8(mCompSelectR);
		mStream->WriteU8(mCompSelectG);
		mStream->WriteU8(mCompSelectB);
		mStream->WriteU8(mCompSelectA);

		mStream->WriteBytes(&mHash[0], 32);

		mStream->WriteU16(mFormat);
		mStream->WriteU16(mUnk3);

		mStream->WriteU32(mTextureSetting1);
		mStream->WriteU32(mTextureSetting2);
		mStream->WriteU32(mTextureSetting3);
		mStream->WriteU32(mTextureSetting4);

		for (std::shared_ptr<Formats::Resources::TXTG::Versions::V0x11::Surface> surface : mSurfaces) {
			mStream->WriteU16(surface->mArrayIndex);
			mStream->WriteU8(surface->mMipLevel);
			mStream->WriteU8(surface->mSurfaceCount);
		}
		for (std::shared_ptr<Formats::Resources::TXTG::Versions::V0x11::Surface> surface : mSurfaces) {
			mStream->WriteU32(surface->mZSTDCompressedSize);
			mStream->WriteU32(surface->mUnk);
		}

		Formats::Texture::Format format = GetFormat();
		if (format == Formats::Texture::Format::UNKNOWN)
			return false;
		F_UT blockWidth = Formats::Texture::GetFormatBlockWidth(format);
		F_UT blockHeight = Formats::Texture::GetFormatBlockHeight(format);
		F_UT blockDepth = Formats::Texture::GetFormatBlockDepth(format);
		F_UT bytesPerBlock = Formats::Texture::GetFormatBytesPerBlock(format);
		BlockHeight blockHeightMip0 = block_height_mip0(div_round_up(mHeight, blockHeight));

		for (std::shared_ptr<Formats::Resources::TXTG::Versions::V0x11::Surface> surface : mSurfaces) {
			F_UT mipWidth = std::max(1, mWidth >> surface->mMipLevel);
			F_UT mipHeight = std::max(1, mHeight >> surface->mMipLevel);
			F_UT mipDepth = std::max(1, mDepth >> surface->mMipLevel);
			BlockHeight mipBlockHeight = mip_block_height(div_round_up(mipHeight, blockHeight), blockHeightMip0);

			F_U8* swizzledSurfaceData;
			F_UT swizzledSurfaceDataSize;
			swizzle_block_linear(div_round_up(mipWidth, blockWidth), div_round_up(mipHeight, blockHeight), div_round_up(mipDepth, blockDepth), surface->mData.get(), surface->mDataSize, mipBlockHeight, bytesPerBlock, &swizzledSurfaceData, &swizzledSurfaceDataSize);
			mStream->WriteBytes(swizzledSurfaceData, swizzledSurfaceDataSize);
		}

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