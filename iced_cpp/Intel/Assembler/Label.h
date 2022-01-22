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

#include <string>
#include <any>
#include <format>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// A label that can be created by <see cref="Assembler.CreateLabel"/>.
	/// </summary>
	class Label
	{
	private:
		std::int32_t InstructionIndex = 0;

	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: internal Label(string? name, ulong id)
		Label(const std::string& name, std::uint64_t id);
		/// <summary>
		/// Name of this label.
		/// </summary>
		std::string Name;
		/// <summary>
		/// Id of this label.
		/// </summary>
		std::uint64_t Id = 0;
		/// <summary>
		/// Gets the instruction index associated with this label. This is setup after calling <see cref="Assembler.Label"/>.
		/// </summary>
		std::int32_t GetInstructionIndex() const;
		void SetInstructionIndex(std::int32_t value);
		/// <summary>
		/// <c>true</c> if this label is empty and was not created by <see cref="Assembler.CreateLabel"/>.
		/// </summary>
		bool IsEmpty() const;
		/// <inheritdoc />
		std::string ToString() const;
		/// <inheritdoc />
		bool Equals(const Label& other);
		/// <inheritdoc />
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public override bool Equals(Object? obj)
		bool Equals(std::any obj);
		/// <inheritdoc />
		std::int32_t GetHashCode();
		/// <summary>
		/// Equality operator for <see cref="Label"/>
		/// </summary>
		/// <param name="left">Label</param>
		/// <param name="right">Label</param>
		/// <returns></returns>
		bool operator == (const Label& right);
		/// <summary>
		/// Inequality operator for <see cref="Label"/>
		/// </summary>
		/// <param name="left">Label</param>
		/// <param name="right">Label</param>
		/// <returns></returns>
		bool operator != (const Label& right);

		Label() = default;
	};
}
