#pragma once

#include <Formats/Resources/Resource.h>
#include <Formats/IO/BinaryIOStream.h>
#include <Formats/IO/Endianness.h>

#include <memory>

namespace Formats::Resources::BYML {
	class BYML : public Formats::Resources::Resource {
	public:
		static std::shared_ptr<BYML> Factory(std::iostream* stream);

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(Formats::Resources::ResourceParsedCallback callback) = 0;

		Formats::IO::Endianness mEndianness;
		unsigned short mVersion;

		std::shared_ptr<Formats::IO::BinaryIOStream> mBStream;
	protected:
		bool ParseBaseInfo();

	};
}