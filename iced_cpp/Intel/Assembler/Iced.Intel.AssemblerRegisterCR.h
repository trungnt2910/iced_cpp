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

#include "../Register.g.h"
#include <any>
#include <format>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel
{
	/// <summary>
	/// An assembler register used with <see cref="Assembler"/>.
	/// </summary>
   //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
   //ORIGINAL LINE: [DebuggerDisplay("{" + nameof(Value) + "}")][EditorBrowsable(EditorBrowsableState.Never)] public partial struct AssemblerRegisterCR: IEquatable<AssemblerRegisterCR>
	class AssemblerRegisterCR : public IEquatable<AssemblerRegisterCR>
	{
		/// <summary>
		/// Creates a new instance.
		/// </summary>
		/// <param name="value">A Register</param>
	public:
		AssemblerRegisterCR(Register value);
		/// <summary>
		/// The register value.
		/// </summary>
		Register Value = static_cast<Register>(0);
		/// <summary>
		/// Converts a <see cref="AssemblerRegisterCR"/> to a <see cref="Register"/>.
		/// </summary>
		/// <param name="reg">AssemblerRegisterCR</param>
		/// <returns></returns>
		operator Register();
		/// <inheritdoc />
		bool Equals(AssemblerRegisterCR other) override;
		/// <inheritdoc />
		std::int32_t GetHashCode();
		/// <inheritdoc />
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public override bool Equals(Object? obj)
		bool Equals(std::any obj);
		/// <summary>
		/// Equality operator for <see cref="AssemblerRegisterCR"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		bool operator == (AssemblerRegisterCR right);
		/// <summary>
		/// Inequality operator for <see cref="AssemblerRegisterCR"/>
		/// </summary>
		/// <param name="left">Register</param>
		/// <param name="right">Register</param>
		/// <returns></returns>
		bool operator != (AssemblerRegisterCR right);

		AssemblerRegisterCR() = default;
	};
}
