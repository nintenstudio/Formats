#pragma once

#include <Formats/Resources/BFRES/BFRES.h>

#include <Formats/IO/Endianness.h>
#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::BFRES_Versions {
	class V0_10_0_0 : public Formats::Resources::BFRES::BFRES {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;

		Formats::IO::Endianness mEndianness;
		F_U8 mAlignment;
		F_U8 mTargetAddressSize;
		std::string mFileName;
		F_U16 mFlag;
		F_U16 mBlockOffset;
	};
}