// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "InstrInfo.h"
#include "../Static.h"
#include "MemorySizes.h"
#include "../OpKind.g.h"
#include "../FormatterInternal/MnemonicCC.h"
#include "Registers.h"
#include "../RoundingControl.g.h"
#include "../FormatterInternal/FormatterUtils.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::GasFormatterInternal
{

	Iced::Intel::Register InstrOpInfo::GetOpRegister(std::int32_t operand) const
	{
		auto switchTempVar_0 = operand;

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_0 == 0) ? (Register)Op0Register : (switchTempVar_0 == 1) ? (Register)Op1Register : (switchTempVar_0 == 2) ? (Register)Op2Register : (switchTempVar_0 == 3) ? (Register)Op3Register : (switchTempVar_0 == 4) ? (Register)Op4Register : throw new ArgumentOutOfRangeException(nameof(operand));
		return (switchTempVar_0 == 0) ? static_cast<Register>(Op0Register) : (switchTempVar_0 == 1) ? static_cast<Register>(Op1Register) : (switchTempVar_0 == 2) ? static_cast<Register>(Op2Register) : (switchTempVar_0 == 3) ? static_cast<Register>(Op3Register) : (switchTempVar_0 == 4) ? static_cast<Register>(Op4Register) : throw std::out_of_range("operand");
	}

	InstrOpKind InstrOpInfo::GetOpKind(std::int32_t operand) const
	{
		switch (operand)
		{
		case 0:
			return Op0Kind;
		case 1:
			return Op1Kind;
		case 2:
			return Op2Kind;
		case 3:
			return Op3Kind;
		case 4:
			return Op4Kind;
		default:
			assert(Op0Kind == InstrOpKind::DeclareByte || Op0Kind == InstrOpKind::DeclareWord || Op0Kind == InstrOpKind::DeclareDword || Op0Kind == InstrOpKind::DeclareQword);
			return Op0Kind;
		}
	}

	std::int32_t InstrOpInfo::GetInstructionIndex(std::int32_t operand) const
	{
		std::int32_t instructionOperand;
		switch (operand)
		{
		case 0:
			instructionOperand = Op0Index;
			break;
		case 1:
			instructionOperand = Op1Index;
			break;
		case 2:
			instructionOperand = Op2Index;
			break;
		case 3:
			instructionOperand = Op3Index;
			break;
		case 4:
			instructionOperand = Op4Index;
			break;
		default:
			assert(Op0Kind == InstrOpKind::DeclareByte || Op0Kind == InstrOpKind::DeclareWord || Op0Kind == InstrOpKind::DeclareDword || Op0Kind == InstrOpKind::DeclareQword);
			instructionOperand = -1;
			break;
		}
		return instructionOperand < 0 ? -1 : instructionOperand;
	}

	bool InstrOpInfo::TryGetOpAccess(std::int32_t operand, OpAccess& access)
	{
		std::int32_t instructionOperand;
		switch (operand)
		{
		case 0:
			instructionOperand = Op0Index;
			break;
		case 1:
			instructionOperand = Op1Index;
			break;
		case 2:
			instructionOperand = Op2Index;
			break;
		case 3:
			instructionOperand = Op3Index;
			break;
		case 4:
			instructionOperand = Op4Index;
			break;
		default:
			assert(Op0Kind == InstrOpKind::DeclareByte || Op0Kind == InstrOpKind::DeclareWord || Op0Kind == InstrOpKind::DeclareDword || Op0Kind == InstrOpKind::DeclareQword);
			instructionOperand = Op0Index;
			break;
		}
		if (instructionOperand < InstrInfo::OpAccess_INVALID)
		{
			access = static_cast<OpAccess>(-instructionOperand - 2);
			return true;
		}
		access = OpAccess::None;
		return false;
	}

	std::int32_t InstrOpInfo::GetOperandIndex(std::int32_t instructionOperand) const
	{
		std::int32_t index;
		if (instructionOperand == Op0Index)
		{
			index = 0;
		}
		else if (instructionOperand == Op1Index)
		{
			index = 1;
		}
		else if (instructionOperand == Op2Index)
		{
			index = 2;
		}
		else if (instructionOperand == Op3Index)
		{
			index = 3;
		}
		else if (instructionOperand == Op4Index)
		{
			index = 4;
		}
		else
		{
			index = -1;
		}
		return index < OpCount ? index : -1;
	}

	InstrOpInfo::InstrOpInfo(FormatterString mnemonic, const Instruction& instruction, InstrOpInfoFlags flags)
	{
		Static::Assert(IcedConstants::MaxOpCount == 5 ? 0 : -1);
		Mnemonic = mnemonic;
		Flags = flags;
		std::int32_t opCount = instruction.GetOpCount();
		OpCount = static_cast<std::uint8_t>(opCount);
		if ((flags & InstrOpInfoFlags::KeepOperandOrder) != 0)
		{
			Op0Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
			Op1Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
			Op2Kind = static_cast<InstrOpKind>(instruction.GetOp2Kind());
			Op3Kind = static_cast<InstrOpKind>(instruction.GetOp3Kind());
			Op4Kind = static_cast<InstrOpKind>(instruction.GetOp4Kind());
			Op0Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
			Op1Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
			Op2Register = static_cast<std::uint8_t>(instruction.GetOp2Register());
			Op3Register = static_cast<std::uint8_t>(instruction.GetOp3Register());
			Op4Register = static_cast<std::uint8_t>(instruction.GetOp4Register());
		}
		else
		{
			switch (opCount)
			{
			case 0:
				Op0Kind = (InstrOpKind)0;
				Op1Kind = (InstrOpKind)0;
				Op2Kind = (InstrOpKind)0;
				Op3Kind = (InstrOpKind)0;
				Op4Kind = (InstrOpKind)0;
				Op0Register = 0;
				Op1Register = 0;
				Op2Register = 0;
				Op3Register = 0;
				Op4Register = 0;
				break;
			case 1:
				Op0Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
				Op1Kind = (InstrOpKind)0;
				Op2Kind = (InstrOpKind)0;
				Op3Kind = (InstrOpKind)0;
				Op4Kind = (InstrOpKind)0;
				Op0Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
				Op1Register = 0;
				Op2Register = 0;
				Op3Register = 0;
				Op4Register = 0;
				break;
			case 2:
				Op0Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
				Op1Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
				Op2Kind = (InstrOpKind)0;
				Op3Kind = (InstrOpKind)0;
				Op4Kind = (InstrOpKind)0;
				Op0Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
				Op1Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
				Op2Register = 0;
				Op3Register = 0;
				Op4Register = 0;
				break;
			case 3:
				Op0Kind = static_cast<InstrOpKind>(instruction.GetOp2Kind());
				Op1Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
				Op2Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
				Op3Kind = (InstrOpKind)0;
				Op4Kind = (InstrOpKind)0;
				Op0Register = static_cast<std::uint8_t>(instruction.GetOp2Register());
				Op1Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
				Op2Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
				Op3Register = 0;
				Op4Register = 0;
				break;
			case 4:
				Op0Kind = static_cast<InstrOpKind>(instruction.GetOp3Kind());
				Op1Kind = static_cast<InstrOpKind>(instruction.GetOp2Kind());
				Op2Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
				Op3Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
				Op4Kind = (InstrOpKind)0;
				Op0Register = static_cast<std::uint8_t>(instruction.GetOp3Register());
				Op1Register = static_cast<std::uint8_t>(instruction.GetOp2Register());
				Op2Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
				Op3Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
				Op4Register = 0;
				break;
			case 5:
				Op0Kind = static_cast<InstrOpKind>(instruction.GetOp4Kind());
				Op1Kind = static_cast<InstrOpKind>(instruction.GetOp3Kind());
				Op2Kind = static_cast<InstrOpKind>(instruction.GetOp2Kind());
				Op3Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
				Op4Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
				Op0Register = static_cast<std::uint8_t>(instruction.GetOp4Register());
				Op1Register = static_cast<std::uint8_t>(instruction.GetOp3Register());
				Op2Register = static_cast<std::uint8_t>(instruction.GetOp2Register());
				Op3Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
				Op4Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
		}
		switch (OpCount)
		{
		case 0:
			Op0Index = InstrInfo::OpAccess_INVALID;
			Op1Index = InstrInfo::OpAccess_INVALID;
			Op2Index = InstrInfo::OpAccess_INVALID;
			Op3Index = InstrInfo::OpAccess_INVALID;
			Op4Index = InstrInfo::OpAccess_INVALID;
			break;
		case 1:
			Op0Index = 0;
			Op1Index = InstrInfo::OpAccess_INVALID;
			Op2Index = InstrInfo::OpAccess_INVALID;
			Op3Index = InstrInfo::OpAccess_INVALID;
			Op4Index = InstrInfo::OpAccess_INVALID;
			break;
		case 2:
			Op0Index = 1;
			Op1Index = 0;
			Op2Index = InstrInfo::OpAccess_INVALID;
			Op3Index = InstrInfo::OpAccess_INVALID;
			Op4Index = InstrInfo::OpAccess_INVALID;
			break;
		case 3:
			Op0Index = 2;
			Op1Index = 1;
			Op2Index = 0;
			Op3Index = InstrInfo::OpAccess_INVALID;
			Op4Index = InstrInfo::OpAccess_INVALID;
			break;
		case 4:
			Op0Index = 3;
			Op1Index = 2;
			Op2Index = 1;
			Op3Index = 0;
			Op4Index = InstrInfo::OpAccess_INVALID;
			break;
		case 5:
			Op0Index = 4;
			Op1Index = 3;
			Op2Index = 2;
			Op3Index = 1;
			Op4Index = 0;
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
	}

	std::int32_t InstrInfo::GetBitness(CodeSize codeSize)
	{
		auto switchTempVar_1 = codeSize;

		return (switchTempVar_1 == CodeSize::Code16) ? static_cast<std::uint8_t>(16) : (switchTempVar_1 == CodeSize::Code32) ? static_cast<std::uint8_t>(32) : (switchTempVar_1 == CodeSize::Code64) ? static_cast<std::uint8_t>(64) : static_cast<std::uint8_t>(0);
	}

	FormatterString InstrInfo::GetMnemonic(const FormatterOptions& options, const Instruction& instruction, FormatterString mnemonic, FormatterString mnemonic_suffix, InstrOpInfoFlags flags)
	{
		if (options.GetGasShowMnemonicSizeSuffix())
		{
			return mnemonic_suffix;
		}
		if ((flags & InstrOpInfoFlags::MnemonicSuffixIfMem) != 0 && MemorySizes::AllMemorySizes[static_cast<std::int32_t>(instruction.GetMemorySize())].GetLength() == 0)
		{
			if (instruction.GetOp0Kind() == OpKind::Memory || instruction.GetOp1Kind() == OpKind::Memory || instruction.GetOp2Kind() == OpKind::Memory)
			{
				return mnemonic_suffix;
			}
		}
		return mnemonic;
	}

	SimpleInstrInfo::SimpleInstrInfo(const std::string& mnemonic) : SimpleInstrInfo(mnemonic, mnemonic, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo::SimpleInstrInfo(const std::string& mnemonic, InstrOpInfoFlags flags) : SimpleInstrInfo(mnemonic, mnemonic, flags)
	{
	}

	SimpleInstrInfo::SimpleInstrInfo(const std::string& mnemonic, const std::string& mnemonic_suffix) : SimpleInstrInfo(mnemonic, mnemonic_suffix, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo::SimpleInstrInfo(const std::string& mnemonic, const std::string& mnemonic_suffix, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
		this->flags = flags;
	}

	void SimpleInstrInfo::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic_suffix, flags), instruction, flags);
	}

	SimpleInstrInfo_cc::SimpleInstrInfo_cc(std::int32_t ccIndex, const std::vector<std::string>& mnemonics, const std::vector<std::string>& mnemonics_suffix)
	{
		this->ccIndex = ccIndex;
		this->mnemonics = FormatterString::Create(mnemonics);
		this->mnemonics_suffix = FormatterString::Create(mnemonics_suffix);
	}

	void SimpleInstrInfo_cc::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = InstrOpInfoFlags::None;
		auto mnemonic = MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		auto mnemonic_suffix = MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics_suffix);
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic_suffix, flags), instruction, flags);
	}

	SimpleInstrInfo_AamAad::SimpleInstrInfo_AamAad(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_AamAad::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		if (instruction.GetImmediate8() == 10)
		{
			info = InstrOpInfo();
			info.Mnemonic = mnemonic;
		}
		else
		{
			info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		}
	}

	SimpleInstrInfo_nop::SimpleInstrInfo_nop(std::int32_t bitness, const std::string& mnemonic, Register register_)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->register_ = register_;
	}

	FormatterString SimpleInstrInfo_nop::str_xchg = FormatterString("xchg");
	FormatterString SimpleInstrInfo_nop::str_xchgw = FormatterString("xchgw");
	FormatterString SimpleInstrInfo_nop::str_xchgl = FormatterString("xchgl");
	FormatterString SimpleInstrInfo_nop::str_xchgq = FormatterString("xchgq");

	void SimpleInstrInfo_nop::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		if (instrBitness == 0 || (instrBitness & bitness) != 0)
		{
			info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		}
		else
		{
			info = InstrOpInfo();
			if (!options.GetGasShowMnemonicSizeSuffix())
			{
				info.Mnemonic = str_xchg;
			}
			else if (register_ == Register::AX)
			{
				info.Mnemonic = str_xchgw;
			}
			else if (register_ == Register::EAX)
			{
				info.Mnemonic = str_xchgl;
			}
			else if (register_ == Register::RAX)
			{
				info.Mnemonic = str_xchgq;
			}
			else
			{
				throw std::runtime_error("invalid operation");
			}
			info.OpCount = 2;
			Static::Assert(InstrOpKind::Register == (InstrOpKind)0 ? 0 : -1);
			//info.Op0Kind = InstrOpKind.Register;
			//info.Op1Kind = InstrOpKind.Register;
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(register_);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(register_);
			info.Op0Index = OpAccess_None;
			info.Op1Index = OpAccess_None;
		}
	}

	SimpleInstrInfo_STIG1::SimpleInstrInfo_STIG1(const std::string& mnemonic, bool pseudoOp)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudoOp = pseudoOp;
	}

	void SimpleInstrInfo_STIG1::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		assert(instruction.GetOpCount() == 2);
		assert(instruction.GetOp0Kind() == OpKind::Register && instruction.GetOp0Register() == Register::ST0);
		if (!pseudoOp || !(options.GetUsePseudoOps() && instruction.GetOp1Register() == Register::ST1))
		{
			info.OpCount = 1;
			Static::Assert(InstrOpKind::Register == (InstrOpKind)0 ? 0 : -1);
			//info.Op0Kind = InstrOpKind.Register;
			info.Op0Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
			info.Op0Index = 1;
		}
	}

	SimpleInstrInfo_STi_ST::SimpleInstrInfo_STi_ST(const std::string& mnemonic, bool pseudoOp)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudoOp = pseudoOp;
	}

	void SimpleInstrInfo_STi_ST::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = (InstrOpInfoFlags)0;
		if (pseudoOp && options.GetUsePseudoOps() && (instruction.GetOp0Register() == Register::ST1 || instruction.GetOp1Register() == Register::ST1))
		{
			info = InstrOpInfo();
			info.Mnemonic = mnemonic;
		}
		else
		{
			info = InstrOpInfo(mnemonic, instruction, flags);
			assert(info.Op0Register == static_cast<std::int32_t>(Register::ST0));
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Registers::Register_ST);
		}
	}

	SimpleInstrInfo_ST_STi::SimpleInstrInfo_ST_STi(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_ST_STi::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		assert(info.Op1Register == static_cast<std::int32_t>(Register::ST0));
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op1Register = static_cast<std::uint8_t>(Registers::Register_ST);
	}

	SimpleInstrInfo_as::SimpleInstrInfo_as(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_as::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		InstrOpInfoFlags flags = (InstrOpInfoFlags)0;
		auto instrBitness = GetBitness(instruction.GetCodeSize());
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				flags |= InstrOpInfoFlags::AddrSize16;
			}
			else if (bitness == 32)
			{
				flags |= InstrOpInfoFlags::AddrSize32;
			}
			else
			{
				flags |= InstrOpInfoFlags::AddrSize64;
			}
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_maskmovq::SimpleInstrInfo_maskmovq(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_maskmovq::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		assert(instruction.GetOpCount() == 3);
		auto instrBitness = GetBitness(instruction.GetCodeSize());
		auto switchTempVar_2 = instruction.GetOp0Kind();


		std::int32_t bitness = (switchTempVar_2 == OpKind::MemorySegDI) ? static_cast<std::uint8_t>(16) : (switchTempVar_2 == OpKind::MemorySegEDI) ? static_cast<std::uint8_t>(32) : (switchTempVar_2 == OpKind::MemorySegRDI) ? static_cast<std::uint8_t>(64) : instrBitness;
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 2;
		info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp2Kind());
		info.Op0Register = static_cast<std::uint8_t>(instruction.GetOp2Register());
		info.Op0Index = 2;
		info.Op1Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
		info.Op1Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
		info.Op1Index = 1;
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				info.Flags |= InstrOpInfoFlags::AddrSize16;
			}
			else if (bitness == 32)
			{
				info.Flags |= InstrOpInfoFlags::AddrSize32;
			}
			else
			{
				info.Flags |= InstrOpInfoFlags::AddrSize64;
			}
		}
	}

	SimpleInstrInfo_pblendvb::SimpleInstrInfo_pblendvb(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_pblendvb::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		assert(instruction.GetOpCount() == 2);
		info.Mnemonic = mnemonic;
		info.OpCount = 3;
		Static::Assert(InstrOpKind::Register == (InstrOpKind)0 ? 0 : -1);
		//info.Op0Kind = InstrOpKind.Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(Register::XMM0);
		info.Op0Index = OpAccess_Read;
		info.Op1Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
		info.Op1Index = 1;
		info.Op1Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
		info.Op2Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
		info.Op2Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
	}

	SimpleInstrInfo_OpSize::SimpleInstrInfo_OpSize(CodeSize codeSize, const std::string& mnemonic, const std::string& mnemonic16, const std::string& mnemonic32, const std::string& mnemonic64)
	{
		this->codeSize = codeSize;
		mnemonics = std::vector<FormatterString>(4);
		mnemonics[static_cast<std::int32_t>(CodeSize::Unknown)] = FormatterString(mnemonic);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code16)] = FormatterString(mnemonic16);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code32)] = FormatterString(mnemonic32);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code64)] = FormatterString(mnemonic64);
	}

	void SimpleInstrInfo_OpSize::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		FormatterString mnemonic;
		if (instruction.GetCodeSize() == codeSize && !options.GetGasShowMnemonicSizeSuffix())
		{
			mnemonic = mnemonics[static_cast<std::int32_t>(CodeSize::Unknown)];
		}
		else
		{
			mnemonic = mnemonics[static_cast<std::int32_t>(codeSize)];
		}
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
	}

	SimpleInstrInfo_OpSize2_bnd::SimpleInstrInfo_OpSize2_bnd(const std::string& mnemonic, const std::string& mnemonic16, const std::string& mnemonic32, const std::string& mnemonic64)
	{
		mnemonics = std::vector<FormatterString>(4);
		mnemonics[static_cast<std::int32_t>(CodeSize::Unknown)] = FormatterString(mnemonic);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code16)] = FormatterString(mnemonic16);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code32)] = FormatterString(mnemonic32);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code64)] = FormatterString(mnemonic64);
	}

	void SimpleInstrInfo_OpSize2_bnd::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		if (instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		std::int32_t codeSize = static_cast<std::int32_t>(instruction.GetCodeSize());
		if (options.GetGasShowMnemonicSizeSuffix())
		{
			codeSize = static_cast<std::int32_t>(CodeSize::Code64);
		}
		auto mnemonic = mnemonics[codeSize];
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_OpSize3::SimpleInstrInfo_OpSize3(std::int32_t bitness, const std::string& mnemonic, const std::string& mnemonic_suffix)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
	}

	void SimpleInstrInfo_OpSize3::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto instrBitness = GetBitness(instruction.GetCodeSize());
		FormatterString mnemonic;
		if (!options.GetGasShowMnemonicSizeSuffix() && (instrBitness == 0 || (instrBitness & bitness) != 0))
		{
			mnemonic = this->mnemonic;
		}
		else
		{
			mnemonic = mnemonic_suffix;
		}
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
	}

	SimpleInstrInfo_os2::SimpleInstrInfo_os2(std::int32_t bitness, const std::string& mnemonic, const std::string& mnemonic_suffix, bool canUseBnd, InstrOpInfoFlags flags)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
		this->canUseBnd = canUseBnd;
		this->flags = flags;
	}

	void SimpleInstrInfo_os2::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = this->flags;
		if (canUseBnd && instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		FormatterString mnemonic;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		if (instrBitness != 0 && instrBitness != bitness)
		{
			mnemonic = mnemonic_suffix;
		}
		else
		{
			mnemonic = GetMnemonic(options, instruction, this->mnemonic, mnemonic_suffix, flags);
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_os::SimpleInstrInfo_os(std::int32_t bitness, const std::string& mnemonic, bool canUseBnd, InstrOpInfoFlags flags)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->canUseBnd = canUseBnd;
		this->flags = flags;
	}

	void SimpleInstrInfo_os::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = this->flags;
		if (canUseBnd && instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				flags |= InstrOpInfoFlags::OpSize16;
			}
			else if (bitness == 32)
			{
				flags |= InstrOpInfoFlags::OpSize32;
			}
			else
			{
				flags |= InstrOpInfoFlags::OpSize64;
			}
		}
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic, flags), instruction, flags);
	}

	SimpleInstrInfo_os_mem::SimpleInstrInfo_os_mem(std::int32_t bitness, const std::string& mnemonic, const std::string& mnemonic_suffix)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
	}

	void SimpleInstrInfo_os_mem::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		bool hasMemOp = instruction.GetOp0Kind() == OpKind::Memory || instruction.GetOp1Kind() == OpKind::Memory;
		if (hasMemOp && !(instrBitness == 0 || (instrBitness != 64 && instrBitness == bitness) || (instrBitness == 64 && bitness == 32)))
		{
			if (bitness == 16)
			{
				flags |= InstrOpInfoFlags::OpSize16;
			}
			else if (bitness == 32)
			{
				flags |= InstrOpInfoFlags::OpSize32;
			}
			else
			{
				flags |= InstrOpInfoFlags::OpSize64;
			}
		}
		auto mnemonic = hasMemOp ? this->mnemonic : GetMnemonic(options, instruction, this->mnemonic, mnemonic_suffix, flags);
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_os_mem2::SimpleInstrInfo_os_mem2(std::int32_t bitness, const std::string& mnemonic, const std::string& mnemonic_suffix)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
	}

	void SimpleInstrInfo_os_mem2::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		FormatterString mnemonic;
		if (instrBitness != 0 && (instrBitness & bitness) == 0)
		{
			mnemonic = mnemonic_suffix;
		}
		else
		{
			mnemonic = GetMnemonic(options, instruction, this->mnemonic, mnemonic_suffix, flags);
		}
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
	}

	SimpleInstrInfo_Reg16::SimpleInstrInfo_Reg16(const std::string& mnemonic, const std::string& mnemonic_suffix)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
	}

	void SimpleInstrInfo_Reg16::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic_suffix, flags), instruction, flags);
		if (Register::EAX <= static_cast<Register>(info.Op0Register) && static_cast<Register>(info.Op0Register) <= Register::R15)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(((static_cast<Register>(info.Op0Register) - Register::EAX) & 0xF) + Register::AX);
		}
		if (Register::EAX <= static_cast<Register>(info.Op1Register) && static_cast<Register>(info.Op1Register) <= Register::R15)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(((static_cast<Register>(info.Op1Register) - Register::EAX) & 0xF) + Register::AX);
		}
		if (Register::EAX <= static_cast<Register>(info.Op2Register) && static_cast<Register>(info.Op2Register) <= Register::R15)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op2Register = static_cast<std::uint8_t>(((static_cast<Register>(info.Op2Register) - Register::EAX) & 0xF) + Register::AX);
		}
	}

	SimpleInstrInfo_mem16::SimpleInstrInfo_mem16(const std::string& mnemonic, const std::string& mnemonic_reg_suffix, const std::string& mnemonic_mem_suffix)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_reg_suffix = FormatterString(mnemonic_reg_suffix);
		this->mnemonic_mem_suffix = FormatterString(mnemonic_mem_suffix);
	}

	void SimpleInstrInfo_mem16::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = InstrOpInfoFlags::None;
		FormatterString mnemonic_suffix;
		if (instruction.GetOp0Kind() == OpKind::Memory || instruction.GetOp1Kind() == OpKind::Memory)
		{
			mnemonic_suffix = mnemonic_mem_suffix;
		}
		else
		{
			mnemonic_suffix = mnemonic_reg_suffix;
		}
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic_suffix, flags), instruction, flags);
	}

	SimpleInstrInfo_os_loop::SimpleInstrInfo_os_loop(std::int32_t bitness, std::int32_t regSize, std::int32_t ccIndex, const std::vector<std::string>& mnemonics, const std::vector<std::string>& mnemonics_suffix)
	{
		this->bitness = bitness;
		this->regSize = regSize;
		this->ccIndex = ccIndex;
		this->mnemonics = FormatterString::Create(mnemonics);
		this->mnemonics_suffix = FormatterString::Create(mnemonics_suffix);
	}

	void SimpleInstrInfo_os_loop::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		auto mnemonics = this->mnemonics;
		if ((instrBitness != 0 && instrBitness != regSize) || options.GetGasShowMnemonicSizeSuffix())
		{
			mnemonics = mnemonics_suffix;
		}
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				flags |= InstrOpInfoFlags::OpSize16 | InstrOpInfoFlags::OpSizeIsByteDirective;
			}
			else if (bitness == 32)
			{
				flags |= InstrOpInfoFlags::OpSize32 | InstrOpInfoFlags::OpSizeIsByteDirective;
			}
			else
			{
				flags |= InstrOpInfoFlags::OpSize64;
			}
		}
		auto mnemonic = ccIndex == -1 ? mnemonics[0] : MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_os_jcc::SimpleInstrInfo_os_jcc(std::int32_t bitness, std::int32_t ccIndex, const std::vector<std::string>& mnemonics)
	{
		this->bitness = bitness;
		this->ccIndex = ccIndex;
		this->mnemonics = FormatterString::Create(mnemonics);
	}

	void SimpleInstrInfo_os_jcc::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				flags |= InstrOpInfoFlags::OpSize16;
			}
			else if (bitness == 32)
			{
				flags |= InstrOpInfoFlags::OpSize32;
			}
			else
			{
				flags |= InstrOpInfoFlags::OpSize64;
			}
		}
		auto prefixSeg = instruction.GetSegmentPrefix();
		if (prefixSeg == Register::CS)
		{
			flags |= InstrOpInfoFlags::JccNotTaken;
		}
		else if (prefixSeg == Register::DS)
		{
			flags |= InstrOpInfoFlags::JccTaken;
		}
		if (instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		auto mnemonic = MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic, flags), instruction, flags);
	}

	SimpleInstrInfo_movabs::SimpleInstrInfo_movabs(const std::string& mnemonic, const std::string& mnemonic_suffix, const std::string& mnemonic64, const std::string& mnemonic_suffix64)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
		this->mnemonic64 = FormatterString(mnemonic64);
		this->mnemonic_suffix64 = FormatterString(mnemonic_suffix64);
	}

	void SimpleInstrInfo_movabs::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		std::int32_t memSize;
		FormatterString mnemonic, mnemonic_suffix;
		switch (instruction.GetMemoryDisplSize())
		{
		case 2:
			mnemonic = this->mnemonic;
			mnemonic_suffix = this->mnemonic_suffix;
			memSize = 16;
			break;
		case 4:
			mnemonic = this->mnemonic;
			mnemonic_suffix = this->mnemonic_suffix;
			memSize = 32;
			break;
		default:
			mnemonic = mnemonic64;
			mnemonic_suffix = mnemonic_suffix64;
			memSize = 64;
			break;
		}
		if (instrBitness == 0)
		{
			instrBitness = memSize;
		}
		if (instrBitness == 64)
		{
			if (memSize == 32)
			{
				flags |= InstrOpInfoFlags::AddrSize32;
			}
		}
		else if (instrBitness != memSize)
		{
			assert(memSize == 16 || memSize == 32);
			if (memSize == 16)
			{
				flags |= InstrOpInfoFlags::AddrSize16;
			}
			else
			{
				flags |= InstrOpInfoFlags::AddrSize32;
			}
		}
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic_suffix, flags), instruction, flags);
	}

	SimpleInstrInfo_er::SimpleInstrInfo_er(std::int32_t erIndex, const std::string& mnemonic) : SimpleInstrInfo_er(erIndex, mnemonic, mnemonic, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo_er::SimpleInstrInfo_er(std::int32_t erIndex, const std::string& mnemonic, const std::string& mnemonic_suffix, InstrOpInfoFlags flags)
	{
		this->erIndex = erIndex;
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
		this->flags = flags;
	}

	void SimpleInstrInfo_er::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic_suffix, flags), instruction, flags);
		if (IcedConstants::IsMvex(instruction.GetCode()))
		{
			auto rc = instruction.GetRoundingControl();
			if (rc != RoundingControl::None)
			{
				InstrOpKind rcOpKind;
				if (instruction.GetSuppressAllExceptions())
				{
					switch (rc)
					{
					case RoundingControl::RoundToNearest:
						rcOpKind = InstrOpKind::RnSae;
						break;
					case RoundingControl::RoundDown:
						rcOpKind = InstrOpKind::RdSae;
						break;
					case RoundingControl::RoundUp:
						rcOpKind = InstrOpKind::RuSae;
						break;
					case RoundingControl::RoundTowardZero:
						rcOpKind = InstrOpKind::RzSae;
						break;
					default:
						return;
					}
				}
				else
				{
					switch (rc)
					{
					case RoundingControl::RoundToNearest:
						rcOpKind = InstrOpKind::Rn;
						break;
					case RoundingControl::RoundDown:
						rcOpKind = InstrOpKind::Rd;
						break;
					case RoundingControl::RoundUp:
						rcOpKind = InstrOpKind::Ru;
						break;
					case RoundingControl::RoundTowardZero:
						rcOpKind = InstrOpKind::Rz;
						break;
					default:
						return;
					}
				}
				MoveOperands(info, erIndex, rcOpKind);
			}
			else if (instruction.GetSuppressAllExceptions())
			{
				SimpleInstrInfo_er::MoveOperands(info, erIndex, InstrOpKind::Sae);
			}
		}
		else
		{
			auto rc = instruction.GetRoundingControl();
			if (rc != RoundingControl::None)
			{
				if (!FormatterUtils::CanShowRoundingControl(instruction, options))
				{
					return;
				}
				InstrOpKind rcOpKind;
				switch (rc)
				{
				case RoundingControl::RoundToNearest:
					rcOpKind = InstrOpKind::RnSae;
					break;
				case RoundingControl::RoundDown:
					rcOpKind = InstrOpKind::RdSae;
					break;
				case RoundingControl::RoundUp:
					rcOpKind = InstrOpKind::RuSae;
					break;
				case RoundingControl::RoundTowardZero:
					rcOpKind = InstrOpKind::RzSae;
					break;
				default:
					return;
				}
				MoveOperands(info, erIndex, rcOpKind);
			}
		}
	}

	void SimpleInstrInfo_er::MoveOperands(InstrOpInfo& info, std::int32_t index, InstrOpKind newOpKind)
	{
		assert(info.OpCount <= 4);
		switch (index)
		{
		case 0:
			info.Op4Kind = info.Op3Kind;
			info.Op4Register = info.Op3Register;
			info.Op3Kind = info.Op2Kind;
			info.Op3Register = info.Op2Register;
			info.Op2Kind = info.Op1Kind;
			info.Op2Register = info.Op1Register;
			info.Op1Kind = info.Op0Kind;
			info.Op1Register = info.Op0Register;
			info.Op0Kind = newOpKind;
			info.Op4Index = info.Op3Index;
			info.Op3Index = info.Op2Index;
			info.Op2Index = info.Op1Index;
			info.Op1Index = info.Op0Index;
			info.Op0Index = OpAccess_None;
			info.OpCount++;
			break;
		case 1:
			info.Op4Kind = info.Op3Kind;
			info.Op4Register = info.Op3Register;
			info.Op3Kind = info.Op2Kind;
			info.Op3Register = info.Op2Register;
			info.Op2Kind = info.Op1Kind;
			info.Op2Register = info.Op1Register;
			info.Op1Kind = newOpKind;
			info.Op4Index = info.Op3Index;
			info.Op3Index = info.Op2Index;
			info.Op2Index = info.Op1Index;
			info.Op1Index = OpAccess_None;
			info.OpCount++;
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
	}

	SimpleInstrInfo_sae::SimpleInstrInfo_sae(std::int32_t saeIndex, const std::string& mnemonic)
	{
		this->saeIndex = saeIndex;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_sae::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		if (instruction.GetSuppressAllExceptions())
		{
			SimpleInstrInfo_er::MoveOperands(info, saeIndex, InstrOpKind::Sae);
		}
	}

	SimpleInstrInfo_far::SimpleInstrInfo_far(std::int32_t bitness, const std::string& mnemonic, const std::string& mnemonic_suffix)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
	}

	void SimpleInstrInfo_far::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::IndirectOperand;
		auto instrBitness = GetBitness(instruction.GetCodeSize());
		FormatterString mnemonic;
		if (instrBitness == 0)
		{
			instrBitness = bitness;
		}
		if (bitness == 64)
		{
			flags |= InstrOpInfoFlags::OpSize64;
			assert(this->mnemonic.Get(false) == mnemonic_suffix.Get(false));
			mnemonic = this->mnemonic;
		}
		else
		{
			if (bitness != instrBitness || options.GetGasShowMnemonicSizeSuffix())
			{
				mnemonic = mnemonic_suffix;
			}
			else
			{
				mnemonic = this->mnemonic;
			}
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_bnd::SimpleInstrInfo_bnd(const std::string& mnemonic, const std::string& mnemonic_suffix, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
		this->flags = flags;
	}

	void SimpleInstrInfo_bnd::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = this->flags;
		if (instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic_suffix, flags), instruction, flags);
	}

	SimpleInstrInfo_pops::SimpleInstrInfo_pops(const std::string& mnemonic, const std::vector<FormatterString>& pseudo_ops, bool canUseSae)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudo_ops = pseudo_ops;
		this->canUseSae = canUseSae;
	}

	void SimpleInstrInfo_pops::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		if (canUseSae && instruction.GetSuppressAllExceptions())
		{
			SimpleInstrInfo_er::MoveOperands(info, 1, InstrOpKind::Sae);
		}
		std::int32_t imm = instruction.GetImmediate8();
		if (options.GetUsePseudoOps() && static_cast<std::uint32_t>(imm) < static_cast<std::uint32_t>(pseudo_ops.size()))
		{
			RemoveFirstImm8Operand(info);
			info.Mnemonic = pseudo_ops[imm];
		}
	}

	void SimpleInstrInfo_pops::RemoveFirstImm8Operand(InstrOpInfo& info)
	{
		assert(info.Op0Kind == InstrOpKind::Immediate8);
		info.OpCount--;
		switch (info.OpCount)
		{
		case 0:
			info.Op0Index = OpAccess_INVALID;
			break;
		case 1:
			info.Op0Kind = info.Op1Kind;
			info.Op0Register = info.Op1Register;
			info.Op0Index = info.Op1Index;
			info.Op1Index = OpAccess_INVALID;
			break;
		case 2:
			info.Op0Kind = info.Op1Kind;
			info.Op0Register = info.Op1Register;
			info.Op1Kind = info.Op2Kind;
			info.Op1Register = info.Op2Register;
			info.Op0Index = info.Op1Index;
			info.Op1Index = info.Op2Index;
			info.Op2Index = OpAccess_INVALID;
			break;
		case 3:
			info.Op0Kind = info.Op1Kind;
			info.Op0Register = info.Op1Register;
			info.Op1Kind = info.Op2Kind;
			info.Op1Register = info.Op2Register;
			info.Op2Kind = info.Op3Kind;
			info.Op2Register = info.Op3Register;
			info.Op0Index = info.Op1Index;
			info.Op1Index = info.Op2Index;
			info.Op2Index = info.Op3Index;
			info.Op3Index = OpAccess_INVALID;
			break;
		case 4:
			info.Op0Kind = info.Op1Kind;
			info.Op0Register = info.Op1Register;
			info.Op1Kind = info.Op2Kind;
			info.Op1Register = info.Op2Register;
			info.Op2Kind = info.Op3Kind;
			info.Op2Register = info.Op3Register;
			info.Op3Kind = info.Op4Kind;
			info.Op3Register = info.Op4Register;
			info.Op0Index = info.Op1Index;
			info.Op1Index = info.Op2Index;
			info.Op2Index = info.Op3Index;
			info.Op3Index = info.Op4Index;
			info.Op4Index = OpAccess_INVALID;
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
	}

	SimpleInstrInfo_pclmulqdq::SimpleInstrInfo_pclmulqdq(const std::string& mnemonic, const std::vector<FormatterString>& pseudo_ops)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudo_ops = pseudo_ops;
	}

	void SimpleInstrInfo_pclmulqdq::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		if (options.GetUsePseudoOps())
		{
			std::int32_t index;
			std::int32_t imm = instruction.GetImmediate8();
			if (imm == 0)
			{
				index = 0;
			}
			else if (imm == 1)
			{
				index = 1;
			}
			else if (imm == 0x10)
			{
				index = 2;
			}
			else if (imm == 0x11)
			{
				index = 3;
			}
			else
			{
				index = -1;
			}
			if (index >= 0)
			{
				SimpleInstrInfo_pops::RemoveFirstImm8Operand(info);
				info.Mnemonic = pseudo_ops[index];
			}
		}
	}

	SimpleInstrInfo_imul::SimpleInstrInfo_imul(const std::string& mnemonic, const std::string& mnemonic_suffix)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic_suffix = FormatterString(mnemonic_suffix);
	}

	void SimpleInstrInfo_imul::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = (InstrOpInfoFlags)0;
		info = InstrOpInfo(GetMnemonic(options, instruction, mnemonic, mnemonic_suffix, flags), instruction, flags);
		assert(info.OpCount == 3);
		if (options.GetUsePseudoOps() && info.Op1Kind == InstrOpKind::Register && info.Op2Kind == InstrOpKind::Register && info.Op1Register == info.Op2Register)
		{
			info.OpCount--;
			info.Op1Index = OpAccess_ReadWrite;
			info.Op2Index = OpAccess_INVALID;
		}
	}

	SimpleInstrInfo_Reg32::SimpleInstrInfo_Reg32(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_Reg32::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = InstrOpInfoFlags::None;
		info = InstrOpInfo(mnemonic, instruction, flags);
		if (Register::RAX <= static_cast<Register>(info.Op0Register) && static_cast<Register>(info.Op0Register) <= Register::R15)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(static_cast<Register>(info.Op0Register) - Register::RAX + Register::EAX);
		}
		if (Register::RAX <= static_cast<Register>(info.Op1Register) && static_cast<Register>(info.Op1Register) <= Register::R15)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(static_cast<Register>(info.Op1Register) - Register::RAX + Register::EAX);
		}
		if (Register::RAX <= static_cast<Register>(info.Op2Register) && static_cast<Register>(info.Op2Register) <= Register::R15)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op2Register = static_cast<std::uint8_t>(static_cast<Register>(info.Op2Register) - Register::RAX + Register::EAX);
		}
	}

	SimpleInstrInfo_DeclareData::SimpleInstrInfo_DeclareData(Code code, const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
		auto switchTempVar_3 = code;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var opKind = (switchTempVar_3 == Code.DeclareByte) ? InstrOpKind.DeclareByte : (switchTempVar_3 == Code.DeclareWord) ? InstrOpKind.DeclareWord : (switchTempVar_3 == Code.DeclareDword) ? InstrOpKind.DeclareDword : (switchTempVar_3 == Code.DeclareQword) ? InstrOpKind.DeclareQword : throw new InvalidOperationException();
		auto opKind = (switchTempVar_3 == Code::DeclareByte) ? InstrOpKind::DeclareByte : (switchTempVar_3 == Code::DeclareWord) ? InstrOpKind::DeclareWord : (switchTempVar_3 == Code::DeclareDword) ? InstrOpKind::DeclareDword : (switchTempVar_3 == Code::DeclareQword) ? InstrOpKind::DeclareQword : throw std::runtime_error("invalid operation");
		this->opKind = opKind;
	}

	void SimpleInstrInfo_DeclareData::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::KeepOperandOrder | InstrOpInfoFlags::MnemonicIsDirective);
		info.OpCount = static_cast<std::uint8_t>(instruction.GetDeclareDataCount());
		info.Op0Kind = opKind;
		info.Op1Kind = opKind;
		info.Op2Kind = opKind;
		info.Op3Kind = opKind;
		info.Op4Kind = opKind;
		info.Op0Index = OpAccess_Read;
		info.Op1Index = OpAccess_Read;
		info.Op2Index = OpAccess_Read;
		info.Op3Index = OpAccess_Read;
		info.Op4Index = OpAccess_Read;
	}
}
