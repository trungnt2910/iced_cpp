// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "IcedFeatures.h"
#include "Decoder.h"

namespace Iced::Intel
{

	bool IcedFeatures::GetHasGasFormatter()
	{
		return true;
	}

	bool IcedFeatures::GetHasIntelFormatter()
	{
		return true;
	}

	bool IcedFeatures::GetHasMasmFormatter()
	{
		return true;
	}

	bool IcedFeatures::GetHasNasmFormatter()
	{
		return true;
	}

	bool IcedFeatures::GetHasFastFormatter()
	{
		return true;
	}

	bool IcedFeatures::GetHasDecoder()
	{
		return true;
	}

	bool IcedFeatures::GetHasEncoder()
	{
		return true;
	}

	bool IcedFeatures::GetHasBlockEncoder()
	{
		return true;
	}

	bool IcedFeatures::GetHasOpCodeInfo()
	{
		return true;
	}

	bool IcedFeatures::GetHasInstructionInfo()
	{
		return true;
	}

	void IcedFeatures::Initialize()
	{
		// The decoder already initializes this stuff, but when it's called, it's a little bit too late.
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
		//RuntimeHelpers::RunClassConstructor(typeof(Decoder)->TypeHandle);
	}
}
