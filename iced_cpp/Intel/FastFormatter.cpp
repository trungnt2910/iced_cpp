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

#include "FastFormatter.h"
#include "FastFormatterInternal/Registers.h"
#include "FastFormatterInternal/Iced.Intel.FastFormatterInternal.FmtData.h"
#include "FastFormatterInternal/MemorySizes.h"
#include "ThrowHelper.h"
#include "OpKind.g.h"
#include "FormatterInternal/PseudoOpsKind.g.h"
#include "Code.g.h"
#include "FormatterConstants.h"
#include "CodeSize.g.h"
#include "Static.h"
#include "FormatterInternal/Iced.Intel.FormatterInternal.FormatterUtils.h"
#include "Iced.Intel.InstructionInfoExtensions.h"
#include "Iced.Intel.IcedConstants.h"
#include "InstructionUtils.h"
#include "MvexRegMemConv.g.h"
#include "MvexInfo.h"
#include "MvexConvFn.g.h"
#include "RoundingControl.g.h"

using namespace Iced::Intel::FastFormatterInternal;
using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel
{

	std::vector<std::string> FastFormatter::s_rcStrings = { "{rn}", "{rd}", "{ru}", "{rz}" };
	std::vector<std::string> FastFormatter::s_rcSaeStrings = { "{rn-sae}", "{rd-sae}", "{ru-sae}", "{rz-sae}" };
	std::vector<std::string> FastFormatter::s_scaleNumbers = { "*1", "*2", "*4", "*8" };
	std::vector<std::string> FastFormatter::s_mvexRegMemConsts32 = { "", "", "{cdab}", "{badc}", "{dacb}", "{aaaa}", "{bbbb}", "{cccc}", "{dddd}", "", "{1to16}", "{4to16}", "{float16}", "{uint8}", "{sint8}", "{uint16}", "{sint16}" };
	std::vector<std::string> FastFormatter::s_mvexRegMemConsts64 = { "", "", "{cdab}", "{badc}", "{dacb}", "{aaaa}", "{bbbb}", "{cccc}", "{dddd}", "", "{1to8}", "{4to8}", "{float16}", "{uint8}", "{sint8}", "{uint16}", "{sint16}" };

	FastFormatterOptions* FastFormatter::GetOptions() const
	{
		return options;
	}

	FastFormatter::FastFormatter() : FastFormatter(nullptr)
	{
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public FastFormatter(ISymbolResolver? symbolResolver)
	FastFormatter::FastFormatter(ISymbolResolver* symbolResolver)
	{
		options = new FastFormatterOptions();
		this->symbolResolver = symbolResolver;
		allRegisters = Registers::AllRegisters;
		codeMnemonics = FmtData::Mnemonics;
		codeFlags = FmtData::Flags;
		allMemorySizes = MemorySizes::AllMemorySizes;
		rcStrings = s_rcStrings;
		rcSaeStrings = s_rcSaeStrings;
		scaleNumbers = s_scaleNumbers;
		mvexRegMemConsts32 = s_mvexRegMemConsts32;
		mvexRegMemConsts64 = s_mvexRegMemConsts64;
	}

	void FastFormatter::Format(Instruction const instruction, FastStringOutput* output)
	{
		if (output == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_output();
		}
		auto code = instruction.GetCode();
		auto mnemonic = codeMnemonics[static_cast<std::int32_t>(code)];
		auto flags = codeFlags[static_cast<std::int32_t>(code)];
		auto opCount = instruction.GetOpCount();
		auto pseudoOpsNum = static_cast<std::uint32_t>(flags) >> static_cast<std::int32_t>(FastFmtFlags::PseudoOpsKindShift);
		if (pseudoOpsNum != 0 && options->GetUsePseudoOps() && instruction.GetOpKind(opCount - 1) == OpKind::Immediate8)
		{
			std::int32_t index = instruction.GetImmediate8();
			auto pseudoOpKind = static_cast<PseudoOpsKind>(pseudoOpsNum - 1);
			if (pseudoOpKind == PseudoOpsKind::vpcmpd6)
			{
				switch (code)
				{
				case Code::MVEX_Vpcmpud_kr_k1_zmm_zmmmt_imm8:
					pseudoOpKind = PseudoOpsKind::vpcmpud6;
					break;
				default:
					break;
				}
			}
			auto pseudoOps = FormatterConstants::GetPseudoOps(pseudoOpKind);
			if (pseudoOpKind == PseudoOpsKind::pclmulqdq || pseudoOpKind == PseudoOpsKind::vpclmulqdq)
			{
				if (index <= 1)
				{
					// nothing
				}
				else if (index == 0x10)
				{
					index = 2;
				}
				else if (index == 0x11)
				{
					index = 3;
				}
				else
				{
					index = -1;
				}
			}
			if (static_cast<std::uint32_t>(index) < static_cast<std::uint32_t>(pseudoOps.size()))
			{
				mnemonic = pseudoOps[index].GetLower();
				opCount--;
			}
		}
		auto prefixSeg = instruction.GetSegmentPrefix();
		Static::Assert(Register::None == (Iced::Intel::Register)0 ? 0 : -1);
		if ((static_cast<std::uint32_t>(prefixSeg) | instruction.GetHasAnyOfLockRepRepnePrefix()) != 0)
		{
			bool hasNoTrackPrefix = prefixSeg == Register::DS && FormatterUtils::IsNotrackPrefixBranch(code);
			if (!hasNoTrackPrefix && prefixSeg != Register::None && ShowSegmentPrefix(instruction, opCount))
			{
				FormatRegister(output, prefixSeg);
				output->Append(' ');
			}
			bool hasXacquirePrefix = false;
			if (instruction.GetHasXacquirePrefix())
			{
				output->AppendNotNull("xacquire ");
				hasXacquirePrefix = true;
			}
			if (instruction.GetHasXreleasePrefix())
			{
				output->AppendNotNull("xrelease ");
				hasXacquirePrefix = true;
			}
			if (instruction.GetHasLockPrefix())
			{
				output->AppendNotNull("lock ");
			}
			if (hasNoTrackPrefix)
			{
				output->AppendNotNull("notrack ");
			}
			if (!hasXacquirePrefix)
			{
				if (instruction.GetHasRepePrefix() && (ShowUselessPrefixes || FormatterUtils::ShowRepOrRepePrefix(code, ShowUselessPrefixes)))
				{
					if (FormatterUtils::IsRepeOrRepneInstruction(code))
					{
						output->AppendNotNull("repe ");
					}
					else
					{
						output->AppendNotNull("rep ");
					}
				}
				if (instruction.GetHasRepnePrefix())
				{
					if ((Code::Retnw_imm16 <= code && code <= Code::Retnq) || (Code::Call_rel16 <= code && code <= Code::Jmp_rel32_64) || (Code::Call_rm16 <= code && code <= Code::Call_rm64) || (Code::Jmp_rm16 <= code && code <= Code::Jmp_rm64) || Iced::Intel::InstructionInfoExtensions::IsJccShortOrNear(code))
					{
						output->AppendNotNull("bnd ");
					}
					else if (ShowUselessPrefixes || FormatterUtils::ShowRepnePrefix(code, ShowUselessPrefixes))
					{
						output->AppendNotNull("repne ");
					}
				}
			}
		}
		output->AppendNotNull(mnemonic);
		bool isDeclareData;
		OpKind declareDataOpKind;
		if (static_cast<std::uint32_t>(code) - static_cast<std::uint32_t>(Code::DeclareByte) <= static_cast<std::uint32_t>(Code::DeclareQword) - static_cast<std::uint32_t>(Code::DeclareByte))
		{
			opCount = instruction.GetDeclareDataCount();
			isDeclareData = true;
			switch (code)
			{
			case Code::DeclareByte:
				declareDataOpKind = OpKind::Immediate8;
				break;
			case Code::DeclareWord:
				declareDataOpKind = OpKind::Immediate16;
				break;
			case Code::DeclareDword:
				declareDataOpKind = OpKind::Immediate32;
				break;
			default:
				assert(code == Code::DeclareQword);
				declareDataOpKind = OpKind::Immediate64;
				break;
			}
		}
		else
		{
			isDeclareData = false;
			declareDataOpKind = OpKind::Register;
		}
		if (opCount > 0)
		{
			output->Append(' ');
			std::int32_t mvexRmOperand;
			if (IcedConstants::IsMvex(instruction.GetCode()))
			{
				assert(opCount != 0);
				mvexRmOperand = instruction.GetOpKind(opCount - 1) == OpKind::Immediate8 ? opCount - 2 : opCount - 1;
			}
			else
			{
				mvexRmOperand = -1;
			}
			for (std::int32_t operand = 0; operand < opCount; operand++)
			{
				if (operand > 0)
				{
					if (options->GetSpaceAfterOperandSeparator())
					{
						output->AppendNotNull(", ");
					}
					else
					{
						output->Append(',');
					}
				}
				std::uint8_t imm8;
				std::uint16_t imm16;
				std::uint32_t imm32;
				std::uint64_t imm64;
				std::int32_t immSize;
				SymbolResult symbol;
				//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
				//ORIGINAL LINE: ISymbolResolver? symbolResolver;
				ISymbolResolver* symbolResolver;
				auto opKind = isDeclareData ? declareDataOpKind : instruction.GetOpKind(operand);
				switch (opKind)
				{
				case OpKind::Register:
					FormatRegister(output, instruction.GetOpRegister(operand));
					break;
				case OpKind::NearBranch16:
				case OpKind::NearBranch32:
				case OpKind::NearBranch64:
					if (opKind == OpKind::NearBranch64)
					{
						immSize = 8;
						imm64 = instruction.GetNearBranch64();
					}
					else if (opKind == OpKind::NearBranch32)
					{
						immSize = 4;
						imm64 = instruction.GetNearBranch32();
					}
					else
					{
						immSize = 2;
						imm64 = instruction.GetNearBranch16();
					}
					if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, operand, imm64, immSize, symbol))
					{
						WriteSymbol(output, imm64, symbol);
					}
					else
					{
						FormatNumber(output, imm64);
					}
					break;
				case OpKind::FarBranch16:
				case OpKind::FarBranch32:
					if (opKind == OpKind::FarBranch32)
					{
						immSize = 4;
						imm64 = instruction.GetFarBranch32();
					}
					else
					{
						immSize = 2;
						imm64 = instruction.GetFarBranch16();
					}
					if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, operand, static_cast<std::uint32_t>(imm64), immSize, symbol))
					{
						assert(operand + 1 == 1);
						SymbolResult selectorSymbol;
						if (!symbolResolver->TryGetSymbol(instruction, operand + 1, operand, instruction.GetFarBranchSelector(), 2, selectorSymbol))
						{
							FormatNumber(output, instruction.GetFarBranchSelector());
						}
						else
						{
							WriteSymbol(output, instruction.GetFarBranchSelector(), selectorSymbol);
						}
						output->Append(':');
						WriteSymbol(output, imm64, symbol);
					}
					else
					{
						FormatNumber(output, instruction.GetFarBranchSelector());
						output->Append(':');
						if (opKind == OpKind::FarBranch32)
						{
							FormatNumber(output, instruction.GetFarBranch32());
						}
						else
						{
							FormatNumber(output, instruction.GetFarBranch16());
						}
					}
					break;
				case OpKind::Immediate8:
				case OpKind::Immediate8_2nd:
					if (isDeclareData)
					{
						imm8 = instruction.GetDeclareByteValue(operand);
					}
					else if (opKind == OpKind::Immediate8)
					{
						imm8 = instruction.GetImmediate8();
					}
					else
					{
						assert(opKind == OpKind::Immediate8_2nd);
						imm8 = instruction.GetImmediate8_2nd();
					}
					if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, operand, imm8, 1, symbol))
					{
						if ((symbol.Flags & SymbolFlags::Relative) == 0)
						{
							output->AppendNotNull("offset ");
						}
						WriteSymbol(output, imm8, symbol);
					}
					else
					{
						FormatNumber(output, imm8);
					}
					break;
				case OpKind::Immediate16:
				case OpKind::Immediate8to16:
					if (isDeclareData)
					{
						imm16 = instruction.GetDeclareWordValue(operand);
					}
					else if (opKind == OpKind::Immediate16)
					{
						imm16 = instruction.GetImmediate16();
					}
					else
					{
						assert(opKind == OpKind::Immediate8to16);
						imm16 = static_cast<std::uint16_t>(instruction.GetImmediate8to16());
					}
					if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, operand, imm16, 2, symbol))
					{
						if ((symbol.Flags & SymbolFlags::Relative) == 0)
						{
							output->AppendNotNull("offset ");
						}
						WriteSymbol(output, imm16, symbol);
					}
					else
					{
						FormatNumber(output, imm16);
					}
					break;
				case OpKind::Immediate32:
				case OpKind::Immediate8to32:
					if (isDeclareData)
					{
						imm32 = instruction.GetDeclareDwordValue(operand);
					}
					else if (opKind == OpKind::Immediate32)
					{
						imm32 = instruction.GetImmediate32();
					}
					else
					{
						assert(opKind == OpKind::Immediate8to32);
						imm32 = static_cast<std::uint32_t>(instruction.GetImmediate8to32());
					}
					if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, operand, imm32, 4, symbol))
					{
						if ((symbol.Flags & SymbolFlags::Relative) == 0)
						{
							output->AppendNotNull("offset ");
						}
						WriteSymbol(output, imm32, symbol);
					}
					else
					{
						FormatNumber(output, imm32);
					}
					break;
				case OpKind::Immediate64:
				case OpKind::Immediate8to64:
				case OpKind::Immediate32to64:
					if (isDeclareData)
					{
						imm64 = instruction.GetDeclareQwordValue(operand);
					}
					else if (opKind == OpKind::Immediate32to64)
					{
						imm64 = static_cast<std::uint64_t>(instruction.GetImmediate32to64());
					}
					else if (opKind == OpKind::Immediate8to64)
					{
						imm64 = static_cast<std::uint64_t>(instruction.GetImmediate8to64());
					}
					else
					{
						assert(opKind == OpKind::Immediate64);
						imm64 = instruction.GetImmediate64();
					}
					if ((symbolResolver = this->symbolResolver) != nullptr && symbolResolver->TryGetSymbol(instruction, operand, operand, imm64, 8, symbol))
					{
						if ((symbol.Flags & SymbolFlags::Relative) == 0)
						{
							output->AppendNotNull("offset ");
						}
						WriteSymbol(output, imm64, symbol);
					}
					else
					{
						FormatNumber(output, imm64);
					}
					break;
				case OpKind::MemorySegSI:
					FormatMemory(output, instruction, operand, instruction.GetMemorySegment(), Register::SI, Register::None, 0, 0, 0, 2);
					break;
				case OpKind::MemorySegESI:
					FormatMemory(output, instruction, operand, instruction.GetMemorySegment(), Register::ESI, Register::None, 0, 0, 0, 4);
					break;
				case OpKind::MemorySegRSI:
					FormatMemory(output, instruction, operand, instruction.GetMemorySegment(), Register::RSI, Register::None, 0, 0, 0, 8);
					break;
				case OpKind::MemorySegDI:
					FormatMemory(output, instruction, operand, instruction.GetMemorySegment(), Register::DI, Register::None, 0, 0, 0, 2);
					break;
				case OpKind::MemorySegEDI:
					FormatMemory(output, instruction, operand, instruction.GetMemorySegment(), Register::EDI, Register::None, 0, 0, 0, 4);
					break;
				case OpKind::MemorySegRDI:
					FormatMemory(output, instruction, operand, instruction.GetMemorySegment(), Register::RDI, Register::None, 0, 0, 0, 8);
					break;
				case OpKind::MemoryESDI:
					FormatMemory(output, instruction, operand, Register::ES, Register::DI, Register::None, 0, 0, 0, 2);
					break;
				case OpKind::MemoryESEDI:
					FormatMemory(output, instruction, operand, Register::ES, Register::EDI, Register::None, 0, 0, 0, 4);
					break;
				case OpKind::MemoryESRDI:
					FormatMemory(output, instruction, operand, Register::ES, Register::RDI, Register::None, 0, 0, 0, 8);
					break;
				case OpKind::Memory:
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
					if (code == Code::Xlat_m8)
					{
						indexReg = Register::None;
					}
					FormatMemory(output, instruction, operand, instruction.GetMemorySegment(), baseReg, indexReg, instruction.GetInternalMemoryIndexScale(), displSize, displ, addrSize);
					break;
				}
				default:
					throw InvalidOperationException();
				}
				if (operand == 0 && instruction.GetHasOpMaskOrZeroingMasking())
				{
					if (instruction.GetHasOpMask())
					{
						output->Append('{');
						FormatRegister(output, instruction.GetOpMask());
						output->Append('}');
					}
					if (instruction.GetZeroingMasking())
					{
						output->AppendNotNull("{z}");
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
							auto s = tbl[static_cast<std::int32_t>(conv)];
							if (s.length() != 0)
							{
								output->AppendNotNull(s);
							}
						}
					}
				}
			}
			if (instruction.GetHasRoundingControlOrSae())
			{
				auto rc = instruction.GetRoundingControl();
				if (rc != RoundingControl::None)
				{
					Static::Assert(static_cast<std::int32_t>(RoundingControl::None) == 0 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
					Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
					if (IcedConstants::IsMvex(instruction.GetCode()) && !instruction.GetSuppressAllExceptions())
					{
						output->AppendNotNull(rcStrings[static_cast<std::int32_t>(rc) - 1]);
					}
					else
					{
						output->AppendNotNull(rcSaeStrings[static_cast<std::int32_t>(rc) - 1]);
					}
				}
				else
				{
					assert(instruction.GetSuppressAllExceptions());
					output->AppendNotNull("{sae}");
				}
			}
		}
	}

	bool FastFormatter::ShowSegmentPrefix(Instruction const instruction, std::int32_t opCount)
	{
		for (std::int32_t i = 0; i < opCount; i++)
		{
			switch (instruction.GetOpKind(i))
			{
			case OpKind::Register:
			case OpKind::NearBranch16:
			case OpKind::NearBranch32:
			case OpKind::NearBranch64:
			case OpKind::FarBranch16:
			case OpKind::FarBranch32:
			case OpKind::Immediate8:
			case OpKind::Immediate8_2nd:
			case OpKind::Immediate16:
			case OpKind::Immediate32:
			case OpKind::Immediate64:
			case OpKind::Immediate8to16:
			case OpKind::Immediate8to32:
			case OpKind::Immediate8to64:
			case OpKind::Immediate32to64:
			case OpKind::MemoryESDI:
			case OpKind::MemoryESEDI:
			case OpKind::MemoryESRDI:
				break;
			case OpKind::MemorySegSI:
			case OpKind::MemorySegESI:
			case OpKind::MemorySegRSI:
			case OpKind::MemorySegDI:
			case OpKind::MemorySegEDI:
			case OpKind::MemorySegRDI:
			case OpKind::Memory:
				return false;
			default:
				throw InvalidOperationException();
			}
		}
		return ShowUselessPrefixes;
	}

	void FastFormatter::FormatRegister(FastStringOutput* output, Register register_)
	{
		output->AppendNotNull(allRegisters[static_cast<std::int32_t>(register_)].GetLower());
	}

	void FastFormatter::FormatNumber(FastStringOutput* output, std::uint64_t value)
	{
		bool useHexPrefix = options->GetUseHexPrefix();
		if (useHexPrefix)
		{
			output->AppendNotNull("0x");
		}
		std::int32_t shift = 0;
		for (std::uint64_t tmp = value; ;)
		{
			shift += 4;
			tmp >>= 4;
			if (tmp == 0)
			{
				break;
			}
		}
		if (!useHexPrefix && static_cast<std::int32_t>((value >> (shift - 4)) & 0xF) > 9)
		{
			output->Append('0');
		}
		auto hexDigits = options->GetUppercaseHex() ? "0123456789ABCDEF" : "0123456789abcdef";
		for (; ;)
		{
			shift -= 4;
			std::int32_t digit = static_cast<std::int32_t>(value >> shift) & 0xF;
			output->Append(hexDigits[digit]);
			if (shift == 0)
			{
				break;
			}
		}
		if (!useHexPrefix)
		{
			output->Append('h');
		}
	}

	void FastFormatter::WriteSymbol(FastStringOutput* output, std::uint64_t address, SymbolResult const symbol)
	{
		WriteSymbol(output, address, symbol, true);
	}

	void FastFormatter::WriteSymbol(FastStringOutput* output, std::uint64_t address, SymbolResult const symbol, bool writeMinusIfSigned)
	{
		std::int64_t displ = static_cast<std::int64_t>(address - symbol.Address);
		if ((symbol.Flags & SymbolFlags::Signed) != 0)
		{
			if (writeMinusIfSigned)
			{
				output->Append('-');
			}
			displ = -displ;
		}
		const TextInfo& text = symbol.Text;
		auto array = text.TextArray;
		if (array != nullptr)
		{
			for (const auto& part : *array)
			{
				std::string s = part.Text;
				if (s != "")
				{
					output->AppendNotNull(s);
				}
			}
		}
		else
		{
			std::string s = text.Text.Text;
			if (s != "")
			{
				output->AppendNotNull(s);
			}
		}
		if (displ != 0)
		{
			if (displ < 0)
			{
				output->Append('-');
				displ = -displ;
			}
			else
			{
				output->Append('+');
			}
			FormatNumber(output, static_cast<std::uint64_t>(displ));
		}
		if (options->GetShowSymbolAddress())
		{
			output->AppendNotNull(" (");
			FormatNumber(output, address);
			output->Append(')');
		}
	}

	void FastFormatter::FormatMemory(FastStringOutput* output, Instruction const instruction, std::int32_t operand, Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int32_t displSize, std::int64_t displ, std::int32_t addrSize)
	{
		assert(static_cast<std::uint32_t>(scale) < static_cast<std::uint32_t>(scaleNumbers.size()));
		assert((InstructionUtils::GetAddressSizeInBytes(baseReg, indexReg, displSize, instruction.GetCodeSize()) == addrSize));
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
		SymbolResult symbol;
		bool useSymbol;
		ISymbolResolver* symbolResolver = dynamic_cast<ISymbolResolver*>(this->symbolResolver);
		if (symbolResolver != nullptr)
		{
			useSymbol = symbolResolver->TryGetSymbol(instruction, operand, operand, absAddr, addrSize, symbol);
		}
		else
		{
			useSymbol = false;
			symbol = Iced::Intel::SymbolResult();
		}
		bool useScale = scale != 0;
		if (!useScale)
		{
			// [rsi] = base reg, [rsi*1] = index reg
			if (baseReg == Register::None)
			{
				useScale = true;
			}
		}
		if (addrSize == 2)
		{
			useScale = false;
		}
		auto flags = codeFlags[static_cast<std::int32_t>(instruction.GetCode())];
		bool showMemSize = (flags & FastFmtFlags::ForceMemSize) != 0 || instruction.IsBroadcast() || options->GetAlwaysShowMemorySize();
		if (showMemSize)
		{
			assert(static_cast<std::uint32_t>(instruction.GetMemorySize()) < static_cast<std::uint32_t>(allMemorySizes.size()));
			auto keywords = allMemorySizes[static_cast<std::int32_t>(instruction.GetMemorySize())];
			output->AppendNotNull(keywords);
		}
		auto codeSize = instruction.GetCodeSize();
		auto segOverride = instruction.GetSegmentPrefix();
		bool noTrackPrefix = segOverride == Register::DS && FormatterUtils::IsNotrackPrefixBranch(instruction.GetCode()) && !((codeSize == CodeSize::Code16 || codeSize == CodeSize::Code32) && (baseReg == Register::BP || baseReg == Register::EBP || baseReg == Register::ESP));
		if (options->GetAlwaysShowSegmentRegister() || (segOverride != Register::None && !noTrackPrefix && (ShowUselessPrefixes || FormatterUtils::ShowSegmentPrefix(Register::None, instruction, ShowUselessPrefixes))))
		{
			FormatRegister(output, segReg);
			output->Append(':');
		}
		output->Append('[');
		bool needPlus = false;
		if (baseReg != Register::None)
		{
			FormatRegister(output, baseReg);
			needPlus = true;
		}
		if (indexReg != Register::None)
		{
			if (needPlus)
			{
				output->Append('+');
			}
			needPlus = true;
			FormatRegister(output, indexReg);
			if (useScale)
			{
				output->AppendNotNull(scaleNumbers[scale]);
			}
		}
		if (useSymbol)
		{
			if (needPlus)
			{
				if ((symbol.Flags & SymbolFlags::Signed) != 0)
				{
					output->Append('-');
				}
				else
				{
					output->Append('+');
				}
			}
			else if ((symbol.Flags & SymbolFlags::Signed) != 0)
			{
				output->Append('-');
			}
			WriteSymbol(output, absAddr, symbol, false);
		}
		else if (!needPlus || (displSize != 0 && displ != 0))
		{
			if (needPlus)
			{
				if (addrSize == 8)
				{
					if (displ < 0)
					{
						displ = -displ;
						output->Append('-');
					}
					else
					{
						output->Append('+');
					}
				}
				else if (addrSize == 4)
				{
					if (static_cast<std::int32_t>(displ) < 0)
					{
						displ = static_cast<std::uint32_t>(-static_cast<std::int32_t>(displ));
						output->Append('-');
					}
					else
					{
						output->Append('+');
					}
				}
				else
				{
					assert(addrSize == 2);
					if (static_cast<std::int16_t>(displ) < 0)
					{
						displ = static_cast<std::uint16_t>(-static_cast<std::int16_t>(displ));
						output->Append('-');
					}
					else
					{
						output->Append('+');
					}
				}
			}
			FormatNumber(output, static_cast<std::uint64_t>(displ));
		}
		output->Append(']');
		if (instruction.IsMvexEvictionHint())
		{
			output->AppendNotNull("{eh}");
		}
	}
}
