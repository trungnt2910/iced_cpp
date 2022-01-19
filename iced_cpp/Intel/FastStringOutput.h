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

#include <string>
#include <vector>
#include <algorithm>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// <see cref="FastFormatter"/> output
	/// </summary>
	class FastStringOutput final
	{
	private:
		std::vector<char> buffer;
		std::int32_t bufferLen = 0;
		/// <summary>
		/// Gets the current length
		/// </summary>
	public:
		std::int32_t GetLength() const;
		/// <summary>
		/// Constructor
		/// </summary>
		FastStringOutput();
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="capacity">Initial capacity</param>
		FastStringOutput(std::int32_t capacity);
		/// <summary>
		/// Append a char
		/// </summary>
		/// <param name="c">Character to append</param>
		void Append(char c);
		/// <summary>
		/// Append a string
		/// </summary>
		/// <param name="value">String to append</param>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public void Append(string? value)
		void Append(const char* value);
		void AppendNotNull(const std::string_view& value);
		void AppendNotNull(const std::string& value);
		void AppendNotNull(const char* value, std::int32_t length = -1);
	private:
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.NoInlining)] void Resize(int extraCount)
		void Resize(std::int32_t extraCount);
		/// <summary>
		/// Copies all data to <paramref name="array"/>
		/// </summary>
		/// <param name="array">Destination array</param>
		/// <param name="arrayIndex">Destination array index</param>
	public:
		void CopyTo(std::vector<char>& array, std::int32_t arrayIndex);
		/// <summary>
		/// Resets the buffer to an empty string
		/// </summary>
		void Clear();
		/// <summary>
		/// Gets the current string
		/// </summary>
		/// <returns></returns>
		std::string ToString();
	};
}
