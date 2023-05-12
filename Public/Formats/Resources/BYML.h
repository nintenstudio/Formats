#pragma once

#include <Formats/Resource.h>
#include <Formats/IO/Endianness.h>

namespace Formats::Resources {
	/// <summary>
	/// This is a base class. This should not be used directly for serialization or deserialization.
	/// Instead, use a specific BYML version from the Formats::Resources::BYML namespace.
	/// </summary>
	class BYML : public Formats::Resource {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;

		unsigned short mVersion;
		Formats::IO::Endianness mEndianness;

	protected:
		bool ParseBaseInfo();
	};
}