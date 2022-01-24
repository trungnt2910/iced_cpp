// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

namespace Iced::Intel
{
	/// <summary>
	/// Gets the available features
	/// </summary>
	class IcedFeatures final
	{
		// These functions cannot be made inline, they are designed
		// to be runtime checks used by client code to get information 
		// on how the original library was built.
	public:
		/// <summary>
		/// <see langword="true"/> if the gas (AT&amp;T) formatter is available
		/// </summary>
		static bool HasGasFormatter();
		/// <summary>
		/// <see langword="true"/> if the Intel (xed) formatter is available
		/// </summary>
		static bool HasIntelFormatter();
		/// <summary>
		/// <see langword="true"/> if the masm formatter is available
		/// </summary>
		static bool HasMasmFormatter();
		/// <summary>
		/// <see langword="true"/> if the nasm formatter is available
		/// </summary>
		static bool HasNasmFormatter();
		/// <summary>
		/// <see langword="true"/> if the fast formatter is available
		/// </summary>
		static bool HasFastFormatter();
		/// <summary>
		/// <see langword="true"/> if the decoder is available
		/// </summary>
		static bool HasDecoder();
		/// <summary>
		/// <see langword="true"/> if the encoder is available
		/// </summary>
		static bool HasEncoder();
		/// <summary>
		/// <see langword="true"/> if the block encoder is available
		/// </summary>
		static bool HasBlockEncoder();
		/// <summary>
		/// <see langword="true"/> if the opcode info is available
		/// </summary>
		static bool HasOpCodeInfo();
		/// <summary>
		/// <see langword="true"/> if the instruction info code is available
		/// </summary>
		static bool HasInstructionInfo();
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
