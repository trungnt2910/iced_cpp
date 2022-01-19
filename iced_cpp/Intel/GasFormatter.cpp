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

#include "GasFormatter.h"
#include "GasFormatterInternal/Registers.h"
#include "GasFormatterInternal/Iced.Intel.GasFormatterInternal.InstrInfos.h"
#include "GasFormatterInternal/MemorySizes.h"
#include "ThrowHelper.h"
#include "FormatterTextKind.g.h"
#include "FormatterInternal/Iced.Intel.FormatterInternal.FormatterUtils.h"
#include "GasFormatterInternal/InstrOpInfoFlags.g.h"
#include "GasFormatterInternal/SizeOverride.g.h"
#include "CodeSize.g.h"
#include "FormatterInternal/MnemonicCC.h"
#include "Code.g.h"
#include "Iced.Intel.IcedConstants.h"
#include "OpKind.g.h"
#include "FormatterInternal/FormatterUtils.h"
#include "InstructionUtils.h"
#include "MvexRegMemConv.g.h"
#include "MvexInfo.h"
#include "MvexConvFn.g.h"

using namespace Iced::Intel::FormatterInternal;
using namespace Iced::Intel::GasFormatterInternal;

namespace Iced::Intel
{

	FormatterOptions* GasFormatter::GetOptions() const
	{
		return options;
	}

	const std::string GasFormatter::ImmediateValuePrefix = "$";

	GasFormatter::GasFormatter() : GasFormatter(nullptr, nullptr, nullptr)
	{
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public GasFormatter(ISymbolResolver? symbolResolver, System.Nullable<IFormatterOptionsProvider> optionsProvider = null) : this(null, symbolResolver, optionsProvider)
	GasFormatter::GasFormatter(ISymbolResolver* symbolResolver, IFormatterOptionsProvider* optionsProvider) : GasFormatter(nullptr, symbolResolver, optionsProvider)
	{
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public GasFormatter(FormatterOptions? options, System.Nullable<ISymbolResolver> symbolResolver = null, System.Nullable<IFormatterOptionsProvider> optionsProvider = null)
	GasFormatter::GasFormatter(FormatterOptions* options, ISymbolResolver* symbolResolver, IFormatterOptionsProvider* optionsProvider) : numberFormatter(true)
	{
		this->options = (options != nullptr) ? options : FormatterOptions::CreateGas();
		this->symbolResolver = symbolResolver;
		this->optionsProvider = optionsProvider;
		allRegisters = Registers::AllRegisters;
		allRegistersNaked = Registers::AllRegistersNaked;
		instrInfos = InstrInfos::AllInfos;
		allMemorySizes = MemorySizes::AllMemorySizes;
		opSizeStrings = s_opSizeStrings;
		addrSizeStrings = s_addrSizeStrings;
		scaleNumbers = s_scaleNumbers;
		mvexRegMemConsts32 = s_mvexRegMemConsts32;
		mvexRegMemConsts64 = s_mvexRegMemConsts64;
	}

	FormatterString GasFormatter::str_bnd = FormatterString("bnd");
	FormatterString GasFormatter::str_dot_byte = FormatterString(".byte");
	FormatterString GasFormatter::str_lock = FormatterString("lock");
	FormatterString GasFormatter::str_notrack = FormatterString("notrack");
	FormatterString GasFormatter::str_pn = FormatterString("pn");
	FormatterString GasFormatter::str_pt = FormatterString("pt");
	FormatterString GasFormatter::str_rep = FormatterString("rep");
	std::vector<FormatterString> GasFormatter::str_repe = { FormatterString("repe"), FormatterString("repz") };
	std::vector<FormatterString> GasFormatter::str_repne = { FormatterString("repne"), FormatterString("repnz") };
	FormatterString GasFormatter::str_rex_w = FormatterString("rex.w");
	FormatterString GasFormatter::str_rn_sae = FormatterString("rn-sae");
	FormatterString GasFormatter::str_rd_sae = FormatterString("rd-sae");
	FormatterString GasFormatter::str_ru_sae = FormatterString("ru-sae");
	FormatterString GasFormatter::str_rz_sae = FormatterString("rz-sae");
	FormatterString GasFormatter::str_sae = FormatterString("sae");
	FormatterString GasFormatter::str_rn = FormatterString("rn");
	FormatterString GasFormatter::str_rd = FormatterString("rd");
	FormatterString GasFormatter::str_ru = FormatterString("ru");
	FormatterString GasFormatter::str_rz = FormatterString("rz");
	FormatterString GasFormatter::str_xacquire = FormatterString("xacquire");
	FormatterString GasFormatter::str_xrelease = FormatterString("xrelease");
	FormatterString GasFormatter::str_z = FormatterString("z");
	std::vector<FormatterString> GasFormatter::s_opSizeStrings = { FormatterString(""), FormatterString("data16"), FormatterString("data32"), FormatterString("rex.w") };
	std::vector<FormatterString> GasFormatter::s_addrSizeStrings = { FormatterString(""), FormatterString("addr16"), FormatterString("addr32"), FormatterString("addr64") };
	std::vector<std::string> GasFormatter::s_scaleNumbers = { "1", "2", "4", "8" };
	std::vector<FormatterString> GasFormatter::s_mvexRegMemConsts32 = { FormatterString(""), FormatterString(""), FormatterString("cdab"), FormatterString("badc"), FormatterString("dacb"), FormatterString("aaaa"), FormatterString("bbbb"), FormatterString("cccc"), FormatterString("dddd"), FormatterString(""), FormatterString("1to16"), FormatterString("4to16"), FormatterString("float16"), FormatterString("uint8"), FormatterString("sint8"), FormatterString("uint16"), FormatterString("sint16") };
	std::vector<FormatterString> GasFormatter::s_mvexRegMemConsts64 = { FormatterString(""), FormatterString(""), FormatterString("cdab"), FormatterString("badc"), FormatterString("dacb"), FormatterString("aaaa"), FormatterString("bbbb"), FormatterString("cccc"), FormatterString("dddd"), FormatterString(""), FormatterString("1to8"), FormatterString("4to8"), FormatterString("float16"), FormatterString("uint8"), FormatterString("sint8"), FormatterString("uint16"), FormatterString("sint16") };
	FormatterString GasFormatter::str_eh = FormatterString("eh");

	void GasFormatter::FormatMnemonic(const Instruction& instruction, FormatterOutput* output, FormatMnemonicOptions options)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(this->options, instruction, opInfo);
		std::int32_t column = 0;
		FormatMnemonic(instruction, output, opInfo, column, options);
	}

	std::int32_t GasFormatter::GetOperandCount(const Instruction& instruction)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		return opInfo.OpCount;
	}

