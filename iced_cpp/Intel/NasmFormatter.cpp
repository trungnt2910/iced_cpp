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

#include "NasmFormatter.h"
#include "NasmFormatterInternal/Registers.h"
#include "NasmFormatterInternal/Iced.Intel.NasmFormatterInternal.InstrInfos.h"
#include "ThrowHelper.h"
#include "FormatterTextKind.g.h"
#include "FormatterInternal/Iced.Intel.FormatterInternal.FormatterUtils.h"
#include "NasmFormatterInternal/SignExtendInfo.g.h"
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
#include "MemorySizeOptions.g.h"

using namespace Iced::Intel::FormatterInternal;
using namespace Iced::Intel::NasmFormatterInternal;

namespace Iced::Intel
{

	const FormatterOptions& NasmFormatter::GetOptions() const
	{
		return options;
	}

	FormatterOptions& NasmFormatter::GetOptions()
	{
		return options;
	}

	NasmFormatter::NasmFormatter() : NasmFormatter(nullptr, nullptr)
	{
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public NasmFormatter(ISymbolResolver? symbolResolver, System.Nullable<IFormatterOptionsProvider> optionsProvider = null) : this(null, symbolResolver, optionsProvider)
	NasmFormatter::NasmFormatter(ISymbolResolver* symbolResolver, IFormatterOptionsProvider* optionsProvider) : numberFormatter(true)
	{
		this->options = FormatterOptions::CreateNasm();
		this->symbolResolver = symbolResolver;
		this->optionsProvider = optionsProvider;
		allRegisters = Registers::AllRegisters;
		instrInfos = InstrInfos::AllInfos;
		allMemorySizes = MemorySizes::AllMemorySizes;
		opSizeStrings = s_opSizeStrings;
		addrSizeStrings = s_addrSizeStrings;
		branchInfos = s_branchInfos;
		scaleNumbers = s_scaleNumbers;
		mvexRegMemConsts32 = s_mvexRegMemConsts32;
		mvexRegMemConsts64 = s_mvexRegMemConsts64;
		memSizeInfos = s_memSizeInfos;
		farMemSizeInfos = s_farMemSizeInfos;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public NasmFormatter(FormatterOptions? options, System.Nullable<ISymbolResolver> symbolResolver = null, System.Nullable<IFormatterOptionsProvider> optionsProvider = null)
	NasmFormatter::NasmFormatter(const FormatterOptions& options, ISymbolResolver* symbolResolver, IFormatterOptionsProvider* optionsProvider) : NasmFormatter(symbolResolver, optionsProvider)
	{
		this->options = options;
	}

	FormatterString NasmFormatter::str_bnd = FormatterString("bnd");
	FormatterString NasmFormatter::str_byte = FormatterString("byte");
	FormatterString NasmFormatter::str_dword = FormatterString("dword");
	FormatterString NasmFormatter::str_lock = FormatterString("lock");
	FormatterString NasmFormatter::str_notrack = FormatterString("notrack");
	FormatterString NasmFormatter::str_qword = FormatterString("qword");
	FormatterString NasmFormatter::str_rel = FormatterString("rel");
	FormatterString NasmFormatter::str_rep = FormatterString("rep");
	std::vector<FormatterString> NasmFormatter::str_repe = { FormatterString("repe"), FormatterString("repz") };
	std::vector<FormatterString> NasmFormatter::str_repne = { FormatterString("repne"), FormatterString("repnz") };
	FormatterString NasmFormatter::str_rn_sae = FormatterString("rn-sae");
	FormatterString NasmFormatter::str_rd_sae = FormatterString("rd-sae");
	FormatterString NasmFormatter::str_ru_sae = FormatterString("ru-sae");
	FormatterString NasmFormatter::str_rz_sae = FormatterString("rz-sae");
	FormatterString NasmFormatter::str_sae = FormatterString("sae");
	FormatterString NasmFormatter::str_rn = FormatterString("rn");
	FormatterString NasmFormatter::str_rd = FormatterString("rd");
	FormatterString NasmFormatter::str_ru = FormatterString("ru");
	FormatterString NasmFormatter::str_rz = FormatterString("rz");
	FormatterString NasmFormatter::str_to = FormatterString("to");
	FormatterString NasmFormatter::str_word = FormatterString("word");
	FormatterString NasmFormatter::str_xacquire = FormatterString("xacquire");
	FormatterString NasmFormatter::str_xrelease = FormatterString("xrelease");
	FormatterString NasmFormatter::str_z = FormatterString("z");
	std::vector<FormatterString> NasmFormatter::s_opSizeStrings = { FormatterString(""), FormatterString("o16"), FormatterString("o32"), FormatterString("o64") };
	std::vector<FormatterString> NasmFormatter::s_addrSizeStrings = { FormatterString(""), FormatterString("a16"), FormatterString("a32"), FormatterString("a64") };
	std::vector<std::vector<FormatterString>> NasmFormatter::s_branchInfos = { {}, std::vector<FormatterString> {FormatterString("near")}, std::vector<FormatterString> {FormatterString("near"), FormatterString("word")}, std::vector<FormatterString> {FormatterString("near"), FormatterString("dword")}, std::vector<FormatterString> {FormatterString("word")}, std::vector<FormatterString> {FormatterString("dword")}, std::vector<FormatterString> {FormatterString("short")}, {} };
	std::vector<FormatterString> NasmFormatter::s_memSizeInfos = { FormatterString(""), FormatterString("word"), FormatterString("dword"), FormatterString("qword") };
	std::vector<FormatterString> NasmFormatter::s_farMemSizeInfos = { FormatterString(""), FormatterString("word"), FormatterString("dword"), FormatterString("") };
	std::vector<std::string> NasmFormatter::s_scaleNumbers = { "1", "2", "4", "8" };
	std::vector<FormatterString> NasmFormatter::s_mvexRegMemConsts32 = { FormatterString(""), FormatterString(""), FormatterString("cdab"), FormatterString("badc"), FormatterString("dacb"), FormatterString("aaaa"), FormatterString("bbbb"), FormatterString("cccc"), FormatterString("dddd"), FormatterString(""), FormatterString("1to16"), FormatterString("4to16"), FormatterString("float16"), FormatterString("uint8"), FormatterString("sint8"), FormatterString("uint16"), FormatterString("sint16") };
	std::vector<FormatterString> NasmFormatter::s_mvexRegMemConsts64 = { FormatterString(""), FormatterString(""), FormatterString("cdab"), FormatterString("badc"), FormatterString("dacb"), FormatterString("aaaa"), FormatterString("bbbb"), FormatterString("cccc"), FormatterString("dddd"), FormatterString(""), FormatterString("1to8"), FormatterString("4to8"), FormatterString("float16"), FormatterString("uint8"), FormatterString("sint8"), FormatterString("uint16"), FormatterString("sint16") };
	FormatterString NasmFormatter::str_eh = FormatterString("eh");

	void NasmFormatter::FormatMnemonic(const Instruction& instruction, FormatterOutput* output, FormatMnemonicOptions options)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(this->options, instruction, opInfo);
		std::int32_t column = 0;
		FormatMnemonic(instruction, output, opInfo, column, options);
	}

	std::int32_t NasmFormatter::GetOperandCount(const Instruction& instruction)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		return opInfo.OpCount;
	}

