#pragma once

#include <Formats/Resources/Resource.h>
#include <memory>

namespace Formats::Resources::AAMP {
	class AAMP : public Formats::Resources::Resource {
	public:
		static std::shared_ptr<AAMP> Factory(std::iostream* stream);

		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::Resources::ResourceParsedCallback callback) override;
	};
}