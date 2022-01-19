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

#include "InstrInfo.h"
#include "../Static.h"
#include "../FormatterInternal/MnemonicCC.h"
#include "Registers.h"
#include "../OpKind.g.h"
#include "../FormatterInternal/Iced.Intel.FormatterInternal.FormatterUtils.h"
#include "MemorySizes.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::IntelFormatterInternal
{

	Iced::Intel::Register InstrOpInfo::GetOpRegister(std::int32_t operand) const
	{
		auto switchTempVar_0 = operand;

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_0 == 0) ? (Register)Op0Register : (switchTempVar_0 == 1) ? (Register)Op1Register : (switchTempVar_0 == 2) ? (Register)Op2Register : (switchTempVar_0 == 3) ? (Register)Op3Register : (switchTempVar_0 == 4) ? (Register)Op4Register : throw new ArgumentOutOfRangeException(nameof(operand));
		return (switchTempVar_0 == 0) ? static_cast<Register>(Op0Register) : (switchTempVar_0 == 1) ? static_cast<Register>(Op1Register) : (switchTempVar_0 == 2) ? static_cast<Register>(Op2Register) : (switchTempVar_0 == 3) ? static_cast<Register>(Op3Register) : (switchTempVar_0 == 4) ? static_cast<Register>(Op4Register) : throw ArgumentOutOfRangeException("operand");
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
		Op0Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
		Op1Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
		Op2Kind = static_cast<InstrOpKind>(instruction.GetOp2Kind());
		Op3Kind = static_cast<InstrOpKind>(instruction.GetOp3Kind());
		Op4Kind = static_cast<InstrOpKind>(instruction.GetOp4Kind());
		Static::Assert(TEST_RegisterBits == 8 ? 0 : -1);
		Op0Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
		Static::Assert(TEST_RegisterBits == 8 ? 0 : -1);
		Op1Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
		Static::Assert(TEST_RegisterBits == 8 ? 0 : -1);
		Op2Register = static_cast<std::uint8_t>(instruction.GetOp2Register());
		Static::Assert(TEST_RegisterBits == 8 ? 0 : -1);
		Op3Register = static_cast<std::uint8_t>(instruction.GetOp3Register());
		Static::Assert(TEST_RegisterBits == 8 ? 0 : -1);
		Op4Register = static_cast<std::uint8_t>(instruction.GetOp4Register());
		std::int32_t opCount = instruction.GetOpCount();
		OpCount = static_cast<std::uint8_t>(opCount);
		switch (opCount)
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
			Op0Index = 0;
			Op1Index = 1;
			Op2Index = InstrInfo::OpAccess_INVALID;
			Op3Index = InstrInfo::OpAccess_INVALID;
			Op4Index = InstrInfo::OpAccess_INVALID;
			break;
		case 3:
			Op0Index = 0;
			Op1Index = 1;
			Op2Index = 2;
			Op3Index = InstrInfo::OpAccess_INVALID;
			Op4Index = InstrInfo::OpAccess_INVALID;
			break;
		case 4:
			Op0Index = 0;
			Op1Index = 1;
			Op2Index = 2;
			Op3Index = 3;
			Op4Index = InstrInfo::OpAccess_INVALID;
			break;
		case 5:
			Op0Index = 0;
			Op1Index = 1;
			Op2Index = 2;
			Op3Index = 3;
			Op4Index = 4;
			break;
		default:
			throw InvalidOperationException();
		}
	}

	std::int32_t InstrInfo::GetBitness(CodeSize codeSize)
	{
		auto switchTempVar_1 = codeSize;

		return (switchTempVar_1 == CodeSize::Code16) ? static_cast<std::uint8_t>(16) : (switchTempVar_1 == CodeSize::Code32) ? static_cast<std::uint8_t>(32) : (switchTempVar_1 == CodeSize::Code64) ? static_cast<std::uint8_t>(64) : static_cast<std::uint8_t>(0);
	}

	SimpleInstrInfo::SimpleInstrInfo(const std::string& mnemonic) : SimpleInstrInfo(mnemonic, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo::SimpleInstrInfo(const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_cc::SimpleInstrInfo_cc(std::int32_t ccIndex, const std::vector<std::string>& mnemonics)
	{
		this->ccIndex = ccIndex;
		this->mnemonics = FormatterString::Create(mnemonics);
	}

	void SimpleInstrInfo_cc::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = InstrOpInfoFlags::None;
		auto mnemonic = MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_memsize::SimpleInstrInfo_memsize(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_memsize::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		auto flags = instrBitness == 0 || (instrBitness & bitness) != 0 ? InstrOpInfoFlags::MemSize_Nothing : InstrOpInfoFlags::ShowNoMemSize_ForceSize | InstrOpInfoFlags::ShowMinMemSize_ForceSize;
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_StringIg1::SimpleInstrInfo_StringIg1(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_StringIg1::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 1;
		info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
	}

	SimpleInstrInfo_StringIg0::SimpleInstrInfo_StringIg0(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_StringIg0::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 1;
		info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
		info.Op0Index = info.Op1Index;
	}

	SimpleInstrInfo_nop::SimpleInstrInfo_nop(std::int32_t bitness, const std::string& mnemonic, Register register_)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->register_ = register_;
	}

	FormatterString SimpleInstrInfo_nop::str_xchg = FormatterString("xchg");

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
			info.Mnemonic = str_xchg;
			info.OpCount = 2;
			info.Op0Kind = InstrOpKind::Register;
			info.Op1Kind = InstrOpKind::Register;
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(register_);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(register_);
			info.Op0Index = OpAccess_None;
			info.Op1Index = OpAccess_None;
		}
	}

	SimpleInstrInfo_ST1::SimpleInstrInfo_ST1(const std::string& mnemonic, InstrOpInfoFlags flags) : SimpleInstrInfo_ST1(mnemonic, flags, false)
	{
	}

	SimpleInstrInfo_ST1::SimpleInstrInfo_ST1(const std::string& mnemonic, InstrOpInfoFlags flags, bool isLoad)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
		op0Access = isLoad ? OpAccess_Write : OpAccess_ReadWrite;
	}

	void SimpleInstrInfo_ST1::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, flags);
		assert(instruction.GetOpCount() == 1);
		info.OpCount = 2;
		info.Op1Kind = info.Op0Kind;
		info.Op1Register = info.Op0Register;
		info.Op0Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(Registers::Register_ST);
		info.Op1Index = info.Op0Index;
		info.Op0Index = static_cast<std::int8_t>(op0Access);
	}

	SimpleInstrInfo_ST2::SimpleInstrInfo_ST2(const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_ST2::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, flags);
		assert(instruction.GetOpCount() == 1);
		info.OpCount = 2;
		info.Op1Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op1Register = static_cast<std::uint8_t>(Registers::Register_ST);
		info.Op1Index = OpAccess_Read;
	}

	SimpleInstrInfo_maskmovq::SimpleInstrInfo_maskmovq(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_maskmovq::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		assert(instruction.GetOpCount() == 3);
		auto opKind = instruction.GetOp0Kind();
		auto switchTempVar_2 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_2 == CodeSize.Unknown) ? opKind : (switchTempVar_2 == CodeSize.Code16) ? OpKind.MemorySegDI : (switchTempVar_2 == CodeSize.Code32) ? OpKind.MemorySegEDI : (switchTempVar_2 == CodeSize.Code64) ? OpKind.MemorySegRDI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_2 == CodeSize::Unknown) ? opKind : (switchTempVar_2 == CodeSize::Code16) ? OpKind::MemorySegDI : (switchTempVar_2 == CodeSize::Code32) ? OpKind::MemorySegEDI : (switchTempVar_2 == CodeSize::Code64) ? OpKind::MemorySegRDI : throw InvalidOperationException();
		auto flags = InstrOpInfoFlags::IgnoreSegmentPrefix;
		if (opKind != shortFormOpKind)
		{
			if (opKind == OpKind::MemorySegDI)
			{
				flags |= InstrOpInfoFlags::AddrSize16;
			}
			else if (opKind == OpKind::MemorySegEDI)
			{
				flags |= InstrOpInfoFlags::AddrSize32;
			}
			else if (opKind == OpKind::MemorySegRDI)
			{
				flags |= InstrOpInfoFlags::AddrSize64;
			}
		}
		info = InstrOpInfo();
		info.Flags = flags;
		info.Mnemonic = mnemonic;
		info.OpCount = 2;
		info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
		info.Op0Index = 1;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
		info.Op1Kind = static_cast<InstrOpKind>(instruction.GetOp2Kind());
		info.Op1Index = 2;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op1Register = static_cast<std::uint8_t>(instruction.GetOp2Register());
		auto segReg = instruction.GetSegmentPrefix();
		if (segReg != Register::None && FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options))
		{
			info.OpCount = 3;
			info.Op2Kind = InstrOpKind::Register;
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op2Register = static_cast<std::uint8_t>(segReg);
			info.Op2Index = OpAccess_Read;
		}
	}

	SimpleInstrInfo_os::SimpleInstrInfo_os(std::int32_t bitness, const std::string& mnemonic) : SimpleInstrInfo_os(bitness, mnemonic, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo_os::SimpleInstrInfo_os(std::int32_t bitness, const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_os::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = this->flags;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				flags |= InstrOpInfoFlags::OpSize16;
			}
			else if (bitness == 32)
			{
				if (instrBitness != 64)
				{
					flags |= InstrOpInfoFlags::OpSize32;
				}
			}
			else
			{
				flags |= InstrOpInfoFlags::OpSize64;
			}
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_os_bnd::SimpleInstrInfo_os_bnd(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_os_bnd::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		if (instruction.GetHasRepnePrefix())
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
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_as::SimpleInstrInfo_as(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_as::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
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

	SimpleInstrInfo_os_jcc::SimpleInstrInfo_os_jcc(std::int32_t bitness, std::int32_t ccIndex, const std::vector<std::string>& mnemonics) : SimpleInstrInfo_os_jcc(bitness, ccIndex, mnemonics, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo_os_jcc::SimpleInstrInfo_os_jcc(std::int32_t bitness, std::int32_t ccIndex, const std::vector<std::string>& mnemonics, InstrOpInfoFlags flags)
	{
		this->bitness = bitness;
		this->ccIndex = ccIndex;
		this->mnemonics = FormatterString::Create(mnemonics);
		this->flags = flags;
	}

	void SimpleInstrInfo_os_jcc::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = this->flags;
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
			flags |= InstrOpInfoFlags::IgnoreSegmentPrefix | InstrOpInfoFlags::JccNotTaken;
		}
		else if (prefixSeg == Register::DS)
		{
			flags |= InstrOpInfoFlags::IgnoreSegmentPrefix | InstrOpInfoFlags::JccTaken;
		}
		if (instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		auto mnemonic = MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_os_loop::SimpleInstrInfo_os_loop(std::int32_t bitness, std::int32_t ccIndex, Register register_, const std::vector<std::string>& mnemonics)
	{
		this->bitness = bitness;
		this->ccIndex = ccIndex;
		this->register_ = register_;
		this->mnemonics = FormatterString::Create(mnemonics);
	}

	void SimpleInstrInfo_os_loop::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		auto switchTempVar_3 = instrBitness;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var expectedReg = (switchTempVar_3 == 0) ? register : (switchTempVar_3 == 16) ? Register.CX : (switchTempVar_3 == 32) ? Register.ECX : (switchTempVar_3 == 64) ? Register.RCX : throw new InvalidOperationException();
		auto expectedReg = (switchTempVar_3 == 0) ? register_ : (switchTempVar_3 == 16) ? Register::CX : (switchTempVar_3 == 32) ? Register::ECX : (switchTempVar_3 == 64) ? Register::RCX : throw InvalidOperationException();
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
		if (expectedReg != register_)
		{
			if (register_ == Register::CX)
			{
				flags |= InstrOpInfoFlags::AddrSize16;
			}
			else if (register_ == Register::ECX)
			{
				flags |= InstrOpInfoFlags::AddrSize32;
			}
			else
			{
				flags |= InstrOpInfoFlags::AddrSize64;
			}
		}
		auto mnemonic = ccIndex == -1 ? mnemonics[0] : MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_movabs::SimpleInstrInfo_movabs(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_movabs::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		auto switchTempVar_4 = instruction.GetMemoryDisplSize();


		auto memSize = (switchTempVar_4 == 2) ? static_cast<std::uint8_t>(16) : (switchTempVar_4 == 4) ? static_cast<std::uint8_t>(32) : static_cast<std::uint8_t>(64);
		if (instrBitness == 0)
		{
			instrBitness = memSize;
		}
		if (instrBitness != memSize)
		{
			if (memSize == 16)
			{
				flags |= InstrOpInfoFlags::AddrSize16;
			}
			else if (memSize == 32)
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

	SimpleInstrInfo_opmask_op::SimpleInstrInfo_opmask_op(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_opmask_op::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		assert(instruction.GetOpCount() <= 2);
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		auto kreg = instruction.GetOpMask();
		if (kreg != Register::None)
		{
			info.OpCount++;
			info.Op2Kind = info.Op1Kind;
			info.Op2Register = info.Op1Register;
			info.Op2Index = 1;
			info.Op1Kind = InstrOpKind::Register;
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(kreg);
			info.Op1Index = OpAccess_Read;
			info.Flags |= InstrOpInfoFlags::IgnoreOpMask;
		}
	}

	SimpleInstrInfo_bnd::SimpleInstrInfo_bnd(const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_bnd::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = this->flags;
		if (instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_ST_STi::SimpleInstrInfo_ST_STi(const std::string& mnemonic, bool pseudoOp)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudoOp = pseudoOp;
	}

	void SimpleInstrInfo_ST_STi::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
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
			assert(info.Op1Register == static_cast<std::int32_t>(Register::ST0));
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(Registers::Register_ST);
		}
	}

	SimpleInstrInfo_pops::SimpleInstrInfo_pops(const std::string& mnemonic, const std::vector<FormatterString>& pseudo_ops)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudo_ops = pseudo_ops;
	}

	void SimpleInstrInfo_pops::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		std::int32_t imm = instruction.GetImmediate8();
		if (options.GetUsePseudoOps() && static_cast<std::uint32_t>(imm) < static_cast<std::uint32_t>(pseudo_ops.size()))
		{
			info.Mnemonic = pseudo_ops[imm];
			RemoveLastOp(info);
		}
	}

	void SimpleInstrInfo_pops::RemoveLastOp(InstrOpInfo& info)
	{
		switch (info.OpCount)
		{
		case 4:
			info.Op3Index = OpAccess_INVALID;
			break;
		case 3:
			info.Op2Index = OpAccess_INVALID;
			break;
		default:
			throw InvalidOperationException();
		}
		info.OpCount--;
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
				info.Mnemonic = pseudo_ops[index];
				SimpleInstrInfo_pops::RemoveLastOp(info);
			}
		}
	}

	SimpleInstrInfo_imul::SimpleInstrInfo_imul(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_imul::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		assert(info.OpCount == 3);
		if (options.GetUsePseudoOps() && info.Op0Kind == InstrOpKind::Register && info.Op1Kind == InstrOpKind::Register && info.Op0Register == info.Op1Register)
		{
			info.OpCount--;
			info.Op0Index = OpAccess_ReadWrite;
			info.Op1Kind = info.Op2Kind;
			info.Op1Index = 2;
			info.Op2Index = OpAccess_INVALID;
		}
	}

	SimpleInstrInfo_Reg16::SimpleInstrInfo_Reg16(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_Reg16::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = InstrOpInfoFlags::None;
		info = InstrOpInfo(mnemonic, instruction, flags);
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

	SimpleInstrInfo_reg::SimpleInstrInfo_reg(const std::string& mnemonic, Register register_)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->register_ = register_;
	}

	void SimpleInstrInfo_reg::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		assert(instruction.GetOpCount() == 0);
		info.OpCount = 1;
		info.Op0Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(register_);
		if (instruction.GetCode() == Code::Skinit)
		{
			info.Op0Index = OpAccess_ReadWrite;
		}
		else
		{
			info.Op0Index = OpAccess_Read;
		}
	}

	SimpleInstrInfo_invlpga::SimpleInstrInfo_invlpga(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_invlpga::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 2;
		info.Op0Kind = InstrOpKind::Register;
		info.Op1Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op1Register = static_cast<std::uint8_t>(Register::ECX);
		info.Op0Index = OpAccess_Read;
		info.Op1Index = OpAccess_Read;
		switch (bitness)
		{
		case 16:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::AX);
			break;
		case 32:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::EAX);
			break;
		case 64:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::RAX);
			break;
		default:
			throw InvalidOperationException();
		}
	}

	SimpleInstrInfo_DeclareData::SimpleInstrInfo_DeclareData(Code code, const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
		auto switchTempVar_5 = code;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: opKind = (switchTempVar_5 == Code.DeclareByte) ? InstrOpKind.DeclareByte : (switchTempVar_5 == Code.DeclareWord) ? InstrOpKind.DeclareWord : (switchTempVar_5 == Code.DeclareDword) ? InstrOpKind.DeclareDword : (switchTempVar_5 == Code.DeclareQword) ? InstrOpKind.DeclareQword : throw new InvalidOperationException();
		opKind = (switchTempVar_5 == Code::DeclareByte) ? InstrOpKind::DeclareByte : (switchTempVar_5 == Code::DeclareWord) ? InstrOpKind::DeclareWord : (switchTempVar_5 == Code::DeclareDword) ? InstrOpKind::DeclareDword : (switchTempVar_5 == Code::DeclareQword) ? InstrOpKind::DeclareQword : throw InvalidOperationException();
	}

	void SimpleInstrInfo_DeclareData::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::MnemonicIsDirective);
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

	SimpleInstrInfo_bcst::SimpleInstrInfo_bcst(const std::string& mnemonic, InstrOpInfoFlags flagsNoBroadcast)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flagsNoBroadcast = flagsNoBroadcast;
	}

	void SimpleInstrInfo_bcst::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto memInfo = MemorySizes::AllMemorySizes[static_cast<std::int32_t>(instruction.GetMemorySize())];
		auto flags = memInfo.bcstTo.GetLength() != 0 ? InstrOpInfoFlags::None : flagsNoBroadcast;
		info = InstrOpInfo(mnemonic, instruction, flags);
	}
}
