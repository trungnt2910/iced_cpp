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

#include "NRT.h"

namespace System::Diagnostics::CodeAnalysis
{

	NotNullWhenAttribute::NotNullWhenAttribute(bool returnValue)
	{
		ReturnValue = returnValue;
	}

	bool NotNullWhenAttribute::GetReturnValue() const
	{
		return ReturnValue;
	}

	DoesNotReturnAttribute::DoesNotReturnAttribute()
	{
	}

	DoesNotReturnIfAttribute::DoesNotReturnIfAttribute(bool parameterValue)
	{
		ParameterValue = parameterValue;
	}

	bool DoesNotReturnIfAttribute::GetParameterValue() const
	{
		return ParameterValue;
	}
}
