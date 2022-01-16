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

#include "MemorySizeOptions.g.h"
#include <string>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// Formatter options
	/// </summary>
	class FormatterOptions final
	{
	private:
		std::int32_t FirstOperandCharIndex = 0;
		std::int32_t TabSize = 0;
		std::string HexPrefix;
		std::string HexSuffix;
		std::int32_t HexDigitGroupSize = 4;
		std::string DecimalPrefix;
		std::string DecimalSuffix;
		std::int32_t DecimalDigitGroupSize = 3;
		std::string OctalPrefix;
		std::string OctalSuffix;
		std::int32_t OctalDigitGroupSize = 4;
		std::string BinaryPrefix;
		std::string BinarySuffix;
		std::int32_t BinaryDigitGroupSize = 4;
		std::string DigitSeparator;

	private:
		enum class Flags1 : int
		{
			None = 0,
			UppercasePrefixes = 0x00000001,
			UppercaseMnemonics = 0x00000002,
			UppercaseRegisters = 0x00000004,
			UppercaseKeywords = 0x00000008,
			UppercaseDecorators = 0x00000010,
			UppercaseAll = 0x00000020,
			SpaceAfterOperandSeparator = 0x00000040,
			SpaceAfterMemoryBracket = 0x00000080,
			SpaceBetweenMemoryAddOperators = 0x00000100,
			SpaceBetweenMemoryMulOperators = 0x00000200,
			ScaleBeforeIndex = 0x00000400,
			AlwaysShowScale = 0x00000800,
			AlwaysShowSegmentRegister = 0x00001000,
			ShowZeroDisplacements = 0x00002000,
			LeadingZeros = 0x00004000,
			UppercaseHex = 0x00008000,
			SmallHexNumbersInDecimal = 0x00010000,
			AddLeadingZeroToHexNumbers = 0x00020000,
			BranchLeadingZeros = 0x00040000,
			SignedImmediateOperands = 0x00080000,
			SignedMemoryDisplacements = 0x00100000,
			DisplacementLeadingZeros = 0x00200000,
			RipRelativeAddresses = 0x00400000,
			ShowBranchSize = 0x00800000,
			UsePseudoOps = 0x01000000,
			ShowSymbolAddress = 0x02000000,
			GasNakedRegisters = 0x04000000,
			GasShowMnemonicSizeSuffix = 0x08000000,
			GasSpaceAfterMemoryOperandComma = 0x10000000,
			MasmAddDsPrefix32 = 0x20000000,
			MasmSymbolDisplInBrackets = 0x40000000,
			MasmDisplInBrackets = 0x80000000
		};
		DEFINE_FLAGS(Flags1)
			DEFINE_COMP(Flags1)
			DEFINE_ARITH(Flags1)

	private:
		enum class Flags2 : int
		{
			None = 0,
			NasmShowSignExtendedImmediateSize = 0x00000001,
			PreferST0 = 0x00000002,
			ShowUselessPrefixes = 0x00000004
		};
		DEFINE_FLAGS(Flags2)
			DEFINE_COMP(Flags2)
			DEFINE_ARITH(Flags2)

	private:
		Flags1 flags1 = static_cast<Flags1>(0);
		Flags2 flags2 = static_cast<Flags2>(0);
		/// <summary>
		/// Constructor
		/// </summary>
	public:
		FormatterOptions();
		/// <summary>
		/// Prefixes are uppercased
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>REP stosd</c>
		/// <br/>
		/// <see langword="false"/>: <c>rep stosd</c>
		/// </summary>
		bool GetUppercasePrefixes() const;
		void SetUppercasePrefixes(bool value);
		/// <summary>
		/// Mnemonics are uppercased
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>MOV rcx,rax</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov rcx,rax</c>
		/// </summary>
		bool GetUppercaseMnemonics() const;
		void SetUppercaseMnemonics(bool value);
		/// <summary>
		/// Registers are uppercased
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov RCX,[RAX+RDX*8]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov rcx,[rax+rdx*8]</c>
		/// </summary>
		bool GetUppercaseRegisters() const;
		void SetUppercaseRegisters(bool value);
		/// <summary>
		/// Keywords are uppercased (eg. <c>BYTE PTR</c>, <c>SHORT</c>)
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov BYTE PTR [rcx],12h</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov byte ptr [rcx],12h</c>
		/// </summary>
		bool GetUppercaseKeywords() const;
		void SetUppercaseKeywords(bool value);
		/// <summary>
		/// Uppercase decorators, eg. <c>{z}</c>, <c>{sae}</c>, <c>{rd-sae}</c> (but not opmask registers: <c>{k1}</c>)
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>vunpcklps xmm2{k5}{Z},xmm6,dword bcst [rax+4]</c>
		/// <br/>
		/// <see langword="false"/>: <c>vunpcklps xmm2{k5}{z},xmm6,dword bcst [rax+4]</c>
		/// </summary>
		bool GetUppercaseDecorators() const;
		void SetUppercaseDecorators(bool value);
		/// <summary>
		/// Everything is uppercased, except numbers and their prefixes/suffixes
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>MOV EAX,GS:[RCX*4+0ffh]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,gs:[rcx*4+0ffh]</c>
		/// </summary>
		bool GetUppercaseAll() const;
		void SetUppercaseAll(bool value);
		/// <summary>
		/// Character index (0-based) where the first operand is formatted. Can be set to 0 to format it immediately after the mnemonic.
		/// At least one space or tab is always added between the mnemonic and the first operand.
		/// <br/>
		/// Default: <c>0</c>
		/// <br/>
		/// <c>0</c>: <c>mov•rcx,rbp</c>
		/// <br/>
		/// <c>8</c>: <c>mov•••••rcx,rbp</c>
		/// <br/>
		/// </summary>
		std::int32_t GetFirstOperandCharIndex() const;
		void SetFirstOperandCharIndex(std::int32_t value);
		/// <summary>
		/// Size of a tab character or &lt;= 0 to use spaces
		/// <br/>
		/// Default: <c>0</c>
		/// </summary>
		std::int32_t GetTabSize() const;
		void SetTabSize(std::int32_t value);
		/// <summary>
		/// Add a space after the operand separator
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov rax, rcx</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov rax,rcx</c>
		/// </summary>
		bool GetSpaceAfterOperandSeparator() const;
		void SetSpaceAfterOperandSeparator(bool value);
		/// <summary>
		/// Add a space between the memory expression and the brackets
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[ rcx+rdx ]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[rcx+rdx]</c>
		/// </summary>
		bool GetSpaceAfterMemoryBracket() const;
		void SetSpaceAfterMemoryBracket(bool value);
		/// <summary>
		/// Add spaces between memory operand <c>+</c> and <c>-</c> operators
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[rcx + rdx*8 - 80h]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[rcx+rdx*8-80h]</c>
		/// </summary>
		bool GetSpaceBetweenMemoryAddOperators() const;
		void SetSpaceBetweenMemoryAddOperators(bool value);
		/// <summary>
		/// Add spaces between memory operand <c>*</c> operator
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[rcx+rdx * 8-80h]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[rcx+rdx*8-80h]</c>
		/// </summary>
		bool GetSpaceBetweenMemoryMulOperators() const;
		void SetSpaceBetweenMemoryMulOperators(bool value);
		/// <summary>
		/// Show memory operand scale value before the index register
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[8*rdx]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[rdx*8]</c>
		/// </summary>
		bool GetScaleBeforeIndex() const;
		void SetScaleBeforeIndex(bool value);
		/// <summary>
		/// Always show the scale value even if it's <c>*1</c>
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[rbx+rcx*1]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[rbx+rcx]</c>
		/// </summary>
		bool GetAlwaysShowScale() const;
		void SetAlwaysShowScale(bool value);
		/// <summary>
		/// Always show the effective segment register. If the option is <see langword="false"/>, only show the segment register if
		/// there's a segment override prefix.
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,ds:[ecx]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[ecx]</c>
		/// </summary>
		bool GetAlwaysShowSegmentRegister() const;
		void SetAlwaysShowSegmentRegister(bool value);
		/// <summary>
		/// Show zero displacements
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[rcx*2+0]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[rcx*2]</c>
		/// </summary>
		bool GetShowZeroDisplacements() const;
		void SetShowZeroDisplacements(bool value);
		/// <summary>
		/// Hex number prefix or <see langword="null"/>/empty string, eg. "0x"
		/// <br/>
		/// Default: <see langword="null"/> (masm/nasm/intel), <c>"0x"</c> (gas)
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? HexPrefix {get;set;}
		std::string GetHexPrefix() const;
		void SetHexPrefix(const std::string& value);
		/// <summary>
		/// Hex number suffix or <see langword="null"/>/empty string, eg. "h"
		/// <br/>
		/// Default: <c>"h"</c> (masm/nasm/intel), <see langword="null"/> (gas)
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? HexSuffix {get;set;}
		std::string GetHexSuffix() const;
		void SetHexSuffix(const std::string& value);
		/// <summary>
		/// Size of a digit group, see also <see cref="DigitSeparator"/>
		/// <br/>
		/// Default: <c>4</c>
		/// <br/>
		/// <c>0</c>: <c>0x12345678</c>
		/// <br/>
		/// <c>4</c>: <c>0x1234_5678</c>
		/// </summary>
		std::int32_t GetHexDigitGroupSize() const;
		void SetHexDigitGroupSize(std::int32_t value);
		/// <summary>
		/// Decimal number prefix or <see langword="null"/>/empty string
		/// <br/>
		/// Default: <see langword="null"/>
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? DecimalPrefix {get;set;}
		std::string GetDecimalPrefix() const;
		void SetDecimalPrefix(const std::string& value);
		/// <summary>
		/// Decimal number suffix or <see langword="null"/>/empty string
		/// <br/>
		/// Default: <see langword="null"/>
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? DecimalSuffix {get;set;}
		std::string GetDecimalSuffix() const;
		void SetDecimalSuffix(const std::string& value);
		/// <summary>
		/// Size of a digit group, see also <see cref="DigitSeparator"/>
		/// <br/>
		/// Default: <c>3</c>
		/// <br/>
		/// <c>0</c>: <c>12345678</c>
		/// <br/>
		/// <c>3</c>: <c>12_345_678</c>
		/// </summary>
		std::int32_t GetDecimalDigitGroupSize() const;
		void SetDecimalDigitGroupSize(std::int32_t value);
		/// <summary>
		/// Octal number prefix or <see langword="null"/>/empty string
		/// <br/>
		/// Default: <see langword="null"/> (masm/nasm/intel), <c>"0"</c> (gas)
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? OctalPrefix {get;set;}
		std::string GetOctalPrefix() const;
		void SetOctalPrefix(const std::string& value);
		/// <summary>
		/// Octal number suffix or <see langword="null"/>/empty string
		/// <br/>
		/// Default: <c>"o"</c> (masm/nasm/intel), <see langword="null"/> (gas)
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? OctalSuffix {get;set;}
		std::string GetOctalSuffix() const;
		void SetOctalSuffix(const std::string& value);
		/// <summary>
		/// Size of a digit group, see also <see cref="DigitSeparator"/>
		/// <br/>
		/// Default: <c>4</c>
		/// <br/>
		/// <c>0</c>: <c>12345670</c>
		/// <br/>
		/// <c>4</c>: <c>1234_5670</c>
		/// </summary>
		std::int32_t GetOctalDigitGroupSize() const;
		void SetOctalDigitGroupSize(std::int32_t value);
		/// <summary>
		/// Binary number prefix or <see langword="null"/>/empty string
		/// <br/>
		/// Default: <see langword="null"/> (masm/nasm/intel), <c>"0b"</c> (gas)
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? BinaryPrefix {get;set;}
		std::string GetBinaryPrefix() const;
		void SetBinaryPrefix(const std::string& value);
		/// <summary>
		/// Binary number suffix or <see langword="null"/>/empty string
		/// <br/>
		/// Default: <c>"b"</c> (masm/nasm/intel), <see langword="null"/> (gas)
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? BinarySuffix {get;set;}
		std::string GetBinarySuffix() const;
		void SetBinarySuffix(const std::string& value);
		/// <summary>
		/// Size of a digit group, see also <see cref="DigitSeparator"/>
		/// <br/>
		/// Default: <c>4</c>
		/// <br/>
		/// <c>0</c>: <c>11010111</c>
		/// <br/>
		/// <c>4</c>: <c>1101_0111</c>
		/// </summary>
		std::int32_t GetBinaryDigitGroupSize() const;
		void SetBinaryDigitGroupSize(std::int32_t value);
		/// <summary>
		/// Digit separator or <see langword="null"/>/empty string. See also eg. <see cref="HexDigitGroupSize"/>.
		/// <br/>
		/// Default: <see langword="null"/>
		/// <br/>
		/// <c>""</c>: <c>0x12345678</c>
		/// <br/>
		/// <c>"_"</c>: <c>0x1234_5678</c>
		/// </summary>
	  //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	  //ORIGINAL LINE: public string? DigitSeparator {get;set;}
		std::string GetDigitSeparator() const;
		void SetDigitSeparator(const std::string& value);
		/// <summary>
		/// Add leading zeros to hexadecimal/octal/binary numbers.
		/// This option has no effect on branch targets and displacements, use <see cref="BranchLeadingZeros"/>
		/// and <see cref="DisplacementLeadingZeros"/>.
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>0x0000000A</c>/<c>0000000Ah</c>
		/// <br/>
		/// <see langword="false"/>: <c>0xA</c>/<c>0Ah</c>
		/// </summary>
		bool GetLeadingZeros() const;
		void SetLeadingZeros(bool value);
		/// <summary>
		/// Add leading zeros to hexadecimal/octal/binary numbers.
		/// This option has no effect on branch targets and displacements, use <see cref="BranchLeadingZeros"/>
		/// and <see cref="DisplacementLeadingZeros"/>.
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>0x0000000A</c>/<c>0000000Ah</c>
		/// <br/>
		/// <see langword="false"/>: <c>0xA</c>/<c>0Ah</c>
		/// </summary>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)] public bool LeadingZeroes
		bool GetLeadingZeroes() const;
		void SetLeadingZeroes(bool value);
		/// <summary>
		/// Use uppercase hex digits
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>0xFF</c>
		/// <br/>
		/// <see langword="false"/>: <c>0xff</c>
		/// </summary>
		bool GetUppercaseHex() const;
		void SetUppercaseHex(bool value);
		/// <summary>
		/// Small hex numbers (-9 .. 9) are shown in decimal
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>9</c>
		/// <br/>
		/// <see langword="false"/>: <c>0x9</c>
		/// </summary>
		bool GetSmallHexNumbersInDecimal() const;
		void SetSmallHexNumbersInDecimal(bool value);
		/// <summary>
		/// Add a leading zero to hex numbers if there's no prefix and the number starts with hex digits <c>A-F</c>
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>0FFh</c>
		/// <br/>
		/// <see langword="false"/>: <c>FFh</c>
		/// </summary>
		bool GetAddLeadingZeroToHexNumbers() const;
		void SetAddLeadingZeroToHexNumbers(bool value);
		/// <summary>
		/// Number base
		/// <br/>
		/// Default: <see cref="NumberBase.Hexadecimal"/>
		/// </summary>
		Iced::Intel::NumberBase GetNumberBase() const;
		void SetNumberBase(Iced::Intel::NumberBase value);
	private:
		Iced::Intel::NumberBase numberBase = NumberBase::Hexadecimal;
		/// <summary>
		/// Add leading zeros to branch offsets. Used by <c>CALL NEAR</c>, <c>CALL FAR</c>, <c>JMP NEAR</c>, <c>JMP FAR</c>, <c>Jcc</c>, <c>LOOP</c>, <c>LOOPcc</c>, <c>XBEGIN</c>
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>je 00000123h</c>
		/// <br/>
		/// <see langword="false"/>: <c>je 123h</c>
		/// </summary>
	public:
		bool GetBranchLeadingZeros() const;
		void SetBranchLeadingZeros(bool value);
		/// <summary>
		/// Add leading zeros to branch offsets. Used by <c>CALL NEAR</c>, <c>CALL FAR</c>, <c>JMP NEAR</c>, <c>JMP FAR</c>, <c>Jcc</c>, <c>LOOP</c>, <c>LOOPcc</c>, <c>XBEGIN</c>
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>je 00000123h</c>
		/// <br/>
		/// <see langword="false"/>: <c>je 123h</c>
		/// </summary>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)] public bool BranchLeadingZeroes
		bool GetBranchLeadingZeroes() const;
		void SetBranchLeadingZeroes(bool value);
		/// <summary>
		/// Show immediate operands as signed numbers
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,-1</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,FFFFFFFF</c>
		/// </summary>
		bool GetSignedImmediateOperands() const;
		void SetSignedImmediateOperands(bool value);
		/// <summary>
		/// Displacements are signed numbers
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov al,[eax-2000h]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov al,[eax+0FFFFE000h]</c>
		/// </summary>
		bool GetSignedMemoryDisplacements() const;
		void SetSignedMemoryDisplacements(bool value);
		/// <summary>
		/// Add leading zeros to displacements
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov al,[eax+00000012h]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov al,[eax+12h]</c>
		/// </summary>
		bool GetDisplacementLeadingZeros() const;
		void SetDisplacementLeadingZeros(bool value);
		/// <summary>
		/// Add leading zeros to displacements
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov al,[eax+00000012h]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov al,[eax+12h]</c>
		/// </summary>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)] public bool DisplacementLeadingZeroes
		bool GetDisplacementLeadingZeroes() const;
		void SetDisplacementLeadingZeroes(bool value);
		/// <summary>
		/// Options that control if the memory size (eg. <c>DWORD PTR</c>) is shown or not.
		/// This is ignored by the gas (AT&amp;T) formatter.
		/// <br/>
		/// Default: <see cref="Intel.MemorySizeOptions.Default"/>
		/// </summary>
		Iced::Intel::MemorySizeOptions GetMemorySizeOptions() const;
		void SetMemorySizeOptions(Iced::Intel::MemorySizeOptions value);
	private:
		Iced::Intel::MemorySizeOptions memorySizeOptions = MemorySizeOptions::Default;
		/// <summary>
		/// Show <c>RIP+displ</c> or the virtual address
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[rip+12345678h]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[1029384756AFBECDh]</c>
		/// </summary>
	public:
		bool GetRipRelativeAddresses() const;
		void SetRipRelativeAddresses(bool value);
		/// <summary>
		/// Show <c>NEAR</c>, <c>SHORT</c>, etc if it's a branch instruction
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>je short 1234h</c>
		/// <br/>
		/// <see langword="false"/>: <c>je 1234h</c>
		/// </summary>
		bool GetShowBranchSize() const;
		void SetShowBranchSize(bool value);
		/// <summary>
		/// Use pseudo instructions
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>vcmpnltsd xmm2,xmm6,xmm3</c>
		/// <br/>
		/// <see langword="false"/>: <c>vcmpsd xmm2,xmm6,xmm3,5</c>
		/// </summary>
		bool GetUsePseudoOps() const;
		void SetUsePseudoOps(bool value);
		/// <summary>
		/// Show the original value after the symbol name
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,[myfield (12345678)]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[myfield]</c>
		/// </summary>
		bool GetShowSymbolAddress() const;
		void SetShowSymbolAddress(bool value);
		/// <summary>
		/// (gas only): If <see langword="true"/>, the formatter doesn't add <c>%</c> to registers
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,ecx</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov %eax,%ecx</c>
		/// </summary>
		bool GetGasNakedRegisters() const;
		void SetGasNakedRegisters(bool value);
		/// <summary>
		/// (gas only): Shows the mnemonic size suffix even when not needed
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>movl %eax,%ecx</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov %eax,%ecx</c>
		/// </summary>
		bool GetGasShowMnemonicSizeSuffix() const;
		void SetGasShowMnemonicSizeSuffix(bool value);
		/// <summary>
		/// (gas only): Add a space after the comma if it's a memory operand
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>(%eax, %ecx, 2)</c>
		/// <br/>
		/// <see langword="false"/>: <c>(%eax,%ecx,2)</c>
		/// </summary>
		bool GetGasSpaceAfterMemoryOperandComma() const;
		void SetGasSpaceAfterMemoryOperandComma(bool value);
		/// <summary>
		/// (masm only): Add a <c>DS</c> segment override even if it's not present. Used if it's 16/32-bit code and mem op is a displ
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>mov eax,ds:[12345678]</c>
		/// <br/>
		/// <see langword="false"/>: <c>mov eax,[12345678]</c>
		/// </summary>
		bool GetMasmAddDsPrefix32() const;
		void SetMasmAddDsPrefix32(bool value);
		/// <summary>
		/// (masm only): Show symbols in brackets
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>[ecx+symbol]</c> / <c>[symbol]</c>
		/// <br/>
		/// <see langword="false"/>: <c>symbol[ecx]</c> / <c>symbol</c>
		/// </summary>
		bool GetMasmSymbolDisplInBrackets() const;
		void SetMasmSymbolDisplInBrackets(bool value);
		/// <summary>
		/// (masm only): Show displacements in brackets
		/// <br/>
		/// Default: <see langword="true"/>
		/// <br/>
		/// <see langword="true"/>: <c>[ecx+1234h]</c>
		/// <br/>
		/// <see langword="false"/>: <c>1234h[ecx]</c>
		/// </summary>
		bool GetMasmDisplInBrackets() const;
		void SetMasmDisplInBrackets(bool value);
		/// <summary>
		/// (nasm only): Shows <c>BYTE</c>, <c>WORD</c>, <c>DWORD</c> or <c>QWORD</c> if it's a sign extended immediate operand value
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>or rcx,byte -1</c>
		/// <br/>
		/// <see langword="false"/>: <c>or rcx,-1</c>
		/// </summary>
		bool GetNasmShowSignExtendedImmediateSize() const;
		void SetNasmShowSignExtendedImmediateSize(bool value);
		/// <summary>
		/// Use <c>st(0)</c> instead of <c>st</c> if <c>st</c> can be used. Ignored by the nasm formatter.
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>fadd st(0),st(3)</c>
		/// <br/>
		/// <see langword="false"/>: <c>fadd st,st(3)</c>
		/// </summary>
		bool GetPreferST0() const;
		void SetPreferST0(bool value);
		/// <summary>
		/// Show useless prefixes. If it has useless prefixes, it could be data and not code.
		/// <br/>
		/// Default: <see langword="false"/>
		/// <br/>
		/// <see langword="true"/>: <c>es rep add eax,ecx</c>
		/// <br/>
		/// <see langword="false"/>: <c>add eax,ecx</c>
		/// </summary>
		bool GetShowUselessPrefixes() const;
		void SetShowUselessPrefixes(bool value);
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JB</c> / <c>JC</c> / <c>JNAE</c>)
		/// <br/>
		/// Default: <c>JB</c>, <c>CMOVB</c>, <c>SETB</c>
		/// </summary>
		Iced::Intel::CC_b GetCCB() const;
		void SetCCB(Iced::Intel::CC_b value);
	private:
		Iced::Intel::CC_b cc_b = CC_b::b;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JAE</c> / <c>JNB</c> / <c>JNC</c>)
		/// <br/>
		/// Default: <c>JAE</c>, <c>CMOVAE</c>, <c>SETAE</c>
		/// </summary>
	public:
		Iced::Intel::CC_ae GetCCAe() const;
		void SetCCAe(Iced::Intel::CC_ae value);
	private:
		Iced::Intel::CC_ae cc_ae = CC_ae::ae;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JE</c> / <c>JZ</c>)
		/// <br/>
		/// Default: <c>JE</c>, <c>CMOVE</c>, <c>SETE</c>, <c>LOOPE</c>, <c>REPE</c>
		/// </summary>
	public:
		Iced::Intel::CC_e GetCCE() const;
		void SetCCE(Iced::Intel::CC_e value);
	private:
		Iced::Intel::CC_e cc_e = CC_e::e;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JNE</c> / <c>JNZ</c>)
		/// <br/>
		/// Default: <c>JNE</c>, <c>CMOVNE</c>, <c>SETNE</c>, <c>LOOPNE</c>, <c>REPNE</c>
		/// </summary>
	public:
		Iced::Intel::CC_ne GetCCNe() const;
		void SetCCNe(Iced::Intel::CC_ne value);
	private:
		Iced::Intel::CC_ne cc_ne = CC_ne::ne;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JBE</c> / <c>JNA</c>)
		/// <br/>
		/// Default: <c>JBE</c>, <c>CMOVBE</c>, <c>SETBE</c>
		/// </summary>
	public:
		Iced::Intel::CC_be GetCCBe() const;
		void SetCCBe(Iced::Intel::CC_be value);
	private:
		Iced::Intel::CC_be cc_be = CC_be::be;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JA</c> / <c>JNBE</c>)
		/// <br/>
		/// Default: <c>JA</c>, <c>CMOVA</c>, <c>SETA</c>
		/// </summary>
	public:
		Iced::Intel::CC_a GetCCA() const;
		void SetCCA(Iced::Intel::CC_a value);
	private:
		Iced::Intel::CC_a cc_a = CC_a::a;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JP</c> / <c>JPE</c>)
		/// <br/>
		/// Default: <c>JP</c>, <c>CMOVP</c>, <c>SETP</c>
		/// </summary>
	public:
		Iced::Intel::CC_p GetCCP() const;
		void SetCCP(Iced::Intel::CC_p value);
	private:
		Iced::Intel::CC_p cc_p = CC_p::p;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JNP</c> / <c>JPO</c>)
		/// <br/>
		/// Default: <c>JNP</c>, <c>CMOVNP</c>, <c>SETNP</c>
		/// </summary>
	public:
		Iced::Intel::CC_np GetCCNp() const;
		void SetCCNp(Iced::Intel::CC_np value);
	private:
		Iced::Intel::CC_np cc_np = CC_np::np;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JL</c> / <c>JNGE</c>)
		/// <br/>
		/// Default: <c>JL</c>, <c>CMOVL</c>, <c>SETL</c>
		/// </summary>
	public:
		Iced::Intel::CC_l GetCCL() const;
		void SetCCL(Iced::Intel::CC_l value);
	private:
		Iced::Intel::CC_l cc_l = CC_l::l;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JGE</c> / <c>JNL</c>)
		/// <br/>
		/// Default: <c>JGE</c>, <c>CMOVGE</c>, <c>SETGE</c>
		/// </summary>
	public:
		Iced::Intel::CC_ge GetCCGe() const;
		void SetCCGe(Iced::Intel::CC_ge value);
	private:
		Iced::Intel::CC_ge cc_ge = CC_ge::ge;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JLE</c> / <c>JNG</c>)
		/// <br/>
		/// Default: <c>JLE</c>, <c>CMOVLE</c>, <c>SETLE</c>
		/// </summary>
	public:
		Iced::Intel::CC_le GetCCLe() const;
		void SetCCLe(Iced::Intel::CC_le value);
	private:
		Iced::Intel::CC_le cc_le = CC_le::le;
		/// <summary>
		/// Mnemonic condition code selector (eg. <c>JG</c> / <c>JNLE</c>)
		/// <br/>
		/// Default: <c>JG</c>, <c>CMOVG</c>, <c>SETG</c>
		/// </summary>
	public:
		Iced::Intel::CC_g GetCCG() const;
		void SetCCG(Iced::Intel::CC_g value);
	private:
		Iced::Intel::CC_g cc_g = CC_g::g;
		/// <summary>
		/// Creates GNU assembler (AT&amp;T) formatter options
		/// </summary>
		/// <returns></returns>
	public:
		static FormatterOptions* CreateGas();
		/// <summary>
		/// Creates Intel (XED) formatter options
		/// </summary>
		/// <returns></returns>
		static FormatterOptions* CreateIntel();
		/// <summary>
		/// Creates masm formatter options
		/// </summary>
		/// <returns></returns>
		static FormatterOptions* CreateMasm();
		/// <summary>
		/// Creates nasm formatter options
		/// </summary>
		/// <returns></returns>
		static FormatterOptions* CreateNasm();
	};
	// GENERATOR-BEGIN: NumberBase
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	/// <summary>Number base</summary>
	enum class NumberBase
	{
		/// <summary>Hex numbers (base 16)</summary>
		Hexadecimal = 0,
		/// <summary>Decimal numbers (base 10)</summary>
		Decimal = 1,
		/// <summary>Octal numbers (base 8)</summary>
		Octal = 2,
		/// <summary>Binary numbers (base 2)</summary>
		Binary = 3
	};

	DEFINE_COMP(NumberBase)
		DEFINE_ARITH(NumberBase)

		// GENERATOR-END: NumberBase
		// GENERATOR-BEGIN: CC_b
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JB</c> / <c>JC</c> / <c>JNAE</c>)</summary>
		enum class CC_b : std::uint8_t
	{
		/// <summary><c>JB</c>, <c>CMOVB</c>, <c>SETB</c></summary>
		b = 0,
		/// <summary><c>JC</c>, <c>CMOVC</c>, <c>SETC</c></summary>
		c = 1,
		/// <summary><c>JNAE</c>, <c>CMOVNAE</c>, <c>SETNAE</c></summary>
		nae = 2
	};

	DEFINE_COMP(CC_b)
		DEFINE_ARITH(CC_b)

		// GENERATOR-END: CC_b
		// GENERATOR-BEGIN: CC_ae
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JAE</c> / <c>JNB</c> / <c>JNC</c>)</summary>
		enum class CC_ae : std::uint8_t
	{
		/// <summary><c>JAE</c>, <c>CMOVAE</c>, <c>SETAE</c></summary>
		ae = 0,
		/// <summary><c>JNB</c>, <c>CMOVNB</c>, <c>SETNB</c></summary>
		nb = 1,
		/// <summary><c>JNC</c>, <c>CMOVNC</c>, <c>SETNC</c></summary>
		nc = 2
	};

	DEFINE_COMP(CC_ae)
		DEFINE_ARITH(CC_ae)

		// GENERATOR-END: CC_ae
		// GENERATOR-BEGIN: CC_e
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JE</c> / <c>JZ</c>)</summary>
		enum class CC_e : std::uint8_t
	{
		/// <summary><c>JE</c>, <c>CMOVE</c>, <c>SETE</c>, <c>LOOPE</c>, <c>REPE</c></summary>
		e = 0,
		/// <summary><c>JZ</c>, <c>CMOVZ</c>, <c>SETZ</c>, <c>LOOPZ</c>, <c>REPZ</c></summary>
		z = 1
	};

	DEFINE_COMP(CC_e)
		DEFINE_ARITH(CC_e)

		// GENERATOR-END: CC_e
		// GENERATOR-BEGIN: CC_ne
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JNE</c> / <c>JNZ</c>)</summary>
		enum class CC_ne : std::uint8_t
	{
		/// <summary><c>JNE</c>, <c>CMOVNE</c>, <c>SETNE</c>, <c>LOOPNE</c>, <c>REPNE</c></summary>
		ne = 0,
		/// <summary><c>JNZ</c>, <c>CMOVNZ</c>, <c>SETNZ</c>, <c>LOOPNZ</c>, <c>REPNZ</c></summary>
		nz = 1
	};

	DEFINE_COMP(CC_ne)
		DEFINE_ARITH(CC_ne)

		// GENERATOR-END: CC_ne
		// GENERATOR-BEGIN: CC_be
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JBE</c> / <c>JNA</c>)</summary>
		enum class CC_be : std::uint8_t
	{
		/// <summary><c>JBE</c>, <c>CMOVBE</c>, <c>SETBE</c></summary>
		be = 0,
		/// <summary><c>JNA</c>, <c>CMOVNA</c>, <c>SETNA</c></summary>
		na = 1
	};

	DEFINE_COMP(CC_be)
		DEFINE_ARITH(CC_be)

		// GENERATOR-END: CC_be
		// GENERATOR-BEGIN: CC_a
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JA</c> / <c>JNBE</c>)</summary>
		enum class CC_a : std::uint8_t
	{
		/// <summary><c>JA</c>, <c>CMOVA</c>, <c>SETA</c></summary>
		a = 0,
		/// <summary><c>JNBE</c>, <c>CMOVNBE</c>, <c>SETNBE</c></summary>
		nbe = 1
	};

	DEFINE_COMP(CC_a)
		DEFINE_ARITH(CC_a)

		// GENERATOR-END: CC_a
		// GENERATOR-BEGIN: CC_p
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JP</c> / <c>JPE</c>)</summary>
		enum class CC_p : std::uint8_t
	{
		/// <summary><c>JP</c>, <c>CMOVP</c>, <c>SETP</c></summary>
		p = 0,
		/// <summary><c>JPE</c>, <c>CMOVPE</c>, <c>SETPE</c></summary>
		pe = 1
	};

	DEFINE_COMP(CC_p)
		DEFINE_ARITH(CC_p)

		// GENERATOR-END: CC_p
		// GENERATOR-BEGIN: CC_np
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JNP</c> / <c>JPO</c>)</summary>
		enum class CC_np : std::uint8_t
	{
		/// <summary><c>JNP</c>, <c>CMOVNP</c>, <c>SETNP</c></summary>
		np = 0,
		/// <summary><c>JPO</c>, <c>CMOVPO</c>, <c>SETPO</c></summary>
		po = 1
	};

	DEFINE_COMP(CC_np)
		DEFINE_ARITH(CC_np)

		// GENERATOR-END: CC_np
		// GENERATOR-BEGIN: CC_l
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JL</c> / <c>JNGE</c>)</summary>
		enum class CC_l : std::uint8_t
	{
		/// <summary><c>JL</c>, <c>CMOVL</c>, <c>SETL</c></summary>
		l = 0,
		/// <summary><c>JNGE</c>, <c>CMOVNGE</c>, <c>SETNGE</c></summary>
		nge = 1
	};

	DEFINE_COMP(CC_l)
		DEFINE_ARITH(CC_l)

		// GENERATOR-END: CC_l
		// GENERATOR-BEGIN: CC_ge
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JGE</c> / <c>JNL</c>)</summary>
		enum class CC_ge : std::uint8_t
	{
		/// <summary><c>JGE</c>, <c>CMOVGE</c>, <c>SETGE</c></summary>
		ge = 0,
		/// <summary><c>JNL</c>, <c>CMOVNL</c>, <c>SETNL</c></summary>
		nl = 1
	};

	DEFINE_COMP(CC_ge)
		DEFINE_ARITH(CC_ge)

		// GENERATOR-END: CC_ge
		// GENERATOR-BEGIN: CC_le
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JLE</c> / <c>JNG</c>)</summary>
		enum class CC_le : std::uint8_t
	{
		/// <summary><c>JLE</c>, <c>CMOVLE</c>, <c>SETLE</c></summary>
		le = 0,
		/// <summary><c>JNG</c>, <c>CMOVNG</c>, <c>SETNG</c></summary>
		ng = 1
	};

	DEFINE_COMP(CC_le)
		DEFINE_ARITH(CC_le)

		// GENERATOR-END: CC_le
		// GENERATOR-BEGIN: CC_g
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		/// <summary>Mnemonic condition code selector (eg. <c>JG</c> / <c>JNLE</c>)</summary>
		enum class CC_g : std::uint8_t
	{
		/// <summary><c>JG</c>, <c>CMOVG</c>, <c>SETG</c></summary>
		g = 0,
		/// <summary><c>JNLE</c>, <c>CMOVNLE</c>, <c>SETNLE</c></summary>
		nle = 1
	};

	DEFINE_COMP(CC_g)
		DEFINE_ARITH(CC_g)

		// GENERATOR-END: CC_g
}