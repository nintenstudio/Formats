#include <Formats/Utils/String.h>

namespace Formats::Utils::String {
	F_U8 HexCharToByte(char input)
	{
		if (input >= '0' && input <= '9')
			return input - '0';
		if (input >= 'A' && input <= 'F')
			return input - 'A' + 10;
		if (input >= 'a' && input <= 'f')
			return input - 'a' + 10;
		throw std::invalid_argument("Invalid input! This is not hex!");
	}
}