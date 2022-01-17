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

#include "NRT_Helpers.h"

namespace System
{

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public static bool IsNullOrEmpty([NotNullWhen(false)] string? value)
	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	bool string2::IsNullOrEmpty(const std::string& value)
	{
		return value.empty();
	}
}

namespace System::Diagnostics
{

	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	//ORIGINAL LINE: [Conditional("DEBUG")] public static void Assert([DoesNotReturnIf(false)] bool condition)
	void Debug2::Assert(bool condition)
	{
		assert(condition);
	}

	void Debug2::Fail(const std::string& str)
	{
		std::cerr << "Fail: " << str << std::endl;
	}
}
