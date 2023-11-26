#pragma once

#include <Formats/Resource.h>
#include <Formats/IO/Stream.h>
#include <Formats/IO/Endianness.h>

#include <string>
#include <memory>

namespace Formats::Resources::BYML {
	class BYML : public Formats::Resource {
	public:
		static std::shared_ptr<BYML> Factory(std::shared_ptr<Formats::IO::Stream> stream);

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) = 0;

		virtual void SetStream(std::shared_ptr<Formats::IO::Stream> stream) override;

		virtual std::string ToYAML() = 0;
		virtual bool LoadYAML(std::string text) = 0;

		Formats::IO::Endianness mEndianness;
		unsigned short mVersion;
	protected:
		bool ParseBaseInfo();
		bool WriteBaseInfo();
	};
}