	bool NasmFormatter::TryGetOpAccess(const Instruction& instruction, std::int32_t operand, OpAccess& access)
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

	std::int32_t NasmFormatter::GetInstructionOperand(const Instruction& instruction, std::int32_t operand)
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

	std::int32_t NasmFormatter::GetFormatterOperand(const Instruction& instruction, std::int32_t instructionOperand)
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

	void NasmFormatter::FormatOperand(const Instruction& instruction, FormatterOutput* output, std::int32_t operand)
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

	void NasmFormatter::FormatOperandSeparator(const Instruction& instruction, FormatterOutput* output)
	{
		if (output == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_output();
		}
		output->Write(",", FormatterTextKind::Punctuation);
		if (options.GetSpaceAfterOperandSeparator())
		{
			output->Write(" ", FormatterTextKind::Text);
		}
	}

	void NasmFormatter::FormatAllOperands(const Instruction& instruction, FormatterOutput* output)
	{
		assert(static_cast<std::uint32_t>(instruction.GetCode()) < static_cast<std::uint32_t>(instrInfos.size()));
		auto instrInfo = instrInfos[static_cast<std::int32_t>(instruction.GetCode())];
		InstrOpInfo opInfo;
		instrInfo->GetOpInfo(options, instruction, opInfo);
		FormatOperands(instruction, output, opInfo);
	}

