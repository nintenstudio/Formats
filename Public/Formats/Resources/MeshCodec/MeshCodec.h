#pragma once

#include <Formats/Resource.h>

#include <Formats/IO/Stream.h>
#include <Formats/Aliases/Primitives.h>
#include <memory>

namespace Formats::Resources::MeshCodec {
	class MeshCodec : public Formats::Resource {
	public:
		static std::shared_ptr<MeshCodec> Factory(std::shared_ptr<Formats::IO::Stream> stream);

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) = 0;

		virtual void SetStream(std::shared_ptr<Formats::IO::Stream> stream) override;

		F_U8 mVersion[4];
	protected:
		bool ParseBaseInfo();
		bool WriteBaseInfo();
	};
}