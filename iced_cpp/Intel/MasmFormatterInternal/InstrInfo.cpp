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
#include "../OpKind.g.h"
#include "../FormatterInternal/Iced.Intel.FormatterInternal.FormatterUtils.h"
#include "Registers.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::MasmFormatterInternal
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

	void SimpleInstrInfo::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_cc::SimpleInstrInfo_cc(std::int32_t ccIndex, const std::vector<std::string>& mnemonics) : SimpleInstrInfo_cc(ccIndex, mnemonics, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo_cc::SimpleInstrInfo_cc(std::int32_t ccIndex, const std::vector<std::string>& mnemonics, InstrOpInfoFlags flags)
	{
		this->ccIndex = ccIndex;
		this->mnemonics = FormatterString::Create(mnemonics);
		this->flags = flags;
	}

	void SimpleInstrInfo_cc::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto mnemonic = MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_memsize::SimpleInstrInfo_memsize(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_memsize::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		std::int32_t instrBitness = GetBitness(instruction.GetCodeSize());
		auto flags = instrBitness == 0 || (instrBitness & bitness) != 0 ? InstrOpInfoFlags::MemSize_Nothing : InstrOpInfoFlags::MemSize_Normal | InstrOpInfoFlags::ShowNoMemSize_ForceSize | InstrOpInfoFlags::ShowMinMemSize_ForceSize;
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_AamAad::SimpleInstrInfo_AamAad(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_AamAad::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
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

	SimpleInstrInfo_Int3::SimpleInstrInfo_Int3(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_Int3::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 1;
		info.Op0Kind = InstrOpKind::ExtraImmediate8_Value3;
		info.Op0Index = OpAccess_Read;
	}

	SimpleInstrInfo_YD::SimpleInstrInfo_YD(const std::string& mnemonic_args, const std::string& mnemonic_no_args)
	{
		this->mnemonic_args = FormatterString(mnemonic_args);
		this->mnemonic_no_args = FormatterString(mnemonic_no_args);
	}

	void SimpleInstrInfo_YD::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_2 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_2 == CodeSize.Unknown) ? instruction.Op0Kind : (switchTempVar_2 == CodeSize.Code16) ? OpKind.MemoryESDI : (switchTempVar_2 == CodeSize.Code32) ? OpKind.MemoryESEDI : (switchTempVar_2 == CodeSize.Code64) ? OpKind.MemoryESRDI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_2 == CodeSize::Unknown) ? instruction.GetOp0Kind() : (switchTempVar_2 == CodeSize::Code16) ? OpKind::MemoryESDI : (switchTempVar_2 == CodeSize::Code32) ? OpKind::MemoryESEDI : (switchTempVar_2 == CodeSize::Code64) ? OpKind::MemoryESRDI : throw InvalidOperationException();
		bool shortForm = instruction.GetOp0Kind() == shortFormOpKind;
		if (!shortForm)
		{
			info = InstrOpInfo(mnemonic_args, instruction, flags);
		}
		else
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_no_args;
		}
	}

	SimpleInstrInfo_DX::SimpleInstrInfo_DX(const std::string& mnemonic_args, const std::string& mnemonic_no_args)
	{
		this->mnemonic_args = FormatterString(mnemonic_args);
		this->mnemonic_no_args = FormatterString(mnemonic_no_args);
	}

	void SimpleInstrInfo_DX::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_3 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_3 == CodeSize.Unknown) ? instruction.Op1Kind : (switchTempVar_3 == CodeSize.Code16) ? OpKind.MemorySegSI : (switchTempVar_3 == CodeSize.Code32) ? OpKind.MemorySegESI : (switchTempVar_3 == CodeSize.Code64) ? OpKind.MemorySegRSI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_3 == CodeSize::Unknown) ? instruction.GetOp1Kind() : (switchTempVar_3 == CodeSize::Code16) ? OpKind::MemorySegSI : (switchTempVar_3 == CodeSize::Code32) ? OpKind::MemorySegESI : (switchTempVar_3 == CodeSize::Code64) ? OpKind::MemorySegRSI : throw InvalidOperationException();
		bool shortForm = instruction.GetOp1Kind() == shortFormOpKind && (instruction.GetSegmentPrefix() == Register::None || !FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options));
		if (!shortForm)
		{
			info = InstrOpInfo(mnemonic_args, instruction, flags);
		}
		else
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_no_args;
		}
	}

	SimpleInstrInfo_YX::SimpleInstrInfo_YX(const std::string& mnemonic_args, const std::string& mnemonic_no_args)
	{
		this->mnemonic_args = FormatterString(mnemonic_args);
		this->mnemonic_no_args = FormatterString(mnemonic_no_args);
	}

	void SimpleInstrInfo_YX::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_4 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_4 == CodeSize.Unknown) ? instruction.Op0Kind : (switchTempVar_4 == CodeSize.Code16) ? OpKind.MemoryESDI : (switchTempVar_4 == CodeSize.Code32) ? OpKind.MemoryESEDI : (switchTempVar_4 == CodeSize.Code64) ? OpKind.MemoryESRDI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_4 == CodeSize::Unknown) ? instruction.GetOp0Kind() : (switchTempVar_4 == CodeSize::Code16) ? OpKind::MemoryESDI : (switchTempVar_4 == CodeSize::Code32) ? OpKind::MemoryESEDI : (switchTempVar_4 == CodeSize::Code64) ? OpKind::MemoryESRDI : throw InvalidOperationException();
		bool shortForm = instruction.GetOp0Kind() == shortFormOpKind && (instruction.GetSegmentPrefix() == Register::None || !FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options));
		if (!shortForm)
		{
			info = InstrOpInfo(mnemonic_args, instruction, flags);
		}
		else
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_no_args;
		}
	}

	SimpleInstrInfo_XY::SimpleInstrInfo_XY(const std::string& mnemonic_args, const std::string& mnemonic_no_args)
	{
		this->mnemonic_args = FormatterString(mnemonic_args);
		this->mnemonic_no_args = FormatterString(mnemonic_no_args);
	}

	void SimpleInstrInfo_XY::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_5 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_5 == CodeSize.Unknown) ? instruction.Op1Kind : (switchTempVar_5 == CodeSize.Code16) ? OpKind.MemoryESDI : (switchTempVar_5 == CodeSize.Code32) ? OpKind.MemoryESEDI : (switchTempVar_5 == CodeSize.Code64) ? OpKind.MemoryESRDI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_5 == CodeSize::Unknown) ? instruction.GetOp1Kind() : (switchTempVar_5 == CodeSize::Code16) ? OpKind::MemoryESDI : (switchTempVar_5 == CodeSize::Code32) ? OpKind::MemoryESEDI : (switchTempVar_5 == CodeSize::Code64) ? OpKind::MemoryESRDI : throw InvalidOperationException();
		bool shortForm = instruction.GetOp1Kind() == shortFormOpKind && (instruction.GetSegmentPrefix() == Register::None || !FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options));
		if (!shortForm)
		{
			info = InstrOpInfo(mnemonic_args, instruction, flags);
		}
		else
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_no_args;
		}
	}

	SimpleInstrInfo_YA::SimpleInstrInfo_YA(const std::string& mnemonic_args, const std::string& mnemonic_no_args)
	{
		this->mnemonic_args = FormatterString(mnemonic_args);
		this->mnemonic_no_args = FormatterString(mnemonic_no_args);
	}

	void SimpleInstrInfo_YA::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_6 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_6 == CodeSize.Unknown) ? instruction.Op0Kind : (switchTempVar_6 == CodeSize.Code16) ? OpKind.MemoryESDI : (switchTempVar_6 == CodeSize.Code32) ? OpKind.MemoryESEDI : (switchTempVar_6 == CodeSize.Code64) ? OpKind.MemoryESRDI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_6 == CodeSize::Unknown) ? instruction.GetOp0Kind() : (switchTempVar_6 == CodeSize::Code16) ? OpKind::MemoryESDI : (switchTempVar_6 == CodeSize::Code32) ? OpKind::MemoryESEDI : (switchTempVar_6 == CodeSize::Code64) ? OpKind::MemoryESRDI : throw InvalidOperationException();
		bool shortForm = instruction.GetOp0Kind() == shortFormOpKind;
		if (!shortForm)
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_args;
			info.OpCount = 1;
			info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp0Kind());
		}
		else
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_no_args;
		}
	}

	SimpleInstrInfo_AX::SimpleInstrInfo_AX(const std::string& mnemonic_args, const std::string& mnemonic_no_args)
	{
		this->mnemonic_args = FormatterString(mnemonic_args);
		this->mnemonic_no_args = FormatterString(mnemonic_no_args);
	}

	void SimpleInstrInfo_AX::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_7 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_7 == CodeSize.Unknown) ? instruction.Op1Kind : (switchTempVar_7 == CodeSize.Code16) ? OpKind.MemorySegSI : (switchTempVar_7 == CodeSize.Code32) ? OpKind.MemorySegESI : (switchTempVar_7 == CodeSize.Code64) ? OpKind.MemorySegRSI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_7 == CodeSize::Unknown) ? instruction.GetOp1Kind() : (switchTempVar_7 == CodeSize::Code16) ? OpKind::MemorySegSI : (switchTempVar_7 == CodeSize::Code32) ? OpKind::MemorySegESI : (switchTempVar_7 == CodeSize::Code64) ? OpKind::MemorySegRSI : throw InvalidOperationException();
		bool shortForm = instruction.GetOp1Kind() == shortFormOpKind && (instruction.GetSegmentPrefix() == Register::None || !FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options));
		if (!shortForm)
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_args;
			info.OpCount = 1;
			info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
			info.Op0Index = 1;
		}
		else
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_no_args;
		}
	}

	SimpleInstrInfo_AY::SimpleInstrInfo_AY(const std::string& mnemonic_args, const std::string& mnemonic_no_args)
	{
		this->mnemonic_args = FormatterString(mnemonic_args);
		this->mnemonic_no_args = FormatterString(mnemonic_no_args);
	}

	void SimpleInstrInfo_AY::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_8 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_8 == CodeSize.Unknown) ? instruction.Op1Kind : (switchTempVar_8 == CodeSize.Code16) ? OpKind.MemoryESDI : (switchTempVar_8 == CodeSize.Code32) ? OpKind.MemoryESEDI : (switchTempVar_8 == CodeSize.Code64) ? OpKind.MemoryESRDI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_8 == CodeSize::Unknown) ? instruction.GetOp1Kind() : (switchTempVar_8 == CodeSize::Code16) ? OpKind::MemoryESDI : (switchTempVar_8 == CodeSize::Code32) ? OpKind::MemoryESEDI : (switchTempVar_8 == CodeSize::Code64) ? OpKind::MemoryESRDI : throw InvalidOperationException();
		bool shortForm = instruction.GetOp1Kind() == shortFormOpKind && (instruction.GetSegmentPrefix() == Register::None || !FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options));
		if (!shortForm)
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_args;
			info.OpCount = 1;
			info.Op0Kind = static_cast<InstrOpKind>(instruction.GetOp1Kind());
			info.Op0Index = 1;
		}
		else
		{
			info = InstrOpInfo();
			info.Flags = flags;
			info.Mnemonic = mnemonic_no_args;
		}
	}

	SimpleInstrInfo_XLAT::SimpleInstrInfo_XLAT(const std::string& mnemonic_args, const std::string& mnemonic_no_args)
	{
		this->mnemonic_args = FormatterString(mnemonic_args);
		this->mnemonic_no_args = FormatterString(mnemonic_no_args);
	}

	void SimpleInstrInfo_XLAT::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto switchTempVar_9 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var baseReg = (switchTempVar_9 == CodeSize.Unknown) ? instruction.MemoryBase : (switchTempVar_9 == CodeSize.Code16) ? Register.BX : (switchTempVar_9 == CodeSize.Code32) ? Register.EBX : (switchTempVar_9 == CodeSize.Code64) ? Register.RBX : throw new InvalidOperationException();
		auto baseReg = (switchTempVar_9 == CodeSize::Unknown) ? instruction.GetMemoryBase() : (switchTempVar_9 == CodeSize::Code16) ? Register::BX : (switchTempVar_9 == CodeSize::Code32) ? Register::EBX : (switchTempVar_9 == CodeSize::Code64) ? Register::RBX : throw InvalidOperationException();
		bool shortForm = instruction.GetMemoryBase() == baseReg && (instruction.GetSegmentPrefix() == Register::None || !FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options));
		if (!shortForm)
		{
			info = InstrOpInfo(mnemonic_args, instruction, InstrOpInfoFlags::ShowNoMemSize_ForceSize | InstrOpInfoFlags::IgnoreIndexReg);
		}
		else
		{
			info = InstrOpInfo();
			info.Mnemonic = mnemonic_no_args;
		}
	}

	SimpleInstrInfo_nop::SimpleInstrInfo_nop(std::int32_t bitness, const std::string& mnemonic, Register register_)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
		this->register_ = register_;
	}

	FormatterString SimpleInstrInfo_nop::str_xchg = FormatterString("xchg");

	void SimpleInstrInfo_nop::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
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

	void SimpleInstrInfo_STIG1::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		assert(instruction.GetOpCount() == 2);
		assert(instruction.GetOp0Kind() == OpKind::Register && instruction.GetOp0Register() == Register::ST0);
		if (!pseudoOp || !(options->GetUsePseudoOps() && instruction.GetOp1Register() == Register::ST1))
		{
			info.OpCount = 1;
			Static::Assert(InstrOpKind::Register == (InstrOpKind)0 ? 0 : -1);
			//info.Op0Kind = InstrOpKind.Register;
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(instruction.GetOp1Register());
			info.Op0Index = 1;
		}
	}

	SimpleInstrInfo_STi_ST::SimpleInstrInfo_STi_ST(const std::string& mnemonic, bool pseudoOp)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudoOp = pseudoOp;
	}

	void SimpleInstrInfo_STi_ST::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		if (pseudoOp && options->GetUsePseudoOps() && (instruction.GetOp0Register() == Register::ST1 || instruction.GetOp1Register() == Register::ST1))
		{
			info = InstrOpInfo();
			info.Mnemonic = mnemonic;
		}
		else
		{
			info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
			assert(info.Op1Register == static_cast<std::int32_t>(Register::ST0));
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(Registers::Register_ST);
		}
	}

	SimpleInstrInfo_ST_STi::SimpleInstrInfo_ST_STi(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_ST_STi::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		assert(info.Op0Register == static_cast<std::int32_t>(Register::ST0));
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(Registers::Register_ST);
	}

	SimpleInstrInfo_monitor::SimpleInstrInfo_monitor(const std::string& mnemonic, Register register1, Register register2, Register register3)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->register1 = register1;
		this->register2 = register2;
		this->register3 = register3;
	}

	void SimpleInstrInfo_monitor::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 3;
		info.Op0Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(register1);
		info.Op1Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op1Register = static_cast<std::uint8_t>(register2);
		info.Op2Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op2Register = static_cast<std::uint8_t>(register3);
		info.Op0Index = OpAccess_Read;
		info.Op1Index = OpAccess_Read;
		info.Op2Index = OpAccess_Read;
		if ((instruction.GetCodeSize() == CodeSize::Code64 || instruction.GetCodeSize() == CodeSize::Unknown) && (Register::EAX <= register2 && register2 <= Register::R15D))
		{
			info.Op1Register += 0x10;
			info.Op2Register += 0x10;
		}
	}

	SimpleInstrInfo_mwait::SimpleInstrInfo_mwait(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_mwait::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 2;
		info.Op0Kind = InstrOpKind::Register;
		info.Op1Kind = InstrOpKind::Register;
		info.Op0Index = OpAccess_Read;
		info.Op1Index = OpAccess_Read;
		switch (instruction.GetCodeSize())
		{
		case CodeSize::Code16:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::AX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(Register::ECX);
			break;
		case CodeSize::Code32:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::EAX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(Register::ECX);
			break;
		case CodeSize::Unknown:
		case CodeSize::Code64:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::RAX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(Register::RCX);
			break;
		}
	}

	SimpleInstrInfo_mwaitx::SimpleInstrInfo_mwaitx(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_mwaitx::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 3;
		info.Op0Kind = InstrOpKind::Register;
		info.Op1Kind = InstrOpKind::Register;
		info.Op2Kind = InstrOpKind::Register;
		info.Op0Index = OpAccess_Read;
		info.Op1Index = OpAccess_Read;
		info.Op2Index = OpAccess_CondRead;
		switch (instruction.GetCodeSize())
		{
		case CodeSize::Code16:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::AX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(Register::ECX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op2Register = static_cast<std::uint8_t>(Register::EBX);
			break;
		case CodeSize::Code32:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::EAX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(Register::ECX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op2Register = static_cast<std::uint8_t>(Register::EBX);
			break;
		case CodeSize::Unknown:
		case CodeSize::Code64:
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op0Register = static_cast<std::uint8_t>(Register::RAX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op1Register = static_cast<std::uint8_t>(Register::RCX);
			Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
			info.Op2Register = static_cast<std::uint8_t>(Register::RBX);
			break;
		}
	}

	SimpleInstrInfo_maskmovq::SimpleInstrInfo_maskmovq(const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_maskmovq::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		assert(instruction.GetOpCount() == 3);
		auto switchTempVar_10 = instruction.GetCodeSize();


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: var shortFormOpKind = (switchTempVar_10 == CodeSize.Unknown) ? instruction.Op0Kind : (switchTempVar_10 == CodeSize.Code16) ? OpKind.MemorySegDI : (switchTempVar_10 == CodeSize.Code32) ? OpKind.MemorySegEDI : (switchTempVar_10 == CodeSize.Code64) ? OpKind.MemorySegRDI : throw new InvalidOperationException();
		auto shortFormOpKind = (switchTempVar_10 == CodeSize::Unknown) ? instruction.GetOp0Kind() : (switchTempVar_10 == CodeSize::Code16) ? OpKind::MemorySegDI : (switchTempVar_10 == CodeSize::Code32) ? OpKind::MemorySegEDI : (switchTempVar_10 == CodeSize::Code64) ? OpKind::MemorySegRDI : throw InvalidOperationException();
		bool shortForm = instruction.GetOp0Kind() == shortFormOpKind && (instruction.GetSegmentPrefix() == Register::None || !FormatterUtils::ShowSegmentPrefix(Register::DS, instruction, options));
		if (!shortForm)
		{
			info = InstrOpInfo(mnemonic, instruction, flags);
		}
		else
		{
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
		}
	}

	SimpleInstrInfo_pblendvb::SimpleInstrInfo_pblendvb(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_pblendvb::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
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
		info.Op2Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op2Register = static_cast<std::uint8_t>(Register::XMM0);
		info.Op2Index = OpAccess_Read;
	}

	SimpleInstrInfo_reverse::SimpleInstrInfo_reverse(const std::string& mnemonic)
	{
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_reverse::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
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

	void SimpleInstrInfo_OpSize::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
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

	SimpleInstrInfo_OpSize_cc::SimpleInstrInfo_OpSize_cc(CodeSize codeSize, std::int32_t ccIndex, const std::vector<std::string>& mnemonics, const std::vector<std::string>& mnemonics_other)
	{
		this->codeSize = codeSize;
		this->ccIndex = ccIndex;
		this->mnemonics = FormatterString::Create(mnemonics);
		this->mnemonics_other = FormatterString::Create(mnemonics_other);
	}

	void SimpleInstrInfo_OpSize_cc::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		std::vector<FormatterString> mnemonics;
		if (instruction.GetCodeSize() == codeSize)
		{
			mnemonics = this->mnemonics;
		}
		else
		{
			mnemonics = mnemonics_other;
		}
		auto mnemonic = MnemonicCC::GetMnemonicCC(options, ccIndex, mnemonics);
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
	}

	SimpleInstrInfo_OpSize2::SimpleInstrInfo_OpSize2(const std::string& mnemonic, const std::string& mnemonic16, const std::string& mnemonic32, const std::string& mnemonic64, bool canUseBnd)
	{
		mnemonics = std::vector<FormatterString>(4);
		mnemonics[static_cast<std::int32_t>(CodeSize::Unknown)] = FormatterString(mnemonic);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code16)] = FormatterString(mnemonic16);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code32)] = FormatterString(mnemonic32);
		mnemonics[static_cast<std::int32_t>(CodeSize::Code64)] = FormatterString(mnemonic64);
		this->canUseBnd = canUseBnd;
	}

	void SimpleInstrInfo_OpSize2::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto mnemonic = mnemonics[static_cast<std::int32_t>(instruction.GetCodeSize())];
		auto flags = InstrOpInfoFlags::None;
		if (canUseBnd && instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_fword::SimpleInstrInfo_fword(CodeSize codeSize, InstrOpInfoFlags flags, const std::string& mnemonic, const std::string& mnemonic2)
	{
		this->codeSize = codeSize;
		this->flags = flags;
		this->mnemonic = FormatterString(mnemonic);
		this->mnemonic2 = FormatterString(mnemonic2);
	}

	void SimpleInstrInfo_fword::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		FormatterString mnemonic;
		if (instruction.GetCodeSize() == codeSize || instruction.GetCodeSize() == CodeSize::Unknown)
		{
			mnemonic = this->mnemonic;
		}
		else
		{
			mnemonic = mnemonic2;
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_jcc::SimpleInstrInfo_jcc(std::int32_t ccIndex, const std::vector<std::string>& mnemonics)
	{
		this->ccIndex = ccIndex;
		this->mnemonics = FormatterString::Create(mnemonics);
	}

	void SimpleInstrInfo_jcc::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = InstrOpInfoFlags::None;
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

	SimpleInstrInfo_bnd::SimpleInstrInfo_bnd(const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_bnd::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		auto flags = this->flags;
		if (instruction.GetHasRepnePrefix())
		{
			flags |= InstrOpInfoFlags::BndPrefix;
		}
		info = InstrOpInfo(mnemonic, instruction, flags);
	}

	SimpleInstrInfo_pops::SimpleInstrInfo_pops(const std::string& mnemonic, const std::vector<FormatterString>& pseudo_ops) : SimpleInstrInfo_pops(mnemonic, pseudo_ops, InstrOpInfoFlags::None)
	{
	}

	SimpleInstrInfo_pops::SimpleInstrInfo_pops(const std::string& mnemonic, const std::vector<FormatterString>& pseudo_ops, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->pseudo_ops = pseudo_ops;
		this->flags = flags;
	}

	void SimpleInstrInfo_pops::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, flags);
		std::int32_t imm = instruction.GetImmediate8();
		if (options->GetUsePseudoOps() && static_cast<std::uint32_t>(imm) < static_cast<std::uint32_t>(pseudo_ops.size()))
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

	void SimpleInstrInfo_pclmulqdq::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		if (options->GetUsePseudoOps())
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

	void SimpleInstrInfo_imul::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo(mnemonic, instruction, InstrOpInfoFlags::None);
		assert(info.OpCount == 3);
		if (options->GetUsePseudoOps() && info.Op0Kind == InstrOpKind::Register && info.Op1Kind == InstrOpKind::Register && info.Op0Register == info.Op1Register)
		{
			info.OpCount--;
			info.Op0Index = OpAccess_ReadWrite;
			info.Op1Kind = info.Op2Kind;
			info.Op1Index = 2;
			info.Op2Index = OpAccess_INVALID;
		}
	}

	SimpleInstrInfo_Reg16::SimpleInstrInfo_Reg16(const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_Reg16::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
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

	SimpleInstrInfo_Reg32::SimpleInstrInfo_Reg32(const std::string& mnemonic, InstrOpInfoFlags flags)
	{
		this->mnemonic = FormatterString(mnemonic);
		this->flags = flags;
	}

	void SimpleInstrInfo_Reg32::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
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

	void SimpleInstrInfo_reg::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
	{
		info = InstrOpInfo();
		info.Mnemonic = mnemonic;
		info.OpCount = 1;
		info.Op0Kind = InstrOpKind::Register;
		Static::Assert(InstrOpInfo::TEST_RegisterBits == 8 ? 0 : -1);
		info.Op0Register = static_cast<std::uint8_t>(register_);
		info.Op0Index = OpAccess_Read;
	}

	SimpleInstrInfo_invlpga::SimpleInstrInfo_invlpga(std::int32_t bitness, const std::string& mnemonic)
	{
		this->bitness = bitness;
		this->mnemonic = FormatterString(mnemonic);
	}

	void SimpleInstrInfo_invlpga::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
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
		auto switchTempVar_11 = code;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: opKind = (switchTempVar_11 == Code.DeclareByte) ? InstrOpKind.DeclareByte : (switchTempVar_11 == Code.DeclareWord) ? InstrOpKind.DeclareWord : (switchTempVar_11 == Code.DeclareDword) ? InstrOpKind.DeclareDword : (switchTempVar_11 == Code.DeclareQword) ? InstrOpKind.DeclareQword : throw new InvalidOperationException();
		opKind = (switchTempVar_11 == Code::DeclareByte) ? InstrOpKind::DeclareByte : (switchTempVar_11 == Code::DeclareWord) ? InstrOpKind::DeclareWord : (switchTempVar_11 == Code::DeclareDword) ? InstrOpKind::DeclareDword : (switchTempVar_11 == Code::DeclareQword) ? InstrOpKind::DeclareQword : throw InvalidOperationException();
	}

	void SimpleInstrInfo_DeclareData::GetOpInfo(FormatterOptions* options, const Instruction& instruction, InstrOpInfo& info)
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
