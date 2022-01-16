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
namespace Iced::Intel
{
	/// <summary>
	/// Gets the available features
	/// </summary>
	class IcedFeatures final
	{
		/// <summary>
		/// <see langword="true"/> if the gas (AT&amp;T) formatter is available
		/// </summary>
	public:
		static bool GetHasGasFormatter();
		/// <summary>
		/// <see langword="true"/> if the Intel (xed) formatter is available
		/// </summary>
		static bool GetHasIntelFormatter();
		/// <summary>
		/// <see langword="true"/> if the masm formatter is available
		/// </summary>
		static bool GetHasMasmFormatter();
		/// <summary>
		/// <see langword="true"/> if the nasm formatter is available
		/// </summary>
		static bool GetHasNasmFormatter();
		/// <summary>
		/// <see langword="true"/> if the fast formatter is available
		/// </summary>
		static bool GetHasFastFormatter();
		/// <summary>
		/// <see langword="true"/> if the decoder is available
		/// </summary>
		static bool GetHasDecoder();
		/// <summary>
		/// <see langword="true"/> if the encoder is available
		/// </summary>
		static bool GetHasEncoder();
		/// <summary>
		/// <see langword="true"/> if the block encoder is available
		/// </summary>
		static bool GetHasBlockEncoder();
		/// <summary>
		/// <see langword="true"/> if the opcode info is available
		/// </summary>
		static bool GetHasOpCodeInfo();
		/// <summary>
		/// <see langword="true"/> if the instruction info code is available
		/// </summary>
		static bool GetHasInstructionInfo();
		/// <summary>
		/// Initializes some static constructors related to the decoder and instruction info. If those
		/// static constructors are initialized, the jitter generates faster code since it doesn't have
		/// to add runtime checks to see if those static constructors must be called.
		/// 
		/// This method should be called before using the decoder and instruction info classes and
		/// should *not* be called from the same method as any code that uses the decoder / instruction
		/// info classes. Eg. call this method from Main() and decode instructions / get instruction info
		/// in a method called by Main().
		/// </summary>
		static void Initialize();
	};
}
