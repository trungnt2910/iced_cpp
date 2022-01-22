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

#include "IntelFormatter.h"
#include "IntelFormatterInternal/Registers.h"
#include "IntelFormatterInternal/Iced.Intel.IntelFormatterInternal.InstrInfos.h"
#include "ThrowHelper.h"
#include "FormatterTextKind.g.h"
#include "FormatterInternal/Iced.Intel.FormatterInternal.FormatterUtils.h"
#include "MemorySizeOptions.g.h"
#include "CodeSize.g.h"
#include "FormatterInternal/MnemonicCC.h"
#include "Code.g.h"
#include "Iced.Intel.IcedConstants.h"
#include "OpKind.g.h"
#include "FormatterInternal/FormatterUtils.h"
#include "InstructionUtils.h"
#include "RoundingControl.g.h"
#include "Static.h"
#include "MvexRegMemConv.g.h"
#include "MvexInfo.h"
#include "MvexConvFn.g.h"

using namespace Iced::Intel::FormatterInternal;
using namespace Iced::Intel::IntelFormatterInternal;

namespace Iced::Intel
{

	const FormatterOptions& IntelFormatter::GetOptions() const
	{
		return options;
	}

	FormatterOptions& IntelFormatter::GetOptions()
	{
		return options;
	}

	IntelFormatter::IntelFormatter() : IntelFormatter(nullptr, nullptr)
	{
	}

	IntelFormatter::IntelFormatter(ISymbolResolver* symbolResolver, IFormatterOptionsProvider* optionsProvider) : numberFormatter(true)
	{
		this->options = FormatterOptions::CreateIntel();
		this->symbolResolver = symbolResolver;
		this->optionsProvider = optionsProvider;
		allRegisters = Registers::AllRegisters;
		instrInfos = InstrInfos::AllInfos;
		allMemorySizes = MemorySizes::AllMemorySizes;
		opSizeStrings = s_opSizeStrings;
		addrSizeStrings = s_addrSizeStrings;
		rcStrings = s_rcStrings;
		rcSaeStrings = s_rcSaeStrings;
		branchInfos = s_branchInfos;
		scaleNumbers = s_scaleNumbers;
		mvexRegMemConsts32 = s_mvexRegMemConsts32;
		mvexRegMemConsts64 = s_mvexRegMemConsts64;
	}

	IntelFormatter::IntelFormatter(const FormatterOptions& options, ISymbolResolver* symbolResolver, IFormatterOptionsProvider* optionsProvider) : IntelFormatter(symbolResolver, optionsProvider)
	{
		// Double assignment, but better than a memory leak.
		this->options = options;
	}

	FormatterString IntelFormatter::str_bnd = FormatterString("bnd");
	FormatterString IntelFormatter::str_far = FormatterString("far");
	FormatterString IntelFormatter::str_hint_not_taken = FormatterString("hint-not-taken");
	FormatterString IntelFormatter::str_hint_taken = FormatterString("hint-taken");
	FormatterString IntelFormatter::str_lock = FormatterString("lock");
	FormatterString IntelFormatter::str_notrack = FormatterString("notrack");
	FormatterString IntelFormatter::str_rep = FormatterString("rep");
	std::vector<FormatterString> IntelFormatter::str_repe = { FormatterString("repe"), FormatterString("repz") };
	std::vector<FormatterString> IntelFormatter::str_repne = { FormatterString("repne"), FormatterString("repnz") };
	FormatterString IntelFormatter::str_sae = FormatterString("sae");
	FormatterString IntelFormatter::str_xacquire = FormatterString("xacquire");
	FormatterString IntelFormatter::str_xrelease = FormatterString("xrelease");
	FormatterString IntelFormatter::str_z = FormatterString("z");
	std::vector<FormatterString> IntelFormatter::s_opSizeStrings = { FormatterString(""), FormatterString("data16"), FormatterString("data32"), FormatterString("data64") };
	std::vector<FormatterString> IntelFormatter::s_addrSizeStrings = { FormatterString(""), FormatterString("addr16"), FormatterString("addr32"), FormatterString("addr64") };
	std::vector<FormatterString> IntelFormatter::s_rcStrings = { FormatterString("rne"), FormatterString("rd"), FormatterString("ru"), FormatterString("rz") };
	std::vector<FormatterString> IntelFormatter::s_rcSaeStrings = { FormatterString("rne-sae"), FormatterString("rd-sae"), FormatterString("ru-sae"), FormatterString("rz-sae") };
	std::vector<std::vector<FormatterString>> IntelFormatter::s_branchInfos = 
	{
		{}, {FormatterString("short")}
	};
	std::vector<std::string> IntelFormatter::s_scaleNumbers = { "1", "2", "4", "8" };
	std::vector<FormatterString> IntelFormatter::s_mvexRegMemConsts32 = { FormatterString(""), FormatterString(""), FormatterString("cdab"), FormatterString("badc"), FormatterString("dacb"), FormatterString("aaaa"), FormatterString("bbbb"), FormatterString("cccc"), FormatterString("dddd"), FormatterString(""), FormatterString("1to16"), FormatterString("4to16"), FormatterString("float16"), FormatterString("uint8"), FormatterString("sint8"), FormatterString("uint16"), FormatterString("sint16") };
	std::vector<FormatterString> IntelFormatter::s_mvexRegMemConsts64 = { FormatterString(""), FormatterString(""), FormatterString("cdab"), FormatterString("badc"), FormatterString("dacb"), FormatterString("aaaa"), FormatterString("bbbb"), FormatterString("cccc"), FormatterString("dddd"), FormatterString(""), FormatterString("1to8"), FormatterString("4to8"), FormatterString("float16"), FormatterString("uint8"), FormatterString("sint8"), FormatterString("uint16"), FormatterString("sint16") };
	FormatterString IntelFormatter::str_eh = FormatterString("eh");

