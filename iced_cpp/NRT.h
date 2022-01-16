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

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace System::Diagnostics::CodeAnalysis
{
	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	//ORIGINAL LINE: [AttributeUsage(AttributeTargets.Parameter, Inherited = false)] sealed class NotNullWhenAttribute : Attribute
	class NotNullWhenAttribute final : public Attribute
	{
	private:
		bool ReturnValue = false;

	public:
		NotNullWhenAttribute(bool returnValue);
		bool GetReturnValue() const;
	};
	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	//ORIGINAL LINE: [AttributeUsage(AttributeTargets.Method, Inherited = false)] sealed class DoesNotReturnAttribute : Attribute
	class DoesNotReturnAttribute final : public Attribute
	{
	public:
		DoesNotReturnAttribute();
	};
	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	//ORIGINAL LINE: [AttributeUsage(AttributeTargets.Parameter, Inherited = false)] sealed class DoesNotReturnIfAttribute : Attribute
	class DoesNotReturnIfAttribute final : public Attribute
	{
	private:
		bool ParameterValue = false;

	public:
		DoesNotReturnIfAttribute(bool parameterValue);
		bool GetParameterValue() const;
	};
}
