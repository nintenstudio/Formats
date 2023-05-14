#pragma once

#include <Formats/Resource.h>
#include <Formats/IO/BinaryIOStream.h>
#include <Formats/IO/Endianness.h>

#include <memory>

namespace Formats::Resources::BYML {
	class BYML : public Formats::Resource {
	public:
		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) = 0;

		Formats::IO::Endianness mEndianness;
		unsigned short mVersion;

		std::shared_ptr<Formats::IO::BinaryIOStream> mBStream;
	protected:
		bool ParseBaseInfo();

	};
}