	void IntelFormatter::FormatMnemonic(const Instruction& instruction, FormatterOutput& output, FormatMnemonicOptions options)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(this->options, instruction, opInfo);
		std::int32_t column = 0;
		FormatMnemonic(instruction, output, opInfo, column, options);
	}

	std::int32_t IntelFormatter::GetOperandCount(const Instruction& instruction)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		return opInfo.OpCount;
	}

	bool IntelFormatter::TryGetOpAccess(const Instruction& instruction, std::int32_t operand, OpAccess& access)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		// Although it's a TryXXX() method, it should only accept valid instruction operand indexes
		if (static_cast<std::uint32_t>(operand) >= static_cast<std::uint32_t>(opInfo.OpCount))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_operand();
		}
		return opInfo.TryGetOpAccess(operand, access);
	}

	std::int32_t IntelFormatter::GetInstructionOperand(const Instruction& instruction, std::int32_t operand)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		if (static_cast<std::uint32_t>(operand) >= static_cast<std::uint32_t>(opInfo.OpCount))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_operand();
		}
		return opInfo.GetInstructionIndex(operand);
	}

	std::int32_t IntelFormatter::GetFormatterOperand(const Instruction& instruction, std::int32_t instructionOperand)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		if (static_cast<std::uint32_t>(instructionOperand) >= static_cast<std::uint32_t>(instruction.GetOpCount()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_instructionOperand();
		}
		return opInfo.GetOperandIndex(instructionOperand);
	}

	void IntelFormatter::FormatOperand(const Instruction& instruction, FormatterOutput& output, std::int32_t operand)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		if (static_cast<std::uint32_t>(operand) >= static_cast<std::uint32_t>(opInfo.OpCount))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_operand();
		}
		FormatOperand(instruction, output, opInfo, operand);
	}

	void IntelFormatter::FormatOperandSeparator(const Instruction& instruction, FormatterOutput& output)
	{

		output.Write(",", FormatterTextKind::Punctuation);
		if (options.GetSpaceAfterOperandSeparator())
		{
			output.Write(" ", FormatterTextKind::Text);
		}
	}

	void IntelFormatter::FormatAllOperands(const Instruction& instruction, FormatterOutput& output)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		FormatOperands(instruction, output, opInfo);
	}

	void IntelFormatter::Format(const Instruction& instruction, FormatterOutput& output)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		std::int32_t column = 0;
		FormatMnemonic(instruction, output, opInfo, column, FormatMnemonicOptions::None);
		if (opInfo.OpCount != 0)
		{
			FormatterUtils::AddTabs(output, column, options.GetFirstOperandCharIndex(), options.GetTabSize());
			FormatOperands(instruction, output, opInfo);
		}
	}

	void IntelFormatter::FormatMnemonic(const Instruction& instruction, FormatterOutput& output, InstrOpInfo const opInfo, std::int32_t& column, FormatMnemonicOptions mnemonicOptions)
	{

		bool needSpace = false;
		if ((mnemonicOptions & FormatMnemonicOptions::NoPrefixes) == 0 && (opInfo.Flags & InstrOpInfoFlags::MnemonicIsDirective) == 0)
		{
			auto prefixSeg = instruction.GetSegmentPrefix();
			constexpr std::uint32_t PrefixFlags = (static_cast<std::uint32_t>(InstrOpInfoFlags::SizeOverrideMask) << static_cast<std::int32_t>(InstrOpInfoFlags::OpSizeShift)) | (static_cast<std::uint32_t>(InstrOpInfoFlags::SizeOverrideMask) << static_cast<std::int32_t>(InstrOpInfoFlags::AddrSizeShift)) | static_cast<std::uint32_t>(InstrOpInfoFlags::BndPrefix) | static_cast<std::uint32_t>(InstrOpInfoFlags::JccNotTaken) | static_cast<std::uint32_t>(InstrOpInfoFlags::JccTaken);
			if ((static_cast<std::uint32_t>(prefixSeg) | instruction.GetHasAnyOfLockRepRepnePrefix() | (static_cast<std::uint32_t>((std::uint32_t)opInfo.Flags & PrefixFlags))) != 0)
			{
				FormatterString prefix;
				prefix = opSizeStrings[(static_cast<std::int32_t>(opInfo.Flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::OpSizeShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::SizeOverrideMask)];
				if (prefix.GetLength() != 0)
				{
					FormatPrefix(output, instruction, column, prefix, PrefixKind::OperandSize, needSpace);
				}
				prefix = addrSizeStrings[(static_cast<std::int32_t>(opInfo.Flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::AddrSizeShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::SizeOverrideMask)];
				if (prefix.GetLength() != 0)
				{
					FormatPrefix(output, instruction, column, prefix, PrefixKind::AddressSize, needSpace);
				}
				bool hasNotrackPrefix = prefixSeg == Register::DS && FormatterUtils::IsNotrackPrefixBranch(instruction.GetCode());
				if (!hasNotrackPrefix && prefixSeg != Register::None && ShowSegmentPrefix(instruction, opInfo))
				{
					FormatPrefix(output, instruction, column, allRegisters[static_cast<std::int32_t>(prefixSeg)], FormatterUtils::GetSegmentRegisterPrefixKind(prefixSeg), needSpace);
				}
				if (instruction.GetHasXacquirePrefix())
				{
					FormatPrefix(output, instruction, column, str_xacquire, PrefixKind::Xacquire, needSpace);
				}
				if (instruction.GetHasXreleasePrefix())
				{
					FormatPrefix(output, instruction, column, str_xrelease, PrefixKind::Xrelease, needSpace);
				}
				if (instruction.GetHasLockPrefix())
				{
					FormatPrefix(output, instruction, column, str_lock, PrefixKind::Lock, needSpace);
				}
				if ((opInfo.Flags & InstrOpInfoFlags::JccNotTaken) != 0)
				{
					FormatPrefix(output, instruction, column, str_hint_not_taken, PrefixKind::HintNotTaken, needSpace);
				}
				else if ((opInfo.Flags & InstrOpInfoFlags::JccTaken) != 0)
				{
					FormatPrefix(output, instruction, column, str_hint_taken, PrefixKind::HintTaken, needSpace);
				}
				if (hasNotrackPrefix)
				{
					FormatPrefix(output, instruction, column, str_notrack, PrefixKind::Notrack, needSpace);
				}
				bool hasBnd = (opInfo.Flags & InstrOpInfoFlags::BndPrefix) != 0;
				if (hasBnd)
				{
					FormatPrefix(output, instruction, column, str_bnd, PrefixKind::Bnd, needSpace);
				}
				if (instruction.GetHasRepePrefix() && FormatterUtils::ShowRepOrRepePrefix(instruction.GetCode(), options))
				{
					if (FormatterUtils::IsRepeOrRepneInstruction(instruction.GetCode()))
					{
						FormatPrefix(output, instruction, column, MnemonicCC::GetMnemonicCC(options, 4, str_repe), PrefixKind::Repe, needSpace);
					}
					else
					{
						FormatPrefix(output, instruction, column, str_rep, PrefixKind::Rep, needSpace);
					}
				}
				if (instruction.GetHasRepnePrefix() && !hasBnd && FormatterUtils::ShowRepnePrefix(instruction.GetCode(), options))
				{
					FormatPrefix(output, instruction, column, MnemonicCC::GetMnemonicCC(options, 5, str_repne), PrefixKind::Repne, needSpace);
				}
			}
		}
		if ((mnemonicOptions & FormatMnemonicOptions::NoMnemonic) == 0)
		{
			if (needSpace)
			{
				output.Write(" ", FormatterTextKind::Text);
				column++;
			}
			auto mnemonic = opInfo.Mnemonic;
			if ((opInfo.Flags & InstrOpInfoFlags::MnemonicIsDirective) != 0)
			{
				output.Write(mnemonic.Get(options.GetUppercaseKeywords() || options.GetUppercaseAll()), FormatterTextKind::Directive);
			}
			else
			{
				output.WriteMnemonic(instruction, mnemonic.Get(options.GetUppercaseMnemonics() || options.GetUppercaseAll()));
			}
			column += mnemonic.GetLength();
			if ((opInfo.Flags & InstrOpInfoFlags::FarMnemonic) != 0)
			{
				output.Write(" ", FormatterTextKind::Text);
				// This should be treated as part of the mnemonic
				output.WriteMnemonic(instruction, str_far.Get(options.GetUppercaseMnemonics() || options.GetUppercaseAll()));
				column += str_far.GetLength() + 1;
			}
		}
	}

	bool IntelFormatter::ShowSegmentPrefix(const Instruction& instruction, InstrOpInfo const opInfo)
	{
		if ((opInfo.Flags & InstrOpInfoFlags::IgnoreSegmentPrefix) != 0)
		{
			return false;
		}
		switch (instruction.GetCode())
		{
		case Code::Monitorw:
		case Code::Monitord:
		case Code::Monitorq:
		case Code::Monitorxw:
		case Code::Monitorxd:
		case Code::Monitorxq:
		case Code::Clzerow:
		case Code::Clzerod:
		case Code::Clzeroq:
		case Code::Umonitor_r16:
		case Code::Umonitor_r32:
		case Code::Umonitor_r64:
			return FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options);
		default:
			break;
		}
		for (std::int32_t i = 0; i < opInfo.OpCount; i++)
		{
			switch (opInfo.GetOpKind(i))
			{
			case InstrOpKind::Register:
			case InstrOpKind::NearBranch16:
			case InstrOpKind::NearBranch32:
			case InstrOpKind::NearBranch64:
			case InstrOpKind::FarBranch16:
			case InstrOpKind::FarBranch32:
			case InstrOpKind::Immediate8:
			case InstrOpKind::Immediate8_2nd:
			case InstrOpKind::Immediate16:
			case InstrOpKind::Immediate32:
			case InstrOpKind::Immediate64:
			case InstrOpKind::Immediate8to16:
			case InstrOpKind::Immediate8to32:
			case InstrOpKind::Immediate8to64:
			case InstrOpKind::Immediate32to64:
			case InstrOpKind::MemoryESDI:
			case InstrOpKind::MemoryESEDI:
			case InstrOpKind::MemoryESRDI:
			case InstrOpKind::DeclareByte:
			case InstrOpKind::DeclareWord:
			case InstrOpKind::DeclareDword:
			case InstrOpKind::DeclareQword:
				break;
			case InstrOpKind::MemorySegSI:
			case InstrOpKind::MemorySegESI:
			case InstrOpKind::MemorySegRSI:
			case InstrOpKind::MemorySegDI:
			case InstrOpKind::MemorySegEDI:
			case InstrOpKind::MemorySegRDI:
			case InstrOpKind::Memory:
				return false;
			default:
				throw InvalidOperationException();
			}
		}
		return options.GetShowUselessPrefixes();
	}

	void IntelFormatter::FormatPrefix(FormatterOutput& output, const Instruction& instruction, std::int32_t& column, FormatterString prefix, PrefixKind prefixKind, bool& needSpace)
	{
		if (needSpace)
		{
			column++;
			output.Write(" ", FormatterTextKind::Text);
		}
		output.WritePrefix(instruction, prefix.Get(options.GetUppercasePrefixes() || options.GetUppercaseAll()), prefixKind);
		column += prefix.GetLength();
		needSpace = true;
	}

	void IntelFormatter::FormatOperands(const Instruction& instruction, FormatterOutput& output, InstrOpInfo const opInfo)
	{

		for (std::int32_t i = 0; i < opInfo.OpCount; i++)
		{
			if (i > 0)
			{
				output.Write(",", FormatterTextKind::Punctuation);
				if (options.GetSpaceAfterOperandSeparator())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
			}
			FormatOperand(instruction, output, opInfo, i);
		}
	}

	void IntelFormatter::FormatOperand(const Instruction& instruction, FormatterOutput& output, InstrOpInfo const opInfo, std::int32_t operand)
	{
		assert(static_cast<std::uint32_t>(operand) < static_cast<std::uint32_t>(opInfo.OpCount));

		std::int32_t mvexRmOperand;
		if (IcedConstants::IsMvex(instruction.GetCode()))
		{
			auto opCount = instruction.GetOpCount();
			assert(opCount != 0);
			mvexRmOperand = instruction.GetOpKind(opCount - 1) == OpKind::Immediate8 ? opCount - 2 : opCount - 1;
		}
		else
		{
			mvexRmOperand = -1;
		}
		std::int32_t instructionOperand = opInfo.GetInstructionIndex(operand);
		std::string s;
		FormatterFlowControl flowControl;
		std::uint8_t imm8;
		std::uint16_t imm16;
		std::uint32_t imm32;
		std::uint64_t imm64, value64;
		std::int32_t immSize;
		NumberFormattingOptions numberOptions;
		SymbolResult symbol;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: ISymbolResolver? symbolResolver;
		ISymbolResolver* symbolResolver;
		FormatterOperandOptions operandOptions;
		NumberKind numberKind;
		auto opKind = opInfo.GetOpKind(operand);
		switch (opKind)
		{
		case InstrOpKind::Register:
			FormatRegister(output, instruction, operand, instructionOperand, opInfo.GetOpRegister(operand));
			break;
		case InstrOpKind::NearBranch16:
		case InstrOpKind::NearBranch32:
		case InstrOpKind::NearBranch64:
			if (opKind == InstrOpKind::NearBranch64)
			{
				immSize = 8;
				imm64 = instruction.GetNearBranch64();
				numberKind = NumberKind::UInt64;
			}
			else if (opKind == InstrOpKind::NearBranch32)
			{
				immSize = 4;
				imm64 = instruction.GetNearBranch32();
				numberKind = NumberKind::UInt32;
			}
			else
			{
				immSize = 2;
				imm64 = instruction.GetNearBranch16();
				numberKind = NumberKind::UInt16;
			}
			numberOptions = NumberFormattingOptions::CreateBranchInternal(options);
			operandOptions = FormatterOperandOptions(options.GetShowBranchSize() ? FormatterOperandOptions::Flags::None : FormatterOperandOptions::Flags::NoBranchSize);
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, imm64, immSize, symbol))
			{
				FormatFlowControl(output, opInfo.Flags, operandOptions);
				output.Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options.GetShowSymbolAddress());
			}
			else
			{
				flowControl = FormatterUtils::GetFlowControl(instruction);
				FormatFlowControl(output, opInfo.Flags, operandOptions);
				if (opKind == InstrOpKind::NearBranch32)
				{
					s = numberFormatter.FormatUInt32(options, numberOptions, instruction.GetNearBranch32(), numberOptions.LeadingZeros);
				}
				else if (opKind == InstrOpKind::NearBranch64)
				{
					s = numberFormatter.FormatUInt64(options, numberOptions, instruction.GetNearBranch64(), numberOptions.LeadingZeros);
				}
				else
				{
					s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetNearBranch16(), numberOptions.LeadingZeros);
				}
				output.WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterUtils::IsCall(flowControl) ? FormatterTextKind::FunctionAddress : FormatterTextKind::LabelAddress);
			}
			break;
		case InstrOpKind::FarBranch16:
		case InstrOpKind::FarBranch32:
			if (opKind == InstrOpKind::FarBranch32)
			{
				immSize = 4;
				imm64 = instruction.GetFarBranch32();
				numberKind = NumberKind::UInt32;
			}
			else
			{
				immSize = 2;
				imm64 = instruction.GetFarBranch16();
				numberKind = NumberKind::UInt16;
			}
			numberOptions = NumberFormattingOptions::CreateBranchInternal(options);
			operandOptions = FormatterOperandOptions(options.GetShowBranchSize() ? FormatterOperandOptions::Flags::None : FormatterOperandOptions::Flags::NoBranchSize);
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, static_cast<std::uint32_t>(imm64), immSize, symbol))
			{
				FormatFlowControl(output, opInfo.Flags, operandOptions);
				output.Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options.GetShowSymbolAddress());
				output.Write(",", FormatterTextKind::Punctuation);
				if (options.GetSpaceAfterOperandSeparator())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				assert(operand + 1 == 1);
				SymbolResult selectorSymbol;
				if (!symbolResolver->TryGetSymbol(instruction, operand + 1, instructionOperand, instruction.GetFarBranchSelector(), 2, selectorSymbol))
				{
					s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranchSelector(), numberOptions.LeadingZeros);
					output.WriteNumber(instruction, operand, instructionOperand, s, instruction.GetFarBranchSelector(), NumberKind::UInt16, FormatterTextKind::SelectorValue);
				}
				else
				{
					output.Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, instruction.GetFarBranchSelector(), selectorSymbol, options.GetShowSymbolAddress());
				}
			}
			else
			{
				flowControl = FormatterUtils::GetFlowControl(instruction);
				FormatFlowControl(output, opInfo.Flags, operandOptions);
				if (opKind == InstrOpKind::FarBranch32)
				{
					s = numberFormatter.FormatUInt32(options, numberOptions, instruction.GetFarBranch32(), numberOptions.LeadingZeros);
				}
				else
				{
					s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranch16(), numberOptions.LeadingZeros);
				}
				output.WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterUtils::IsCall(flowControl) ? FormatterTextKind::FunctionAddress : FormatterTextKind::LabelAddress);
				output.Write(",", FormatterTextKind::Punctuation);
				if (options.GetSpaceAfterOperandSeparator())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranchSelector(), numberOptions.LeadingZeros);
				output.WriteNumber(instruction, operand, instructionOperand, s, instruction.GetFarBranchSelector(), NumberKind::UInt16, FormatterTextKind::SelectorValue);
			}
			break;
		case InstrOpKind::Immediate8:
		case InstrOpKind::Immediate8_2nd:
		case InstrOpKind::DeclareByte:
			if (opKind == InstrOpKind::Immediate8)
			{
				imm8 = instruction.GetImmediate8();
			}
			else if (opKind == InstrOpKind::Immediate8_2nd)
			{
				imm8 = instruction.GetImmediate8_2nd();
			}
			else
			{
				imm8 = instruction.GetDeclareByteValue(operand);
			}
			numberOptions = NumberFormattingOptions::CreateImmediateInternal(options);
			operandOptions = Iced::Intel::FormatterOperandOptions();
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, imm8, 1, symbol))
			{
				output.Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm8, symbol, options.GetShowSymbolAddress());
			}
			else
			{
				if (numberOptions.SignedNumber)
				{
					imm64 = static_cast<std::uint64_t>(static_cast<std::int8_t>(imm8));
					numberKind = NumberKind::Int8;
					if (static_cast<std::int8_t>(imm8) < 0)
					{
						output.Write("-", FormatterTextKind::Operator);
						imm8 = static_cast<std::uint8_t>(-static_cast<std::int8_t>(imm8));
					}
				}
				else
				{
					imm64 = imm8;
					numberKind = NumberKind::UInt8;
				}
				s = numberFormatter.FormatUInt8(options, numberOptions, imm8);
				output.WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterTextKind::Number);
			}
			break;
		case InstrOpKind::Immediate16:
		case InstrOpKind::Immediate8to16:
		case InstrOpKind::DeclareWord:
			if (opKind == InstrOpKind::Immediate16)
			{
				imm16 = instruction.GetImmediate16();
			}
			else if (opKind == InstrOpKind::Immediate8to16)
			{
				imm16 = static_cast<std::uint16_t>(instruction.GetImmediate8to16());
			}
			else
			{
				imm16 = instruction.GetDeclareWordValue(operand);
			}
			numberOptions = NumberFormattingOptions::CreateImmediateInternal(options);
			operandOptions = Iced::Intel::FormatterOperandOptions();
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, imm16, 2, symbol))
			{
				output.Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm16, symbol, options.GetShowSymbolAddress());
			}
			else
			{
				if (numberOptions.SignedNumber)
				{
					imm64 = static_cast<std::uint64_t>(static_cast<std::int16_t>(imm16));
					numberKind = NumberKind::Int16;
					if (static_cast<std::int16_t>(imm16) < 0)
					{
						output.Write("-", FormatterTextKind::Operator);
						imm16 = static_cast<std::uint16_t>(-static_cast<std::int16_t>(imm16));
					}
				}
				else
				{
					imm64 = imm16;
					numberKind = NumberKind::UInt16;
				}
				s = numberFormatter.FormatUInt16(options, numberOptions, imm16);
				output.WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterTextKind::Number);
			}
			break;
		case InstrOpKind::Immediate32:
		case InstrOpKind::Immediate8to32:
		case InstrOpKind::DeclareDword:
			if (opKind == InstrOpKind::Immediate32)
			{
				imm32 = instruction.GetImmediate32();
			}
			else if (opKind == InstrOpKind::Immediate8to32)
			{
				imm32 = static_cast<std::uint32_t>(instruction.GetImmediate8to32());
			}
			else
			{
				imm32 = instruction.GetDeclareDwordValue(operand);
			}
			numberOptions = NumberFormattingOptions::CreateImmediateInternal(options);
			operandOptions = Iced::Intel::FormatterOperandOptions();
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, imm32, 4, symbol))
			{
				output.Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm32, symbol, options.GetShowSymbolAddress());
			}
			else
			{
				if (numberOptions.SignedNumber)
				{
					imm64 = static_cast<std::uint64_t>(static_cast<std::int32_t>(imm32));
					numberKind = NumberKind::Int32;
					if (static_cast<std::int32_t>(imm32) < 0)
					{
						output.Write("-", FormatterTextKind::Operator);
						imm32 = static_cast<std::uint32_t>(-static_cast<std::int32_t>(imm32));
					}
				}
				else
				{
					imm64 = imm32;
					numberKind = NumberKind::UInt32;
				}
				s = numberFormatter.FormatUInt32(options, numberOptions, imm32);
				output.WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterTextKind::Number);
			}
			break;
		case InstrOpKind::Immediate64:
		case InstrOpKind::Immediate8to64:
		case InstrOpKind::Immediate32to64:
		case InstrOpKind::DeclareQword:
			if (opKind == InstrOpKind::Immediate32to64)
			{
				imm64 = static_cast<std::uint64_t>(instruction.GetImmediate32to64());
			}
			else if (opKind == InstrOpKind::Immediate8to64)
			{
				imm64 = static_cast<std::uint64_t>(instruction.GetImmediate8to64());
			}
			else if (opKind == InstrOpKind::Immediate64)
			{
				imm64 = instruction.GetImmediate64();
			}
			else
			{
				imm64 = instruction.GetDeclareQwordValue(operand);
			}
			numberOptions = NumberFormattingOptions::CreateImmediateInternal(options);
			operandOptions = Iced::Intel::FormatterOperandOptions();
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, imm64, 8, symbol))
			{
				output.Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options.GetShowSymbolAddress());
			}
			else
			{
				value64 = imm64;
				if (numberOptions.SignedNumber)
				{
					numberKind = NumberKind::Int64;
					if (static_cast<std::int64_t>(imm64) < 0)
					{
						output.Write("-", FormatterTextKind::Operator);
						imm64 = static_cast<std::uint64_t>(-static_cast<std::int64_t>(imm64));
					}
				}
				else
				{
					numberKind = NumberKind::UInt64;
				}
				s = numberFormatter.FormatUInt64(options, numberOptions, imm64);
				output.WriteNumber(instruction, operand, instructionOperand, s, value64, numberKind, FormatterTextKind::Number);
			}
			break;
		case InstrOpKind::MemorySegSI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::SI, Register::None, 0, 0, 0, 2, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegESI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::ESI, Register::None, 0, 0, 0, 4, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegRSI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::RSI, Register::None, 0, 0, 0, 8, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegDI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::DI, Register::None, 0, 0, 0, 2, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegEDI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::EDI, Register::None, 0, 0, 0, 4, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegRDI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::RDI, Register::None, 0, 0, 0, 8, opInfo.Flags);
			break;
		case InstrOpKind::MemoryESDI:
			FormatMemory(output, instruction, operand, instructionOperand, Register::ES, Register::DI, Register::None, 0, 0, 0, 2, opInfo.Flags);
			break;
		case InstrOpKind::MemoryESEDI:
			FormatMemory(output, instruction, operand, instructionOperand, Register::ES, Register::EDI, Register::None, 0, 0, 0, 4, opInfo.Flags);
			break;
		case InstrOpKind::MemoryESRDI:
			FormatMemory(output, instruction, operand, instructionOperand, Register::ES, Register::RDI, Register::None, 0, 0, 0, 8, opInfo.Flags);
			break;
		case InstrOpKind::Memory:
		{
			std::int32_t displSize = instruction.GetMemoryDisplSize();
			auto baseReg = instruction.GetMemoryBase();
			auto indexReg = instruction.GetMemoryIndex();
			std::int32_t addrSize = InstructionUtils::GetAddressSizeInBytes(baseReg, indexReg, displSize, instruction.GetCodeSize());
			std::int64_t displ;
			if (addrSize == 8)
			{
				displ = static_cast<std::int64_t>(instruction.GetMemoryDisplacement64());
			}
			else
			{
				displ = instruction.GetMemoryDisplacement32();
			}
			if ((opInfo.Flags & InstrOpInfoFlags::IgnoreIndexReg) != 0)
			{
				indexReg = Register::None;
			}
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), baseReg, indexReg, instruction.GetInternalMemoryIndexScale(), displSize, displ, addrSize, opInfo.Flags);
			break;
		}
		default:
			throw InvalidOperationException();
		}
		if (operand == 0 && instruction.GetHasOpMaskOrZeroingMasking())
		{
			if (instruction.GetHasOpMask() && (opInfo.Flags & InstrOpInfoFlags::IgnoreOpMask) == 0)
			{
				output.Write("{", FormatterTextKind::Punctuation);
				FormatRegister(output, instruction, operand, instructionOperand, instruction.GetOpMask());
				output.Write("}", FormatterTextKind::Punctuation);
			}
			if (instruction.GetZeroingMasking())
			{
				FormatDecorator(output, instruction, operand, instructionOperand, str_z, DecoratorKind::ZeroingMasking);
			}
		}
		if (operand == 0 && instruction.GetHasRoundingControlOrSae())
		{
			auto rc = instruction.GetRoundingControl();
			if (rc != RoundingControl::None && FormatterUtils::CanShowRoundingControl(instruction, options))
			{
				Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
				FormatterString decStr;
				if (IcedConstants::IsMvex(instruction.GetCode()))
				{
					decStr = instruction.GetSuppressAllExceptions() ? rcSaeStrings[static_cast<std::int32_t>(rc) - 1] : rcStrings[static_cast<std::int32_t>(rc) - 1];
				}
				else
				{
					decStr = rcSaeStrings[static_cast<std::int32_t>(rc) - 1];
				}
				FormatDecorator(output, instruction, operand, instructionOperand, decStr, DecoratorKind::RoundingControl);
			}
			else if (instruction.GetSuppressAllExceptions())
			{
				FormatDecorator(output, instruction, operand, instructionOperand, str_sae, DecoratorKind::SuppressAllExceptions);
			}
		}
		if (mvexRmOperand == operand)
		{
			auto conv = instruction.GetMvexRegMemConv();
			if (conv != MvexRegMemConv::None)
			{
				auto mvex = MvexInfo(instruction.GetCode());
				if (mvex.GetConvFn() != MvexConvFn::None)
				{
					auto tbl = mvex.IsConvFn32() ? mvexRegMemConsts32 : mvexRegMemConsts64;
					auto fs = tbl[static_cast<std::int32_t>(conv)];
					if (fs.GetLength() != 0)
					{
						FormatDecorator(output, instruction, operand, instructionOperand, fs, DecoratorKind::SwizzleMemConv);
					}
				}
			}
		}
	}

	void IntelFormatter::FormatFlowControl(FormatterOutput& output, InstrOpInfoFlags flags, FormatterOperandOptions operandOptions)
	{
		if (!operandOptions.GetBranchSize())
		{
			return;
		}
		auto keywords = branchInfos[(static_cast<std::int32_t>(flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::BranchSizeInfoShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::BranchSizeInfoMask)];
		if (keywords.empty())
		{
			return;
		}
		for (auto keyword : keywords)
		{
			FormatKeyword(output, keyword);
			output.Write(" ", FormatterTextKind::Text);
		}
	}

	void IntelFormatter::FormatDecorator(FormatterOutput& output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterString text, DecoratorKind decorator)
	{
		output.Write("{", FormatterTextKind::Punctuation);
		output.WriteDecorator(instruction, operand, instructionOperand, text.Get(options.GetUppercaseDecorators() || options.GetUppercaseAll()), decorator);
		output.Write("}", FormatterTextKind::Punctuation);
	}

	std::string IntelFormatter::ToRegisterString(Register reg)
	{
		assert(static_cast<std::uint32_t>(reg) < static_cast<std::uint32_t>(allRegisters.size()));
		if (options.GetPreferST0() && reg == Registers::Register_ST)
		{
			reg = Register::ST0;
		}
		auto regStr = allRegisters[static_cast<std::int32_t>(reg)];
		return regStr.Get(options.GetUppercaseRegisters() || options.GetUppercaseAll());
	}

	void IntelFormatter::FormatRegister(FormatterOutput& output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, Register reg)
	{
		output.WriteRegister(instruction, operand, instructionOperand, ToRegisterString(reg), reg);
	}

	void IntelFormatter::FormatMemory(FormatterOutput& output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int32_t displSize, std::int64_t displ, std::int32_t addrSize, InstrOpInfoFlags flags)
	{
		assert(static_cast<std::uint32_t>(scale) < static_cast<std::uint32_t>(scaleNumbers.size()));
		assert((InstructionUtils::GetAddressSizeInBytes(baseReg, indexReg, displSize, instruction.GetCodeSize()) == addrSize));
		auto numberOptions = NumberFormattingOptions::CreateDisplacementInternal(options);
		SymbolResult symbol;
		bool useSymbol;
		auto operandOptions = FormatterOperandOptions(options.GetMemorySizeOptions());
		operandOptions.SetRipRelativeAddresses(options.GetRipRelativeAddresses());
		if (optionsProvider != nullptr)
		{
			optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
		}
		std::uint64_t absAddr;
		if (baseReg == Register::RIP)
		{
			absAddr = static_cast<std::uint64_t>(displ);
			if (options.GetRipRelativeAddresses())
			{
				displ -= static_cast<std::int64_t>(instruction.GetNextIP());
			}
			else
			{
				assert(indexReg == Register::None);
				baseReg = Register::None;
			}
			displSize = 8;
		}
		else if (baseReg == Register::EIP)
		{
			absAddr = static_cast<std::uint32_t>(displ);
			if (options.GetRipRelativeAddresses())
			{
				displ = static_cast<std::int32_t>(static_cast<std::uint32_t>(displ) - instruction.GetNextIP32());
			}
			else
			{
				assert(indexReg == Register::None);
				baseReg = Register::None;
			}
			displSize = 4;
		}
		else
		{
			absAddr = static_cast<std::uint64_t>(displ);
		}
		ISymbolResolver* symbolResolver = dynamic_cast<ISymbolResolver*>(this->symbolResolver);
		if (symbolResolver != nullptr)
		{
			useSymbol = symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, absAddr, addrSize, symbol);
		}
		else
		{
			useSymbol = false;
			symbol = Iced::Intel::SymbolResult();
		}
		bool useScale = scale != 0 || options.GetAlwaysShowScale();
		if (!useScale)
		{
			// [rsi] = base reg, [rsi*1] = index reg
			if (baseReg == Register::None)
			{
				useScale = true;
			}
		}
		if (addrSize == 2 || !FormatterUtils::ShowIndexScale(instruction, options))
		{
			useScale = false;
		}
		FormatMemorySize(output, symbol, instruction.GetMemorySize(), flags, operandOptions, useSymbol);
		auto codeSize = instruction.GetCodeSize();
		auto segOverride = instruction.GetSegmentPrefix();
		bool noTrackPrefix = segOverride == Register::DS && FormatterUtils::IsNotrackPrefixBranch(instruction.GetCode()) && !((codeSize == CodeSize::Code16 || codeSize == CodeSize::Code32) && (baseReg == Register::BP || baseReg == Register::EBP || baseReg == Register::ESP));
		if (options.GetAlwaysShowSegmentRegister() || (segOverride != Register::None && !noTrackPrefix && FormatterUtils::ShowSegmentPrefix(Register::None, instruction, options)))
		{
			FormatRegister(output, instruction, operand, instructionOperand, segReg);
			output.Write(":", FormatterTextKind::Punctuation);
		}
		output.Write("[", FormatterTextKind::Punctuation);
		if (options.GetSpaceAfterMemoryBracket())
		{
			output.Write(" ", FormatterTextKind::Text);
		}
		bool needPlus = false;
		if (baseReg != Register::None)
		{
			FormatRegister(output, instruction, operand, instructionOperand, baseReg);
			needPlus = true;
		}
		if (indexReg != Register::None)
		{
			if (needPlus)
			{
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				output.Write("+", FormatterTextKind::Operator);
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
			}
			needPlus = true;
			if (!useScale)
			{
				FormatRegister(output, instruction, operand, instructionOperand, indexReg);
			}
			else if (options.GetScaleBeforeIndex())
			{
				output.WriteNumber(instruction, operand, instructionOperand, scaleNumbers[scale], 1U << scale, NumberKind::Int32, FormatterTextKind::Number);
				if (options.GetSpaceBetweenMemoryMulOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				output.Write("*", FormatterTextKind::Operator);
				if (options.GetSpaceBetweenMemoryMulOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				FormatRegister(output, instruction, operand, instructionOperand, indexReg);
			}
			else
			{
				FormatRegister(output, instruction, operand, instructionOperand, indexReg);
				if (options.GetSpaceBetweenMemoryMulOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				output.Write("*", FormatterTextKind::Operator);
				if (options.GetSpaceBetweenMemoryMulOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				output.WriteNumber(instruction, operand, instructionOperand, scaleNumbers[scale], 1U << scale, NumberKind::Int32, FormatterTextKind::Number);
			}
		}
		if (useSymbol)
		{
			if (needPlus)
			{
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				if ((symbol.Flags & SymbolFlags::Signed) != 0)
				{
					output.Write("-", FormatterTextKind::Operator);
				}
				else
				{
					output.Write("+", FormatterTextKind::Operator);
				}
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
			}
			else if ((symbol.Flags & SymbolFlags::Signed) != 0)
			{
				output.Write("-", FormatterTextKind::Operator);
			}
			output.Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, absAddr, symbol, options.GetShowSymbolAddress(), false, options.GetSpaceBetweenMemoryAddOperators());
		}
		else if (!needPlus || (displSize != 0 && (options.GetShowZeroDisplacements() || displ != 0)))
		{
			std::uint64_t origDispl = static_cast<std::uint64_t>(displ);
			bool isSigned;
			if (needPlus)
			{
				isSigned = numberOptions.SignedNumber;
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
				if (addrSize == 8)
				{
					if (!numberOptions.SignedNumber)
					{
						output.Write("+", FormatterTextKind::Operator);
					}
					else if (displ < 0)
					{
						displ = -displ;
						output.Write("-", FormatterTextKind::Operator);
					}
					else
					{
						output.Write("+", FormatterTextKind::Operator);
					}
					if (numberOptions.DisplacementLeadingZeros)
					{
						displSize = 4;
					}
				}
				else if (addrSize == 4)
				{
					if (!numberOptions.SignedNumber)
					{
						output.Write("+", FormatterTextKind::Operator);
					}
					else if (static_cast<std::int32_t>(displ) < 0)
					{
						displ = static_cast<std::uint32_t>(-static_cast<std::int32_t>(displ));
						output.Write("-", FormatterTextKind::Operator);
					}
					else
					{
						output.Write("+", FormatterTextKind::Operator);
					}
					if (numberOptions.DisplacementLeadingZeros)
					{
						displSize = 4;
					}
				}
				else
				{
					assert(addrSize == 2);
					if (!numberOptions.SignedNumber)
					{
						output.Write("+", FormatterTextKind::Operator);
					}
					else if (static_cast<std::int16_t>(displ) < 0)
					{
						displ = static_cast<std::uint16_t>(-static_cast<std::int16_t>(displ));
						output.Write("-", FormatterTextKind::Operator);
					}
					else
					{
						output.Write("+", FormatterTextKind::Operator);
					}
					if (numberOptions.DisplacementLeadingZeros)
					{
						displSize = 2;
					}
				}
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output.Write(" ", FormatterTextKind::Text);
				}
			}
			else
			{
				isSigned = false;
			}
			NumberKind displKind;
			std::string s;
			if (displSize <= 1 && static_cast<std::uint64_t>(displ) <= std::numeric_limits<std::uint8_t>::max())
			{
				s = numberFormatter.FormatDisplUInt8(options, numberOptions, static_cast<std::uint8_t>(displ));
				displKind = isSigned ? NumberKind::Int8 : NumberKind::UInt8;
			}
			else if (displSize <= 2 && static_cast<std::uint64_t>(displ) <= std::numeric_limits<std::uint16_t>::max())
			{
				s = numberFormatter.FormatDisplUInt16(options, numberOptions, static_cast<std::uint16_t>(displ));
				displKind = isSigned ? NumberKind::Int16 : NumberKind::UInt16;
			}
			else if (displSize <= 4 && static_cast<std::uint64_t>(displ) <= std::numeric_limits<std::uint32_t>::max())
			{
				s = numberFormatter.FormatDisplUInt32(options, numberOptions, static_cast<std::uint32_t>(displ));
				displKind = isSigned ? NumberKind::Int32 : NumberKind::UInt32;
			}
			else if (displSize <= 8)
			{
				s = numberFormatter.FormatDisplUInt64(options, numberOptions, static_cast<std::uint64_t>(displ));
				displKind = isSigned ? NumberKind::Int64 : NumberKind::UInt64;
			}
			else
			{
				throw InvalidOperationException();
			}
			output.WriteNumber(instruction, operand, instructionOperand, s, origDispl, displKind, FormatterTextKind::Number);
		}
		if (options.GetSpaceAfterMemoryBracket())
		{
			output.Write(" ", FormatterTextKind::Text);
		}
		output.Write("]", FormatterTextKind::Punctuation);
		auto memSize = instruction.GetMemorySize();
		assert(static_cast<std::uint32_t>(memSize) < static_cast<std::uint32_t>(allMemorySizes.size()));
		auto bcstTo = allMemorySizes[static_cast<std::int32_t>(memSize)].bcstTo;
		if (bcstTo.GetLength() != 0)
		{
			FormatDecorator(output, instruction, operand, instructionOperand, bcstTo, DecoratorKind::Broadcast);
		}
		if (instruction.IsMvexEvictionHint())
		{
			FormatDecorator(output, instruction, operand, instructionOperand, str_eh, DecoratorKind::EvictionHint);
		}
	}

	void IntelFormatter::FormatMemorySize(FormatterOutput& output, SymbolResult& symbol, MemorySize memSize, InstrOpInfoFlags flags, FormatterOperandOptions operandOptions, bool useSymbol)
	{
		auto memSizeOptions = operandOptions.GetMemorySizeOptions();
		if (memSizeOptions == MemorySizeOptions::Never)
		{
			return;
		}
		if ((flags & InstrOpInfoFlags::MemSize_Nothing) != 0)
		{
			return;
		}
		assert(static_cast<std::uint32_t>(memSize) < static_cast<std::uint32_t>(allMemorySizes.size()));
		auto memInfo = allMemorySizes[static_cast<std::int32_t>(memSize)];
		if (memSizeOptions == MemorySizeOptions::Default)
		{
			if (useSymbol && symbol.GetHasSymbolSize())
			{
				if (IsSameMemSize(memInfo.keywords, symbol))
				{
					return;
				}
			}
			else if ((flags & InstrOpInfoFlags::ShowNoMemSize_ForceSize) == 0)
			{
				return;
			}
		}
		else if (memSizeOptions == MemorySizeOptions::Minimal)
		{
			if (useSymbol && symbol.GetHasSymbolSize())
			{
				if (IsSameMemSize(memInfo.keywords, symbol))
				{
					return;
				}
			}
			if ((flags & InstrOpInfoFlags::ShowMinMemSize_ForceSize) == 0)
			{
				return;
			}
		}
		else
		{
			assert(memSizeOptions == MemorySizeOptions::Always);
		}
		for (auto keyword : memInfo.keywords)
		{
			FormatKeyword(output, keyword);
			output.Write(" ", FormatterTextKind::Text);
		}
	}

	bool IntelFormatter::IsSameMemSize(const std::vector<FormatterString>& memSizeStrings, SymbolResult& symbol)
	{
		assert(static_cast<std::uint32_t>(symbol.SymbolSize) < static_cast<std::uint32_t>(allMemorySizes.size()));
		auto symbolMemInfo = allMemorySizes[static_cast<std::int32_t>(symbol.SymbolSize)];
		auto symbolMemSizeStrings = symbolMemInfo.keywords;
		return IsSameMemSize(memSizeStrings, symbolMemSizeStrings);
	}

	bool IntelFormatter::IsSameMemSize(const std::vector<FormatterString>& a, const std::vector<FormatterString>& b)
	{
		if (&a == &b)
		{
			return true;
		}
		if (a.size() != b.size())
		{
			return false;
		}
		for (std::int32_t i = 0; i < a.size(); i++)
		{
			if (a[i].Get(false) != b[i].Get(false))
			{
				return false;
			}
		}
		return true;
	}

	void IntelFormatter::FormatKeyword(FormatterOutput& output, FormatterString keyword)
	{
		output.Write(keyword.Get(options.GetUppercaseKeywords() || options.GetUppercaseAll()), FormatterTextKind::Keyword);
	}

	std::string IntelFormatter::Format(Register register_)
	{
		return ToRegisterString(register_);
	}

	std::string IntelFormatter::FormatInt8(std::int8_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatInt8(options, numberOptions, value);
	}

	std::string IntelFormatter::FormatInt16(std::int16_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatInt16(options, numberOptions, value);
	}

	std::string IntelFormatter::FormatInt32(std::int32_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatInt32(options, numberOptions, value);
	}

	std::string IntelFormatter::FormatInt64(std::int64_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatInt64(options, numberOptions, value);
	}

	std::string IntelFormatter::FormatUInt8(std::uint8_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatUInt8(options, numberOptions, value);
	}

	std::string IntelFormatter::FormatUInt16(std::uint16_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatUInt16(options, numberOptions, value);
	}

	std::string IntelFormatter::FormatUInt32(std::uint32_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatUInt32(options, numberOptions, value);
	}

	std::string IntelFormatter::FormatUInt64(std::uint64_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatUInt64(options, numberOptions, value);
	}
}
