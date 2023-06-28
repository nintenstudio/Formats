#pragma once

#include <Formats/Resource.h>
#include <Formats/IO/BinaryIOStream.h>
#include <Formats/IO/Endianness.h>

#include <string>
#include <memory>

namespace Formats::Resources::BYML {
	class BYML : public Formats::Resource {
	public:
		static std::shared_ptr<BYML> Factory(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream);

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) = 0;

		virtual void SetStream(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) override;

		virtual std::string ToYAML() = 0;

		Formats::IO::Endianness mEndianness;
		unsigned short mVersion;

		std::shared_ptr<Formats::IO::BinaryIOStream> mBStream;
	protected:
		bool ParseBaseInfo();
		bool WriteBaseInfo();
	};
}