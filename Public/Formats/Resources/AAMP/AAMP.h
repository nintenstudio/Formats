#pragma once

#include <Formats/Resource.h>

namespace Formats::Resources {
	class AAMP : public Formats::Resource {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;
	};
}