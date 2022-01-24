#include "IcedFeatures.h"
#include "Decoder.h"

namespace Iced::Intel
{
	bool IcedFeatures::HasGasFormatter()
	{
#if defined(GAS)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasIntelFormatter()
	{
#if defined(INTEL)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasMasmFormatter()
	{
#if defined(MASM)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasNasmFormatter()
	{
#if defined(NASM)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasFastFormatter()
	{
#if defined(FAST_FMT)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasDecoder()
	{
#if defined(DECODER)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasEncoder()
	{
#if defined(ENCODER)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasBlockEncoder()
	{
#if defined(ENCODER) && defined(BLOCK_ENCODER)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasOpCodeInfo()
	{
#if defined(ENCODER) && defined(OPCODE_INFO)
		return true;
#else
		return false;
#endif
	}

	bool IcedFeatures::HasInstructionInfo()
	{
#if defined(INSTR_INFO)
		return true;
#else
		return false;
#endif
	}

	void IcedFeatures::Initialize()
	{

	}
}
