#pragma once

#include <Formats/Resource.h>

namespace Formats::Resources {
	class BFRES : public Formats::Resource {
	public:
		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) = 0;

		unsigned char mVersionMajor1;
		unsigned char mVersionMajor2;
		unsigned char mVersionMinor1;
		unsigned char mVersionMinor2;

	protected:
		bool ParseBaseInfo();
	};
}