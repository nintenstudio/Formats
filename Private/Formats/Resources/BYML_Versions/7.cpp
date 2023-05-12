#include <Formats/Resources/BYML_Versions/7.h>

namespace Formats::Resources::BYML_Versions {
	bool V7::Parse() {
		if (!Formats::Resources::BYML::ParseBaseInfo())
			return false;

		if (mVersion != 7)
			return false;

		// FORMATS_TODO_FUNCTIONAL Implement

		return false;
	}
	bool V7::Serialize() {
		return false;
	}
}