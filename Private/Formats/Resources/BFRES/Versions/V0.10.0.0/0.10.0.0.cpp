#include <Formats/Resources/BFRES/Versions/V0.10.0.0/0.10.0.0.h>

namespace Formats::Resources::BFRES_Versions {
	bool V0_10_0_0::Parse() {
		if (!Formats::Resources::BFRES::BFRES::ParseBaseInfo())
			return false;

		if (mVersionMajor1 != 0 || mVersionMajor2 != 10 || mVersionMinor1 != 0 || mVersionMinor2 != 0)
			return false;

		// FORMATS_TODO_FUNCTIONAL Implement

		return false;
	}
	bool V0_10_0_0::Serialize() {
		return false;
	}
}