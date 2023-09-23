#pragma once

#include <Formats/Resources/MeshCodec/MeshCodec.h>

#include <Formats/Aliases/Primitives.h>

namespace Formats::Resources::MeshCodec::Versions::V1_1_0_0 {
	class V1_1_0_0 : public Formats::Resources::MeshCodec::MeshCodec {
	public:
		virtual bool Parse() override;
		virtual bool Serialize() override;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) override;

	protected:
		F_U32 mFlags;
	};
}