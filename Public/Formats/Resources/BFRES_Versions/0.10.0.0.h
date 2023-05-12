#pragma once

#include <Formats/Resources/BFRES.h>

namespace Formats::Resources::BFRES_Versions {
	class V0_10_0_0 : public Formats::Resources::BFRES {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;
	};
}