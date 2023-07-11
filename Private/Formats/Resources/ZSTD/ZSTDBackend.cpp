#include <Formats/Resources/ZSTD/ZSTDBackend.h>

#include <Formats/IO/BinaryIOStreamBasics/Buffer/Buffer.h>
#include <Formats/Aliases/Primitives.h>
#define ZSTD_STATIC_LINKING_ONLY
#include <zstd.h>
#include <zdict.h>
#include <vector>

ZSTD_DCtx* dctx = nullptr;
ZSTD_CCtx* cctx = nullptr;

std::vector<ZSTD_DDict*> ddicts; // For freeing
std::vector<ZSTD_CDict*> cdicts; // For freeing

namespace Formats::Resources::ZSTD {
	void ZSTDBackend::Init() {
		dctx = ZSTD_createDCtx();
		cctx = ZSTD_createCCtx();
	}

	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> ZSTDBackend::Decompress(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		ZSTD_DCtx_reset(dctx, ZSTD_reset_session_and_parameters);
		ZSTD_DCtx_setParameter(dctx, ZSTD_d_refMultipleDDicts, ZSTD_rmd_refMultipleDDicts);

		F_U8* compressedBuffer = stream->GetBuffer().get();
		F_UT compressedBufferLength = stream->GetBufferLength();
		F_UT frameContentSize = ZSTD_getFrameContentSize(compressedBuffer, compressedBufferLength);
		F_U8* decompressedBuffer = new F_U8[frameContentSize];

		ZSTD_inBuffer inBuffer;
		inBuffer.pos = 0;
		inBuffer.src = compressedBuffer;
		inBuffer.size = compressedBufferLength;

		ZSTD_outBuffer outBuffer;
		outBuffer.pos = 0;
		outBuffer.dst = decompressedBuffer;
		outBuffer.size = frameContentSize;

		while (true) {
			size_t status = ZSTD_decompressStream(dctx, &outBuffer, &inBuffer);
			if (status == 0) {
				break; // We've decompressed successfully!
			}
			if (ZSTD_isError(status)) {
				ZSTD_DCtx_reset(dctx, ZSTD_reset_session_only);
				return nullptr;
			}
		}
	
		std::shared_ptr<Formats::IO::BinaryIOStreamBasic> res = std::make_shared<Formats::IO::BinaryIOStreamBasics::Buffer::Buffer>(std::shared_ptr<F_U8>(decompressedBuffer), frameContentSize);
		return res;
	}
	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> ZSTDBackend::Compress(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		ZSTD_CCtx_reset(cctx, ZSTD_reset_session_and_parameters);

		F_U8* decompressedBuffer = stream->GetBuffer().get();
		F_UT decompressedBufferSize = stream->GetBufferLength();
		F_U8* compressedBuffer = new F_U8[stream->GetBufferLength()];
		F_UT compressedBufferSize = stream->GetBufferLength(); // ZSTD won't compress to larger than the input data.

		ZSTD_inBuffer inBuffer;
		inBuffer.pos = 0;
		inBuffer.src = decompressedBuffer;
		inBuffer.size = decompressedBufferSize;

		ZSTD_outBuffer outBuffer;
		outBuffer.pos = 0;
		outBuffer.dst = compressedBuffer;
		outBuffer.size = compressedBufferSize;

		while (inBuffer.pos < inBuffer.size)
			ZSTD_compressStream2(cctx, &outBuffer, &inBuffer, ZSTD_e_continue);

		std::shared_ptr<Formats::IO::BinaryIOStreamBasic> res = std::make_shared<Formats::IO::BinaryIOStreamBasics::Buffer::Buffer>(std::shared_ptr<F_U8>(compressedBuffer), compressedBufferSize);
		return res;
	}

	bool AddDict(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream, F_U32 compressionLevel = 5) {
		ZSTD_DDict* ddict = ZSTD_createDDict(stream->GetBuffer().get(), stream->GetBufferLength());
		ZSTD_DCtx_refDDict(dctx, ddict);
		ddicts.push_back(ddict);

		ZSTD_CDict* cdict = ZSTD_createCDict(stream->GetBuffer().get(), stream->GetBufferLength(), compressionLevel);
		ZSTD_CCtx_refCDict(cctx, cdict);
		cdicts.push_back(cdict);
	}
}