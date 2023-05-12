#pragma once

#include <Formats/Resource.h>

namespace Formats::Resources {
	/// <summary>
	/// This is a base class. This should not be used directly for serialization or deserialization.
	/// Instead, use a specific BFRES version from the Formats::Resources::BFRES namespace.
	/// </summary>
	class BFRES : public Formats::Resource {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;

		unsigned char mVersionMajor1;
		unsigned char mVersionMajor2;
		unsigned char mVersionMinor1;
		unsigned char mVersionMinor2;

	protected:
		bool ParseBaseInfo();
	};
}