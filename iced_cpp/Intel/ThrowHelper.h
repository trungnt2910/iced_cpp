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
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentException()
		static void ThrowArgumentException();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowInvalidOperationException()
		static void ThrowInvalidOperationException();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_codeWriter()
		static void ThrowArgumentNullException_codeWriter();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_data()
		static void ThrowArgumentNullException_data();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_writer()
		static void ThrowArgumentNullException_writer();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_options()
		static void ThrowArgumentNullException_options();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_value()
		static void ThrowArgumentNullException_value();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_list()
		static void ThrowArgumentNullException_list();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_collection()
		static void ThrowArgumentNullException_collection();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_array()
		static void ThrowArgumentNullException_array();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_sb()
		static void ThrowArgumentNullException_sb();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentNullException_output()
		static void ThrowArgumentNullException_output();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_value()
		static void ThrowArgumentOutOfRangeException_value();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_index()
		static void ThrowArgumentOutOfRangeException_index();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_count()
		static void ThrowArgumentOutOfRangeException_count();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_length()
		static void ThrowArgumentOutOfRangeException_length();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_operand()
		static void ThrowArgumentOutOfRangeException_operand();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_instructionOperand()
		static void ThrowArgumentOutOfRangeException_instructionOperand();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_capacity()
		static void ThrowArgumentOutOfRangeException_capacity();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_memorySize()
		static void ThrowArgumentOutOfRangeException_memorySize();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_size()
		static void ThrowArgumentOutOfRangeException_size();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_elementSize()
		static void ThrowArgumentOutOfRangeException_elementSize();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_register()
		static void ThrowArgumentOutOfRangeException_register();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_code()
		static void ThrowArgumentOutOfRangeException_code();
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DoesNotReturn] internal static void ThrowArgumentOutOfRangeException_data()
		static void ThrowArgumentOutOfRangeException_data();
	};
}
