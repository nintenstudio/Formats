#pragma once

#include <istream>
#include <memory>

namespace Formats::Resources {
	class Resource;
	typedef void (*ResourceParsedCallback)(Resource* resource, bool success);

	class Resource {
	public:
		static std::shared_ptr<Resource> Factory(std::iostream* stream);

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(ResourceParsedCallback callback) = 0; // FORMATS_TODO_FUNCTIONAL Implement

		void SetStream(std::iostream* stream) {
			mStream = stream;
		}
	protected:
		Resource(std::iostream* stream) : mStream(stream) {

		}
		Resource() : mStream(nullptr) {

		}

		std::iostream* mStream;
	};
}