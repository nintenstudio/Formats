#pragma once

#include <Formats/Resource.h>
#include <memory>

namespace Formats::Resources::AAMP {
	class AAMP : public Formats::Resource {
	public:
		static std::shared_ptr<AAMP> Factory(std::iostream* stream);

		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;
	};
}