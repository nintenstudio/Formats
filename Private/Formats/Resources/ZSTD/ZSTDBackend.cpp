#include <Formats/Resources/ZSTD/ZSTDBackend.h>

#include <Formats/IO/BinaryIOStreamBasics/Buffer/Buffer.h>
#include <Formats/Aliases/Primitives.h>
#define ZSTD_STATIC_LINKING_ONLY
#include <zstd.h>
#include <zdict.h>
#include <map>
#include <vector>
#include <shared_mutex>
#include <thread>

struct ThreadData {
	ZSTD_DCtx* dctx = nullptr;
	ZSTD_CCtx* cctx = nullptr;
};
std::map<std::thread::id, ThreadData> threadData; std::shared_mutex threadDataMutex;
ThreadData* GetThreadData() {
	return &threadData.at(std::this_thread::get_id());
}

std::vector<ZSTD_DDict*> ddicts; std::shared_mutex ddictMutex; // For freeing
std::vector<ZSTD_CDict*> cdicts; std::shared_mutex cdictMutex; // For freeing

namespace Formats::Resources::ZSTD {
	void ZSTDBackend::InitThread() {
		if (!threadData.count(std::this_thread::get_id())) {
			threadData.insert({ std::this_thread::get_id(), ThreadData() });

			GetThreadData()->dctx = ZSTD_createDCtx();
			ZSTD_DCtx_setParameter(GetThreadData()->dctx, ZSTD_d_refMultipleDDicts, ZSTD_rmd_refMultipleDDicts);

			GetThreadData()->cctx = ZSTD_createCCtx();
		}

		{
			std::shared_lock<std::shared_mutex> lock(ddictMutex);
			for (ZSTD_DDict* ddict : ddicts)
				ZSTD_DCtx_refDDict(GetThreadData()->dctx, ddict);
		}
		{
			std::shared_lock<std::shared_mutex> lock(cdictMutex);
			for (ZSTD_CDict* cdict : cdicts)
				ZSTD_CCtx_refCDict(GetThreadData()->cctx, cdict);
		}
	}

	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> ZSTDBackend::Decompress(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		InitThread();

		ZSTD_DCtx_reset(GetThreadData()->dctx, ZSTD_reset_session_only);
		ZSTD_DCtx_setParameter(GetThreadData()->dctx, ZSTD_d_refMultipleDDicts, ZSTD_rmd_refMultipleDDicts);

		std::shared_ptr<F_U8[]> compressedBuffer = stream->GetBuffer();
		F_UT compressedBufferLength = stream->GetBufferLength();
		F_UT frameContentSize = ZSTD_getFrameContentSize(compressedBuffer.get(), compressedBufferLength);
		if (frameContentSize == ZSTD_CONTENTSIZE_ERROR)
			return nullptr;
		F_U8* decompressedBuffer = new F_U8[frameContentSize];

		ZSTD_inBuffer inBuffer;
		inBuffer.pos = 0;
		inBuffer.src = compressedBuffer.get();
		inBuffer.size = compressedBufferLength;

		ZSTD_outBuffer outBuffer;
		outBuffer.pos = 0;
		outBuffer.dst = decompressedBuffer;
		outBuffer.size = frameContentSize;

		while (true) {
			size_t status = ZSTD_decompressStream(GetThreadData()->dctx, &outBuffer, &inBuffer);
			if (status == 0) {
				break; // We've decompressed successfully!
			}
			if (ZSTD_isError(status)) {
				const char* errorName = ZSTD_getErrorName(status);
				ZSTD_DCtx_reset(GetThreadData()->dctx, ZSTD_reset_session_only);
				return nullptr;
			}
		}
	
		std::shared_ptr<Formats::IO::BinaryIOStreamBasic> res = std::make_shared<Formats::IO::BinaryIOStreamBasics::Buffer::Buffer>(std::shared_ptr<F_U8[]>(decompressedBuffer), frameContentSize);
		return res;
	}
	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> ZSTDBackend::Compress(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		InitThread();

		ZSTD_CCtx_reset(GetThreadData()->cctx, ZSTD_reset_session_and_parameters);

		std::shared_ptr<F_U8[]> decompressedBuffer = stream->GetBuffer();
		F_UT decompressedBufferSize = stream->GetBufferLength();
		F_U8* compressedBuffer = new F_U8[stream->GetBufferLength()];
		F_UT compressedBufferSize = stream->GetBufferLength(); // ZSTD won't compress to larger than the input data.

		ZSTD_inBuffer inBuffer;
		inBuffer.pos = 0;
		inBuffer.src = decompressedBuffer.get();
		inBuffer.size = decompressedBufferSize;

		ZSTD_outBuffer outBuffer;
		outBuffer.pos = 0;
		outBuffer.dst = compressedBuffer;
		outBuffer.size = compressedBufferSize;

		while (inBuffer.pos < inBuffer.size)
			ZSTD_compressStream2(GetThreadData()->cctx, &outBuffer, &inBuffer, ZSTD_e_continue);

		std::shared_ptr<Formats::IO::BinaryIOStreamBasic> res = std::make_shared<Formats::IO::BinaryIOStreamBasics::Buffer::Buffer>(std::shared_ptr<F_U8[]>(compressedBuffer), compressedBufferSize);
		return res;
	}

	bool ZSTDBackend::AddDict(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream, F_U32 compressionLevel) {
		{
			std::unique_lock<std::shared_mutex> lock(ddictMutex);
			ddicts.push_back(ZSTD_createDDict(stream->GetBuffer().get(), stream->GetBufferLength()));
		}
		{
			std::unique_lock<std::shared_mutex> lock(cdictMutex);
			cdicts.push_back(ZSTD_createCDict(stream->GetBuffer().get(), stream->GetBufferLength(), compressionLevel));
		}

		return true;
	}
}