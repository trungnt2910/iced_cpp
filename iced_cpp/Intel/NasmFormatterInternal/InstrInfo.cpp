// C# helper headers

#include <csharp/enum.h>



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
#include "BranchSizeInfo.g.h"
#include "../RoundingControl.g.h"
#include "../FormatterInternal/Iced.Intel.FormatterInternal.FormatterUtils.h"
#include "MemorySizes.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::NasmFormatterInternal
{

	Iced::Intel::MemorySize InstrOpInfo::GetMemorySize() const
	{
		return static_cast<Iced::Intel::MemorySize>((static_cast<std::uint32_t>(Flags) >> static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeShift)) & static_cast<std::uint32_t>(InstrOpInfoFlags::MemorySizeMask));
	}

	void InstrOpInfo::SetMemorySize(Iced::Intel::MemorySize value)
	{
		Flags = static_cast<InstrOpInfoFlags>((static_cast<std::uint32_t>(Flags) & ~(static_cast<std::uint32_t>(InstrOpInfoFlags::MemorySizeMask) << static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeShift))) | ((static_cast<std::uint32_t>(value) & static_cast<std::uint32_t>(InstrOpInfoFlags::MemorySizeMask)) << static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeShift)));
	}

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
		Flags = flags | static_cast<InstrOpInfoFlags>(static_cast<std::uint32_t>(instruction.GetMemorySize()) << static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeShift));
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
			throw std::runtime_error("invalid operation");
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

	SimpleInstrInfo_push_imm8::SimpleInstrInfo_push_imm8(std::int32_t bitness, SignExtendInfo sexInfo, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->sexInfo = sexInfo;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_push_imm8::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(sexInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::SignExtendInfoShift));
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		if (bitness != 0 && instrBitness != 0 && instrBitness != bitness)
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

	SimpleInstrInfo_push_imm::SimpleInstrInfo_push_imm(std::int32_t bitness, SignExtendInfo sexInfo, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->sexInfo = sexInfo;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_push_imm::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		bool signExtend = true;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		if (bitness != 0 && instrBitness != 0 && instrBitness != bitness)
		{
			if (instrBitness == 64)
			{
				flags |= InstrOpInfoFlags::OpSize16;
			}
		}
		else if (bitness == 16 && instrBitness == 16)
		{
			signExtend = false;
		}
		if (signExtend)
		{
			flags |= static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(sexInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::SignExtendInfoShift));
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_SignExt::SimpleInstrInfo_SignExt(SignExtendInfo sexInfo, const std::string& mnemonic, InstrOpInfoFlags flags) : SimpleInstrInfo_SignExt(sexInfo, sexInfo, mnemonic, flags)
	{
	}

	SimpleInstrInfo_SignExt::SimpleInstrInfo_SignExt(SignExtendInfo sexInfoReg, SignExtendInfo sexInfoMem, const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->sexInfoReg = sexInfoReg;
		this->sexInfoMem = sexInfoMem;
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_SignExt::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		assert(instruction.GetOpCount() == 2);
		auto sexInfo = instruction.GetOp0Kind() == OpKind::Memory || instruction.GetOp1Kind() == OpKind::Memory ? sexInfoMem : sexInfoReg;
		auto flags = this->flags;
		flags |= static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(sexInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::SignExtendInfoShift));
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_imul::SimpleInstrInfo_imul(SignExtendInfo sexInfo, const std::string& mnemonic)
	{
		this->sexInfo = sexInfo;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_imul::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(sexInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::SignExtendInfoShift));
		info = InstrOpInfo(mnemonic, instruction, flags);
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

	SimpleInstrInfo_String::SimpleInstrInfo_String(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	InstrOpInfoFlags SimpleInstrInfo_String::GetAddressSizeFlags(OpKind opKind)
	{
		switch (opKind)
		{
		case OpKind::MemorySegSI:
		case OpKind::MemorySegDI:
		case OpKind::MemoryESDI:
			return InstrOpInfoFlags::AddrSize16;
		case OpKind::MemorySegESI:
		case OpKind::MemorySegEDI:
		case OpKind::MemoryESEDI:
			return InstrOpInfoFlags::AddrSize32;
		case OpKind::MemorySegRSI:
		case OpKind::MemorySegRDI:
		case OpKind::MemoryESRDI:
			return InstrOpInfoFlags::AddrSize64;
		default:
			return (InstrOpInfoFlags)0;
		}
	}

	void SimpleInstrInfo_String::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto opKind = instruction.GetOp0Kind() != OpKind::Register ? instruction.GetOp0Kind() : instruction.GetOp1Kind();
		auto opKindFlags = GetAddressSizeFlags(opKind);
		auto switchTempVar_2 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var instrFlags = (switchTempVar_2 == CodeSize.Unknown) ? opKindFlags : (switchTempVar_2 == CodeSize.Code16) ? InstrOpInfoFlags.AddrSize16 : (switchTempVar_2 == CodeSize.Code32) ? InstrOpInfoFlags.AddrSize32 : (switchTempVar_2 == CodeSize.Code64) ? InstrOpInfoFlags.AddrSize64 : throw new InvalidOperationException();
		auto instrFlags = (switchTempVar_2 == CodeSize::Unknown) ? opKindFlags : (switchTempVar_2 == CodeSize::Code16) ? InstrOpInfoFlags::AddrSize16 : (switchTempVar_2 == CodeSize::Code32) ? InstrOpInfoFlags::AddrSize32 : (switchTempVar_2 == CodeSize::Code64) ? InstrOpInfoFlags::AddrSize64 : throw std::runtime_error("invalid operation");
		InstrOpInfoFlags flags = (InstrOpInfoFlags)0;
		if (opKindFlags != instrFlags)
		{
			flags |= opKindFlags;
		}
		info = InstrOpInfo();
		info.Flags = flags;
		info.Mnemonic = mnemonic;
	}

	SimpleInstrInfo_XLAT::SimpleInstrInfo_XLAT(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_XLAT::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_3 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var baseReg = (switchTempVar_3 == CodeSize.Unknown) ? instruction.MemoryBase : (switchTempVar_3 == CodeSize.Code16) ? Register.BX : (switchTempVar_3 == CodeSize.Code32) ? Register.EBX : (switchTempVar_3 == CodeSize.Code64) ? Register.RBX : throw new InvalidOperationException();
		auto baseReg = (switchTempVar_3 == CodeSize::Unknown) ? instruction.GetMemoryBase() : (switchTempVar_3 == CodeSize::Code16) ? Register::BX : (switchTempVar_3 == CodeSize::Code32) ? Register::EBX : (switchTempVar_3 == CodeSize::Code64) ? Register::RBX : throw std::runtime_error("invalid operation");
		InstrOpInfoFlags flags = (InstrOpInfoFlags)0;
		auto memBaseReg = instruction.GetMemoryBase();
		if (memBaseReg != baseReg)
		{
			if (memBaseReg == Register::BX)
			{
				flags |= InstrOpInfoFlags::AddrSize16;
			}
			else if (memBaseReg == Register::EBX)
			{
				flags |= InstrOpInfoFlags::AddrSize32;
			}
			else if (memBaseReg == Register::RBX)
			{
				flags |= InstrOpInfoFlags::AddrSize64;
			}
		}
		info = InstrOpInfo();
		info.Flags = flags;
		info.Mnemonic = mnemonic;
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
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
			info.Op0Index = 1;
		}
	}

	SimpleInstrInfo_STIG2::SimpleInstrInfo_STIG2(const std::string& mnemonic, bool pseudoOp) : SimpleInstrInfo_STIG2(mnemonic, (InstrOpInfoFlags)0, pseudoOp)
	{
	}

	SimpleInstrInfo_STIG2::SimpleInstrInfo_STIG2(const std::string& mnemonic, InstrOpInfoFlags flags) : SimpleInstrInfo_STIG2(mnemonic, flags, false)
	{
	}

	SimpleInstrInfo_STIG2::SimpleInstrInfo_STIG2(const std::string& mnemonic, InstrOpInfoFlags flags, bool pseudoOp)
	{
		this->flags = flags;
		this->mnemonic = FormatterString(mnemonic);
		this->pseudoOp = pseudoOp;
	}

	void SimpleInstrInfo_STIG2::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Flags = flags;
		info.Mnemonic = mnemonic;
		assert(instruction.GetOpCount() == 2);
		assert(instruction.GetOp1Kind() == OpKind::Register && instruction.GetOp1Register() == Register::ST0);
		if (!pseudoOp || !(options.GetUsePseudoOps() && instruction.GetOp0Register() == Register::ST1))
		{
			info.OpCount = 1;
			Static::Assert(InstrOpKind::Register == (InstrOpKind)0 ? 0 : -1);
			//info.Op0Kind = InstrOpKind.Register;
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
		}
	}

	SimpleInstrInfo_as::SimpleInstrInfo_as(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_as::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
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
		auto switchTempVar_4 = instruction.GetOp0Kind();


		auto bitness = (switchTempVar_4 == OpKind::MemorySegDI) ? static_cast<std::uint8_t>(16) : (switchTempVar_4 == OpKind::MemorySegEDI) ? static_cast<std::uint8_t>(32) : (switchTempVar_4 == OpKind::MemorySegRDI) ? static_cast<std::uint8_t>(64) : instrBitness;
		info = InstrOpInfo();
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

	SimpleInstrInfo_pblendvb::SimpleInstrInfo_pblendvb(const std::string& mnemonic, MemorySize memSize)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->memSize = memSize;
	}

	void SimpleInstrInfo_pblendvb::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		assert(instruction.GetOpCount() == 2);
		info.Mnemonic = mnemonic;
		info.OpCount = 3;
		info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
		info.Op1Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
		info.Op1Index = 1;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op1Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
		Static::Assert(InstrOpKind::Register == (InstrOpKind)0 ? 0 : -1);
		//info.Op2Kind = InstrOpKind.Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op2Register = static_cast<std::uint8_t>(Register::XMM0);
		info.SetMemorySize(memSize);
		info.Op2Index = OpAccess_Read;
	}

	SimpleInstrInfo_reverse::SimpleInstrInfo_reverse(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_reverse::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		assert(instruction.GetOpCount() == 2);
		info.OpCount = 2;
		info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
		info.Op0Index = 1;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
		info.Op1Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op1Register = static_cast<std::uint8_t>(instruction.GetOp0Register());
		info.SetMemorySize(instruction.GetMemorySize());
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
		if (instruction.GetCodeSize() == codeSize)
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
		auto mnemonic = mnemonics[static_cast<std::int32_t>(instruction.GetCodeSize())];
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_OpSize3::SimpleInstrInfo_OpSize3(std::int32_t bitness, const std::string& mnemonicDefault, const std::string& mnemonicFull)
	{
		this->bitness = bitness;
		this->mnemonicDefault = FormatterString(mnemonicDefault);
		this->mnemonicFull = FormatterString(mnemonicFull);
	}

	void SimpleInstrInfo_OpSize3::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto instrBitness = GetBitness(instruction.GetCodeSize());
		FormatterString mnemonic;
		if (instrBitness == 0 || (instrBitness & bitness) != 0)
		{
			mnemonic = mnemonicDefault;
		}
		else
		{
			mnemonic = mnemonicFull;
		}
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
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
				flags |= InstrOpInfoFlags::OpSize32;
			}
			else
			{
				flags |= InstrOpInfoFlags::OpSize64;
			}
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_os_mem::SimpleInstrInfo_os_mem(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
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
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_os_mem2::SimpleInstrInfo_os_mem2(std::int32_t bitness, const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->flags = flags;
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_os_mem2::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = this->flags;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		if (instrBitness != 0 && (instrBitness & bitness) == 0)
		{
			if (instrBitness != 16)
			{
				flags |= InstrOpInfoFlags::OpSize16;
			}
			else
			{
				flags |= InstrOpInfoFlags::OpSize32;
			}
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_os_mem_reg16::SimpleInstrInfo_os_mem_reg16(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_os_mem_reg16::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		assert(instruction.GetOpCount() == 1);
		if (instruction.GetOp0Kind() == OpKind::Memory)
		{
			if (!(instrBitness == 0 || (instrBitness != 64 && instrBitness == bitness) || (instrBitness == 64 && bitness == 32)))
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
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
		if (instruction.GetOp0Kind() == OpKind::Register)
		{
			auto reg = static_cast<Register>(info.Op0Register);
			std::int32_t regSize = 0;
			if (Register::AX <= reg && reg <= Register::R15W)
			{
				regSize = 16;
			}
			else if (Register::EAX <= reg && reg <= Register::R15D)
			{
				regSize = 32;
				reg = (Register)(reg - Register::EAX + Register::AX);
			}
			else if (Register::RAX <= reg && reg <= Register::R15)
			{
				regSize = 64;
				reg = (Register)(reg - Register::RAX + Register::AX);
			}
			assert(regSize != 0);
			if (regSize != 0)
			{
				Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
				info.Op0Register = static_cast<std::uint8_t>(reg);
				if (!((instrBitness != 64 && instrBitness == regSize) || (instrBitness == 64 && regSize == 32)))
				{
					if (bitness == 16)
					{
						info.Flags |= InstrOpInfoFlags::OpSize16;
					}
					else if (bitness == 32)
					{
						info.Flags |= InstrOpInfoFlags::OpSize32;
					}
					else
					{
						info.Flags |= InstrOpInfoFlags::OpSize64;
					}
				}
			}
		}
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
		if (flags != InstrOpInfoFlags::None)
		{
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
		}
		else
		{
			auto branchInfo = BranchSizeInfo::Near;
			if (instrBitness != 0 && instrBitness != bitness)
			{
				if (bitness == 16)
				{
					branchInfo = BranchSizeInfo::NearWord;
				}
				else if (bitness == 32)
				{
					branchInfo = BranchSizeInfo::NearDword;
				}
			}
			flags |= static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(branchInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::BranchSizeInfoShift));
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
		auto switchTempVar_5 = instrBitness;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var expectedReg = (switchTempVar_5 == 0) ? register : (switchTempVar_5 == 16) ? Register.CX : (switchTempVar_5 == 32) ? Register.ECX : (switchTempVar_5 == 64) ? Register.RCX : throw new InvalidOperationException();
		auto expectedReg = (switchTempVar_5 == 0) ? register_ : (switchTempVar_5 == 16) ? Register::CX : (switchTempVar_5 == 32) ? Register::ECX : (switchTempVar_5 == 64) ? Register::RCX : throw std::runtime_error("invalid operation");
		bool addReg = expectedReg != register_;
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
		auto mnemonic = ccIndex == -1 ? mnemonics[0] : MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		info = InstrOpInfo(mnemonic, instruction, flags);
		if (addReg)
		{
			assert(info.OpCount == 1);
			info.OpCount = 2;
			info.Op1Kind = InstrOpKind::Register;
			info.Op1Index = OpAccess_ReadWrite;
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(register_);
		}
	}

	SimpleInstrInfo_os_call::SimpleInstrInfo_os_call(std::int32_t bitness, const std::string& mnemonic, bool canHaveBndPrefix)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->canHaveBndPrefix = canHaveBndPrefix;
	}

	void SimpleInstrInfo_os_call::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		if (canHaveBndPrefix && instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		auto branchInfo = BranchSizeInfo::None;
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				branchInfo = BranchSizeInfo::Word;
			}
			else if (bitness == 32)
			{
				branchInfo = BranchSizeInfo::Dword;
			}
		}
		flags |= static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(branchInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::BranchSizeInfoShift));
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_far::SimpleInstrInfo_far(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_far::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		auto branchInfo = BranchSizeInfo::None;
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				branchInfo = BranchSizeInfo::Word;
			}
			else
			{
				branchInfo = BranchSizeInfo::Dword;
			}
		}
		flags |= static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(branchInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::BranchSizeInfoShift));
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_far_mem::SimpleInstrInfo_far_mem(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_far_mem::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::ShowNoMemSize_ForceSize;
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		auto farMemSizeInfo = FarMemorySizeInfo::None;
		if (instrBitness != 0 && instrBitness != bitness)
		{
			if (bitness == 16)
			{
				farMemSizeInfo = FarMemorySizeInfo::Word;
			}
			else
			{
				farMemSizeInfo = FarMemorySizeInfo::Dword;
			}
		}
		flags |= static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(farMemSizeInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::FarMemorySizeInfoShift));
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
		auto switchTempVar_6 = instruction.GetMemoryDisplSize();


		auto memSize = (switchTempVar_6 == 2) ? static_cast<std::uint8_t>(16) : (switchTempVar_6 == 4) ? static_cast<std::uint8_t>(32) : static_cast<std::uint8_t>(64);
		if (instrBitness == 0)
		{
			instrBitness = memSize;
		}
		auto memSizeInfo = MemorySizeInfo::None;
		if (instrBitness == 64)
		{
			if (memSize == 32)
			{
				flags |= InstrOpInfoFlags::AddrSize32;
			}
			else
			{
				memSizeInfo = MemorySizeInfo::Qword;
			}
		}
		else if (instrBitness != memSize)
		{
			assert(memSize == 16 || memSize == 32);
			if (memSize == 16)
			{
				memSizeInfo = MemorySizeInfo::Word;
			}
			else
			{
				memSizeInfo = MemorySizeInfo::Dword;
			}
		}
		flags |= static_cast<InstrOpInfoFlags>(static_cast<std::int32_t>(memSizeInfo) << static_cast<std::int32_t>(InstrOpInfoFlags::MemorySizeInfoShift));
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_er::SimpleInstrInfo_er(std::int32_t erIndex, const std::string& mnemonic) : SimpleInstrInfo_er(erIndex, mnemonic, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo_er::SimpleInstrInfo_er(std::int32_t erIndex, const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->erIndex = erIndex;
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_er::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, flags);
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
		case 2:
			assert(info.OpCount < 4 || info.Op3Kind != InstrOpKind::Register);
			info.Op4Kind = info.Op3Kind;
			info.Op3Kind = info.Op2Kind;
			info.Op3Register = info.Op2Register;
			info.Op2Kind = newOpKind;
			info.Op4Index = info.Op3Index;
			info.Op3Index = info.Op2Index;
			info.Op2Index = OpAccess_None;
			info.OpCount++;
			break;
		case 3:
			assert(info.OpCount < 4 || info.Op3Kind != InstrOpKind::Register);
			info.Op4Kind = info.Op3Kind;
			info.Op3Kind = newOpKind;
			info.Op4Index = info.Op3Index;
			info.Op3Index = OpAccess_None;
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

	SimpleInstrInfo_pops::SimpleInstrInfo_pops(const std::string& mnemonic, const std::vector<FormatterString>& pseudo_ops)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudo_ops = pseudo_ops;
	}

	void SimpleInstrInfo_pops::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		if (instruction.GetSuppressAllExceptions())
		{
			SimpleInstrInfo_er::MoveOperands(info, instruction.GetOpCount() - 1, InstrOpKind::Sae);
		}
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
		case 5:
			info.Op4Index = OpAccess_INVALID;
			break;
		case 4:
			info.Op3Index = OpAccess_INVALID;
			break;
		case 3:
			info.Op2Index = OpAccess_INVALID;
			break;
		default:
			throw std::runtime_error("invalid operation");
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

	SimpleInstrInfo_Reg16::SimpleInstrInfo_Reg16(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_Reg16::GetOpInfo(const FormatterOptions& options, const Instruction& instruction, InstrOpInfo& info)
	{
		constexpr InstrOpInfoFlags flags = InstrOpInfoFlags::None;
		info = InstrOpInfo(mnemonic, instruction, flags);
		if (Register::EAX <= static_cast<Register>(info.Op0Register) && static_cast<Register>(info.Op0Register) <= Register::R15D)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(static_cast<Register>(info.Op0Register) - Register::EAX + Register::AX);
		}
		if (Register::EAX <= static_cast<Register>(info.Op1Register) && static_cast<Register>(info.Op1Register) <= Register::R15D)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(static_cast<Register>(info.Op1Register) - Register::EAX + Register::AX);
		}
		if (Register::EAX <= static_cast<Register>(info.Op2Register) && static_cast<Register>(info.Op2Register) <= Register::R15D)
		{
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op2Register = static_cast<std::uint8_t>(static_cast<Register>(info.Op2Register) - Register::EAX + Register::AX);
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
			throw std::runtime_error("invalid operation");
		}
	}

	SimpleInstrInfo_DeclareData::SimpleInstrInfo_DeclareData(Code code, const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
		auto switchTempVar_7 = code;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: opKind = (switchTempVar_7 == Code.DeclareByte) ? InstrOpKind.DeclareByte : (switchTempVar_7 == Code.DeclareWord) ? InstrOpKind.DeclareWord : (switchTempVar_7 == Code.DeclareDword) ? InstrOpKind.DeclareDword : (switchTempVar_7 == Code.DeclareQword) ? InstrOpKind.DeclareQword : throw new InvalidOperationException();
		opKind = (switchTempVar_7 == Code::DeclareByte) ? InstrOpKind::DeclareByte : (switchTempVar_7 == Code::DeclareWord) ? InstrOpKind::DeclareWord : (switchTempVar_7 == Code::DeclareDword) ? InstrOpKind::DeclareDword : (switchTempVar_7 == Code::DeclareQword) ? InstrOpKind::DeclareQword : throw std::runtime_error("invalid operation");
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
}
