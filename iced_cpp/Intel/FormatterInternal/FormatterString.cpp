// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>
#include <csharp/interfaces.h>
#include <csharp/primitives.h>

// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "FormatterString.h"

namespace Iced::Intel::FormatterInternal
{

	std::int32_t FormatterString::GetLength() const
	{
		return lower.length();
	}

	FormatterString::FormatterString(const std::string& lower)
	{
		//C# TO C++ CONVERTER TODO TASK: There is no direct C++ equivalent to this .NET String method:
		assert(lower.ToLowerInvariant() == lower);
		this->lower = lower;
		//C# TO C++ CONVERTER TODO TASK: There is no direct C++ equivalent to this .NET String method:
		upper = std::string::Intern(lower.ToUpperInvariant());
	}

	std::vector<FormatterString> FormatterString::Create(std::vector<std::string>& strings)
	{
		auto res = std::vector<FormatterString>(strings.size());
		for (std::int32_t i = 0; i < strings.size(); i++)
		{
			res[i] = FormatterString(strings[i]);
		}
		return res;
	}

	std::string FormatterString::Get(bool upper)
	{
		return upper ? this->upper : lower;
	}

	std::string FormatterString::GetLower() const
	{
		return lower;
	}
}
