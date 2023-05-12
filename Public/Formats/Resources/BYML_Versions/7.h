#pragma once

#include <Formats/Resources/BYML.h>

namespace Formats::Resources::BYML_Versions {
	class V7 : public Formats::Resources::BYML {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;
	};
}