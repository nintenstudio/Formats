#pragma once

#include <Formats/IO/BinaryIOStreamBasic.h>
#include <memory>

namespace Formats {
	class Resource;
	typedef void (*ResourceParsedCallback)(Resource* resource, bool success);

	class Resource {
	public:
		static std::shared_ptr<Resource> Factory(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream);

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(ResourceParsedCallback callback) = 0; // FORMATS_TODO_FUNCTIONAL Implement

		virtual void SetStream(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
			mStream = stream;
		}
	protected:
		Resource(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) : mStream(stream) {

		}
		Resource() : mStream(nullptr) {

		}

		std::shared_ptr<Formats::IO::BinaryIOStreamBasic> mStream;
	};
}