#include <Formats/Resources/ZSTD/ZSTDBackend.h>

#include <Formats/Aliases/Primitives.h>
#define ZSTD_STATIC_LINKING_ONLY
#include <zstd.h>
#include <zdict.h>
#include <vector>

ZSTD_DCtx* dctx = nullptr;

std::vector<ZSTD_DDict*> ddicts; // For freeing

namespace Formats::Resources::ZSTD {
	void ZSTDBackend::Init() {
		ZSTD_DCtx_setParameter(dctx, ZSTD_d_refMultipleDDicts, ZSTD_rmd_refMultipleDDicts);
		dctx = ZSTD_createDCtx();
	}

	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> ZSTDBackend::Decompress(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		F_U64 contentSize = ZSTD_getFrameContentSize()
		ZSTD_decompressStream(dctx, );
	}
	std::shared_ptr<Formats::IO::BinaryIOStreamBasic> ZSTDBackend::Compress(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {

	}

	bool AddDict(std::shared_ptr<Formats::IO::BinaryIOStreamBasic> stream) {
		ZSTD_DDict* ddict = ZSTD_createDDict(nullptr, 0);
		ZSTD_DCtx_refDDict(dctx, ddict);
		ddicts.push_back(ddict);
	}
}