	bool GasFormatter::TryGetOpAccess(const Instruction& instruction, std::int32_t operand, OpAccess& access)
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

	std::int32_t GasFormatter::GetInstructionOperand(const Instruction& instruction, std::int32_t operand)
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

	std::int32_t GasFormatter::GetFormatterOperand(const Instruction& instruction, std::int32_t instructionOperand)
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

	void GasFormatter::FormatOperand(const Instruction& instruction, FormatterOutput* output, std::int32_t operand)
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

	void GasFormatter::FormatOperandSeparator(const Instruction& instruction, FormatterOutput* output)
	{
		if (output == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_output();
		}
		output->Write(",", FormatterTextKind::Punctuation);
		if (options->GetSpaceAfterOperandSeparator())
		{
			output->Write(" ", FormatterTextKind::Text);
		}
	}

	void GasFormatter::FormatAllOperands(const Instruction& instruction, FormatterOutput* output)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		FormatOperands(instruction, output, opInfo);
	}

	void GasFormatter::Format(const Instruction& instruction, FormatterOutput* output)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		std::int32_t column = 0;
		FormatMnemonic(instruction, output, opInfo, column, FormatMnemonicOptions::None);
		if (opInfo.OpCount != 0)
		{
			FormatterUtils::AddTabs(output, column, options->GetFirstOperandCharIndex(), options->GetTabSize());
			FormatOperands(instruction, output, opInfo);
		}
	}

	void GasFormatter::FormatMnemonic(const Instruction& instruction, FormatterOutput* output, InstrOpInfo const opInfo, std::int32_t& column, FormatMnemonicOptions mnemonicOptions)
	{
		if (output == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_output();
		}
		bool needSpace = false;
		if ((mnemonicOptions & FormatMnemonicOptions::NoPrefixes) == 0 && (opInfo.Flags & InstrOpInfoFlags::MnemonicIsDirective) == 0)
		{
			auto prefixSeg = instruction.GetSegmentPrefix();
			constexpr std::uint32_t PrefixFlags = (static_cast<std::uint32_t>(InstrOpInfoFlags::SizeOverrideMask) << static_cast<std::int32_t>(InstrOpInfoFlags::OpSizeShift)) | (static_cast<std::uint32_t>(InstrOpInfoFlags::SizeOverrideMask) << static_cast<std::int32_t>(InstrOpInfoFlags::AddrSizeShift)) | static_cast<std::uint32_t>(InstrOpInfoFlags::BndPrefix);
			if ((static_cast<std::uint32_t>(prefixSeg) | instruction.GetHasAnyOfLockRepRepnePrefix() | (static_cast<std::uint32_t>((uint)opInfo.Flags & PrefixFlags))) != 0)
			{
				FormatterString prefix;
				if ((opInfo.Flags & InstrOpInfoFlags::OpSizeIsByteDirective) != 0)
				{
					switch (static_cast<SizeOverride>((static_cast<std::int32_t>(opInfo.Flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::OpSizeShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::SizeOverrideMask)))
					{
					case SizeOverride::None:
						break;
					case SizeOverride::Size16:
					case SizeOverride::Size32:
					{
						output->Write(str_dot_byte.Get(options->GetUppercaseKeywords() || options->GetUppercaseAll()), FormatterTextKind::Directive);
						output->Write(" ", FormatterTextKind::Text);
						auto numberOptions = NumberFormattingOptions::CreateImmediateInternal(options);
						auto s = numberFormatter.FormatUInt8(options, numberOptions, 0x66);
						output->Write(s, FormatterTextKind::Number);
						output->Write(";", FormatterTextKind::Punctuation);
						output->Write(" ", FormatterTextKind::Text);
						column += str_dot_byte.GetLength() + 1 + (std::int32_t)s.length() + 1 + 1;
						break;
					}
					case SizeOverride::Size64:
						FormatPrefix(output, instruction, column, str_rex_w, PrefixKind::OperandSize, needSpace);
						break;
					default:
						throw InvalidOperationException();
					}
				}
				else
				{
					prefix = opSizeStrings[(static_cast<std::int32_t>(opInfo.Flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::OpSizeShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::SizeOverrideMask)];
					if (prefix.GetLength() != 0)
					{
						FormatPrefix(output, instruction, column, prefix, PrefixKind::OperandSize, needSpace);
					}
				}
				prefix = addrSizeStrings[(static_cast<std::int32_t>(opInfo.Flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::AddrSizeShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::SizeOverrideMask)];
				if (prefix.GetLength() != 0)
				{
					FormatPrefix(output, instruction, column, prefix, PrefixKind::AddressSize, needSpace);
				}
				bool hasNoTrackPrefix = prefixSeg == Register::DS && FormatterUtils::IsNotrackPrefixBranch(instruction.GetCode());
				if (!hasNoTrackPrefix && prefixSeg != Register::None && ShowSegmentPrefix(instruction, opInfo))
				{
					FormatPrefix(output, instruction, column, allRegistersNaked[static_cast<std::int32_t>(prefixSeg)], FormatterUtils::GetSegmentRegisterPrefixKind(prefixSeg), needSpace);
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
				if (hasNoTrackPrefix)
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
				output->Write(" ", FormatterTextKind::Text);
				column++;
			}
			auto mnemonic = opInfo.Mnemonic;
			if ((opInfo.Flags & InstrOpInfoFlags::MnemonicIsDirective) != 0)
			{
				output->Write(mnemonic.Get(options->GetUppercaseKeywords() || options->GetUppercaseAll()), FormatterTextKind::Directive);
			}
			else
			{
				output->WriteMnemonic(instruction, mnemonic.Get(options->GetUppercaseMnemonics() || options->GetUppercaseAll()));
			}
			column += mnemonic.GetLength();
		}
		if ((mnemonicOptions & FormatMnemonicOptions::NoPrefixes) == 0)
		{
			if ((opInfo.Flags & InstrOpInfoFlags::JccNotTaken) != 0)
			{
				FormatBranchHint(output, column, str_pn);
			}
			else if ((opInfo.Flags & InstrOpInfoFlags::JccTaken) != 0)
			{
				FormatBranchHint(output, column, str_pt);
			}
		}
	}

	void GasFormatter::FormatBranchHint(FormatterOutput* output, std::int32_t& column, FormatterString brHint)
	{
		output->Write(",", FormatterTextKind::Text);
		output->Write(brHint.Get(options->GetUppercasePrefixes() || options->GetUppercaseAll()), FormatterTextKind::Keyword);
		column += 1 + brHint.GetLength();
	}

	bool GasFormatter::ShowSegmentPrefix(const Instruction& instruction, InstrOpInfo const opInfo)
	{
		if ((opInfo.Flags & (InstrOpInfoFlags::JccNotTaken | InstrOpInfoFlags::JccTaken)) != 0)
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
		case Code::Maskmovq_rDI_mm_mm:
		case Code::Maskmovdqu_rDI_xmm_xmm:
		case Code::VEX_Vmaskmovdqu_rDI_xmm_xmm:
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
			case InstrOpKind::Sae:
			case InstrOpKind::RnSae:
			case InstrOpKind::RdSae:
			case InstrOpKind::RuSae:
			case InstrOpKind::RzSae:
			case InstrOpKind::Rn:
			case InstrOpKind::Rd:
			case InstrOpKind::Ru:
			case InstrOpKind::Rz:
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
		return options->GetShowUselessPrefixes();
	}

	void GasFormatter::FormatPrefix(FormatterOutput* output, const Instruction& instruction, std::int32_t& column, FormatterString prefix, PrefixKind prefixKind, bool& needSpace)
	{
		if (needSpace)
		{
			column++;
			output->Write(" ", FormatterTextKind::Text);
		}
		output->WritePrefix(instruction, prefix.Get(options->GetUppercasePrefixes() || options->GetUppercaseAll()), prefixKind);
		column += prefix.GetLength();
		needSpace = true;
	}

	void GasFormatter::FormatOperands(const Instruction& instruction, FormatterOutput* output, InstrOpInfo const opInfo)
	{
		if (output == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_output();
		}
		for (std::int32_t i = 0; i < opInfo.OpCount; i++)
		{
			if (i > 0)
			{
				output->Write(",", FormatterTextKind::Punctuation);
				if (options->GetSpaceAfterOperandSeparator())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
			}
			FormatOperand(instruction, output, opInfo, i);
		}
	}

	void GasFormatter::FormatOperand(const Instruction& instruction, FormatterOutput* output, InstrOpInfo const opInfo, std::int32_t operand)
	{
		assert(static_cast<std::uint32_t>(operand) < static_cast<std::uint32_t>(opInfo.OpCount));
		if (output == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_output();
		}
		std::int32_t mvexRmOperand;
		if (IcedConstants::IsMvex(instruction.GetCode()))
		{
			auto opCount = instruction.GetOpCount();
			assert(opCount != 0);
			mvexRmOperand = instruction.GetOpKind(opCount - 1) == OpKind::Immediate8 && opInfo.OpCount == opCount ? 1 : 0;
		}
		else
		{
			mvexRmOperand = -1;
		}
		std::int32_t instructionOperand = opInfo.GetInstructionIndex(operand);
		if ((opInfo.Flags & InstrOpInfoFlags::IndirectOperand) != 0)
		{
			output->Write("*", FormatterTextKind::Operator);
		}
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
			operandOptions = Iced::Intel::FormatterOperandOptions();
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, imm64, immSize, symbol))
			{
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options->GetShowSymbolAddress());
			}
			else
			{
				flowControl = FormatterUtils::GetFlowControl(instruction);
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
				output->WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterUtils::IsCall(flowControl) ? FormatterTextKind::FunctionAddress : FormatterTextKind::LabelAddress);
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
			operandOptions = Iced::Intel::FormatterOperandOptions();
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, static_cast<std::uint32_t>(imm64), immSize, symbol))
			{
				output->Write(ImmediateValuePrefix, FormatterTextKind::Operator);
				assert(operand + 1 == 1);
				SymbolResult selectorSymbol;
				if (!symbolResolver->TryGetSymbol(instruction, operand + 1, instructionOperand, instruction.GetFarBranchSelector(), 2, selectorSymbol))
				{
					s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranchSelector(), numberOptions.LeadingZeros);
					output->WriteNumber(instruction, operand, instructionOperand, s, instruction.GetFarBranchSelector(), NumberKind::UInt16, FormatterTextKind::SelectorValue);
				}
				else
				{
					output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, instruction.GetFarBranchSelector(), selectorSymbol, options->GetShowSymbolAddress());
				}
				output->Write(",", FormatterTextKind::Punctuation);
				if (options->GetSpaceAfterOperandSeparator())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
				output->Write(ImmediateValuePrefix, FormatterTextKind::Operator);
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options->GetShowSymbolAddress());
			}
			else
			{
				flowControl = FormatterUtils::GetFlowControl(instruction);
				s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranchSelector(), numberOptions.LeadingZeros);
				output->Write(ImmediateValuePrefix, FormatterTextKind::Operator);
				output->WriteNumber(instruction, operand, instructionOperand, s, instruction.GetFarBranchSelector(), NumberKind::UInt16, FormatterTextKind::SelectorValue);
				output->Write(",", FormatterTextKind::Punctuation);
				if (options->GetSpaceAfterOperandSeparator())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
				if (opKind == InstrOpKind::FarBranch32)
				{
					s = numberFormatter.FormatUInt32(options, numberOptions, instruction.GetFarBranch32(), numberOptions.LeadingZeros);
				}
				else
				{
					s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranch16(), numberOptions.LeadingZeros);
				}
				output->Write(ImmediateValuePrefix, FormatterTextKind::Operator);
				output->WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterUtils::IsCall(flowControl) ? FormatterTextKind::FunctionAddress : FormatterTextKind::LabelAddress);
			}
			break;
		case InstrOpKind::Immediate8:
		case InstrOpKind::Immediate8_2nd:
		case InstrOpKind::DeclareByte:
			if (opKind != InstrOpKind::DeclareByte)
			{
				output->Write(ImmediateValuePrefix, FormatterTextKind::Operator);
			}
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm8, symbol, options->GetShowSymbolAddress());
			}
			else
			{
				if (numberOptions.SignedNumber)
				{
					imm64 = static_cast<std::uint64_t>(static_cast<std::int8_t>(imm8));
					numberKind = NumberKind::Int8;
					if (static_cast<std::int8_t>(imm8) < 0)
					{
						output->Write("-", FormatterTextKind::Operator);
						imm8 = static_cast<std::uint8_t>(-static_cast<std::int8_t>(imm8));
					}
				}
				else
				{
					imm64 = imm8;
					numberKind = NumberKind::UInt8;
				}
				s = numberFormatter.FormatUInt8(options, numberOptions, imm8);
				output->WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterTextKind::Number);
			}
			break;
		case InstrOpKind::Immediate16:
		case InstrOpKind::Immediate8to16:
		case InstrOpKind::DeclareWord:
			if (opKind != InstrOpKind::DeclareWord)
			{
				output->Write(ImmediateValuePrefix, FormatterTextKind::Operator);
			}
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm16, symbol, options->GetShowSymbolAddress());
			}
			else
			{
				if (numberOptions.SignedNumber)
				{
					imm64 = static_cast<std::uint64_t>(static_cast<std::int16_t>(imm16));
					numberKind = NumberKind::Int16;
					if (static_cast<std::int16_t>(imm16) < 0)
					{
						output->Write("-", FormatterTextKind::Operator);
						imm16 = static_cast<std::uint16_t>(-static_cast<std::int16_t>(imm16));
					}
				}
				else
				{
					imm64 = imm16;
					numberKind = NumberKind::UInt16;
				}
				s = numberFormatter.FormatUInt16(options, numberOptions, imm16);
				output->WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterTextKind::Number);
			}
			break;
		case InstrOpKind::Immediate32:
		case InstrOpKind::Immediate8to32:
		case InstrOpKind::DeclareDword:
			if (opKind != InstrOpKind::DeclareDword)
			{
				output->Write(ImmediateValuePrefix, FormatterTextKind::Operator);
			}
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm32, symbol, options->GetShowSymbolAddress());
			}
			else
			{
				if (numberOptions.SignedNumber)
				{
					imm64 = static_cast<std::uint64_t>(static_cast<std::int32_t>(imm32));
					numberKind = NumberKind::Int32;
					if (static_cast<std::int32_t>(imm32) < 0)
					{
						output->Write("-", FormatterTextKind::Operator);
						imm32 = static_cast<std::uint32_t>(-static_cast<std::int32_t>(imm32));
					}
				}
				else
				{
					imm64 = imm32;
					numberKind = NumberKind::UInt32;
				}
				s = numberFormatter.FormatUInt32(options, numberOptions, imm32);
				output->WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterTextKind::Number);
			}
			break;
		case InstrOpKind::Immediate64:
		case InstrOpKind::Immediate8to64:
		case InstrOpKind::Immediate32to64:
		case InstrOpKind::DeclareQword:
			if (opKind != InstrOpKind::DeclareQword)
			{
				output->Write(ImmediateValuePrefix, FormatterTextKind::Operator);
			}
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options->GetShowSymbolAddress());
			}
			else
			{
				value64 = imm64;
				if (numberOptions.SignedNumber)
				{
					numberKind = NumberKind::Int64;
					if (static_cast<std::int64_t>(imm64) < 0)
					{
						output->Write("-", FormatterTextKind::Operator);
						imm64 = static_cast<std::uint64_t>(-static_cast<std::int64_t>(imm64));
					}
				}
				else
				{
					numberKind = NumberKind::UInt64;
				}
				s = numberFormatter.FormatUInt64(options, numberOptions, imm64);
				output->WriteNumber(instruction, operand, instructionOperand, s, value64, numberKind, FormatterTextKind::Number);
			}
			break;
		case InstrOpKind::MemorySegSI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::SI, Register::None, 0, 0, 0, 2);
			break;
		case InstrOpKind::MemorySegESI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::ESI, Register::None, 0, 0, 0, 4);
			break;
		case InstrOpKind::MemorySegRSI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::RSI, Register::None, 0, 0, 0, 8);
			break;
		case InstrOpKind::MemorySegDI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::DI, Register::None, 0, 0, 0, 2);
			break;
		case InstrOpKind::MemorySegEDI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::EDI, Register::None, 0, 0, 0, 4);
			break;
		case InstrOpKind::MemorySegRDI:
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), Register::RDI, Register::None, 0, 0, 0, 8);
			break;
		case InstrOpKind::MemoryESDI:
			FormatMemory(output, instruction, operand, instructionOperand, Register::ES, Register::DI, Register::None, 0, 0, 0, 2);
			break;
		case InstrOpKind::MemoryESEDI:
			FormatMemory(output, instruction, operand, instructionOperand, Register::ES, Register::EDI, Register::None, 0, 0, 0, 4);
			break;
		case InstrOpKind::MemoryESRDI:
			FormatMemory(output, instruction, operand, instructionOperand, Register::ES, Register::RDI, Register::None, 0, 0, 0, 8);
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
			FormatMemory(output, instruction, operand, instructionOperand, instruction.GetMemorySegment(), baseReg, indexReg, instruction.GetInternalMemoryIndexScale(), displSize, displ, addrSize);
			break;
		}
		case InstrOpKind::Sae:
			FormatDecorator(output, instruction, operand, instructionOperand, str_sae, DecoratorKind::SuppressAllExceptions);
			break;
		case InstrOpKind::RnSae:
			FormatDecorator(output, instruction, operand, instructionOperand, str_rn_sae, DecoratorKind::RoundingControl);
			break;
		case InstrOpKind::RdSae:
			FormatDecorator(output, instruction, operand, instructionOperand, str_rd_sae, DecoratorKind::RoundingControl);
			break;
		case InstrOpKind::RuSae:
			FormatDecorator(output, instruction, operand, instructionOperand, str_ru_sae, DecoratorKind::RoundingControl);
			break;
		case InstrOpKind::RzSae:
			FormatDecorator(output, instruction, operand, instructionOperand, str_rz_sae, DecoratorKind::RoundingControl);
			break;
		case InstrOpKind::Rn:
			FormatDecorator(output, instruction, operand, instructionOperand, str_rn, DecoratorKind::RoundingControl);
			break;
		case InstrOpKind::Rd:
			FormatDecorator(output, instruction, operand, instructionOperand, str_rd, DecoratorKind::RoundingControl);
			break;
		case InstrOpKind::Ru:
			FormatDecorator(output, instruction, operand, instructionOperand, str_ru, DecoratorKind::RoundingControl);
			break;
		case InstrOpKind::Rz:
			FormatDecorator(output, instruction, operand, instructionOperand, str_rz, DecoratorKind::RoundingControl);
			break;
		default:
			throw InvalidOperationException();
		}
		if (operand + 1 == opInfo.OpCount && instruction.GetHasOpMaskOrZeroingMasking())
		{
			if (instruction.GetHasOpMask())
			{
				output->Write("{", FormatterTextKind::Punctuation);
				FormatRegister(output, instruction, operand, instructionOperand, instruction.GetOpMask());
				output->Write("}", FormatterTextKind::Punctuation);
			}
			if (instruction.GetZeroingMasking())
			{
				FormatDecorator(output, instruction, operand, instructionOperand, str_z, DecoratorKind::ZeroingMasking);
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

	void GasFormatter::FormatDecorator(FormatterOutput* output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterString text, DecoratorKind decorator)
	{
		output->Write("{", FormatterTextKind::Punctuation);
		output->WriteDecorator(instruction, operand, instructionOperand, text.Get(options->GetUppercaseDecorators() || options->GetUppercaseAll()), decorator);
		output->Write("}", FormatterTextKind::Punctuation);
	}

	std::string GasFormatter::ToRegisterString(Register reg)
	{
		assert(static_cast<std::uint32_t>(reg) < static_cast<std::uint32_t>(Registers::AllRegisters.size()));
		if (options->GetPreferST0() && reg == Registers::Register_ST)
		{
			reg = Register::ST0;
		}
		auto regStr = Registers::AllRegisters[static_cast<std::int32_t>(reg)];
		return regStr.Get(options->GetUppercaseRegisters() || options->GetUppercaseAll());
	}

	void GasFormatter::FormatRegister(FormatterOutput* output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, Register reg)
	{
		output->WriteRegister(instruction, operand, instructionOperand, ToRegisterString(reg), reg);
	}

	void GasFormatter::FormatMemory(FormatterOutput* output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int32_t displSize, std::int64_t displ, std::int32_t addrSize)
	{
		assert(static_cast<std::uint32_t>(scale) < static_cast<std::uint32_t>(scaleNumbers.size()));
		assert((InstructionUtils::GetAddressSizeInBytes(baseReg, indexReg, displSize, instruction.GetCodeSize()) == addrSize));
		auto numberOptions = NumberFormattingOptions::CreateDisplacementInternal(options);
		SymbolResult symbol;
		bool useSymbol;
		auto operandOptions = FormatterOperandOptions(options->GetMemorySizeOptions());
		operandOptions.SetRipRelativeAddresses(options->GetRipRelativeAddresses());
		if (optionsProvider != nullptr)
		{
			optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
		}
		std::uint64_t absAddr;
		if (baseReg == Register::RIP)
		{
			absAddr = static_cast<std::uint64_t>(displ);
			if (options->GetRipRelativeAddresses())
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
			if (options->GetRipRelativeAddresses())
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
		bool useScale = scale != 0 || options->GetAlwaysShowScale();
		if (addrSize == 2 || !FormatterUtils::ShowIndexScale(instruction, options))
		{
			useScale = false;
		}
		bool hasBaseOrIndexReg = baseReg != Register::None || indexReg != Register::None;
		auto codeSize = instruction.GetCodeSize();
		auto segOverride = instruction.GetSegmentPrefix();
		bool noTrackPrefix = segOverride == Register::DS && FormatterUtils::IsNotrackPrefixBranch(instruction.GetCode()) && !((codeSize == CodeSize::Code16 || codeSize == CodeSize::Code32) && (baseReg == Register::BP || baseReg == Register::EBP || baseReg == Register::ESP));
		if (options->GetAlwaysShowSegmentRegister() || (segOverride != Register::None && !noTrackPrefix && FormatterUtils::ShowSegmentPrefix(Register::None, instruction, options)))
		{
			FormatRegister(output, instruction, operand, instructionOperand, segReg);
			output->Write(":", FormatterTextKind::Punctuation);
		}
		if (useSymbol)
		{
			output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, absAddr, symbol, options->GetShowSymbolAddress());
		}
		else if (!hasBaseOrIndexReg || (displSize != 0 && (options->GetShowZeroDisplacements() || displ != 0)))
		{
			std::uint64_t origDispl = static_cast<std::uint64_t>(displ);
			bool isSigned;
			if (hasBaseOrIndexReg)
			{
				isSigned = numberOptions.SignedNumber;
				if (addrSize == 8)
				{
					if (numberOptions.SignedNumber && displ < 0)
					{
						output->Write("-", FormatterTextKind::Operator);
						displ = -displ;
					}
					if (numberOptions.DisplacementLeadingZeros)
					{
						displSize = 4;
					}
				}
				else if (addrSize == 4)
				{
					if (numberOptions.SignedNumber && static_cast<std::int32_t>(displ) < 0)
					{
						output->Write("-", FormatterTextKind::Operator);
						displ = static_cast<std::uint32_t>(-static_cast<std::int32_t>(displ));
					}
					if (numberOptions.DisplacementLeadingZeros)
					{
						displSize = 4;
					}
				}
				else
				{
					assert(addrSize == 2);
					if (numberOptions.SignedNumber && static_cast<std::int16_t>(displ) < 0)
					{
						output->Write("-", FormatterTextKind::Operator);
						displ = static_cast<std::uint16_t>(-static_cast<std::int16_t>(displ));
					}
					if (numberOptions.DisplacementLeadingZeros)
					{
						displSize = 2;
					}
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
			output->WriteNumber(instruction, operand, instructionOperand, s, origDispl, displKind, FormatterTextKind::Number);
		}
		if (hasBaseOrIndexReg)
		{
			output->Write("(", FormatterTextKind::Punctuation);
			if (options->GetSpaceAfterMemoryBracket())
			{
				output->Write(" ", FormatterTextKind::Text);
			}
			if (baseReg != Register::None && indexReg == Register::None && !useScale)
			{
				FormatRegister(output, instruction, operand, instructionOperand, baseReg);
			}
			else
			{
				if (baseReg != Register::None)
				{
					FormatRegister(output, instruction, operand, instructionOperand, baseReg);
				}
				output->Write(",", FormatterTextKind::Punctuation);
				if (options->GetGasSpaceAfterMemoryOperandComma())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
				if (indexReg != Register::None)
				{
					FormatRegister(output, instruction, operand, instructionOperand, indexReg);
					if (useScale)
					{
						output->Write(",", FormatterTextKind::Punctuation);
						if (options->GetGasSpaceAfterMemoryOperandComma())
						{
							output->Write(" ", FormatterTextKind::Text);
						}
						output->WriteNumber(instruction, operand, instructionOperand, scaleNumbers[scale], 1U << scale, NumberKind::Int32, FormatterTextKind::Number);
					}
				}
			}
			if (options->GetSpaceAfterMemoryBracket())
			{
				output->Write(" ", FormatterTextKind::Text);
			}
			output->Write(")", FormatterTextKind::Punctuation);
		}
		auto memSize = instruction.GetMemorySize();
		assert(static_cast<std::uint32_t>(memSize) < static_cast<std::uint32_t>(allMemorySizes.size()));
		auto bcstTo = allMemorySizes[static_cast<std::int32_t>(memSize)];
		if (bcstTo.GetLength() != 0)
		{
			FormatDecorator(output, instruction, operand, instructionOperand, bcstTo, DecoratorKind::Broadcast);
		}
		if (instruction.IsMvexEvictionHint())
		{
			FormatDecorator(output, instruction, operand, instructionOperand, str_eh, DecoratorKind::EvictionHint);
		}
	}

	std::string GasFormatter::Format(Register register_)
	{
		return ToRegisterString(register_);
	}

	std::string GasFormatter::FormatInt8(std::int8_t value, NumberFormattingOptions const numberOptions)
	{
		return numberFormatter.FormatInt8(options, numberOptions, value);
	}

	std::string GasFormatter::FormatInt16(std::int16_t value, NumberFormattingOptions const numberOptions)
	{
		return numberFormatter.FormatInt16(options, numberOptions, value);
	}

	std::string GasFormatter::FormatInt32(std::int32_t value, NumberFormattingOptions const numberOptions)
	{
		return numberFormatter.FormatInt32(options, numberOptions, value);
	}

	std::string GasFormatter::FormatInt64(std::int64_t value, NumberFormattingOptions const numberOptions)
	{
		return numberFormatter.FormatInt64(options, numberOptions, value);
	}

	std::string GasFormatter::FormatUInt8(std::uint8_t value, NumberFormattingOptions const numberOptions)
	{
		return numberFormatter.FormatUInt8(options, numberOptions, value);
	}

	std::string GasFormatter::FormatUInt16(std::uint16_t value, NumberFormattingOptions const numberOptions)
	{
		return numberFormatter.FormatUInt16(options, numberOptions, value);
	}

	std::string GasFormatter::FormatUInt32(std::uint32_t value, NumberFormattingOptions const numberOptions)
	{
		return numberFormatter.FormatUInt32(options, numberOptions, value);
	}

	std::string GasFormatter::FormatUInt64(std::uint64_t value, NumberFormattingOptions const numberOptions)
	{
		return numberFormatter.FormatUInt64(options, numberOptions, value);
	}
}
