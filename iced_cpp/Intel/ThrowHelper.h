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

#pragma once

#include <stdexcept>
#include <csharp/exceptionhelper.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	class ThrowHelper final
	{
		// NOTE: NoInlining is not used because RyuJIT doesn't move the method call to the end of the caller's method
	public:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentException()
		[[ noreturn ]] static constexpr void ThrowArgumentException(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowInvalidOperationException()
		[[ noreturn ]] static constexpr void ThrowInvalidOperationException(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_codeWriter()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_codeWriter(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_data()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_data(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_writer()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_writer(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_options()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_options(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_value()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_value(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_list()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_list(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_collection()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_collection(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_array()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_array(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_sb()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_sb(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentNullException_output()
		[[ noreturn ]] static constexpr void ThrowArgumentNullException_output(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_value()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_value(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_index()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_index(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_count()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_count(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_length()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_length(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_operand()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_operand(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_instructionOperand()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_instructionOperand(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_capacity()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_capacity(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_memorySize()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_memorySize(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_size()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_size(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_elementSize()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_elementSize(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_register()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_register(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_code()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_code(bool dummy = 0);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static constexpr void ThrowArgumentOutOfRangeException_data()
		[[ noreturn ]] static constexpr void ThrowArgumentOutOfRangeException_data(bool dummy = 0);
	};

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentException(bool dummy)
	{
		if (!dummy)
		//C# TO C++ CONVERTER TODO TASK: This exception's constructor requires an argument:
		//ORIGINAL LINE: throw new ArgumentException();
		throw std::invalid_argument("no argument provided");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowInvalidOperationException(bool dummy)
	{
		if (!dummy)
		throw InvalidOperationException();
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_codeWriter(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("codeWriter");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_data(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("data");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_writer(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("writer");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_options(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("options");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_value(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("value");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_list(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("list");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_collection(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("collection");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_array(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("array");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_sb(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("sb");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentNullException_output(bool dummy)
	{
		if (!dummy)
		throw std::invalid_argument("output");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_value(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("value");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_index(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("index");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_count(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("count");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_length(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("length");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_operand(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("operand");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_instructionOperand(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("instructionOperand");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_capacity(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("capacity");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_memorySize(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("memorySize");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_size(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("size");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_elementSize(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("elementSize");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_register(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("register");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_code(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("code");
	}

	[[noreturn]]
	constexpr void ThrowHelper::ThrowArgumentOutOfRangeException_data(bool dummy)
	{
		if (!dummy)
		throw ArgumentOutOfRangeException("data");
	}
}
