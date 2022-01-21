#include "OpCodeInfoStrings.h"

namespace Iced::Intel::EncoderInternal
{
	const char* GetOpCodeInfoStringAtIndex(int index)
	{
		return &OpCodeInfoStrings::Data[index];
	}
}