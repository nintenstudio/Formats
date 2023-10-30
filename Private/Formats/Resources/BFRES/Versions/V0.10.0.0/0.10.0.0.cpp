#include <Formats/Resources/BFRES/Versions/V0.10.0.0/0.10.0.0.h>

#include <Formats/Resources/BFRES/Versions/V0.10.0.0/IO/ByteOrderMark.h>

namespace Formats::Resources::BFRES_Versions {
	bool V0_10_0_0::Parse() {
		if (!Formats::Resources::BFRES::BFRES::ParseBaseInfo())
			return false;

		if (mVersionMajor1 != 0 || mVersionMajor2 != 10 || mVersionMinor1 != 0 || mVersionMinor2 != 0)
			return false;

		Formats::Resources::BFRES::Versions::V0_10_0_0::IO::ByteOrderMark byteOrderMark = (Formats::Resources::BFRES::Versions::V0_10_0_0::IO::ByteOrderMark)mStream->ReadU32();

		switch (byteOrderMark) {
			case Formats::Resources::BFRES::Versions::V0_10_0_0::IO::ByteOrderMark::LITTLE:
				mEndianness = Formats::IO::Endianness::LITTLE;
				break;
			case Formats::Resources::BFRES::Versions::V0_10_0_0::IO::ByteOrderMark::BIG:
				mEndianness = Formats::IO::Endianness::BIG;
				break;
			default:
				return false;
		}

		mAlignment = mStream->ReadU8();
		mTargetAddressSize = mStream->ReadU8();

		mStream->PushSeek(mStream->ReadU32());
		mFileName = mStream->ReadZeroTerminatedString();
		mStream->PopSeek();

		mFlag = mStream->ReadU16();
		mBlockOffset = mStream->ReadU16();

		return true;
	}
	bool V0_10_0_0::Serialize() {
		return false;
	}
}