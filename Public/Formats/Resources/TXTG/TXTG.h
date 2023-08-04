#pragma once

#include <Formats/Resource.h>

#include <Formats/Resources/TXTG/Surface.h>
#include <Formats/IO/BinaryIOStream.h>
#include <Formats/IO/Endianness.h>

#include <string>
#include <memory>

namespace Formats::Resources::TXTG {
	class TXTG : public Formats::Resource {
	public:
		static std::shared_ptr<TXTG> Factory(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream);

		virtual bool Parse() = 0;
		virtual bool Serialize() = 0;
		virtual bool RequestParse(Formats::ResourceParsedCallback callback) = 0;

		virtual void SetStream(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) override;

		virtual F_U16 GetWidth() = 0;
		virtual F_U16 GetHeight() = 0;
		virtual F_U16 GetArrayCount() = 0;
		virtual F_U8 GetMipCount() = 0;
		virtual std::shared_ptr<Formats::Resources::TXTG::Surface> GetSurface(F_U16 arrayIndex, F_U8 mipLevel) = 0;

		unsigned short mVersion;

		std::shared_ptr<Formats::IO::BinaryIOStream> mBStream;
	protected:
		bool ParseBaseInfo();
		bool WriteBaseInfo();
	};
}