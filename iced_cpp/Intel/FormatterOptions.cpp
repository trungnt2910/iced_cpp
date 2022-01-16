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

#include "FormatterOptions.h"
#include "ThrowHelper.h"

namespace Iced::Intel
{

	FormatterOptions::FormatterOptions()
	{
		flags1 = Flags1::UppercaseHex | Flags1::SmallHexNumbersInDecimal | Flags1::AddLeadingZeroToHexNumbers | Flags1::BranchLeadingZeros | Flags1::SignedMemoryDisplacements | Flags1::ShowBranchSize | Flags1::UsePseudoOps | Flags1::MasmAddDsPrefix32 | Flags1::MasmSymbolDisplInBrackets | Flags1::MasmDisplInBrackets;
		flags2 = Flags2::None;
	}

	bool FormatterOptions::GetUppercasePrefixes() const
	{
		return (flags1 & Flags1::UppercasePrefixes) != 0;
	}

	void FormatterOptions::SetUppercasePrefixes(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UppercasePrefixes;
		}
		else
		{
			flags1 &= ~Flags1::UppercasePrefixes;
		}
	}

	bool FormatterOptions::GetUppercaseMnemonics() const
	{
		return (flags1 & Flags1::UppercaseMnemonics) != 0;
	}

	void FormatterOptions::SetUppercaseMnemonics(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UppercaseMnemonics;
		}
		else
		{
			flags1 &= ~Flags1::UppercaseMnemonics;
		}
	}

	bool FormatterOptions::GetUppercaseRegisters() const
	{
		return (flags1 & Flags1::UppercaseRegisters) != 0;
	}

	void FormatterOptions::SetUppercaseRegisters(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UppercaseRegisters;
		}
		else
		{
			flags1 &= ~Flags1::UppercaseRegisters;
		}
	}

	bool FormatterOptions::GetUppercaseKeywords() const
	{
		return (flags1 & Flags1::UppercaseKeywords) != 0;
	}

	void FormatterOptions::SetUppercaseKeywords(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UppercaseKeywords;
		}
		else
		{
			flags1 &= ~Flags1::UppercaseKeywords;
		}
	}

	bool FormatterOptions::GetUppercaseDecorators() const
	{
		return (flags1 & Flags1::UppercaseDecorators) != 0;
	}

	void FormatterOptions::SetUppercaseDecorators(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UppercaseDecorators;
		}
		else
		{
			flags1 &= ~Flags1::UppercaseDecorators;
		}
	}

	bool FormatterOptions::GetUppercaseAll() const
	{
		return (flags1 & Flags1::UppercaseAll) != 0;
	}

	void FormatterOptions::SetUppercaseAll(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UppercaseAll;
		}
		else
		{
			flags1 &= ~Flags1::UppercaseAll;
		}
	}

	std::int32_t FormatterOptions::GetFirstOperandCharIndex() const
	{
		return FirstOperandCharIndex;
	}

	void FormatterOptions::SetFirstOperandCharIndex(std::int32_t value)
	{
		FirstOperandCharIndex = value;
	}

	std::int32_t FormatterOptions::GetTabSize() const
	{
		return TabSize;
	}

	void FormatterOptions::SetTabSize(std::int32_t value)
	{
		TabSize = value;
	}

	bool FormatterOptions::GetSpaceAfterOperandSeparator() const
	{
		return (flags1 & Flags1::SpaceAfterOperandSeparator) != 0;
	}

	void FormatterOptions::SetSpaceAfterOperandSeparator(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::SpaceAfterOperandSeparator;
		}
		else
		{
			flags1 &= ~Flags1::SpaceAfterOperandSeparator;
		}
	}

	bool FormatterOptions::GetSpaceAfterMemoryBracket() const
	{
		return (flags1 & Flags1::SpaceAfterMemoryBracket) != 0;
	}

	void FormatterOptions::SetSpaceAfterMemoryBracket(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::SpaceAfterMemoryBracket;
		}
		else
		{
			flags1 &= ~Flags1::SpaceAfterMemoryBracket;
		}
	}

	bool FormatterOptions::GetSpaceBetweenMemoryAddOperators() const
	{
		return (flags1 & Flags1::SpaceBetweenMemoryAddOperators) != 0;
	}

	void FormatterOptions::SetSpaceBetweenMemoryAddOperators(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::SpaceBetweenMemoryAddOperators;
		}
		else
		{
			flags1 &= ~Flags1::SpaceBetweenMemoryAddOperators;
		}
	}

	bool FormatterOptions::GetSpaceBetweenMemoryMulOperators() const
	{
		return (flags1 & Flags1::SpaceBetweenMemoryMulOperators) != 0;
	}

	void FormatterOptions::SetSpaceBetweenMemoryMulOperators(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::SpaceBetweenMemoryMulOperators;
		}
		else
		{
			flags1 &= ~Flags1::SpaceBetweenMemoryMulOperators;
		}
	}

	bool FormatterOptions::GetScaleBeforeIndex() const
	{
		return (flags1 & Flags1::ScaleBeforeIndex) != 0;
	}

	void FormatterOptions::SetScaleBeforeIndex(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::ScaleBeforeIndex;
		}
		else
		{
			flags1 &= ~Flags1::ScaleBeforeIndex;
		}
	}

	bool FormatterOptions::GetAlwaysShowScale() const
	{
		return (flags1 & Flags1::AlwaysShowScale) != 0;
	}

	void FormatterOptions::SetAlwaysShowScale(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::AlwaysShowScale;
		}
		else
		{
			flags1 &= ~Flags1::AlwaysShowScale;
		}
	}

	bool FormatterOptions::GetAlwaysShowSegmentRegister() const
	{
		return (flags1 & Flags1::AlwaysShowSegmentRegister) != 0;
	}

	void FormatterOptions::SetAlwaysShowSegmentRegister(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::AlwaysShowSegmentRegister;
		}
		else
		{
			flags1 &= ~Flags1::AlwaysShowSegmentRegister;
		}
	}

	bool FormatterOptions::GetShowZeroDisplacements() const
	{
		return (flags1 & Flags1::ShowZeroDisplacements) != 0;
	}

	void FormatterOptions::SetShowZeroDisplacements(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::ShowZeroDisplacements;
		}
		else
		{
			flags1 &= ~Flags1::ShowZeroDisplacements;
		}
	}

	std::string FormatterOptions::GetHexPrefix() const
	{
		return HexPrefix;
	}

	void FormatterOptions::SetHexPrefix(const std::string& value)
	{
		HexPrefix = value;
	}

	std::string FormatterOptions::GetHexSuffix() const
	{
		return HexSuffix;
	}

	void FormatterOptions::SetHexSuffix(const std::string& value)
	{
		HexSuffix = value;
	}

	std::int32_t FormatterOptions::GetHexDigitGroupSize() const
	{
		return HexDigitGroupSize;
	}

	void FormatterOptions::SetHexDigitGroupSize(std::int32_t value)
	{
		HexDigitGroupSize = value;
	}

	std::string FormatterOptions::GetDecimalPrefix() const
	{
		return DecimalPrefix;
	}

	void FormatterOptions::SetDecimalPrefix(const std::string& value)
	{
		DecimalPrefix = value;
	}

	std::string FormatterOptions::GetDecimalSuffix() const
	{
		return DecimalSuffix;
	}

	void FormatterOptions::SetDecimalSuffix(const std::string& value)
	{
		DecimalSuffix = value;
	}

	std::int32_t FormatterOptions::GetDecimalDigitGroupSize() const
	{
		return DecimalDigitGroupSize;
	}

	void FormatterOptions::SetDecimalDigitGroupSize(std::int32_t value)
	{
		DecimalDigitGroupSize = value;
	}

	std::string FormatterOptions::GetOctalPrefix() const
	{
		return OctalPrefix;
	}

	void FormatterOptions::SetOctalPrefix(const std::string& value)
	{
		OctalPrefix = value;
	}

	std::string FormatterOptions::GetOctalSuffix() const
	{
		return OctalSuffix;
	}

	void FormatterOptions::SetOctalSuffix(const std::string& value)
	{
		OctalSuffix = value;
	}

	std::int32_t FormatterOptions::GetOctalDigitGroupSize() const
	{
		return OctalDigitGroupSize;
	}

	void FormatterOptions::SetOctalDigitGroupSize(std::int32_t value)
	{
		OctalDigitGroupSize = value;
	}

	std::string FormatterOptions::GetBinaryPrefix() const
	{
		return BinaryPrefix;
	}

	void FormatterOptions::SetBinaryPrefix(const std::string& value)
	{
		BinaryPrefix = value;
	}

	std::string FormatterOptions::GetBinarySuffix() const
	{
		return BinarySuffix;
	}

	void FormatterOptions::SetBinarySuffix(const std::string& value)
	{
		BinarySuffix = value;
	}

	std::int32_t FormatterOptions::GetBinaryDigitGroupSize() const
	{
		return BinaryDigitGroupSize;
	}

	void FormatterOptions::SetBinaryDigitGroupSize(std::int32_t value)
	{
		BinaryDigitGroupSize = value;
	}

	std::string FormatterOptions::GetDigitSeparator() const
	{
		return DigitSeparator;
	}

	void FormatterOptions::SetDigitSeparator(const std::string& value)
	{
		DigitSeparator = value;
	}

	bool FormatterOptions::GetLeadingZeros() const
	{
		return (flags1 & Flags1::LeadingZeros) != 0;
	}

	void FormatterOptions::SetLeadingZeros(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::LeadingZeros;
		}
		else
		{
			flags1 &= ~Flags1::LeadingZeros;
		}
	}

	bool FormatterOptions::GetLeadingZeroes() const
	{
		return GetLeadingZeros();
	}

	void FormatterOptions::SetLeadingZeroes(bool value)
	{
		SetLeadingZeros(value);
	}

	bool FormatterOptions::GetUppercaseHex() const
	{
		return (flags1 & Flags1::UppercaseHex) != 0;
	}

	void FormatterOptions::SetUppercaseHex(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UppercaseHex;
		}
		else
		{
			flags1 &= ~Flags1::UppercaseHex;
		}
	}

	bool FormatterOptions::GetSmallHexNumbersInDecimal() const
	{
		return (flags1 & Flags1::SmallHexNumbersInDecimal) != 0;
	}

	void FormatterOptions::SetSmallHexNumbersInDecimal(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::SmallHexNumbersInDecimal;
		}
		else
		{
			flags1 &= ~Flags1::SmallHexNumbersInDecimal;
		}
	}

	bool FormatterOptions::GetAddLeadingZeroToHexNumbers() const
	{
		return (flags1 & Flags1::AddLeadingZeroToHexNumbers) != 0;
	}

	void FormatterOptions::SetAddLeadingZeroToHexNumbers(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::AddLeadingZeroToHexNumbers;
		}
		else
		{
			flags1 &= ~Flags1::AddLeadingZeroToHexNumbers;
		}
	}

	Iced::Intel::NumberBase FormatterOptions::GetNumberBase() const
	{
		return numberBase;
	}

	void FormatterOptions::SetNumberBase(Iced::Intel::NumberBase value)
	{
		if (static_cast<std::uint32_t>(value) > static_cast<std::uint32_t>(NumberBase::Binary))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		numberBase = value;
	}

	bool FormatterOptions::GetBranchLeadingZeros() const
	{
		return (flags1 & Flags1::BranchLeadingZeros) != 0;
	}

	void FormatterOptions::SetBranchLeadingZeros(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::BranchLeadingZeros;
		}
		else
		{
			flags1 &= ~Flags1::BranchLeadingZeros;
		}
	}

	bool FormatterOptions::GetBranchLeadingZeroes() const
	{
		return GetBranchLeadingZeros();
	}

	void FormatterOptions::SetBranchLeadingZeroes(bool value)
	{
		SetBranchLeadingZeros(value);
	}

	bool FormatterOptions::GetSignedImmediateOperands() const
	{
		return (flags1 & Flags1::SignedImmediateOperands) != 0;
	}

	void FormatterOptions::SetSignedImmediateOperands(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::SignedImmediateOperands;
		}
		else
		{
			flags1 &= ~Flags1::SignedImmediateOperands;
		}
	}

	bool FormatterOptions::GetSignedMemoryDisplacements() const
	{
		return (flags1 & Flags1::SignedMemoryDisplacements) != 0;
	}

	void FormatterOptions::SetSignedMemoryDisplacements(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::SignedMemoryDisplacements;
		}
		else
		{
			flags1 &= ~Flags1::SignedMemoryDisplacements;
		}
	}

	bool FormatterOptions::GetDisplacementLeadingZeros() const
	{
		return (flags1 & Flags1::DisplacementLeadingZeros) != 0;
	}

	void FormatterOptions::SetDisplacementLeadingZeros(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::DisplacementLeadingZeros;
		}
		else
		{
			flags1 &= ~Flags1::DisplacementLeadingZeros;
		}
	}

	bool FormatterOptions::GetDisplacementLeadingZeroes() const
	{
		return GetDisplacementLeadingZeros();
	}

	void FormatterOptions::SetDisplacementLeadingZeroes(bool value)
	{
		SetDisplacementLeadingZeros(value);
	}

	Iced::Intel::MemorySizeOptions FormatterOptions::GetMemorySizeOptions() const
	{
		return memorySizeOptions;
	}

	void FormatterOptions::SetMemorySizeOptions(Iced::Intel::MemorySizeOptions value)
	{
		if (static_cast<std::uint32_t>(value) > static_cast<std::uint32_t>(MemorySizeOptions::Never))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		memorySizeOptions = value;
	}

	bool FormatterOptions::GetRipRelativeAddresses() const
	{
		return (flags1 & Flags1::RipRelativeAddresses) != 0;
	}

	void FormatterOptions::SetRipRelativeAddresses(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::RipRelativeAddresses;
		}
		else
		{
			flags1 &= ~Flags1::RipRelativeAddresses;
		}
	}

	bool FormatterOptions::GetShowBranchSize() const
	{
		return (flags1 & Flags1::ShowBranchSize) != 0;
	}

	void FormatterOptions::SetShowBranchSize(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::ShowBranchSize;
		}
		else
		{
			flags1 &= ~Flags1::ShowBranchSize;
		}
	}

	bool FormatterOptions::GetUsePseudoOps() const
	{
		return (flags1 & Flags1::UsePseudoOps) != 0;
	}

	void FormatterOptions::SetUsePseudoOps(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::UsePseudoOps;
		}
		else
		{
			flags1 &= ~Flags1::UsePseudoOps;
		}
	}

	bool FormatterOptions::GetShowSymbolAddress() const
	{
		return (flags1 & Flags1::ShowSymbolAddress) != 0;
	}

	void FormatterOptions::SetShowSymbolAddress(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::ShowSymbolAddress;
		}
		else
		{
			flags1 &= ~Flags1::ShowSymbolAddress;
		}
	}

	bool FormatterOptions::GetGasNakedRegisters() const
	{
		return (flags1 & Flags1::GasNakedRegisters) != 0;
	}

	void FormatterOptions::SetGasNakedRegisters(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::GasNakedRegisters;
		}
		else
		{
			flags1 &= ~Flags1::GasNakedRegisters;
		}
	}

	bool FormatterOptions::GetGasShowMnemonicSizeSuffix() const
	{
		return (flags1 & Flags1::GasShowMnemonicSizeSuffix) != 0;
	}

	void FormatterOptions::SetGasShowMnemonicSizeSuffix(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::GasShowMnemonicSizeSuffix;
		}
		else
		{
			flags1 &= ~Flags1::GasShowMnemonicSizeSuffix;
		}
	}

	bool FormatterOptions::GetGasSpaceAfterMemoryOperandComma() const
	{
		return (flags1 & Flags1::GasSpaceAfterMemoryOperandComma) != 0;
	}

	void FormatterOptions::SetGasSpaceAfterMemoryOperandComma(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::GasSpaceAfterMemoryOperandComma;
		}
		else
		{
			flags1 &= ~Flags1::GasSpaceAfterMemoryOperandComma;
		}
	}

	bool FormatterOptions::GetMasmAddDsPrefix32() const
	{
		return (flags1 & Flags1::MasmAddDsPrefix32) != 0;
	}

	void FormatterOptions::SetMasmAddDsPrefix32(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::MasmAddDsPrefix32;
		}
		else
		{
			flags1 &= ~Flags1::MasmAddDsPrefix32;
		}
	}

	bool FormatterOptions::GetMasmSymbolDisplInBrackets() const
	{
		return (flags1 & Flags1::MasmSymbolDisplInBrackets) != 0;
	}

	void FormatterOptions::SetMasmSymbolDisplInBrackets(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::MasmSymbolDisplInBrackets;
		}
		else
		{
			flags1 &= ~Flags1::MasmSymbolDisplInBrackets;
		}
	}

	bool FormatterOptions::GetMasmDisplInBrackets() const
	{
		return (flags1 & Flags1::MasmDisplInBrackets) != 0;
	}

	void FormatterOptions::SetMasmDisplInBrackets(bool value)
	{
		if (value)
		{
			flags1 |= Flags1::MasmDisplInBrackets;
		}
		else
		{
			flags1 &= ~Flags1::MasmDisplInBrackets;
		}
	}

	bool FormatterOptions::GetNasmShowSignExtendedImmediateSize() const
	{
		return (flags2 & Flags2::NasmShowSignExtendedImmediateSize) != 0;
	}

	void FormatterOptions::SetNasmShowSignExtendedImmediateSize(bool value)
	{
		if (value)
		{
			flags2 |= Flags2::NasmShowSignExtendedImmediateSize;
		}
		else
		{
			flags2 &= ~Flags2::NasmShowSignExtendedImmediateSize;
		}
	}

	bool FormatterOptions::GetPreferST0() const
	{
		return (flags2 & Flags2::PreferST0) != 0;
	}

	void FormatterOptions::SetPreferST0(bool value)
	{
		if (value)
		{
			flags2 |= Flags2::PreferST0;
		}
		else
		{
			flags2 &= ~Flags2::PreferST0;
		}
	}

	bool FormatterOptions::GetShowUselessPrefixes() const
	{
		return (flags2 & Flags2::ShowUselessPrefixes) != 0;
	}

	void FormatterOptions::SetShowUselessPrefixes(bool value)
	{
		if (value)
		{
			flags2 |= Flags2::ShowUselessPrefixes;
		}
		else
		{
			flags2 &= ~Flags2::ShowUselessPrefixes;
		}
	}

	Iced::Intel::CC_b FormatterOptions::GetCCB() const
	{
		return cc_b;
	}

	void FormatterOptions::SetCCB(Iced::Intel::CC_b value)
	{
		if (value >= static_cast<Iced::Intel::CC_b>(3))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_b = value;
	}

	Iced::Intel::CC_ae FormatterOptions::GetCCAe() const
	{
		return cc_ae;
	}

	void FormatterOptions::SetCCAe(Iced::Intel::CC_ae value)
	{
		if (value >= static_cast<Iced::Intel::CC_ae>(3))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_ae = value;
	}

	Iced::Intel::CC_e FormatterOptions::GetCCE() const
	{
		return cc_e;
	}

	void FormatterOptions::SetCCE(Iced::Intel::CC_e value)
	{
		if (value >= static_cast<Iced::Intel::CC_e>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_e = value;
	}

	Iced::Intel::CC_ne FormatterOptions::GetCCNe() const
	{
		return cc_ne;
	}

	void FormatterOptions::SetCCNe(Iced::Intel::CC_ne value)
	{
		if (value >= static_cast<Iced::Intel::CC_ne>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_ne = value;
	}

	Iced::Intel::CC_be FormatterOptions::GetCCBe() const
	{
		return cc_be;
	}

	void FormatterOptions::SetCCBe(Iced::Intel::CC_be value)
	{
		if (value >= static_cast<Iced::Intel::CC_be>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_be = value;
	}

	Iced::Intel::CC_a FormatterOptions::GetCCA() const
	{
		return cc_a;
	}

	void FormatterOptions::SetCCA(Iced::Intel::CC_a value)
	{
		if (value >= static_cast<Iced::Intel::CC_a>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_a = value;
	}

	Iced::Intel::CC_p FormatterOptions::GetCCP() const
	{
		return cc_p;
	}

	void FormatterOptions::SetCCP(Iced::Intel::CC_p value)
	{
		if (value >= static_cast<Iced::Intel::CC_p>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_p = value;
	}

	Iced::Intel::CC_np FormatterOptions::GetCCNp() const
	{
		return cc_np;
	}

	void FormatterOptions::SetCCNp(Iced::Intel::CC_np value)
	{
		if (value >= static_cast<Iced::Intel::CC_np>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_np = value;
	}

	Iced::Intel::CC_l FormatterOptions::GetCCL() const
	{
		return cc_l;
	}

	void FormatterOptions::SetCCL(Iced::Intel::CC_l value)
	{
		if (value >= static_cast<Iced::Intel::CC_l>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_l = value;
	}

	Iced::Intel::CC_ge FormatterOptions::GetCCGe() const
	{
		return cc_ge;
	}

	void FormatterOptions::SetCCGe(Iced::Intel::CC_ge value)
	{
		if (value >= static_cast<Iced::Intel::CC_ge>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_ge = value;
	}

	Iced::Intel::CC_le FormatterOptions::GetCCLe() const
	{
		return cc_le;
	}

	void FormatterOptions::SetCCLe(Iced::Intel::CC_le value)
	{
		if (value >= static_cast<Iced::Intel::CC_le>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_le = value;
	}

	Iced::Intel::CC_g FormatterOptions::GetCCG() const
	{
		return cc_g;
	}

	void FormatterOptions::SetCCG(Iced::Intel::CC_g value)
	{
		if (value >= static_cast<Iced::Intel::CC_g>(2))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		cc_g = value;
	}

	FormatterOptions* FormatterOptions::CreateGas()
	{
		FormatterOptions* tempVar = new FormatterOptions();
		tempVar->SetHexPrefix("0x");
		tempVar->SetOctalPrefix("0");
		tempVar->SetBinaryPrefix("0b");
		return tempVar;
	}

	FormatterOptions* FormatterOptions::CreateIntel()
	{
		FormatterOptions* tempVar = new FormatterOptions();
		tempVar->SetHexSuffix("h");
		tempVar->SetOctalSuffix("o");
		tempVar->SetBinarySuffix("b");
		return tempVar;
	}

	FormatterOptions* FormatterOptions::CreateMasm()
	{
		FormatterOptions* tempVar = new FormatterOptions();
		tempVar->SetHexSuffix("h");
		tempVar->SetOctalSuffix("o");
		tempVar->SetBinarySuffix("b");
		return tempVar;
	}

	FormatterOptions* FormatterOptions::CreateNasm()
	{
		FormatterOptions* tempVar = new FormatterOptions();
		tempVar->SetHexSuffix("h");
		tempVar->SetOctalSuffix("o");
		tempVar->SetBinarySuffix("b");
		return tempVar;
	}
}
