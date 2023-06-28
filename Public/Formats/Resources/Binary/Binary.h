#pragma once

#include <Formats/Resource.h>

namespace Formats::Resources::Binary {

	/// <summary>
	/// Just holds on to a stream. For use when arbitrary data needs to be treated as a resource.
	/// </summary>
	class Binary : Formats::Resource {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;
	};
}