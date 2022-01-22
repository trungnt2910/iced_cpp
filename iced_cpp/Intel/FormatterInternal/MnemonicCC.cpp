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

#include "MnemonicCC.h"

namespace Iced::Intel::FormatterInternal
{

	FormatterString MnemonicCC::GetMnemonicCC(const FormatterOptions& options, std::int32_t ccIndex, const std::vector<FormatterString>& mnemonics)
	{
		std::int32_t index;
		switch (ccIndex)
		{
		case 0: // o
			assert(mnemonics.size() == 1);
			index = 0;
			break;
		case 1: // no
			assert(mnemonics.size() == 1);
			index = 0;
			break;
		case 2: // b, c, nae
			assert(mnemonics.size() == 3);
			index = static_cast<std::int32_t>(options.GetCCB());
			break;
		case 3: // ae, nb, nc
			assert(mnemonics.size() == 3);
			index = static_cast<std::int32_t>(options.GetCCAe());
			break;
		case 4: // e, z
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCE());
			break;
		case 5: // ne, nz
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCNe());
			break;
		case 6: // be, na
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCBe());
			break;
		case 7: // a, nbe
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCA());
			break;
		case 8: // s
			assert(mnemonics.size() == 1);
			index = 0;
			break;
		case 9: // ns
			assert(mnemonics.size() == 1);
			index = 0;
			break;
		case 10: // p, pe
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCP());
			break;
		case 11: // np, po
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCNp());
			break;
		case 12: // l, nge
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCL());
			break;
		case 13: // ge, nl
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCGe());
			break;
		case 14: // le, ng
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCLe());
			break;
		case 15: // g, nle
			assert(mnemonics.size() == 2);
			index = static_cast<std::int32_t>(options.GetCCG());
			break;
		default:
			throw InvalidOperationException();
		}
		assert(static_cast<std::uint32_t>(index) < static_cast<std::uint32_t>(mnemonics.size()));
		return mnemonics[index];
	}
}
