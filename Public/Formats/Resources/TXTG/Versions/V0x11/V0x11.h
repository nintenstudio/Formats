#pragma once

#include <Formats/Resources/TXTG/TXTG.h>
#include <Formats/Resources/TXTG/Versions/V0x11/Surface.h>
#include <Formats/Aliases/Primitives.h>

#include <vector>
#include <memory>

namespace Formats::Resources::TXTG::Versions::V0x11 {
	class V0x11 : public Formats::Resources::TXTG::TXTG {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;

		virtual F_U16 GetWidth() override;
		virtual F_U16 GetHeight() override;
		virtual F_U16 GetArrayCount() override;
		virtual F_U8 GetMipCount() override;
		virtual std::shared_ptr<Formats::Resources::TXTG::Surface> GetSurface(F_U16 arrayIndex, F_U8 mipLevel) override;

	protected:
		F_U16 mWidth;
		F_U16 mHeight;
		F_U16 mArrayCount;
		F_U8 mMipCount;
		F_U8 mUnk1;
		F_U8 mUnk2;

		F_U8 mFormatFlag;
		F_U32 mFormatSetting;

		F_U8 mCompSelectR;
		F_U8 mCompSelectG;
		F_U8 mCompSelectB;
		F_U8 mCompSelectA;

		F_U8 mHash[32];

		F_U16 mFormat;
		F_U16 mUnk3;

		F_U32 mTextureSetting1;
		F_U32 mTextureSetting2;
		F_U32 mTextureSetting3;
		F_U32 mTextureSetting4;

		std::vector<std::shared_ptr<Formats::Resources::TXTG::Versions::V0x11::Surface>> mSurfaces;
	};
}