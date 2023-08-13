#include <Formats/Resources/TXTG/TXTG.h>

#include <Formats/Resources/TXTG/Versions/V0x11/V0x11.h>

struct BlockDimX64
        {
            F_U64 width;
            F_U64 height;
            F_U64 depth;
		};

extern "C" void deswizzle_surface(F_U64 width, F_U64 height, F_U64 depth,
            F_U8* source, F_U64 sourceLength,
            F_U8* destination, F_U64 destinationLength,
            BlockDimX64 blockDim, F_U64 blockHeightMip0, F_U64 bytesPerPixel,
            F_U64 mipmapCount, F_U64 arrayCount);

namespace Formats::Resources::TXTG {
	std::shared_ptr<TXTG> TXTG::Factory(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		std::shared_ptr<Formats::Resources::TXTG::Versions::V0x11::V0x11> v0x11 = std::make_shared<Formats::Resources::TXTG::Versions::V0x11::V0x11>();
		v0x11->SetStream(stream);
		if (v0x11->Parse())
			return v0x11;

		// Test interop temporarily
		//deswizzle_surface(0, 0, 0, 0, 0, 0, 0, BlockDimX64(), 0, 0, 0, 0);

		return nullptr;
	}

	void TXTG::SetStream(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		Formats::Resource::SetStream(stream);

		mBStream = stream->Factory(Formats::IO::Endianness::LITTLE); // Unsure if endianess is specified in the format.
	}

	bool TXTG::ParseBaseInfo() {
		F_U16 headerSize;
		mStream->ReadBytes(&headerSize, 2);

		mStream->ReadBytes(&mVersion, 2);

		char signature[5];
		mStream->ReadBytes(&signature, 4);
		signature[4] = '\0';

		if (strcmp(signature, "6PK0") != 0)
			return false;

		mBStream = mStream->Factory(Formats::IO::Endianness::LITTLE); // Unsure if endianess is specified in the format.

		return true;
	}
	bool TXTG::WriteBaseInfo() {
		F_U16 headerSize = 0x50;
		mStream->WriteBytes(&headerSize, 2);

		mStream->WriteBytes(&mVersion, 2);

		char signature[5] = "6PK0";
		mStream->WriteBytes(&signature, 4);
		signature[4] = '\0';

		mBStream = mStream->Factory(Formats::IO::Endianness::LITTLE); // Unsure if endianess is specified in the format.

		return true;
	}
}