	void NasmFormatter::Format(const Instruction& instruction, FormatterOutput* output)
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

	void NasmFormatter::FormatMnemonic(const Instruction& instruction, FormatterOutput* output, InstrOpInfo const opInfo, std::int32_t& column, FormatMnemonicOptions mnemonicOptions)
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
				bool hasNoTrackPrefix = prefixSeg == Register::DS && FormatterUtils::IsNotrackPrefixBranch(instruction.GetCode());
				if (!hasNoTrackPrefix && prefixSeg != Register::None && ShowSegmentPrefix(instruction, opInfo))
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
				output->Write(mnemonic.Get(options.GetUppercaseKeywords() || options.GetUppercaseAll()), FormatterTextKind::Directive);
			}
			else
			{
				output->WriteMnemonic(instruction, mnemonic.Get(options.GetUppercaseMnemonics() || options.GetUppercaseAll()));
			}
			column += mnemonic.GetLength();
		}
	}

	bool NasmFormatter::ShowSegmentPrefix(const Instruction& instruction, InstrOpInfo const opInfo)
	{
		if ((opInfo.Flags & (InstrOpInfoFlags::JccNotTaken | InstrOpInfoFlags::JccTaken)) != 0)
		{
			return true;
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
		case Code::Xlat_m8:
		case Code::Outsb_DX_m8:
		case Code::Outsw_DX_m16:
		case Code::Outsd_DX_m32:
		case Code::Movsb_m8_m8:
		case Code::Movsw_m16_m16:
		case Code::Movsd_m32_m32:
		case Code::Movsq_m64_m64:
		case Code::Cmpsb_m8_m8:
		case Code::Cmpsw_m16_m16:
		case Code::Cmpsd_m32_m32:
		case Code::Cmpsq_m64_m64:
		case Code::Lodsb_AL_m8:
		case Code::Lodsw_AX_m16:
		case Code::Lodsd_EAX_m32:
		case Code::Lodsq_RAX_m64:
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
		return options.GetShowUselessPrefixes();
	}

	void NasmFormatter::FormatPrefix(FormatterOutput* output, const Instruction& instruction, std::int32_t& column, FormatterString prefix, PrefixKind prefixKind, bool& needSpace)
	{
		if (needSpace)
		{
			column++;
			output->Write(" ", FormatterTextKind::Text);
		}
		output->WritePrefix(instruction, prefix.Get(options.GetUppercasePrefixes() || options.GetUppercaseAll()), prefixKind);
		column += prefix.GetLength();
		needSpace = true;
	}

	void NasmFormatter::FormatOperands(const Instruction& instruction, FormatterOutput* output, InstrOpInfo const opInfo)
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
				if (options.GetSpaceAfterOperandSeparator())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
			}
			FormatOperand(instruction, output, opInfo, i);
		}
	}

	void NasmFormatter::FormatOperand(const Instruction& instruction, FormatterOutput* output, InstrOpInfo const opInfo, std::int32_t operand)
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
			if ((opInfo.Flags & InstrOpInfoFlags::RegisterTo) != 0)
			{
				FormatKeyword(output, str_to);
				output->Write(" ", FormatterTextKind::Text);
			}
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options.GetShowSymbolAddress());
			}
			else
			{
				operandOptions = FormatterOperandOptions(options.GetShowBranchSize() ? FormatterOperandOptions::Flags::None : FormatterOperandOptions::Flags::NoBranchSize);
				if (optionsProvider != nullptr)
				{
					optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
				}
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
			operandOptions = FormatterOperandOptions(options.GetShowBranchSize() ? FormatterOperandOptions::Flags::None : FormatterOperandOptions::Flags::NoBranchSize);
			if (optionsProvider != nullptr)
			{
				optionsProvider->GetOperandOptions(instruction, operand, instructionOperand, operandOptions, numberOptions);
			}
			if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, instructionOperand, static_cast<std::uint32_t>(imm64), immSize, symbol))
			{
				FormatFlowControl(output, opInfo.Flags, operandOptions);
				assert(operand + 1 == 1);
				SymbolResult selectorSymbol;
				if (!symbolResolver->TryGetSymbol(instruction, operand + 1, instructionOperand, instruction.GetFarBranchSelector(), 2, selectorSymbol))
				{
					s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranchSelector(), numberOptions.LeadingZeros);
					output->WriteNumber(instruction, operand, instructionOperand, s, instruction.GetFarBranchSelector(), NumberKind::UInt16, FormatterTextKind::SelectorValue);
				}
				else
				{
					output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, instruction.GetFarBranchSelector(), selectorSymbol, options.GetShowSymbolAddress());
				}
				output->Write(":", FormatterTextKind::Punctuation);
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options.GetShowSymbolAddress());
			}
			else
			{
				flowControl = FormatterUtils::GetFlowControl(instruction);
				FormatFlowControl(output, opInfo.Flags, operandOptions);
				s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranchSelector(), numberOptions.LeadingZeros);
				output->WriteNumber(instruction, operand, instructionOperand, s, instruction.GetFarBranchSelector(), NumberKind::UInt16, FormatterTextKind::SelectorValue);
				output->Write(":", FormatterTextKind::Punctuation);
				if (opKind == InstrOpKind::FarBranch32)
				{
					s = numberFormatter.FormatUInt32(options, numberOptions, instruction.GetFarBranch32(), numberOptions.LeadingZeros);
				}
				else
				{
					s = numberFormatter.FormatUInt16(options, numberOptions, instruction.GetFarBranch16(), numberOptions.LeadingZeros);
				}
				output->WriteNumber(instruction, operand, instructionOperand, s, imm64, numberKind, FormatterUtils::IsCall(flowControl) ? FormatterTextKind::FunctionAddress : FormatterTextKind::LabelAddress);
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm8, symbol, options.GetShowSymbolAddress());
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
			ShowSignExtendInfo(output, opInfo.Flags);
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm16, symbol, options.GetShowSymbolAddress());
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
			ShowSignExtendInfo(output, opInfo.Flags);
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm32, symbol, options.GetShowSymbolAddress());
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
			ShowSignExtendInfo(output, opInfo.Flags);
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
				output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, imm64, symbol, options.GetShowSymbolAddress());
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
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), instruction.GetMemorySegment(), Register::SI, Register::None, 0, 0, 0, 2, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegESI:
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), instruction.GetMemorySegment(), Register::ESI, Register::None, 0, 0, 0, 4, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegRSI:
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), instruction.GetMemorySegment(), Register::RSI, Register::None, 0, 0, 0, 8, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegDI:
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), instruction.GetMemorySegment(), Register::DI, Register::None, 0, 0, 0, 2, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegEDI:
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), instruction.GetMemorySegment(), Register::EDI, Register::None, 0, 0, 0, 4, opInfo.Flags);
			break;
		case InstrOpKind::MemorySegRDI:
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), instruction.GetMemorySegment(), Register::RDI, Register::None, 0, 0, 0, 8, opInfo.Flags);
			break;
		case InstrOpKind::MemoryESDI:
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), Register::ES, Register::DI, Register::None, 0, 0, 0, 2, opInfo.Flags);
			break;
		case InstrOpKind::MemoryESEDI:
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), Register::ES, Register::EDI, Register::None, 0, 0, 0, 4, opInfo.Flags);
			break;
		case InstrOpKind::MemoryESRDI:
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), Register::ES, Register::RDI, Register::None, 0, 0, 0, 8, opInfo.Flags);
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
			FormatMemory(output, instruction, operand, instructionOperand, opInfo.GetMemorySize(), instruction.GetMemorySegment(), baseReg, indexReg, instruction.GetInternalMemoryIndexScale(), displSize, displ, addrSize, opInfo.Flags);
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
		if (operand == 0 && instruction.GetHasOpMaskOrZeroingMasking())
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

	void NasmFormatter::ShowSignExtendInfo(FormatterOutput* output, InstrOpInfoFlags flags)
	{
		if (!options.GetNasmShowSignExtendedImmediateSize())
		{
			return;
		}
		FormatterString keyword;
		switch (static_cast<SignExtendInfo>((static_cast<std::int32_t>(flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::SignExtendInfoShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::SignExtendInfoMask)))
		{
		case SignExtendInfo::None:
			return;
		case SignExtendInfo::Sex1to2:
		case SignExtendInfo::Sex1to4:
		case SignExtendInfo::Sex1to8:
			keyword = str_byte;
			break;
		case SignExtendInfo::Sex2:
			keyword = str_word;
			break;
		case SignExtendInfo::Sex4:
			keyword = str_dword;
			break;
		case SignExtendInfo::Sex4to8:
			keyword = str_qword;
			break;
		default:
			throw InvalidOperationException();
		}
		FormatKeyword(output, keyword);
		output->Write(" ", FormatterTextKind::Text);
	}

	void NasmFormatter::FormatFlowControl(FormatterOutput* output, InstrOpInfoFlags flags, FormatterOperandOptions operandOptions)
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
			output->Write(" ", FormatterTextKind::Text);
		}
	}

	void NasmFormatter::FormatDecorator(FormatterOutput* output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, FormatterString text, DecoratorKind decorator)
	{
		output->Write("{", FormatterTextKind::Punctuation);
		output->WriteDecorator(instruction, operand, instructionOperand, text.Get(options.GetUppercaseDecorators() || options.GetUppercaseAll()), decorator);
		output->Write("}", FormatterTextKind::Punctuation);
	}

	std::string NasmFormatter::ToRegisterString(Register reg)
	{
		assert(static_cast<std::uint32_t>(reg) < static_cast<std::uint32_t>(allRegisters.size()));
		auto regStr = allRegisters[static_cast<std::int32_t>(reg)];
		return regStr.Get(options.GetUppercaseRegisters() || options.GetUppercaseAll());
	}

	void NasmFormatter::FormatRegister(FormatterOutput* output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, Register reg)
	{
		output->WriteRegister(instruction, operand, instructionOperand, ToRegisterString(reg), static_cast<Register>(reg));
	}

	void NasmFormatter::FormatMemory(FormatterOutput* output, const Instruction& instruction, std::int32_t operand, std::int32_t instructionOperand, MemorySize memSize, Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int32_t displSize, std::int64_t displ, std::int32_t addrSize, InstrOpInfoFlags flags)
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
		bool addRelKeyword = false;
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
				flags &= ~static_cast<InstrOpInfoFlags>(static_cast<std::uint32_t>(InstrOpInfoFlags::MemorySizeInfoMask) << static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeInfoShift));
				addRelKeyword = true;
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
				flags = (flags & ~static_cast<InstrOpInfoFlags>(static_cast<std::uint32_t>(InstrOpInfoFlags::MemorySizeInfoMask) << static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeInfoShift))) | static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(NasmFormatterInternal::MemorySizeInfo::Dword) << static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeInfoShift));
				addRelKeyword = true;
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
		FormatMemorySize(output, memSize, flags, operandOptions);
		output->Write("[", FormatterTextKind::Punctuation);
		if (options.GetSpaceAfterMemoryBracket())
		{
			output->Write(" ", FormatterTextKind::Text);
		}
		auto memSizeName = memSizeInfos[(static_cast<std::int32_t>(flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeInfoShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeInfoMask)];
		if (memSizeName.GetLength() != 0)
		{
			FormatKeyword(output, memSizeName);
			output->Write(" ", FormatterTextKind::Text);
		}
		if (addRelKeyword)
		{
			FormatKeyword(output, str_rel);
			output->Write(" ", FormatterTextKind::Text);
		}
		auto codeSize = instruction.GetCodeSize();
		auto segOverride = instruction.GetSegmentPrefix();
		bool noTrackPrefix = segOverride == Register::DS && FormatterUtils::IsNotrackPrefixBranch(instruction.GetCode()) && !((codeSize == CodeSize::Code16 || codeSize == CodeSize::Code32) && (baseReg == Register::BP || baseReg == Register::EBP || baseReg == Register::ESP));
		if (options.GetAlwaysShowSegmentRegister() || (segOverride != Register::None && !noTrackPrefix && FormatterUtils::ShowSegmentPrefix(Register::None, instruction, options)))
		{
			FormatRegister(output, instruction, operand, instructionOperand, segReg);
			output->Write(":", FormatterTextKind::Punctuation);
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
					output->Write(" ", FormatterTextKind::Text);
				}
				output->Write("+", FormatterTextKind::Operator);
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
			}
			needPlus = true;
			if (!useScale)
			{
				FormatRegister(output, instruction, operand, instructionOperand, indexReg);
			}
			else if (options.GetScaleBeforeIndex())
			{
				output->WriteNumber(instruction, operand, instructionOperand, scaleNumbers[scale], 1U << scale, NumberKind::Int32, FormatterTextKind::Number);
				if (options.GetSpaceBetweenMemoryMulOperators())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
				output->Write("*", FormatterTextKind::Operator);
				if (options.GetSpaceBetweenMemoryMulOperators())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
				FormatRegister(output, instruction, operand, instructionOperand, indexReg);
			}
			else
			{
				FormatRegister(output, instruction, operand, instructionOperand, indexReg);
				if (options.GetSpaceBetweenMemoryMulOperators())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
				output->Write("*", FormatterTextKind::Operator);
				if (options.GetSpaceBetweenMemoryMulOperators())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
				output->WriteNumber(instruction, operand, instructionOperand, scaleNumbers[scale], 1U << scale, NumberKind::Int32, FormatterTextKind::Number);
			}
		}
		if (useSymbol)
		{
			if (needPlus)
			{
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
				if ((symbol.Flags & SymbolFlags::Signed) != 0)
				{
					output->Write("-", FormatterTextKind::Operator);
				}
				else
				{
					output->Write("+", FormatterTextKind::Operator);
				}
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output->Write(" ", FormatterTextKind::Text);
				}
			}
			else if ((symbol.Flags & SymbolFlags::Signed) != 0)
			{
				output->Write("-", FormatterTextKind::Operator);
			}
			output->Write(instruction, operand, instructionOperand, options, numberFormatter, numberOptions, absAddr, symbol, options.GetShowSymbolAddress(), false, options.GetSpaceBetweenMemoryAddOperators());
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
					output->Write(" ", FormatterTextKind::Text);
				}
				if (addrSize == 8)
				{
					if (!numberOptions.SignedNumber)
					{
						output->Write("+", FormatterTextKind::Operator);
					}
					else if (displ < 0)
					{
						displ = -displ;
						output->Write("-", FormatterTextKind::Operator);
					}
					else
					{
						output->Write("+", FormatterTextKind::Operator);
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
						output->Write("+", FormatterTextKind::Operator);
					}
					else if (static_cast<std::int32_t>(displ) < 0)
					{
						displ = static_cast<std::uint32_t>(-static_cast<std::int32_t>(displ));
						output->Write("-", FormatterTextKind::Operator);
					}
					else
					{
						output->Write("+", FormatterTextKind::Operator);
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
						output->Write("+", FormatterTextKind::Operator);
					}
					else if (static_cast<std::int16_t>(displ) < 0)
					{
						displ = static_cast<std::uint16_t>(-static_cast<std::int16_t>(displ));
						output->Write("-", FormatterTextKind::Operator);
					}
					else
					{
						output->Write("+", FormatterTextKind::Operator);
					}
					if (numberOptions.DisplacementLeadingZeros)
					{
						displSize = 2;
					}
				}
				if (options.GetSpaceBetweenMemoryAddOperators())
				{
					output->Write(" ", FormatterTextKind::Text);
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
		if (options.GetSpaceAfterMemoryBracket())
		{
			output->Write(" ", FormatterTextKind::Text);
		}
		output->Write("]", FormatterTextKind::Punctuation);
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

	void NasmFormatter::FormatMemorySize(FormatterOutput* output, MemorySize memSize, InstrOpInfoFlags flags, FormatterOperandOptions operandOptions)
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
		auto keyword = memInfo.keyword;
		if (keyword.GetLength() == 0)
		{
			return;
		}
		if (memSizeOptions == MemorySizeOptions::Default)
		{
			if ((flags & InstrOpInfoFlags::ShowNoMemSize_ForceSize) == 0)
			{
				return;
			}
		}
		else if (memSizeOptions == MemorySizeOptions::Minimal)
		{
			if ((flags & InstrOpInfoFlags::ShowMinMemSize_ForceSize) == 0)
			{
				return;
			}
		}
		else
		{
			assert(memSizeOptions == MemorySizeOptions::Always);
		}
		auto farKind = farMemSizeInfos[(static_cast<std::int32_t>(flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::FarMemorySizeInfoShift)) & static_cast<std::int32_t>(InstrOpInfoFlags::FarMemorySizeInfoMask)];
		if (farKind.GetLength() != 0)
		{
			FormatKeyword(output, farKind);
			output->Write(" ", FormatterTextKind::Text);
		}
		FormatKeyword(output, keyword);
		output->Write(" ", FormatterTextKind::Text);
	}

	void NasmFormatter::FormatKeyword(FormatterOutput* output, FormatterString keyword)
	{
		output->Write(keyword.Get(options.GetUppercaseKeywords() || options.GetUppercaseAll()), FormatterTextKind::Keyword);
	}

	std::string NasmFormatter::Format(Register register_)
	{
		return ToRegisterString(register_);
	}

	std::string NasmFormatter::FormatInt8(std::int8_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatInt8(options, numberOptions, value);
	}

	std::string NasmFormatter::FormatInt16(std::int16_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatInt16(options, numberOptions, value);
	}

	std::string NasmFormatter::FormatInt32(std::int32_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatInt32(options, numberOptions, value);
	}

	std::string NasmFormatter::FormatInt64(std::int64_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatInt64(options, numberOptions, value);
	}

	std::string NasmFormatter::FormatUInt8(std::uint8_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatUInt8(options, numberOptions, value);
	}

	std::string NasmFormatter::FormatUInt16(std::uint16_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatUInt16(options, numberOptions, value);
	}

	std::string NasmFormatter::FormatUInt32(std::uint32_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatUInt32(options, numberOptions, value);
	}

	std::string NasmFormatter::FormatUInt64(std::uint64_t value, const NumberFormattingOptions& numberOptions)
	{
		return numberFormatter.FormatUInt64(options, numberOptions, value);
	}
}
