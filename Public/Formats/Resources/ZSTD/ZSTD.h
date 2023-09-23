#pragma once

#include <Formats/Resource.h>

#include <Formats/Resources/ZSTD/ZSTDBackend.h>
#include <Formats/Resources/ZSTD/CompressionInfo.h>
#include <memory>
#include <type_traits>

namespace Formats::Resources::ZSTD {
	template <typename T>
	class ZSTD : Formats::Resource {
	public:
		static std::shared_ptr<ZSTD> Factory(std::shared_ptr<Formats::IO::Stream> stream) {
			// FORMATS_TODO_FUNCTIONAL: Decompress, pass decompressed stream through system to detect type and return parsed resource, create a ZSTD from that.
		}

		ZSTD(std::shared_ptr<Formats::IO::Stream> stream) : Formats::Resource(stream) {
			static_assert(std::is_base_of<Formats::Resource, T>::value, "Type parameter does not derive as required!");
		}
		ZSTD() : Formats::Resource() {
			static_assert(std::is_base_of<Formats::Resource, T>::value, "Type parameter does not derive as required!");
		}

		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;

		virtual void SetStream(std::shared_ptr<Formats::IO::Stream> stream) override;

		operator T() {
			return mResource;
		}

		T mResource;
		Formats::Resources::ZSTD::CompressionInfo mCompressionInfo;
	};
}