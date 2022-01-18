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

#include "Iced.Intel.Instruction.h"
#include "EncoderInternal/OpCodeHandlers.h"
#include "Static.h"
#include "ThrowHelper.h"
#include "Iced.Intel.IcedConstants.h"
#include "MnemonicUtils.h"
#include "InstructionOpCounts.g.h"
#include "MvexInfo.h"
#include "MvexMemorySizeLut.g.h"
#include "InstructionMemorySizes.g.h"
#include "EncoderCodeExtensions.h"
#include "StringOutput.h"
#include "MasmFormatter.h"
#include "Iced.Intel.InstructionInfoExtensions.h"
#include "InstructionInfoInternal/InstrInfoTable.g.h"
#include "InstructionInfoInternal/CpuidFeatureInternal.g.h"
#include "InstructionInfoInternal/RflagsInfoConstants.g.h"
#include "InstructionInfoInternal/Iced.Intel.InstructionInfoInternal.CpuidFeatureInternalData.h"
#include "InstructionUtils.h"
#include "CodeExtensions.h"

namespace Iced::Intel
{

	void Instruction::InitializeSignedImmediate(Instruction& instruction, std::int32_t operand, std::int64_t immediate)
	{
		auto opKind = GetImmediateOpKind(instruction.GetCode(), operand);
		instruction.SetOpKind(operand, opKind);
		switch (opKind)
		{
		case OpKind::Immediate8:
			// All sbyte and all byte values can be used
			if (!(std::numeric_limits<std::int8_t>::min() <= immediate && immediate <= std::numeric_limits<std::uint8_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate8_2nd:
			// All sbyte and all byte values can be used
			if (!(std::numeric_limits<std::int8_t>::min() <= immediate && immediate <= std::numeric_limits<std::uint8_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8_2nd(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate8to16:
			if (!(std::numeric_limits<std::int8_t>::min() <= immediate && immediate <= std::numeric_limits<std::int8_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate8to32:
			if (!(std::numeric_limits<std::int8_t>::min() <= immediate && immediate <= std::numeric_limits<std::int8_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate8to64:
			if (!(std::numeric_limits<std::int8_t>::min() <= immediate && immediate <= std::numeric_limits<std::int8_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate16:
			// All short and all ushort values can be used
			if (!(std::numeric_limits<std::int16_t>::min() <= immediate && immediate <= std::numeric_limits<std::uint16_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate16(static_cast<std::uint16_t>(immediate));
			break;
		case OpKind::Immediate32:
			// All int and all uint values can be used
			if (!(std::numeric_limits<std::int32_t>::min() <= immediate && immediate <= std::numeric_limits<std::uint32_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetImmediate32(static_cast<std::uint32_t>(immediate));
			break;
		case OpKind::Immediate32to64:
			if (!(std::numeric_limits<std::int32_t>::min() <= immediate && immediate <= std::numeric_limits<std::int32_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetImmediate32(static_cast<std::uint32_t>(immediate));
			break;
		case OpKind::Immediate64:
			instruction.SetImmediate64(static_cast<std::uint64_t>(immediate));
			break;
		default:
			throw ArgumentOutOfRangeException("instruction");
		}
	}

	void Instruction::InitializeUnsignedImmediate(Instruction& instruction, std::int32_t operand, std::uint64_t immediate)
	{
		auto opKind = GetImmediateOpKind(instruction.GetCode(), operand);
		instruction.SetOpKind(operand, opKind);
		switch (opKind)
		{
		case OpKind::Immediate8:
			if (immediate > std::numeric_limits<std::uint8_t>::max())
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate8_2nd:
			if (immediate > std::numeric_limits<std::uint8_t>::max())
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8_2nd(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate8to16:
			if (!(immediate <= static_cast<std::uint64_t>(std::numeric_limits<std::int8_t>::max()) || (0xFF80 <= immediate && immediate <= 0xFFFF)))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate8to32:
			if (!(immediate <= static_cast<std::uint64_t>(std::numeric_limits<std::int8_t>::max()) || (0xFFFF'FF80 <= immediate && immediate <= 0xFFFF'FFFF)))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate8to64:
			// Allow 00..7F and FFFF_FFFF_FFFF_FF80..FFFF_FFFF_FFFF_FFFF
			if ((immediate + 0x80) > std::numeric_limits<std::uint8_t>::max())
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate8(static_cast<std::uint8_t>(immediate));
			break;
		case OpKind::Immediate16:
			if (immediate > std::numeric_limits<std::uint16_t>::max())
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetInternalImmediate16(static_cast<std::uint16_t>(immediate));
			break;
		case OpKind::Immediate32:
			if (immediate > std::numeric_limits<std::uint32_t>::max())
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetImmediate32(static_cast<std::uint32_t>(immediate));
			break;
		case OpKind::Immediate32to64:
			// Allow 0..7FFF_FFFF and FFFF_FFFF_8000_0000..FFFF_FFFF_FFFF_FFFF
			if ((immediate + 0x8000'0000) > static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max()))
			{
				throw ArgumentOutOfRangeException("immediate");
			}
			instruction.SetImmediate32(static_cast<std::uint32_t>(immediate));
			break;
		case OpKind::Immediate64:
			instruction.SetImmediate64(immediate);
			break;
		default:
			throw ArgumentOutOfRangeException("instruction");
		}
	}

	OpKind Instruction::GetImmediateOpKind(Iced::Intel::Code code, std::int32_t operand)
	{
		auto handlers = EncoderInternal::OpCodeHandlers::Handlers;
		if (static_cast<std::uint32_t>(code) >= static_cast<std::uint32_t>(handlers.size()))
		{
			throw ArgumentOutOfRangeException("code");
		}
		auto operands = handlers[static_cast<std::int32_t>(code)]->Operands;
		if (static_cast<std::uint32_t>(operand) >= static_cast<std::uint32_t>(operands.size()))
		{
			throw ArgumentOutOfRangeException("operand", std::format("{0:s} doesn't have at least {1:s} operands", to_string(code), to_string(operand + 1)));
		}
		auto opKind = operands[operand]->GetImmediateOpKind();
		OpKind opKindPrev = operands[operand - 1]->GetImmediateOpKind();
		if (opKind == OpKind::Immediate8 && operand > 0 && operand + 1 == operands.size() && (opKindPrev == OpKind::Immediate8 || opKindPrev == OpKind::Immediate16))
		{
			opKind = OpKind::Immediate8_2nd;
		}
		if (opKind == static_cast<OpKind>(-1))
		{
			throw std::invalid_argument(std::format("{0:s}'s op{1:s} isn't an immediate operand", to_string(code), to_string(operand)));
		}
		return opKind;
	}

	OpKind Instruction::GetNearBranchOpKind(Iced::Intel::Code code, std::int32_t operand)
	{
		auto handlers = EncoderInternal::OpCodeHandlers::Handlers;
		if (static_cast<std::uint32_t>(code) >= static_cast<std::uint32_t>(handlers.size()))
		{
			throw ArgumentOutOfRangeException("code");
		}
		auto operands = handlers[static_cast<std::int32_t>(code)]->Operands;
		if (static_cast<std::uint32_t>(operand) >= static_cast<std::uint32_t>(operands.size()))
		{
			throw ArgumentOutOfRangeException("operand", std::format("{0:s} doesn't have at least {1:s} operands", to_string(code), to_string(operand + 1)));
		}
		auto opKind = operands[operand]->GetNearBranchOpKind();
		if (opKind == static_cast<OpKind>(-1))
		{
			throw std::invalid_argument(std::format("{0:s}'s op{1:s} isn't a near branch operand", to_string(code), to_string(operand)));
		}
		return opKind;
	}

	OpKind Instruction::GetFarBranchOpKind(Iced::Intel::Code code, std::int32_t operand)
	{
		auto handlers = EncoderInternal::OpCodeHandlers::Handlers;
		if (static_cast<std::uint32_t>(code) >= static_cast<std::uint32_t>(handlers.size()))
		{
			throw ArgumentOutOfRangeException("code");
		}
		auto operands = handlers[static_cast<std::int32_t>(code)]->Operands;
		if (static_cast<std::uint32_t>(operand) >= static_cast<std::uint32_t>(operands.size()))
		{
			throw ArgumentOutOfRangeException("operand", std::format("{0:s} doesn't have at least {1:s} operands", to_string(code), to_string(operand + 1)));
		}
		auto opKind = operands[operand]->GetFarBranchOpKind();
		if (opKind == static_cast<OpKind>(-1))
		{
			throw std::invalid_argument(std::format("{0:s}'s op{1:s} isn't a far branch operand", to_string(code), to_string(operand)));
		}
		return opKind;
	}

	Instruction Instruction::CreateString_Reg_SegRSI(Iced::Intel::Code code, std::int32_t addressSize, Register register_, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		if (repPrefix == RepPrefixKind::Repe)
		{
			instruction.InternalSetHasRepePrefix();
		}
		else if (repPrefix == RepPrefixKind::Repne)
		{
			instruction.InternalSetHasRepnePrefix();
		}
		else
		{
			assert(repPrefix == RepPrefixKind::None);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		if (addressSize == 64)
		{
			instruction.SetOp1Kind(OpKind::MemorySegRSI);
		}
		else if (addressSize == 32)
		{
			instruction.SetOp1Kind(OpKind::MemorySegESI);
		}
		else if (addressSize == 16)
		{
			instruction.SetOp1Kind(OpKind::MemorySegSI);
		}
		else
		{
			throw ArgumentOutOfRangeException("addressSize");
		}
		instruction.SetSegmentPrefix(segmentPrefix);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::CreateString_Reg_ESRDI(Iced::Intel::Code code, std::int32_t addressSize, Register register_, RepPrefixKind repPrefix)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		if (repPrefix == RepPrefixKind::Repe)
		{
			instruction.InternalSetHasRepePrefix();
		}
		else if (repPrefix == RepPrefixKind::Repne)
		{
			instruction.InternalSetHasRepnePrefix();
		}
		else
		{
			assert(repPrefix == RepPrefixKind::None);
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		if (addressSize == 64)
		{
			instruction.SetOp1Kind(OpKind::MemoryESRDI);
		}
		else if (addressSize == 32)
		{
			instruction.SetOp1Kind(OpKind::MemoryESEDI);
		}
		else if (addressSize == 16)
		{
			instruction.SetOp1Kind(OpKind::MemoryESDI);
		}
		else
		{
			throw ArgumentOutOfRangeException("addressSize");
		}
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::CreateString_ESRDI_Reg(Iced::Intel::Code code, std::int32_t addressSize, Register register_, RepPrefixKind repPrefix)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		if (repPrefix == RepPrefixKind::Repe)
		{
			instruction.InternalSetHasRepePrefix();
		}
		else if (repPrefix == RepPrefixKind::Repne)
		{
			instruction.InternalSetHasRepnePrefix();
		}
		else
		{
			assert(repPrefix == RepPrefixKind::None);
		}
		if (addressSize == 64)
		{
			instruction.SetOp0Kind(OpKind::MemoryESRDI);
		}
		else if (addressSize == 32)
		{
			instruction.SetOp0Kind(OpKind::MemoryESEDI);
		}
		else if (addressSize == 16)
		{
			instruction.SetOp0Kind(OpKind::MemoryESDI);
		}
		else
		{
			throw ArgumentOutOfRangeException("addressSize");
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register_);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::CreateString_SegRSI_ESRDI(Iced::Intel::Code code, std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		if (repPrefix == RepPrefixKind::Repe)
		{
			instruction.InternalSetHasRepePrefix();
		}
		else if (repPrefix == RepPrefixKind::Repne)
		{
			instruction.InternalSetHasRepnePrefix();
		}
		else
		{
			assert(repPrefix == RepPrefixKind::None);
		}
		if (addressSize == 64)
		{
			instruction.SetOp0Kind(OpKind::MemorySegRSI);
			instruction.SetOp1Kind(OpKind::MemoryESRDI);
		}
		else if (addressSize == 32)
		{
			instruction.SetOp0Kind(OpKind::MemorySegESI);
			instruction.SetOp1Kind(OpKind::MemoryESEDI);
		}
		else if (addressSize == 16)
		{
			instruction.SetOp0Kind(OpKind::MemorySegSI);
			instruction.SetOp1Kind(OpKind::MemoryESDI);
		}
		else
		{
			throw ArgumentOutOfRangeException("addressSize");
		}
		instruction.SetSegmentPrefix(segmentPrefix);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::CreateString_ESRDI_SegRSI(Iced::Intel::Code code, std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		if (repPrefix == RepPrefixKind::Repe)
		{
			instruction.InternalSetHasRepePrefix();
		}
		else if (repPrefix == RepPrefixKind::Repne)
		{
			instruction.InternalSetHasRepnePrefix();
		}
		else
		{
			assert(repPrefix == RepPrefixKind::None);
		}
		if (addressSize == 64)
		{
			instruction.SetOp0Kind(OpKind::MemoryESRDI);
			instruction.SetOp1Kind(OpKind::MemorySegRSI);
		}
		else if (addressSize == 32)
		{
			instruction.SetOp0Kind(OpKind::MemoryESEDI);
			instruction.SetOp1Kind(OpKind::MemorySegESI);
		}
		else if (addressSize == 16)
		{
			instruction.SetOp0Kind(OpKind::MemoryESDI);
			instruction.SetOp1Kind(OpKind::MemorySegSI);
		}
		else
		{
			throw ArgumentOutOfRangeException("addressSize");
		}
		instruction.SetSegmentPrefix(segmentPrefix);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::CreateMaskmov(Iced::Intel::Code code, std::int32_t addressSize, Register register1, Register register2, Register segmentPrefix)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		if (addressSize == 64)
		{
			instruction.SetOp0Kind(OpKind::MemorySegRDI);
		}
		else if (addressSize == 32)
		{
			instruction.SetOp0Kind(OpKind::MemorySegEDI);
		}
		else if (addressSize == 16)
		{
			instruction.SetOp0Kind(OpKind::MemorySegDI);
		}
		else
		{
			throw ArgumentOutOfRangeException("addressSize");
		}
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register2);
		instruction.SetSegmentPrefix(segmentPrefix);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	void Instruction::InitMemoryOperand(Instruction& instruction, MemoryOperand const memory)
	{
		instruction.SetInternalMemoryBase(memory.Base);
		instruction.SetInternalMemoryIndex(memory.Index);
		instruction.SetMemoryIndexScale(memory.Scale);
		instruction.SetMemoryDisplSize(memory.DisplSize);
		instruction.SetMemoryDisplacement64(static_cast<std::uint64_t>(memory.Displacement));
		instruction.SetBroadcast(memory.IsBroadcast);
		instruction.SetSegmentPrefix(memory.SegmentPrefix);
	}

	Instruction Instruction::Create(Iced::Intel::Code code)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		assert(instruction.GetOpCount() == 1);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		InitializeSignedImmediate(instruction, 0, immediate);
		assert(instruction.GetOpCount() == 1);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		InitializeUnsignedImmediate(instruction, 0, immediate);
		assert(instruction.GetOpCount() == 1);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, MemoryOperand const memory)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		assert(instruction.GetOpCount() == 1);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		InitializeSignedImmediate(instruction, 1, immediate);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		InitializeUnsignedImmediate(instruction, 1, immediate);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, std::int64_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		InitializeSignedImmediate(instruction, 1, immediate);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, std::uint64_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		InitializeUnsignedImmediate(instruction, 1, immediate);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, MemoryOperand const memory)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		instruction.SetOp1Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, std::int32_t immediate, Register register_)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		InitializeSignedImmediate(instruction, 0, immediate);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register_);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, std::uint32_t immediate, Register register_)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		InitializeUnsignedImmediate(instruction, 0, immediate);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register_);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, std::int32_t immediate1, std::int32_t immediate2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		InitializeSignedImmediate(instruction, 0, immediate1);
		InitializeSignedImmediate(instruction, 1, immediate2);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, std::uint32_t immediate1, std::uint32_t immediate2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		InitializeUnsignedImmediate(instruction, 0, immediate1);
		InitializeUnsignedImmediate(instruction, 1, immediate2);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, MemoryOperand const memory, Register register_)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register_);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, MemoryOperand const memory, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		InitializeSignedImmediate(instruction, 1, immediate);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, MemoryOperand const memory, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		InitializeUnsignedImmediate(instruction, 1, immediate);
		assert(instruction.GetOpCount() == 2);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		InitializeSignedImmediate(instruction, 2, immediate);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		InitializeUnsignedImmediate(instruction, 2, immediate);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, MemoryOperand const memory)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		instruction.SetOp2Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, std::int32_t immediate1, std::int32_t immediate2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		InitializeSignedImmediate(instruction, 1, immediate1);
		InitializeSignedImmediate(instruction, 2, immediate2);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, std::uint32_t immediate1, std::uint32_t immediate2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		InitializeUnsignedImmediate(instruction, 1, immediate1);
		InitializeUnsignedImmediate(instruction, 2, immediate2);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, MemoryOperand const memory, Register register2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		instruction.SetOp1Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register2);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, MemoryOperand const memory, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		instruction.SetOp1Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		InitializeSignedImmediate(instruction, 2, immediate);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register_, MemoryOperand const memory, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register_);
		instruction.SetOp1Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		InitializeUnsignedImmediate(instruction, 2, immediate);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, MemoryOperand const memory, Register register1, Register register2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register2);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, MemoryOperand const memory, Register register_, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register_);
		InitializeSignedImmediate(instruction, 2, immediate);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, MemoryOperand const memory, Register register_, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register_);
		InitializeUnsignedImmediate(instruction, 2, immediate);
		assert(instruction.GetOpCount() == 3);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3, Register register4)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op3Kind = OpKind.Register;
		instruction.SetOp3Register(register4);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		InitializeSignedImmediate(instruction, 3, immediate);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		InitializeUnsignedImmediate(instruction, 3, immediate);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3, MemoryOperand const memory)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		instruction.SetOp3Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, std::int32_t immediate1, std::int32_t immediate2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		InitializeSignedImmediate(instruction, 2, immediate1);
		InitializeSignedImmediate(instruction, 3, immediate2);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, std::uint32_t immediate1, std::uint32_t immediate2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		InitializeUnsignedImmediate(instruction, 2, immediate1);
		InitializeUnsignedImmediate(instruction, 3, immediate2);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, MemoryOperand const memory, Register register3)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		instruction.SetOp2Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op3Kind = OpKind.Register;
		instruction.SetOp3Register(register3);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, MemoryOperand const memory, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		instruction.SetOp2Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		InitializeSignedImmediate(instruction, 3, immediate);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, MemoryOperand const memory, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		instruction.SetOp2Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		InitializeUnsignedImmediate(instruction, 3, immediate);
		assert(instruction.GetOpCount() == 4);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3, Register register4, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op3Kind = OpKind.Register;
		instruction.SetOp3Register(register4);
		InitializeSignedImmediate(instruction, 4, immediate);
		assert(instruction.GetOpCount() == 5);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3, Register register4, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op3Kind = OpKind.Register;
		instruction.SetOp3Register(register4);
		InitializeUnsignedImmediate(instruction, 4, immediate);
		assert(instruction.GetOpCount() == 5);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3, MemoryOperand const memory, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		instruction.SetOp3Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		InitializeSignedImmediate(instruction, 4, immediate);
		assert(instruction.GetOpCount() == 5);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, Register register3, MemoryOperand const memory, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op2Kind = OpKind.Register;
		instruction.SetOp2Register(register3);
		instruction.SetOp3Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		InitializeUnsignedImmediate(instruction, 4, immediate);
		assert(instruction.GetOpCount() == 5);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, MemoryOperand const memory, Register register3, std::int32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		instruction.SetOp2Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op3Kind = OpKind.Register;
		instruction.SetOp3Register(register3);
		InitializeSignedImmediate(instruction, 4, immediate);
		assert(instruction.GetOpCount() == 5);
		return instruction;
	}

	Instruction Instruction::Create(Iced::Intel::Code code, Register register1, Register register2, MemoryOperand const memory, Register register3, std::uint32_t immediate)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op0Kind = OpKind.Register;
		instruction.SetOp0Register(register1);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op1Kind = OpKind.Register;
		instruction.SetOp1Register(register2);
		instruction.SetOp2Kind(OpKind::Memory);
		InitMemoryOperand(instruction, memory);
		Static::Assert(OpKind::Register == (Iced::Intel::OpKind)0 ? 0 : -1);
		//instruction.Op3Kind = OpKind.Register;
		instruction.SetOp3Register(register3);
		InitializeUnsignedImmediate(instruction, 4, immediate);
		assert(instruction.GetOpCount() == 5);
		return instruction;
	}

	Instruction Instruction::CreateBranch(Iced::Intel::Code code, std::uint64_t target)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(GetNearBranchOpKind(code, 0));
		instruction.SetNearBranch64(target);
		assert(instruction.GetOpCount() == 1);
		return instruction;
	}

	Instruction Instruction::CreateBranch(Iced::Intel::Code code, std::uint16_t selector, std::uint32_t offset)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(code);
		instruction.SetOp0Kind(GetFarBranchOpKind(code, 0));
		instruction.SetFarBranchSelector(selector);
		instruction.SetFarBranch32(offset);
		assert(instruction.GetOpCount() == 1);
		return instruction;
	}

	Instruction Instruction::CreateXbegin(std::int32_t bitness, std::uint64_t target)
	{
		Instruction instruction = Iced::Intel::Instruction();
		switch (bitness)
		{
		case 16:
			instruction.SetCode(Code::Xbegin_rel16);
			instruction.SetOp0Kind(OpKind::NearBranch32);
			instruction.SetNearBranch32(static_cast<std::uint32_t>(target));
			break;
		case 32:
			instruction.SetCode(Code::Xbegin_rel32);
			instruction.SetOp0Kind(OpKind::NearBranch32);
			instruction.SetNearBranch32(static_cast<std::uint32_t>(target));
			break;
		case 64:
			instruction.SetCode(Code::Xbegin_rel32);
			instruction.SetOp0Kind(OpKind::NearBranch64);
			instruction.SetNearBranch64(target);
			break;
		default:
			throw ArgumentOutOfRangeException("bitness");
		}
		assert(instruction.GetOpCount() == 1);
		return instruction;
	}

	Instruction Instruction::CreateOutsb(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_SegRSI(Code::Outsb_DX_m8, addressSize, Register::DX, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepOutsb(std::int32_t addressSize)
	{
		return CreateString_Reg_SegRSI(Code::Outsb_DX_m8, addressSize, Register::DX, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateOutsw(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_SegRSI(Code::Outsw_DX_m16, addressSize, Register::DX, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepOutsw(std::int32_t addressSize)
	{
		return CreateString_Reg_SegRSI(Code::Outsw_DX_m16, addressSize, Register::DX, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateOutsd(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_SegRSI(Code::Outsd_DX_m32, addressSize, Register::DX, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepOutsd(std::int32_t addressSize)
	{
		return CreateString_Reg_SegRSI(Code::Outsd_DX_m32, addressSize, Register::DX, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateLodsb(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_SegRSI(Code::Lodsb_AL_m8, addressSize, Register::AL, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepLodsb(std::int32_t addressSize)
	{
		return CreateString_Reg_SegRSI(Code::Lodsb_AL_m8, addressSize, Register::AL, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateLodsw(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_SegRSI(Code::Lodsw_AX_m16, addressSize, Register::AX, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepLodsw(std::int32_t addressSize)
	{
		return CreateString_Reg_SegRSI(Code::Lodsw_AX_m16, addressSize, Register::AX, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateLodsd(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_SegRSI(Code::Lodsd_EAX_m32, addressSize, Register::EAX, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepLodsd(std::int32_t addressSize)
	{
		return CreateString_Reg_SegRSI(Code::Lodsd_EAX_m32, addressSize, Register::EAX, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateLodsq(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_SegRSI(Code::Lodsq_RAX_m64, addressSize, Register::RAX, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepLodsq(std::int32_t addressSize)
	{
		return CreateString_Reg_SegRSI(Code::Lodsq_RAX_m64, addressSize, Register::RAX, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateScasb(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_ESRDI(Code::Scasb_AL_m8, addressSize, Register::AL, repPrefix);
	}

	Instruction Instruction::CreateRepeScasb(std::int32_t addressSize)
	{
		return CreateString_Reg_ESRDI(Code::Scasb_AL_m8, addressSize, Register::AL, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateRepneScasb(std::int32_t addressSize)
	{
		return CreateString_Reg_ESRDI(Code::Scasb_AL_m8, addressSize, Register::AL, RepPrefixKind::Repne);
	}

	Instruction Instruction::CreateScasw(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_ESRDI(Code::Scasw_AX_m16, addressSize, Register::AX, repPrefix);
	}

	Instruction Instruction::CreateRepeScasw(std::int32_t addressSize)
	{
		return CreateString_Reg_ESRDI(Code::Scasw_AX_m16, addressSize, Register::AX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateRepneScasw(std::int32_t addressSize)
	{
		return CreateString_Reg_ESRDI(Code::Scasw_AX_m16, addressSize, Register::AX, RepPrefixKind::Repne);
	}

	Instruction Instruction::CreateScasd(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_ESRDI(Code::Scasd_EAX_m32, addressSize, Register::EAX, repPrefix);
	}

	Instruction Instruction::CreateRepeScasd(std::int32_t addressSize)
	{
		return CreateString_Reg_ESRDI(Code::Scasd_EAX_m32, addressSize, Register::EAX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateRepneScasd(std::int32_t addressSize)
	{
		return CreateString_Reg_ESRDI(Code::Scasd_EAX_m32, addressSize, Register::EAX, RepPrefixKind::Repne);
	}

	Instruction Instruction::CreateScasq(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_Reg_ESRDI(Code::Scasq_RAX_m64, addressSize, Register::RAX, repPrefix);
	}

	Instruction Instruction::CreateRepeScasq(std::int32_t addressSize)
	{
		return CreateString_Reg_ESRDI(Code::Scasq_RAX_m64, addressSize, Register::RAX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateRepneScasq(std::int32_t addressSize)
	{
		return CreateString_Reg_ESRDI(Code::Scasq_RAX_m64, addressSize, Register::RAX, RepPrefixKind::Repne);
	}

	Instruction Instruction::CreateInsb(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_Reg(Code::Insb_m8_DX, addressSize, Register::DX, repPrefix);
	}

	Instruction Instruction::CreateRepInsb(std::int32_t addressSize)
	{
		return CreateString_ESRDI_Reg(Code::Insb_m8_DX, addressSize, Register::DX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateInsw(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_Reg(Code::Insw_m16_DX, addressSize, Register::DX, repPrefix);
	}

	Instruction Instruction::CreateRepInsw(std::int32_t addressSize)
	{
		return CreateString_ESRDI_Reg(Code::Insw_m16_DX, addressSize, Register::DX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateInsd(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_Reg(Code::Insd_m32_DX, addressSize, Register::DX, repPrefix);
	}

	Instruction Instruction::CreateRepInsd(std::int32_t addressSize)
	{
		return CreateString_ESRDI_Reg(Code::Insd_m32_DX, addressSize, Register::DX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateStosb(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_Reg(Code::Stosb_m8_AL, addressSize, Register::AL, repPrefix);
	}

	Instruction Instruction::CreateRepStosb(std::int32_t addressSize)
	{
		return CreateString_ESRDI_Reg(Code::Stosb_m8_AL, addressSize, Register::AL, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateStosw(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_Reg(Code::Stosw_m16_AX, addressSize, Register::AX, repPrefix);
	}

	Instruction Instruction::CreateRepStosw(std::int32_t addressSize)
	{
		return CreateString_ESRDI_Reg(Code::Stosw_m16_AX, addressSize, Register::AX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateStosd(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_Reg(Code::Stosd_m32_EAX, addressSize, Register::EAX, repPrefix);
	}

	Instruction Instruction::CreateRepStosd(std::int32_t addressSize)
	{
		return CreateString_ESRDI_Reg(Code::Stosd_m32_EAX, addressSize, Register::EAX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateStosq(std::int32_t addressSize, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_Reg(Code::Stosq_m64_RAX, addressSize, Register::RAX, repPrefix);
	}

	Instruction Instruction::CreateRepStosq(std::int32_t addressSize)
	{
		return CreateString_ESRDI_Reg(Code::Stosq_m64_RAX, addressSize, Register::RAX, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateCmpsb(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsb_m8_m8, addressSize, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepeCmpsb(std::int32_t addressSize)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsb_m8_m8, addressSize, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateRepneCmpsb(std::int32_t addressSize)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsb_m8_m8, addressSize, Register::None, RepPrefixKind::Repne);
	}

	Instruction Instruction::CreateCmpsw(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsw_m16_m16, addressSize, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepeCmpsw(std::int32_t addressSize)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsw_m16_m16, addressSize, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateRepneCmpsw(std::int32_t addressSize)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsw_m16_m16, addressSize, Register::None, RepPrefixKind::Repne);
	}

	Instruction Instruction::CreateCmpsd(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsd_m32_m32, addressSize, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepeCmpsd(std::int32_t addressSize)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsd_m32_m32, addressSize, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateRepneCmpsd(std::int32_t addressSize)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsd_m32_m32, addressSize, Register::None, RepPrefixKind::Repne);
	}

	Instruction Instruction::CreateCmpsq(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsq_m64_m64, addressSize, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepeCmpsq(std::int32_t addressSize)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsq_m64_m64, addressSize, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateRepneCmpsq(std::int32_t addressSize)
	{
		return CreateString_SegRSI_ESRDI(Code::Cmpsq_m64_m64, addressSize, Register::None, RepPrefixKind::Repne);
	}

	Instruction Instruction::CreateMovsb(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_SegRSI(Code::Movsb_m8_m8, addressSize, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepMovsb(std::int32_t addressSize)
	{
		return CreateString_ESRDI_SegRSI(Code::Movsb_m8_m8, addressSize, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateMovsw(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_SegRSI(Code::Movsw_m16_m16, addressSize, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepMovsw(std::int32_t addressSize)
	{
		return CreateString_ESRDI_SegRSI(Code::Movsw_m16_m16, addressSize, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateMovsd(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_SegRSI(Code::Movsd_m32_m32, addressSize, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepMovsd(std::int32_t addressSize)
	{
		return CreateString_ESRDI_SegRSI(Code::Movsd_m32_m32, addressSize, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateMovsq(std::int32_t addressSize, Register segmentPrefix, RepPrefixKind repPrefix)
	{
		return CreateString_ESRDI_SegRSI(Code::Movsq_m64_m64, addressSize, segmentPrefix, repPrefix);
	}

	Instruction Instruction::CreateRepMovsq(std::int32_t addressSize)
	{
		return CreateString_ESRDI_SegRSI(Code::Movsq_m64_m64, addressSize, Register::None, RepPrefixKind::Repe);
	}

	Instruction Instruction::CreateMaskmovq(std::int32_t addressSize, Register register1, Register register2, Register segmentPrefix)
	{
		return CreateMaskmov(Code::Maskmovq_rDI_mm_mm, addressSize, register1, register2, segmentPrefix);
	}

	Instruction Instruction::CreateMaskmovdqu(std::int32_t addressSize, Register register1, Register register2, Register segmentPrefix)
	{
		return CreateMaskmov(Code::Maskmovdqu_rDI_xmm_xmm, addressSize, register1, register2, segmentPrefix);
	}

	Instruction Instruction::CreateVmaskmovdqu(std::int32_t addressSize, Register register1, Register register2, Register segmentPrefix)
	{
		return CreateMaskmov(Code::VEX_Vmaskmovdqu_rDI_xmm_xmm, addressSize, register1, register2, segmentPrefix);
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(1);
		instruction.SetDeclareByteValue(0, b0);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(2);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(3);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(4);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(5);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(6);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(7);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(8);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7, std::uint8_t b8)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(9);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		instruction.SetDeclareByteValue(8, b8);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7, std::uint8_t b8, std::uint8_t b9)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(10);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		instruction.SetDeclareByteValue(8, b8);
		instruction.SetDeclareByteValue(9, b9);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7, std::uint8_t b8, std::uint8_t b9, std::uint8_t b10)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(11);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		instruction.SetDeclareByteValue(8, b8);
		instruction.SetDeclareByteValue(9, b9);
		instruction.SetDeclareByteValue(10, b10);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7, std::uint8_t b8, std::uint8_t b9, std::uint8_t b10, std::uint8_t b11)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(12);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		instruction.SetDeclareByteValue(8, b8);
		instruction.SetDeclareByteValue(9, b9);
		instruction.SetDeclareByteValue(10, b10);
		instruction.SetDeclareByteValue(11, b11);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7, std::uint8_t b8, std::uint8_t b9, std::uint8_t b10, std::uint8_t b11, std::uint8_t b12)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(13);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		instruction.SetDeclareByteValue(8, b8);
		instruction.SetDeclareByteValue(9, b9);
		instruction.SetDeclareByteValue(10, b10);
		instruction.SetDeclareByteValue(11, b11);
		instruction.SetDeclareByteValue(12, b12);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7, std::uint8_t b8, std::uint8_t b9, std::uint8_t b10, std::uint8_t b11, std::uint8_t b12, std::uint8_t b13)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(14);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		instruction.SetDeclareByteValue(8, b8);
		instruction.SetDeclareByteValue(9, b9);
		instruction.SetDeclareByteValue(10, b10);
		instruction.SetDeclareByteValue(11, b11);
		instruction.SetDeclareByteValue(12, b12);
		instruction.SetDeclareByteValue(13, b13);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7, std::uint8_t b8, std::uint8_t b9, std::uint8_t b10, std::uint8_t b11, std::uint8_t b12, std::uint8_t b13, std::uint8_t b14)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(15);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		instruction.SetDeclareByteValue(8, b8);
		instruction.SetDeclareByteValue(9, b9);
		instruction.SetDeclareByteValue(10, b10);
		instruction.SetDeclareByteValue(11, b11);
		instruction.SetDeclareByteValue(12, b12);
		instruction.SetDeclareByteValue(13, b13);
		instruction.SetDeclareByteValue(14, b14);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::uint8_t b0, std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6, std::uint8_t b7, std::uint8_t b8, std::uint8_t b9, std::uint8_t b10, std::uint8_t b11, std::uint8_t b12, std::uint8_t b13, std::uint8_t b14, std::uint8_t b15)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(16);
		instruction.SetDeclareByteValue(0, b0);
		instruction.SetDeclareByteValue(1, b1);
		instruction.SetDeclareByteValue(2, b2);
		instruction.SetDeclareByteValue(3, b3);
		instruction.SetDeclareByteValue(4, b4);
		instruction.SetDeclareByteValue(5, b5);
		instruction.SetDeclareByteValue(6, b6);
		instruction.SetDeclareByteValue(7, b7);
		instruction.SetDeclareByteValue(8, b8);
		instruction.SetDeclareByteValue(9, b9);
		instruction.SetDeclareByteValue(10, b10);
		instruction.SetDeclareByteValue(11, b11);
		instruction.SetDeclareByteValue(12, b12);
		instruction.SetDeclareByteValue(13, b13);
		instruction.SetDeclareByteValue(14, b14);
		instruction.SetDeclareByteValue(15, b15);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareByte(std::vector<std::uint8_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		return CreateDeclareByte(data, 0, (std::int32_t)data.size());
	}

	Instruction Instruction::CreateDeclareByte(std::vector<std::uint8_t>& data, std::int32_t index, std::int32_t length)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		if (static_cast<std::uint32_t>(length) - 1 > 16 - 1)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_length();
		}
		if (static_cast<std::uint64_t>(static_cast<std::uint32_t>(index)) + static_cast<std::uint32_t>(length) > static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareByte);
		instruction.SetInternalDeclareDataCount(static_cast<std::uint32_t>(length));
		for (std::int32_t i = 0; i < length; i++)
		{
			instruction.SetDeclareByteValue(i, data[index + i]);
		}
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::uint16_t w0)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(1);
		instruction.SetDeclareWordValue(0, w0);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::uint16_t w0, std::uint16_t w1)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(2);
		instruction.SetDeclareWordValue(0, w0);
		instruction.SetDeclareWordValue(1, w1);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::uint16_t w0, std::uint16_t w1, std::uint16_t w2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(3);
		instruction.SetDeclareWordValue(0, w0);
		instruction.SetDeclareWordValue(1, w1);
		instruction.SetDeclareWordValue(2, w2);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::uint16_t w0, std::uint16_t w1, std::uint16_t w2, std::uint16_t w3)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(4);
		instruction.SetDeclareWordValue(0, w0);
		instruction.SetDeclareWordValue(1, w1);
		instruction.SetDeclareWordValue(2, w2);
		instruction.SetDeclareWordValue(3, w3);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::uint16_t w0, std::uint16_t w1, std::uint16_t w2, std::uint16_t w3, std::uint16_t w4)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(5);
		instruction.SetDeclareWordValue(0, w0);
		instruction.SetDeclareWordValue(1, w1);
		instruction.SetDeclareWordValue(2, w2);
		instruction.SetDeclareWordValue(3, w3);
		instruction.SetDeclareWordValue(4, w4);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::uint16_t w0, std::uint16_t w1, std::uint16_t w2, std::uint16_t w3, std::uint16_t w4, std::uint16_t w5)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(6);
		instruction.SetDeclareWordValue(0, w0);
		instruction.SetDeclareWordValue(1, w1);
		instruction.SetDeclareWordValue(2, w2);
		instruction.SetDeclareWordValue(3, w3);
		instruction.SetDeclareWordValue(4, w4);
		instruction.SetDeclareWordValue(5, w5);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::uint16_t w0, std::uint16_t w1, std::uint16_t w2, std::uint16_t w3, std::uint16_t w4, std::uint16_t w5, std::uint16_t w6)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(7);
		instruction.SetDeclareWordValue(0, w0);
		instruction.SetDeclareWordValue(1, w1);
		instruction.SetDeclareWordValue(2, w2);
		instruction.SetDeclareWordValue(3, w3);
		instruction.SetDeclareWordValue(4, w4);
		instruction.SetDeclareWordValue(5, w5);
		instruction.SetDeclareWordValue(6, w6);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::uint16_t w0, std::uint16_t w1, std::uint16_t w2, std::uint16_t w3, std::uint16_t w4, std::uint16_t w5, std::uint16_t w6, std::uint16_t w7)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(8);
		instruction.SetDeclareWordValue(0, w0);
		instruction.SetDeclareWordValue(1, w1);
		instruction.SetDeclareWordValue(2, w2);
		instruction.SetDeclareWordValue(3, w3);
		instruction.SetDeclareWordValue(4, w4);
		instruction.SetDeclareWordValue(5, w5);
		instruction.SetDeclareWordValue(6, w6);
		instruction.SetDeclareWordValue(7, w7);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::vector<std::uint8_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		return CreateDeclareWord(data, 0, (std::int32_t)data.size());
	}

	Instruction Instruction::CreateDeclareWord(std::vector<std::uint8_t>& data, std::int32_t index, std::int32_t length)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		if (static_cast<std::uint32_t>(length) - 1 > 16 - 1 || (static_cast<std::uint32_t>(length) & 1) != 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_length();
		}
		if (static_cast<std::uint64_t>(static_cast<std::uint32_t>(index)) + static_cast<std::uint32_t>(length) > static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(static_cast<std::uint32_t>(length) / 2);
		for (std::int32_t i = 0; i < length; i += 2)
		{
			std::uint32_t v = data[index + i] | (static_cast<std::uint32_t>(data[index + i + 1]) << 8);
			instruction.SetDeclareWordValue(i / 2, static_cast<std::uint16_t>(v));
		}
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareWord(std::vector<std::uint16_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		return CreateDeclareWord(data, 0, (std::int32_t)data.size());
	}

	Instruction Instruction::CreateDeclareWord(std::vector<std::uint16_t>& data, std::int32_t index, std::int32_t length)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		if (static_cast<std::uint32_t>(length) - 1 > 8 - 1)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_length();
		}
		if (static_cast<std::uint64_t>(static_cast<std::uint32_t>(index)) + static_cast<std::uint32_t>(length) > static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareWord);
		instruction.SetInternalDeclareDataCount(static_cast<std::uint32_t>(length));
		for (std::int32_t i = 0; i < length; i++)
		{
			instruction.SetDeclareWordValue(i, data[index + i]);
		}
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareDword(std::uint32_t d0)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareDword);
		instruction.SetInternalDeclareDataCount(1);
		instruction.SetDeclareDwordValue(0, d0);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareDword(std::uint32_t d0, std::uint32_t d1)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareDword);
		instruction.SetInternalDeclareDataCount(2);
		instruction.SetDeclareDwordValue(0, d0);
		instruction.SetDeclareDwordValue(1, d1);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareDword(std::uint32_t d0, std::uint32_t d1, std::uint32_t d2)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareDword);
		instruction.SetInternalDeclareDataCount(3);
		instruction.SetDeclareDwordValue(0, d0);
		instruction.SetDeclareDwordValue(1, d1);
		instruction.SetDeclareDwordValue(2, d2);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareDword(std::uint32_t d0, std::uint32_t d1, std::uint32_t d2, std::uint32_t d3)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareDword);
		instruction.SetInternalDeclareDataCount(4);
		instruction.SetDeclareDwordValue(0, d0);
		instruction.SetDeclareDwordValue(1, d1);
		instruction.SetDeclareDwordValue(2, d2);
		instruction.SetDeclareDwordValue(3, d3);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareDword(std::vector<std::uint8_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		return CreateDeclareDword(data, 0, (std::int32_t)data.size());
	}

	Instruction Instruction::CreateDeclareDword(std::vector<std::uint8_t>& data, std::int32_t index, std::int32_t length)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		if (static_cast<std::uint32_t>(length) - 1 > 16 - 1 || (static_cast<std::uint32_t>(length) & 3) != 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_length();
		}
		if (static_cast<std::uint64_t>(static_cast<std::uint32_t>(index)) + static_cast<std::uint32_t>(length) > static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareDword);
		instruction.SetInternalDeclareDataCount(static_cast<std::uint32_t>(length) / 4);
		for (std::int32_t i = 0; i < length; i += 4)
		{
			std::uint32_t v = data[index + i] | (static_cast<std::uint32_t>(data[index + i + 1]) << 8) | (static_cast<std::uint32_t>(data[index + i + 2]) << 16) | (static_cast<std::uint32_t>(data[index + i + 3]) << 24);
			instruction.SetDeclareDwordValue(i / 4, v);
		}
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareDword(std::vector<std::uint32_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		return CreateDeclareDword(data, 0, (std::int32_t)data.size());
	}

	Instruction Instruction::CreateDeclareDword(std::vector<std::uint32_t>& data, std::int32_t index, std::int32_t length)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		if (static_cast<std::uint32_t>(length) - 1 > 4 - 1)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_length();
		}
		if (static_cast<std::uint64_t>(static_cast<std::uint32_t>(index)) + static_cast<std::uint32_t>(length) > static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareDword);
		instruction.SetInternalDeclareDataCount(static_cast<std::uint32_t>(length));
		for (std::int32_t i = 0; i < length; i++)
		{
			instruction.SetDeclareDwordValue(i, data[index + i]);
		}
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareQword(std::uint64_t q0)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareQword);
		instruction.SetInternalDeclareDataCount(1);
		instruction.SetDeclareQwordValue(0, q0);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareQword(std::uint64_t q0, std::uint64_t q1)
	{
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareQword);
		instruction.SetInternalDeclareDataCount(2);
		instruction.SetDeclareQwordValue(0, q0);
		instruction.SetDeclareQwordValue(1, q1);
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareQword(std::vector<std::uint8_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		return CreateDeclareQword(data, 0, (std::int32_t)data.size());
	}

	Instruction Instruction::CreateDeclareQword(std::vector<std::uint8_t>& data, std::int32_t index, std::int32_t length)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		if (static_cast<std::uint32_t>(length) - 1 > 16 - 1 || (static_cast<std::uint32_t>(length) & 7) != 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_length();
		}
		if (static_cast<std::uint64_t>(static_cast<std::uint32_t>(index)) + static_cast<std::uint32_t>(length) > static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareQword);
		instruction.SetInternalDeclareDataCount(static_cast<std::uint32_t>(length) / 8);
		for (std::int32_t i = 0; i < length; i += 8)
		{
			std::uint32_t v1 = data[index + i] | (static_cast<std::uint32_t>(data[index + i + 1]) << 8) | (static_cast<std::uint32_t>(data[index + i + 2]) << 16) | (static_cast<std::uint32_t>(data[index + i + 3]) << 24);
			std::uint32_t v2 = data[index + i + 4] | (static_cast<std::uint32_t>(data[index + i + 5]) << 8) | (static_cast<std::uint32_t>(data[index + i + 6]) << 16) | (static_cast<std::uint32_t>(data[index + i + 7]) << 24);
			instruction.SetDeclareQwordValue(i / 8, static_cast<std::uint64_t>(v1) | (static_cast<std::uint64_t>(v2) << 32));
		}
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	Instruction Instruction::CreateDeclareQword(std::vector<std::uint64_t>& data)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		return CreateDeclareQword(data, 0, (std::int32_t)data.size());
	}

	Instruction Instruction::CreateDeclareQword(std::vector<std::uint64_t>& data, std::int32_t index, std::int32_t length)
	{
		if (data.empty())
		{
			ThrowHelper::ThrowArgumentNullException_data();
		}
		if (static_cast<std::uint32_t>(length) - 1 > 2 - 1)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_length();
		}
		if (static_cast<std::uint64_t>(static_cast<std::uint32_t>(index)) + static_cast<std::uint32_t>(length) > static_cast<std::uint32_t>(data.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		Instruction instruction = Iced::Intel::Instruction();
		instruction.SetCode(Code::DeclareQword);
		instruction.SetInternalDeclareDataCount(static_cast<std::uint32_t>(length));
		for (std::int32_t i = 0; i < length; i++)
		{
			instruction.SetDeclareQwordValue(i, data[index + i]);
		}
		assert(instruction.GetOpCount() == 0);
		return instruction;
	}

	bool Instruction::operator == (Instruction const right)
	{
		return EqualsInternal(*this, right);
	}

	bool Instruction::operator != (Instruction const right)
	{
		return !EqualsInternal(*this, right);
	}

	bool Instruction::Equals(Instruction const other)
	{
		return EqualsInternal(*this, other);
	}

	bool Instruction::IEquatable_Equals(Instruction other)
	{
		return EqualsInternal(*this, other);
	}

	bool Instruction::EqualsInternal(Instruction const a, Instruction const b)
	{
		return a.memDispl == b.memDispl && ((a.flags1 ^ b.flags1) & ~static_cast<std::uint32_t>(InstrFlags1::EqualsIgnoreMask)) == 0 && a.immediate == b.immediate && a.code == b.code && a.memBaseReg == b.memBaseReg && a.memIndexReg == b.memIndexReg && a.reg0 == b.reg0 && a.reg1 == b.reg1 && a.reg2 == b.reg2 && a.reg3 == b.reg3 && a.opKind0 == b.opKind0 && a.opKind1 == b.opKind1 && a.opKind2 == b.opKind2 && a.opKind3 == b.opKind3 && a.scale == b.scale && a.displSize == b.displSize && a.pad == b.pad;
	}

	std::int32_t Instruction::GetHashCode()
	{
		std::uint32_t c = static_cast<std::uint32_t>(memDispl);
		c ^= static_cast<std::uint32_t>(memDispl >> 32);
		c ^= flags1 & ~static_cast<std::uint32_t>(InstrFlags1::EqualsIgnoreMask);
		c ^= immediate;
		c ^= static_cast<std::uint32_t>(code) << 8;
		c ^= static_cast<std::uint32_t>(memBaseReg) << 16;
		c ^= static_cast<std::uint32_t>(memIndexReg) << 24;
		c ^= reg3;
		c ^= static_cast<std::uint32_t>(reg2) << 8;
		c ^= static_cast<std::uint32_t>(reg1) << 16;
		c ^= static_cast<std::uint32_t>(reg0) << 24;
		c ^= opKind3;
		c ^= static_cast<std::uint32_t>(opKind2) << 8;
		c ^= static_cast<std::uint32_t>(opKind1) << 16;
		c ^= static_cast<std::uint32_t>(opKind0) << 24;
		c ^= scale;
		c ^= static_cast<std::uint32_t>(displSize) << 8;
		c ^= static_cast<std::uint32_t>(pad) << 16;
		return static_cast<std::int32_t>(c);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool Instruction::Equals(std::any obj)
	{
		Instruction* other = std::any_cast<Instruction>(&obj);
		return other != nullptr && EqualsInternal(*this, *other);
	}

	bool Instruction::EqualsAllBits(Instruction const a, Instruction const b)
	{
		return a.nextRip == b.nextRip && a.memDispl == b.memDispl && a.flags1 == b.flags1 && a.immediate == b.immediate && a.code == b.code && a.memBaseReg == b.memBaseReg && a.memIndexReg == b.memIndexReg && a.reg0 == b.reg0 && a.reg1 == b.reg1 && a.reg2 == b.reg2 && a.reg3 == b.reg3 && a.opKind0 == b.opKind0 && a.opKind1 == b.opKind1 && a.opKind2 == b.opKind2 && a.opKind3 == b.opKind3 && a.scale == b.scale && a.displSize == b.displSize && a.len == b.len && a.pad == b.pad;
	}

	std::uint16_t Instruction::GetIP16() const
	{
		return static_cast<std::uint16_t>(static_cast<std::uint32_t>(nextRip) - static_cast<std::uint32_t>(GetLength()));
	}

	void Instruction::SetIP16(std::uint16_t value)
	{
		nextRip = value + static_cast<std::uint32_t>(GetLength());
	}

	std::uint32_t Instruction::GetIP32() const
	{
		return static_cast<std::uint32_t>(nextRip) - static_cast<std::uint32_t>(GetLength());
	}

	void Instruction::SetIP32(std::uint32_t value)
	{
		nextRip = value + static_cast<std::uint32_t>(GetLength());
	}

	std::uint64_t Instruction::GetIP() const
	{
		return nextRip - static_cast<std::uint32_t>(GetLength());
	}

	void Instruction::SetIP(std::uint64_t value)
	{
		nextRip = value + static_cast<std::uint32_t>(GetLength());
	}

	std::uint16_t Instruction::GetNextIP16() const
	{
		return static_cast<std::uint16_t>(nextRip);
	}

	void Instruction::SetNextIP16(std::uint16_t value)
	{
		nextRip = value;
	}

	std::uint32_t Instruction::GetNextIP32() const
	{
		return static_cast<std::uint32_t>(nextRip);
	}

	void Instruction::SetNextIP32(std::uint32_t value)
	{
		nextRip = value;
	}

	std::uint64_t Instruction::GetNextIP() const
	{
		return nextRip;
	}

	void Instruction::SetNextIP(std::uint64_t value)
	{
		nextRip = value;
	}

	Iced::Intel::CodeSize Instruction::GetCodeSize() const
	{
		return static_cast<Iced::Intel::CodeSize>((flags1 >> static_cast<std::int32_t>(InstrFlags1::CodeSizeShift)) & static_cast<std::uint32_t>(InstrFlags1::CodeSizeMask));
	}

	void Instruction::SetCodeSize(Iced::Intel::CodeSize value)
	{
		flags1 = ((flags1 & ~(static_cast<std::uint32_t>(InstrFlags1::CodeSizeMask) << static_cast<std::int32_t>(InstrFlags1::CodeSizeShift))) | ((static_cast<std::uint32_t>(value) & static_cast<std::uint32_t>(InstrFlags1::CodeSizeMask)) << static_cast<std::int32_t>(InstrFlags1::CodeSizeShift)));
	}

	void Instruction::SetInternalCodeSize(Iced::Intel::CodeSize value)
	{
		flags1 |= (static_cast<std::uint32_t>(value) << static_cast<std::int32_t>(InstrFlags1::CodeSizeShift));
	}

	bool Instruction::IsInvalid() const
	{
		return code == static_cast<std::uint16_t>(Code::INVALID);
	}

	Iced::Intel::Code Instruction::GetCode() const
	{
		return static_cast<Iced::Intel::Code>(code);
	}

	void Instruction::SetCode(Iced::Intel::Code value)
	{
		if (static_cast<std::uint32_t>(value) >= static_cast<std::uint32_t>(IcedConstants::CodeEnumCount))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
		code = static_cast<std::uint16_t>(value);
	}

	void Instruction::InternalSetCodeNoCheck(Iced::Intel::Code code)
	{
		this->code = static_cast<std::uint16_t>(code);
	}

	Iced::Intel::Mnemonic Instruction::GetMnemonic() const
	{
		return Iced::Intel::MnemonicUtils::Mnemonic(GetCode());
	}

	std::int32_t Instruction::GetOpCount() const
	{
		return InstructionOpCounts::OpCount[static_cast<std::int32_t>(code)];
	}

	std::int32_t Instruction::GetLength() const
	{
		return len;
	}

	void Instruction::SetLength(std::int32_t value)
	{
		len = static_cast<std::uint8_t>(value);
	}

	bool Instruction::GetInternalHasRepeOrRepnePrefix() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::RepePrefix | InstrFlags1::RepnePrefix)) != 0;
	}

	std::uint32_t Instruction::GetHasAnyOfLockRepRepnePrefix() const
	{
		return flags1 & static_cast<std::uint32_t>(InstrFlags1::LockPrefix | InstrFlags1::RepePrefix | InstrFlags1::RepnePrefix);
	}

	bool Instruction::IsXacquireInstr() const
	{
		if (GetOp0Kind() != OpKind::Memory)
		{
			return false;
		}
		if (GetHasLockPrefix())
		{
			return GetCode() != Code::Cmpxchg16b_m128;
		}
		return GetMnemonic() == Mnemonic::Xchg;
	}

	bool Instruction::IsXreleaseInstr() const
	{
		if (GetOp0Kind() != OpKind::Memory)
		{
			return false;
		}
		if (GetHasLockPrefix())
		{
			return GetCode() != Code::Cmpxchg16b_m128;
		}
		switch (GetCode())
		{
		case Code::Xchg_rm8_r8:
		case Code::Xchg_rm16_r16:
		case Code::Xchg_rm32_r32:
		case Code::Xchg_rm64_r64:
		case Code::Mov_rm8_r8:
		case Code::Mov_rm16_r16:
		case Code::Mov_rm32_r32:
		case Code::Mov_rm64_r64:
		case Code::Mov_rm8_imm8:
		case Code::Mov_rm16_imm16:
		case Code::Mov_rm32_imm32:
		case Code::Mov_rm64_imm32:
			return true;
		default:
			return false;
		}
	}

	bool Instruction::GetHasXacquirePrefix() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::RepnePrefix)) != 0 && IsXacquireInstr();
	}

	void Instruction::SetHasXacquirePrefix(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::RepnePrefix);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::RepnePrefix);
		}
	}

	void Instruction::InternalSetHasXacquirePrefix()
	{
		flags1 |= static_cast<std::uint32_t>(InstrFlags1::RepnePrefix);
	}

	bool Instruction::GetHasXreleasePrefix() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::RepePrefix)) != 0 && IsXreleaseInstr();
	}

	void Instruction::SetHasXreleasePrefix(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
		}
	}

	void Instruction::InternalSetHasXreleasePrefix()
	{
		flags1 |= static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
	}

	bool Instruction::GetHasRepPrefix() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::RepePrefix)) != 0;
	}

	void Instruction::SetHasRepPrefix(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
		}
	}

	bool Instruction::GetHasRepePrefix() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::RepePrefix)) != 0;
	}

	void Instruction::SetHasRepePrefix(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
		}
	}

	void Instruction::InternalSetHasRepePrefix()
	{
		flags1 = (flags1 & ~static_cast<std::uint32_t>(InstrFlags1::RepnePrefix)) | static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
	}

	void Instruction::InternalClearHasRepePrefix()
	{
		flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::RepePrefix);
	}

	void Instruction::InternalClearHasRepeRepnePrefix()
	{
		flags1 &= ~(static_cast<std::uint32_t>(InstrFlags1::RepePrefix) | static_cast<std::uint32_t>(InstrFlags1::RepnePrefix));
	}

	bool Instruction::GetHasRepnePrefix() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::RepnePrefix)) != 0;
	}

	void Instruction::SetHasRepnePrefix(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::RepnePrefix);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::RepnePrefix);
		}
	}

	void Instruction::InternalSetHasRepnePrefix()
	{
		flags1 = (flags1 & ~static_cast<std::uint32_t>(InstrFlags1::RepePrefix)) | static_cast<std::uint32_t>(InstrFlags1::RepnePrefix);
	}

	void Instruction::InternalClearHasRepnePrefix()
	{
		flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::RepnePrefix);
	}

	bool Instruction::GetHasLockPrefix() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::LockPrefix)) != 0;
	}

	void Instruction::SetHasLockPrefix(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::LockPrefix);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::LockPrefix);
		}
	}

	void Instruction::InternalSetHasLockPrefix()
	{
		flags1 |= static_cast<std::uint32_t>(InstrFlags1::LockPrefix);
	}

	void Instruction::InternalClearHasLockPrefix()
	{
		flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::LockPrefix);
	}

	OpKind Instruction::GetOp0Kind() const
	{
		return static_cast<OpKind>(opKind0);
	}

	void Instruction::SetOp0Kind(OpKind value)
	{
		opKind0 = static_cast<std::uint8_t>(value);
	}

	bool Instruction::GetInternalOp0IsNotRegOrOp1IsNotReg() const
	{
		return (opKind0 | opKind1) != 0;
	}

	OpKind Instruction::GetOp1Kind() const
	{
		return static_cast<OpKind>(opKind1);
	}

	void Instruction::SetOp1Kind(OpKind value)
	{
		opKind1 = static_cast<std::uint8_t>(value);
	}

	OpKind Instruction::GetOp2Kind() const
	{
		return static_cast<OpKind>(opKind2);
	}

	void Instruction::SetOp2Kind(OpKind value)
	{
		opKind2 = static_cast<std::uint8_t>(value);
	}

	OpKind Instruction::GetOp3Kind() const
	{
		return static_cast<OpKind>(opKind3);
	}

	void Instruction::SetOp3Kind(OpKind value)
	{
		opKind3 = static_cast<std::uint8_t>(value);
	}

	OpKind Instruction::GetOp4Kind() const
	{
		return OpKind::Immediate8;
	}

	void Instruction::SetOp4Kind(OpKind value)
	{
		if (value != OpKind::Immediate8)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
	}

	OpKind Instruction::GetOpKind(std::int32_t operand) const
	{
		switch (operand)
		{
		case 0:
			return GetOp0Kind();
		case 1:
			return GetOp1Kind();
		case 2:
			return GetOp2Kind();
		case 3:
			return GetOp3Kind();
		case 4:
			return GetOp4Kind();
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_operand();
		}
	}

	bool Instruction::HasOpKind(OpKind opKind)
	{
		for (std::int32_t i = 0; i < GetOpCount(); i++)
		{
			if (GetOpKind(i) == opKind)
			{
				return true;
			}
		}
		return false;
	}

	void Instruction::SetOpKind(std::int32_t operand, OpKind opKind)
	{
		switch (operand)
		{
		case 0:
			SetOp0Kind(opKind);
			break;
		case 1:
			SetOp1Kind(opKind);
			break;
		case 2:
			SetOp2Kind(opKind);
			break;
		case 3:
			SetOp3Kind(opKind);
			break;
		case 4:
			SetOp4Kind(opKind);
			break;
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_operand();
			break;
		}
	}

	bool Instruction::GetHasSegmentPrefix() const
	{
		return (((flags1 >> static_cast<std::int32_t>(InstrFlags1::SegmentPrefixShift)) & static_cast<std::uint32_t>(InstrFlags1::SegmentPrefixMask)) - 1) < 6;
	}

	Register Instruction::GetSegmentPrefix() const
	{
		std::uint32_t index = ((flags1 >> static_cast<std::int32_t>(InstrFlags1::SegmentPrefixShift)) & static_cast<std::uint32_t>(InstrFlags1::SegmentPrefixMask)) - 1;
		return index < 6 ? (Register)(Register::ES + static_cast<std::int32_t>(index)) : Register::None;
	}

	void Instruction::SetSegmentPrefix(Register value)
	{
		std::uint32_t encValue;
		if (value == Register::None)
		{
			encValue = 0;
		}
		else
		{
			encValue = ((static_cast<std::uint32_t>(value) - static_cast<std::uint32_t>(Register::ES)) + 1) & static_cast<std::uint32_t>(InstrFlags1::SegmentPrefixMask);
		}
		flags1 = (flags1 & ~(static_cast<std::uint32_t>(InstrFlags1::SegmentPrefixMask) << static_cast<std::int32_t>(InstrFlags1::SegmentPrefixShift))) | (encValue << static_cast<std::int32_t>(InstrFlags1::SegmentPrefixShift));
	}

	Register Instruction::GetMemorySegment() const
	{
		auto segReg = GetSegmentPrefix();
		if (segReg != Register::None)
		{
			return segReg;
		}
		auto baseReg = GetMemoryBase();
		if (baseReg == Register::BP || baseReg == Register::EBP || baseReg == Register::ESP || baseReg == Register::RBP || baseReg == Register::RSP)
		{
			return Register::SS;
		}
		return Register::DS;
	}

	std::int32_t Instruction::GetMemoryDisplSize() const
	{
		auto switchTempVar_0 = displSize;

		return (switchTempVar_0 == 0) ? static_cast<std::uint8_t>(0) : (switchTempVar_0 == 1) ? static_cast<std::uint8_t>(1) : (switchTempVar_0 == 2) ? static_cast<std::uint8_t>(2) : (switchTempVar_0 == 3) ? static_cast<std::uint8_t>(4) : static_cast<std::uint8_t>(8);
	}

	void Instruction::SetMemoryDisplSize(std::int32_t value)
	{
		auto switchTempVar_1 = value;


		displSize = (switchTempVar_1 == 0) ? static_cast<std::uint8_t>(0) : (switchTempVar_1 == 1) ? static_cast<std::uint8_t>(1) : (switchTempVar_1 == 2) ? static_cast<std::uint8_t>(2) : (switchTempVar_1 == 4) ? static_cast<std::uint8_t>(3) : static_cast<std::uint8_t>(4);
	}

	void Instruction::InternalSetMemoryDisplSize(std::uint32_t scale)
	{
		assert(0 <= scale && scale <= 4);
		displSize = static_cast<std::uint8_t>(scale);
	}

	bool Instruction::IsBroadcast() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::Broadcast)) != 0;
	}

	void Instruction::SetBroadcast(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::Broadcast);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::Broadcast);
		}
	}

	void Instruction::InternalSetIsBroadcast()
	{
		flags1 |= static_cast<std::uint32_t>(InstrFlags1::Broadcast);
	}

	bool Instruction::IsMvexEvictionHint() const
	{
		return IcedConstants::IsMvex(GetCode()) && (immediate & static_cast<std::uint32_t>(MvexInstrFlags::EvictionHint)) != 0;
	}

	void Instruction::SetMvexEvictionHint(bool value)
	{
		if (value)
		{
			immediate |= static_cast<std::uint32_t>(MvexInstrFlags::EvictionHint);
		}
		else
		{
			immediate &= ~static_cast<std::uint32_t>(MvexInstrFlags::EvictionHint);
		}
	}

	void Instruction::InternalSetIsMvexEvictionHint()
	{
		immediate |= static_cast<std::uint32_t>(MvexInstrFlags::EvictionHint);
	}

	Iced::Intel::MvexRegMemConv Instruction::GetMvexRegMemConv() const
	{
		if (!IcedConstants::IsMvex(GetCode()))
		{
			return MvexRegMemConv::None;
		}
		return static_cast<Iced::Intel::MvexRegMemConv>((immediate >> static_cast<std::int32_t>(MvexInstrFlags::MvexRegMemConvShift)) & static_cast<std::uint32_t>(MvexInstrFlags::MvexRegMemConvMask));
	}

	void Instruction::SetMvexRegMemConv(Iced::Intel::MvexRegMemConv value)
	{
		immediate = (immediate & ~(static_cast<std::uint32_t>(MvexInstrFlags::MvexRegMemConvMask) << static_cast<std::int32_t>(MvexInstrFlags::MvexRegMemConvShift))) | (static_cast<std::uint32_t>(value) << static_cast<std::int32_t>(MvexInstrFlags::MvexRegMemConvShift));
	}

	void Instruction::InternalSetMvexRegMemConv(Iced::Intel::MvexRegMemConv newValue)
	{
		immediate |= (static_cast<std::uint32_t>(newValue) << static_cast<std::int32_t>(MvexInstrFlags::MvexRegMemConvShift));
	}

	Iced::Intel::MemorySize Instruction::GetMemorySize() const
	{
		std::int32_t index = static_cast<std::int32_t>(GetCode());
		if (IcedConstants::IsMvex(static_cast<Iced::Intel::Code>(index)))
		{
			auto mvex = MvexInfo(static_cast<Iced::Intel::Code>(index));
			std::int32_t sss = (static_cast<std::int32_t>(GetMvexRegMemConv()) - static_cast<std::int32_t>(MvexRegMemConv::MemConvNone)) & 7;
			return static_cast<Iced::Intel::MemorySize>(MvexMemorySizeLut::Data[static_cast<std::int32_t>(mvex.GetTupleTypeLutKind()) * 8 + sss]);
		}
		if (IsBroadcast())
		{
			return static_cast<Iced::Intel::MemorySize>(InstructionMemorySizes::SizesBcst[index]);
		}
		else
		{
			return static_cast<Iced::Intel::MemorySize>(InstructionMemorySizes::SizesNormal[index]);
		}
	}

	std::int32_t Instruction::GetMemoryIndexScale() const
	{
		return 1 << static_cast<std::int32_t>(scale);
	}

	void Instruction::SetMemoryIndexScale(std::int32_t value)
	{
		if (value == 1)
		{
			scale = 0;
		}
		else if (value == 2)
		{
			scale = 1;
		}
		else if (value == 4)
		{
			scale = 2;
		}
		else
		{
			assert(value == 8);
			scale = 3;
		}
	}

	std::int32_t Instruction::GetInternalMemoryIndexScale() const
	{
		return scale;
	}

	void Instruction::SetInternalMemoryIndexScale(std::int32_t value)
	{
		scale = static_cast<std::uint8_t>(value);
	}

	std::uint32_t Instruction::GetMemoryDisplacement32() const
	{
		return static_cast<std::uint32_t>(memDispl);
	}

	void Instruction::SetMemoryDisplacement32(std::uint32_t value)
	{
		memDispl = value;
	}

	std::uint64_t Instruction::GetMemoryDisplacement64() const
	{
		return memDispl;
	}

	void Instruction::SetMemoryDisplacement64(std::uint64_t value)
	{
		memDispl = value;
	}

	std::uint64_t Instruction::GetImmediate(std::int32_t operand)
	{
		auto switchTempVar_2 = GetOpKind(operand);

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_2 == OpKind.Immediate8) ? Immediate8 : (switchTempVar_2 == OpKind.Immediate8_2nd) ? Immediate8_2nd : (switchTempVar_2 == OpKind.Immediate16) ? Immediate16 : (switchTempVar_2 == OpKind.Immediate32) ? Immediate32 : (switchTempVar_2 == OpKind.Immediate64) ? Immediate64 : (switchTempVar_2 == OpKind.Immediate8to16) ? (ulong)Immediate8to16 : (switchTempVar_2 == OpKind.Immediate8to32) ? (ulong)Immediate8to32 : (switchTempVar_2 == OpKind.Immediate8to64) ? (ulong)Immediate8to64 : (switchTempVar_2 == OpKind.Immediate32to64) ? (ulong)Immediate32to64 : throw new ArgumentException(string.Format("Op{0} isn't an immediate operand", operand), nameof(operand));
		//C# TO C++ CONVERTER TODO TASK: This exception's constructor requires only one argument:
		return (switchTempVar_2 == OpKind::Immediate8) ? GetImmediate8() : (switchTempVar_2 == OpKind::Immediate8_2nd) ? GetImmediate8_2nd() : (switchTempVar_2 == OpKind::Immediate16) ? GetImmediate16() : (switchTempVar_2 == OpKind::Immediate32) ? GetImmediate32() : (switchTempVar_2 == OpKind::Immediate64) ? GetImmediate64() : (switchTempVar_2 == OpKind::Immediate8to16) ? static_cast<std::uint64_t>(GetImmediate8to16()) : (switchTempVar_2 == OpKind::Immediate8to32) ? static_cast<std::uint64_t>(GetImmediate8to32()) : (switchTempVar_2 == OpKind::Immediate8to64) ? static_cast<std::uint64_t>(GetImmediate8to64()) : (switchTempVar_2 == OpKind::Immediate32to64) ? static_cast<std::uint64_t>(GetImmediate32to64()) : throw std::invalid_argument(std::format("Op{0:s} isn't an immediate operand", to_string(operand)));
	}

	void Instruction::SetImmediate(std::int32_t operand, std::int32_t immediate)
	{
		SetImmediate(operand, static_cast<std::uint64_t>(immediate));
	}

	void Instruction::SetImmediate(std::int32_t operand, std::uint32_t immediate)
	{
		SetImmediate(operand, static_cast<std::uint64_t>(immediate));
	}

	void Instruction::SetImmediate(std::int32_t operand, std::int64_t immediate)
	{
		SetImmediate(operand, static_cast<std::uint64_t>(immediate));
	}

	void Instruction::SetImmediate(std::int32_t operand, std::uint64_t immediate)
	{
		switch (GetOpKind(operand))
		{
		case OpKind::Immediate8:
		case OpKind::Immediate8to16:
		case OpKind::Immediate8to32:
		case OpKind::Immediate8to64:
			this->immediate = static_cast<std::uint8_t>(immediate);
			break;
		case OpKind::Immediate8_2nd:
			memDispl = static_cast<std::uint8_t>(immediate);
			break;
		case OpKind::Immediate16:
			this->immediate = static_cast<std::uint16_t>(immediate);
			break;
		case OpKind::Immediate32to64:
		case OpKind::Immediate32:
			this->immediate = static_cast<std::uint32_t>(immediate);
			break;
		case OpKind::Immediate64:
			SetImmediate64(immediate);
			break;
		default:
			//C# TO C++ CONVERTER TODO TASK: This exception's constructor requires only one argument:
			//ORIGINAL LINE: throw new ArgumentException(string.Format("Op{0} isn't an immediate operand", operand), nameof(operand));
			throw std::invalid_argument(std::format("Op{0:s} isn't an immediate operand", to_string(operand)));
		}
	}

	std::uint8_t Instruction::GetImmediate8() const
	{
		return static_cast<std::uint8_t>(immediate);
	}

	void Instruction::SetImmediate8(std::uint8_t value)
	{
		immediate = (immediate & 0xFFFF'FF00) | static_cast<std::uint32_t>(value);
	}

	void Instruction::SetInternalImmediate8(std::uint32_t value)
	{
		immediate = value;
	}

	std::uint8_t Instruction::GetImmediate8_2nd() const
	{
		return static_cast<std::uint8_t>(memDispl);
	}

	void Instruction::SetImmediate8_2nd(std::uint8_t value)
	{
		memDispl = value;
	}

	void Instruction::SetInternalImmediate8_2nd(std::uint32_t value)
	{
		memDispl = value;
	}

	std::uint16_t Instruction::GetImmediate16() const
	{
		return static_cast<std::uint16_t>(immediate);
	}

	void Instruction::SetImmediate16(std::uint16_t value)
	{
		immediate = value;
	}

	void Instruction::SetInternalImmediate16(std::uint32_t value)
	{
		immediate = value;
	}

	std::uint32_t Instruction::GetImmediate32() const
	{
		return immediate;
	}

	void Instruction::SetImmediate32(std::uint32_t value)
	{
		immediate = value;
	}

	std::uint64_t Instruction::GetImmediate64() const
	{
		return (memDispl << 32) | immediate;
	}

	void Instruction::SetImmediate64(std::uint64_t value)
	{
		immediate = static_cast<std::uint32_t>(value);
		memDispl = static_cast<std::uint32_t>(value >> 32);
	}

	void Instruction::SetInternalImmediate64Lo(std::uint32_t value)
	{
		immediate = value;
	}

	void Instruction::SetInternalImmediate64Hi(std::uint32_t value)
	{
		memDispl = value;
	}

	std::int16_t Instruction::GetImmediate8to16() const
	{
		return static_cast<std::int8_t>(immediate);
	}

	void Instruction::SetImmediate8to16(std::int16_t value)
	{
		immediate = static_cast<std::uint32_t>(static_cast<std::int8_t>(value));
	}

	std::int32_t Instruction::GetImmediate8to32() const
	{
		return static_cast<std::int8_t>(immediate);
	}

	void Instruction::SetImmediate8to32(std::int32_t value)
	{
		immediate = static_cast<std::uint32_t>(static_cast<std::int8_t>(value));
	}

	std::int64_t Instruction::GetImmediate8to64() const
	{
		return static_cast<std::int8_t>(immediate);
	}

	void Instruction::SetImmediate8to64(std::int64_t value)
	{
		immediate = static_cast<std::uint32_t>(static_cast<std::int8_t>(value));
	}

	std::int64_t Instruction::GetImmediate32to64() const
	{
		return static_cast<std::int32_t>(immediate);
	}

	void Instruction::SetImmediate32to64(std::int64_t value)
	{
		immediate = static_cast<std::uint32_t>(value);
	}

	std::uint16_t Instruction::GetNearBranch16() const
	{
		return static_cast<std::uint16_t>(memDispl);
	}

	void Instruction::SetNearBranch16(std::uint16_t value)
	{
		memDispl = value;
	}

	void Instruction::SetInternalNearBranch16(std::uint32_t value)
	{
		memDispl = value;
	}

	std::uint32_t Instruction::GetNearBranch32() const
	{
		return static_cast<std::uint32_t>(memDispl);
	}

	void Instruction::SetNearBranch32(std::uint32_t value)
	{
		memDispl = value;
	}

	std::uint64_t Instruction::GetNearBranch64() const
	{
		return memDispl;
	}

	void Instruction::SetNearBranch64(std::uint64_t value)
	{
		memDispl = value;
	}

	std::uint64_t Instruction::GetNearBranchTarget() const
	{
		auto opKind = GetOp0Kind();
		// Check if JKZD/JKNZD
		if (GetOpCount() == 2)
		{
			opKind = GetOp1Kind();
		}
		auto switchTempVar_3 = opKind;


		return (switchTempVar_3 == OpKind::NearBranch16) ? GetNearBranch16() : (switchTempVar_3 == OpKind::NearBranch32) ? GetNearBranch32() : (switchTempVar_3 == OpKind::NearBranch64) ? GetNearBranch64() : static_cast<std::uint8_t>(0);
	}

	std::uint16_t Instruction::GetFarBranch16() const
	{
		return static_cast<std::uint16_t>(immediate);
	}

	void Instruction::SetFarBranch16(std::uint16_t value)
	{
		immediate = value;
	}

	void Instruction::SetInternalFarBranch16(std::uint32_t value)
	{
		immediate = value;
	}

	std::uint32_t Instruction::GetFarBranch32() const
	{
		return immediate;
	}

	void Instruction::SetFarBranch32(std::uint32_t value)
	{
		immediate = value;
	}

	std::uint16_t Instruction::GetFarBranchSelector() const
	{
		return static_cast<std::uint16_t>(memDispl);
	}

	void Instruction::SetFarBranchSelector(std::uint16_t value)
	{
		memDispl = value;
	}

	void Instruction::SetInternalFarBranchSelector(std::uint32_t value)
	{
		memDispl = value;
	}

	Register Instruction::GetMemoryBase() const
	{
		return static_cast<Register>(memBaseReg);
	}

	void Instruction::SetMemoryBase(Register value)
	{
		memBaseReg = static_cast<std::uint8_t>(value);
	}

	void Instruction::SetInternalMemoryBase(Register value)
	{
		memBaseReg = static_cast<std::uint8_t>(value);
	}

	Register Instruction::GetMemoryIndex() const
	{
		return static_cast<Register>(memIndexReg);
	}

	void Instruction::SetMemoryIndex(Register value)
	{
		memIndexReg = static_cast<std::uint8_t>(value);
	}

	void Instruction::SetInternalMemoryIndex(Register value)
	{
		memIndexReg = static_cast<std::uint8_t>(value);
	}

	Register Instruction::GetOp0Register() const
	{
		return static_cast<Register>(reg0);
	}

	void Instruction::SetOp0Register(Register value)
	{
		reg0 = static_cast<std::uint8_t>(value);
	}

	void Instruction::SetInternalOp0Register(Register value)
	{
		reg0 = static_cast<std::uint8_t>(value);
	}

	Register Instruction::GetOp1Register() const
	{
		return static_cast<Register>(reg1);
	}

	void Instruction::SetOp1Register(Register value)
	{
		reg1 = static_cast<std::uint8_t>(value);
	}

	void Instruction::SetInternalOp1Register(Register value)
	{
		reg1 = static_cast<std::uint8_t>(value);
	}

	Register Instruction::GetOp2Register() const
	{
		return static_cast<Register>(reg2);
	}

	void Instruction::SetOp2Register(Register value)
	{
		reg2 = static_cast<std::uint8_t>(value);
	}

	void Instruction::SetInternalOp2Register(Register value)
	{
		reg2 = static_cast<std::uint8_t>(value);
	}

	Register Instruction::GetOp3Register() const
	{
		return static_cast<Register>(reg3);
	}

	void Instruction::SetOp3Register(Register value)
	{
		reg3 = static_cast<std::uint8_t>(value);
	}

	void Instruction::SetInternalOp3Register(Register value)
	{
		reg3 = static_cast<std::uint8_t>(value);
	}

	Register Instruction::GetOp4Register() const
	{
		return Register::None;
	}

	void Instruction::SetOp4Register(Register value)
	{
		if (value != Register::None)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_value();
		}
	}

	Register Instruction::GetOpRegister(std::int32_t operand) const
	{
		switch (operand)
		{
		case 0:
			return GetOp0Register();
		case 1:
			return GetOp1Register();
		case 2:
			return GetOp2Register();
		case 3:
			return GetOp3Register();
		case 4:
			return GetOp4Register();
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_operand();
		}
	}

	void Instruction::SetOpRegister(std::int32_t operand, Register register_)
	{
		switch (operand)
		{
		case 0:
			SetOp0Register(register_);
			break;
		case 1:
			SetOp1Register(register_);
			break;
		case 2:
			SetOp2Register(register_);
			break;
		case 3:
			SetOp3Register(register_);
			break;
		case 4:
			SetOp4Register(register_);
			break;
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_operand();
			break;
		}
	}

	Register Instruction::GetOpMask() const
	{
		std::int32_t r = static_cast<std::int32_t>(flags1 >> static_cast<std::int32_t>(InstrFlags1::OpMaskShift)) & static_cast<std::int32_t>(InstrFlags1::OpMaskMask);
		return r == 0 ? Register::None : (Register)(r + Register::K0);
	}

	void Instruction::SetOpMask(Register value)
	{
		std::uint32_t r;
		if (value == Register::None)
		{
			r = 0;
		}
		else
		{
			r = static_cast<std::uint32_t>(value - Register::K0) & static_cast<std::uint32_t>(InstrFlags1::OpMaskMask);
		}
		flags1 = (flags1 & ~(static_cast<std::uint32_t>(InstrFlags1::OpMaskMask) << static_cast<std::int32_t>(InstrFlags1::OpMaskShift))) | (r << static_cast<std::int32_t>(InstrFlags1::OpMaskShift));
	}

	std::uint32_t Instruction::GetInternalOpMask() const
	{
		return (flags1 >> static_cast<std::int32_t>(InstrFlags1::OpMaskShift)) & static_cast<std::uint32_t>(InstrFlags1::OpMaskMask);
	}

	void Instruction::SetInternalOpMask(std::uint32_t value)
	{
		flags1 |= value << static_cast<std::int32_t>(InstrFlags1::OpMaskShift);
	}

	bool Instruction::GetHasOpMask() const
	{
		return (flags1 & (static_cast<std::uint32_t>(InstrFlags1::OpMaskMask) << static_cast<std::int32_t>(InstrFlags1::OpMaskShift))) != 0;
	}

	bool Instruction::GetHasOpMaskOrZeroingMasking() const
	{
		return (flags1 & ((static_cast<std::uint32_t>(InstrFlags1::OpMaskMask) << static_cast<std::int32_t>(InstrFlags1::OpMaskShift)) | static_cast<std::uint32_t>(InstrFlags1::ZeroingMasking))) != 0;
	}

	bool Instruction::GetZeroingMasking() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::ZeroingMasking)) != 0;
	}

	void Instruction::SetZeroingMasking(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::ZeroingMasking);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::ZeroingMasking);
		}
	}

	void Instruction::InternalSetZeroingMasking()
	{
		flags1 |= static_cast<std::uint32_t>(InstrFlags1::ZeroingMasking);
	}

	bool Instruction::GetMergingMasking() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::ZeroingMasking)) == 0;
	}

	void Instruction::SetMergingMasking(bool value)
	{
		if (value)
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::ZeroingMasking);
		}
		else
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::ZeroingMasking);
		}
	}

	Iced::Intel::RoundingControl Instruction::GetRoundingControl() const
	{
		return static_cast<Iced::Intel::RoundingControl>((flags1 >> static_cast<std::int32_t>(InstrFlags1::RoundingControlShift)) & static_cast<std::int32_t>(InstrFlags1::RoundingControlMask));
	}

	void Instruction::SetRoundingControl(Iced::Intel::RoundingControl value)
	{
		flags1 = (flags1 & ~(static_cast<std::uint32_t>(InstrFlags1::RoundingControlMask) << static_cast<std::int32_t>(InstrFlags1::RoundingControlShift))) | (static_cast<std::uint32_t>(value) << static_cast<std::int32_t>(InstrFlags1::RoundingControlShift));
	}

	void Instruction::SetInternalRoundingControl(std::uint32_t value)
	{
		flags1 |= value << static_cast<std::int32_t>(InstrFlags1::RoundingControlShift);
	}

	bool Instruction::GetHasRoundingControlOrSae() const
	{
		return (flags1 & ((static_cast<std::uint32_t>(InstrFlags1::RoundingControlMask) << static_cast<std::int32_t>(InstrFlags1::RoundingControlShift)) | static_cast<std::uint32_t>(InstrFlags1::SuppressAllExceptions))) != 0;
	}

	std::int32_t Instruction::GetDeclareDataCount() const
	{
		return static_cast<std::int32_t>((flags1 >> static_cast<std::int32_t>(InstrFlags1::DataLengthShift)) & static_cast<std::uint32_t>(InstrFlags1::DataLengthMask)) + 1;
	}

	void Instruction::SetDeclareDataCount(std::int32_t value)
	{
		flags1 = (flags1 & ~(static_cast<std::uint32_t>(InstrFlags1::DataLengthMask) << static_cast<std::int32_t>(InstrFlags1::DataLengthShift))) | ((static_cast<std::uint32_t>(value - 1) & static_cast<std::uint32_t>(InstrFlags1::DataLengthMask)) << static_cast<std::int32_t>(InstrFlags1::DataLengthShift));
	}

	void Instruction::SetInternalDeclareDataCount(std::uint32_t value)
	{
		flags1 |= (value - 1) << static_cast<std::int32_t>(InstrFlags1::DataLengthShift);
	}

	void Instruction::SetDeclareByteValue(std::int32_t index, std::int8_t value)
	{
		SetDeclareByteValue(index, static_cast<std::uint8_t>(value));
	}

	void Instruction::SetDeclareByteValue(std::int32_t index, std::uint8_t value)
	{
		switch (index)
		{
		case 0:
			reg0 = value;
			break;
		case 1:
			reg1 = value;
			break;
		case 2:
			reg2 = value;
			break;
		case 3:
			reg3 = value;
			break;
		case 4:
			immediate = (immediate & 0xFFFFFF00) | value;
			break;
		case 5:
			immediate = (immediate & 0xFFFF00FF) | (static_cast<std::uint32_t>(value) << 8);
			break;
		case 6:
			immediate = (immediate & 0xFF00FFFF) | (static_cast<std::uint32_t>(value) << 16);
			break;
		case 7:
			immediate = (immediate & 0x00FFFFFF) | (static_cast<std::uint32_t>(value) << 24);
			break;
		case 8:
			memDispl = (memDispl & 0xFFFF'FFFF'FFFF'FF00) | static_cast<std::uint64_t>(value);
			break;
		case 9:
			memDispl = (memDispl & 0xFFFF'FFFF'FFFF'00FF) | (static_cast<std::uint64_t>(value) << 8);
			break;
		case 10:
			memDispl = (memDispl & 0xFFFF'FFFF'FF00'FFFF) | (static_cast<std::uint64_t>(value) << 16);
			break;
		case 11:
			memDispl = (memDispl & 0xFFFF'FFFF'00FF'FFFF) | (static_cast<std::uint64_t>(value) << 24);
			break;
		case 12:
			memDispl = (memDispl & 0xFFFF'FF00'FFFF'FFFF) | (static_cast<std::uint64_t>(value) << 32);
			break;
		case 13:
			memDispl = (memDispl & 0xFFFF'00FF'FFFF'FFFF) | (static_cast<std::uint64_t>(value) << 40);
			break;
		case 14:
			memDispl = (memDispl & 0xFF00'FFFF'FFFF'FFFF) | (static_cast<std::uint64_t>(value) << 48);
			break;
		case 15:
			memDispl = (memDispl & 0x00FF'FFFF'FFFF'FFFF) | (static_cast<std::uint64_t>(value) << 56);
			break;
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
			break;
		}
	}

	std::uint8_t Instruction::GetDeclareByteValue(std::int32_t index) const
	{
		switch (index)
		{
		case 0:
			return reg0;
		case 1:
			return reg1;
		case 2:
			return reg2;
		case 3:
			return reg3;
		case 4:
			return static_cast<std::uint8_t>(immediate);
		case 5:
			return static_cast<std::uint8_t>(immediate >> 8);
		case 6:
			return static_cast<std::uint8_t>(immediate >> 16);
		case 7:
			return static_cast<std::uint8_t>(immediate >> 24);
		case 8:
			return static_cast<std::uint8_t>(memDispl);
		case 9:
			return static_cast<std::uint8_t>(static_cast<std::uint32_t>(memDispl) >> 8);
		case 10:
			return static_cast<std::uint8_t>(static_cast<std::uint32_t>(memDispl) >> 16);
		case 11:
			return static_cast<std::uint8_t>(static_cast<std::uint32_t>(memDispl) >> 24);
		case 12:
			return static_cast<std::uint8_t>(memDispl >> 32);
		case 13:
			return static_cast<std::uint8_t>(memDispl >> 40);
		case 14:
			return static_cast<std::uint8_t>(memDispl >> 48);
		case 15:
			return static_cast<std::uint8_t>(memDispl >> 56);
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
			return 0;
		}
	}

	void Instruction::SetDeclareWordValue(std::int32_t index, std::int16_t value)
	{
		SetDeclareWordValue(index, static_cast<std::uint16_t>(value));
	}

	void Instruction::SetDeclareWordValue(std::int32_t index, std::uint16_t value)
	{
		switch (index)
		{
		case 0:
			reg0 = static_cast<std::uint8_t>(value);
			reg1 = static_cast<std::uint8_t>(value >> 8);
			break;
		case 1:
			reg2 = static_cast<std::uint8_t>(value);
			reg3 = static_cast<std::uint8_t>(value >> 8);
			break;
		case 2:
			immediate = (immediate & 0xFFFF0000) | value;
			break;
		case 3:
			immediate = static_cast<std::uint32_t>(static_cast<std::uint16_t>(immediate)) | (static_cast<std::uint32_t>(value) << 16);
			break;
		case 4:
			memDispl = (memDispl & 0xFFFF'FFFF'FFFF'0000) | static_cast<std::uint64_t>(value);
			break;
		case 5:
			memDispl = (memDispl & 0xFFFF'FFFF'0000'FFFF) | (static_cast<std::uint64_t>(value) << 16);
			break;
		case 6:
			memDispl = (memDispl & 0xFFFF'0000'FFFF'FFFF) | (static_cast<std::uint64_t>(value) << 32);
			break;
		case 7:
			memDispl = (memDispl & 0x0000'FFFF'FFFF'FFFF) | (static_cast<std::uint64_t>(value) << 48);
			break;
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
			break;
		}
	}

	std::uint16_t Instruction::GetDeclareWordValue(std::int32_t index) const
	{
		switch (index)
		{
		case 0:
			return static_cast<std::uint16_t>(static_cast<std::uint32_t>(reg0) | static_cast<std::uint32_t>(reg1 << 8));
		case 1:
			return static_cast<std::uint16_t>(static_cast<std::uint32_t>(reg2) | static_cast<std::uint32_t>(reg3 << 8));
		case 2:
			return static_cast<std::uint16_t>(immediate);
		case 3:
			return static_cast<std::uint16_t>(immediate >> 16);
		case 4:
			return static_cast<std::uint16_t>(memDispl);
		case 5:
			return static_cast<std::uint16_t>(static_cast<std::uint32_t>(memDispl) >> 16);
		case 6:
			return static_cast<std::uint16_t>(memDispl >> 32);
		case 7:
			return static_cast<std::uint16_t>(memDispl >> 48);
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
			return 0;
		}
	}

	void Instruction::SetDeclareDwordValue(std::int32_t index, std::int32_t value)
	{
		SetDeclareDwordValue(index, static_cast<std::uint32_t>(value));
	}

	void Instruction::SetDeclareDwordValue(std::int32_t index, std::uint32_t value)
	{
		switch (index)
		{
		case 0:
			reg0 = static_cast<std::uint8_t>(value);
			reg1 = static_cast<std::uint8_t>(value >> 8);
			reg2 = static_cast<std::uint8_t>(value >> 16);
			reg3 = static_cast<std::uint8_t>(value >> 24);
			break;
		case 1:
			immediate = value;
			break;
		case 2:
			memDispl = (memDispl & 0xFFFF'FFFF'0000'0000) | static_cast<std::uint64_t>(value);
			break;
		case 3:
			memDispl = (memDispl & 0x0000'0000'FFFF'FFFF) | (static_cast<std::uint64_t>(value) << 32);
			break;
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
			break;
		}
	}

	std::uint32_t Instruction::GetDeclareDwordValue(std::int32_t index) const
	{
		switch (index)
		{
		case 0:
			return static_cast<std::uint32_t>(reg0) | static_cast<std::uint32_t>(reg1 << 8) | static_cast<std::uint32_t>(reg2 << 16) | static_cast<std::uint32_t>(reg3 << 24);
		case 1:
			return immediate;
		case 2:
			return static_cast<std::uint32_t>(memDispl);
		case 3:
			return static_cast<std::uint32_t>(memDispl >> 32);
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
			return 0;
		}
	}

	void Instruction::SetDeclareQwordValue(std::int32_t index, std::int64_t value)
	{
		SetDeclareQwordValue(index, static_cast<std::uint64_t>(value));
	}

	void Instruction::SetDeclareQwordValue(std::int32_t index, std::uint64_t value)
	{
		std::uint32_t v;
		switch (index)
		{
		case 0:
			v = static_cast<std::uint32_t>(value);
			reg0 = static_cast<std::uint8_t>(v);
			reg1 = static_cast<std::uint8_t>(v >> 8);
			reg2 = static_cast<std::uint8_t>(v >> 16);
			reg3 = static_cast<std::uint8_t>(v >> 24);
			immediate = static_cast<std::uint32_t>(value >> 32);
			break;
		case 1:
			memDispl = value;
			break;
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
			break;
		}
	}

	std::uint64_t Instruction::GetDeclareQwordValue(std::int32_t index) const
	{
		switch (index)
		{
		case 0:
			return static_cast<std::uint64_t>(reg0) | static_cast<std::uint64_t>(static_cast<std::uint32_t>(reg1) << 8) | static_cast<std::uint64_t>(static_cast<std::uint32_t>(reg2) << 16) | static_cast<std::uint64_t>(static_cast<std::uint32_t>(reg3) << 24) | (static_cast<std::uint64_t>(immediate) << 32);
		case 1:
			return memDispl;
		default:
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
			return 0;
		}
	}

	bool Instruction::IsVsib() const
	{
		bool _;
		return TryGetVsib64(_);
	}

	bool Instruction::IsVsib32() const
	{
		bool vsib64;
		return TryGetVsib64(vsib64) && !vsib64;
	}

	bool Instruction::IsVsib64() const
	{
		bool vsib64;
		return TryGetVsib64(vsib64) && vsib64;
	}

	bool Instruction::TryGetVsib64(bool& vsib64) const
	{
		switch (GetCode())
		{
			// GENERATOR-BEGIN: Vsib32
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::VEX_Vpgatherdd_xmm_vm32x_xmm:
		case Code::VEX_Vpgatherdd_ymm_vm32y_ymm:
		case Code::VEX_Vpgatherdq_xmm_vm32x_xmm:
		case Code::VEX_Vpgatherdq_ymm_vm32x_ymm:
		case Code::EVEX_Vpgatherdd_xmm_k1_vm32x:
		case Code::EVEX_Vpgatherdd_ymm_k1_vm32y:
		case Code::EVEX_Vpgatherdd_zmm_k1_vm32z:
		case Code::EVEX_Vpgatherdq_xmm_k1_vm32x:
		case Code::EVEX_Vpgatherdq_ymm_k1_vm32x:
		case Code::EVEX_Vpgatherdq_zmm_k1_vm32y:
		case Code::VEX_Vgatherdps_xmm_vm32x_xmm:
		case Code::VEX_Vgatherdps_ymm_vm32y_ymm:
		case Code::VEX_Vgatherdpd_xmm_vm32x_xmm:
		case Code::VEX_Vgatherdpd_ymm_vm32x_ymm:
		case Code::EVEX_Vgatherdps_xmm_k1_vm32x:
		case Code::EVEX_Vgatherdps_ymm_k1_vm32y:
		case Code::EVEX_Vgatherdps_zmm_k1_vm32z:
		case Code::EVEX_Vgatherdpd_xmm_k1_vm32x:
		case Code::EVEX_Vgatherdpd_ymm_k1_vm32x:
		case Code::EVEX_Vgatherdpd_zmm_k1_vm32y:
		case Code::EVEX_Vpscatterdd_vm32x_k1_xmm:
		case Code::EVEX_Vpscatterdd_vm32y_k1_ymm:
		case Code::EVEX_Vpscatterdd_vm32z_k1_zmm:
		case Code::EVEX_Vpscatterdq_vm32x_k1_xmm:
		case Code::EVEX_Vpscatterdq_vm32x_k1_ymm:
		case Code::EVEX_Vpscatterdq_vm32y_k1_zmm:
		case Code::EVEX_Vscatterdps_vm32x_k1_xmm:
		case Code::EVEX_Vscatterdps_vm32y_k1_ymm:
		case Code::EVEX_Vscatterdps_vm32z_k1_zmm:
		case Code::EVEX_Vscatterdpd_vm32x_k1_xmm:
		case Code::EVEX_Vscatterdpd_vm32x_k1_ymm:
		case Code::EVEX_Vscatterdpd_vm32y_k1_zmm:
		case Code::EVEX_Vgatherpf0dps_vm32z_k1:
		case Code::EVEX_Vgatherpf0dpd_vm32y_k1:
		case Code::EVEX_Vgatherpf1dps_vm32z_k1:
		case Code::EVEX_Vgatherpf1dpd_vm32y_k1:
		case Code::EVEX_Vscatterpf0dps_vm32z_k1:
		case Code::EVEX_Vscatterpf0dpd_vm32y_k1:
		case Code::EVEX_Vscatterpf1dps_vm32z_k1:
		case Code::EVEX_Vscatterpf1dpd_vm32y_k1:
		case Code::MVEX_Vpgatherdd_zmm_k1_mvt:
		case Code::MVEX_Vpgatherdq_zmm_k1_mvt:
		case Code::MVEX_Vgatherdps_zmm_k1_mvt:
		case Code::MVEX_Vgatherdpd_zmm_k1_mvt:
		case Code::MVEX_Vpscatterdd_mvt_k1_zmm:
		case Code::MVEX_Vpscatterdq_mvt_k1_zmm:
		case Code::MVEX_Vscatterdps_mvt_k1_zmm:
		case Code::MVEX_Vscatterdpd_mvt_k1_zmm:
		case Code::MVEX_Undoc_zmm_k1_mvt_512_66_0F38_W0_B0:
		case Code::MVEX_Undoc_zmm_k1_mvt_512_66_0F38_W0_B2:
		case Code::MVEX_Undoc_zmm_k1_mvt_512_66_0F38_W0_C0:
		case Code::MVEX_Vgatherpf0hintdps_mvt_k1:
		case Code::MVEX_Vgatherpf0hintdpd_mvt_k1:
		case Code::MVEX_Vgatherpf0dps_mvt_k1:
		case Code::MVEX_Vgatherpf1dps_mvt_k1:
		case Code::MVEX_Vscatterpf0hintdps_mvt_k1:
		case Code::MVEX_Vscatterpf0hintdpd_mvt_k1:
		case Code::MVEX_Vscatterpf0dps_mvt_k1:
		case Code::MVEX_Vscatterpf1dps_mvt_k1:
			vsib64 = false;
			return true;
			// GENERATOR-END: Vsib32
			// GENERATOR-BEGIN: Vsib64
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::VEX_Vpgatherqd_xmm_vm64x_xmm:
		case Code::VEX_Vpgatherqd_xmm_vm64y_xmm:
		case Code::VEX_Vpgatherqq_xmm_vm64x_xmm:
		case Code::VEX_Vpgatherqq_ymm_vm64y_ymm:
		case Code::EVEX_Vpgatherqd_xmm_k1_vm64x:
		case Code::EVEX_Vpgatherqd_xmm_k1_vm64y:
		case Code::EVEX_Vpgatherqd_ymm_k1_vm64z:
		case Code::EVEX_Vpgatherqq_xmm_k1_vm64x:
		case Code::EVEX_Vpgatherqq_ymm_k1_vm64y:
		case Code::EVEX_Vpgatherqq_zmm_k1_vm64z:
		case Code::VEX_Vgatherqps_xmm_vm64x_xmm:
		case Code::VEX_Vgatherqps_xmm_vm64y_xmm:
		case Code::VEX_Vgatherqpd_xmm_vm64x_xmm:
		case Code::VEX_Vgatherqpd_ymm_vm64y_ymm:
		case Code::EVEX_Vgatherqps_xmm_k1_vm64x:
		case Code::EVEX_Vgatherqps_xmm_k1_vm64y:
		case Code::EVEX_Vgatherqps_ymm_k1_vm64z:
		case Code::EVEX_Vgatherqpd_xmm_k1_vm64x:
		case Code::EVEX_Vgatherqpd_ymm_k1_vm64y:
		case Code::EVEX_Vgatherqpd_zmm_k1_vm64z:
		case Code::EVEX_Vpscatterqd_vm64x_k1_xmm:
		case Code::EVEX_Vpscatterqd_vm64y_k1_xmm:
		case Code::EVEX_Vpscatterqd_vm64z_k1_ymm:
		case Code::EVEX_Vpscatterqq_vm64x_k1_xmm:
		case Code::EVEX_Vpscatterqq_vm64y_k1_ymm:
		case Code::EVEX_Vpscatterqq_vm64z_k1_zmm:
		case Code::EVEX_Vscatterqps_vm64x_k1_xmm:
		case Code::EVEX_Vscatterqps_vm64y_k1_xmm:
		case Code::EVEX_Vscatterqps_vm64z_k1_ymm:
		case Code::EVEX_Vscatterqpd_vm64x_k1_xmm:
		case Code::EVEX_Vscatterqpd_vm64y_k1_ymm:
		case Code::EVEX_Vscatterqpd_vm64z_k1_zmm:
		case Code::EVEX_Vgatherpf0qps_vm64z_k1:
		case Code::EVEX_Vgatherpf0qpd_vm64z_k1:
		case Code::EVEX_Vgatherpf1qps_vm64z_k1:
		case Code::EVEX_Vgatherpf1qpd_vm64z_k1:
		case Code::EVEX_Vscatterpf0qps_vm64z_k1:
		case Code::EVEX_Vscatterpf0qpd_vm64z_k1:
		case Code::EVEX_Vscatterpf1qps_vm64z_k1:
		case Code::EVEX_Vscatterpf1qpd_vm64z_k1:
			vsib64 = true;
			return true;
			// GENERATOR-END: Vsib64
		default:
			vsib64 = false;
			return false;
		}
	}

	bool Instruction::GetSuppressAllExceptions() const
	{
		return (flags1 & static_cast<std::uint32_t>(InstrFlags1::SuppressAllExceptions)) != 0;
	}

	void Instruction::SetSuppressAllExceptions(bool value)
	{
		if (value)
		{
			flags1 |= static_cast<std::uint32_t>(InstrFlags1::SuppressAllExceptions);
		}
		else
		{
			flags1 &= ~static_cast<std::uint32_t>(InstrFlags1::SuppressAllExceptions);
		}
	}

	void Instruction::InternalSetSuppressAllExceptions()
	{
		flags1 |= static_cast<std::uint32_t>(InstrFlags1::SuppressAllExceptions);
	}

	bool Instruction::IsIPRelativeMemoryOperand() const
	{
		return GetMemoryBase() == Register::RIP || GetMemoryBase() == Register::EIP;
	}

	std::uint64_t Instruction::GetIPRelativeMemoryAddress() const
	{
		return GetMemoryBase() == Register::EIP ? GetMemoryDisplacement32() : GetMemoryDisplacement64();
	}

	OpCodeInfo* Instruction::GetOpCode() const
	{
		return Iced::Intel::EncoderCodeExtensions::ToOpCode(GetCode());
	}

	std::string Instruction::ToString() const
	{
		// If the order of #if/elif checks gets updated, also update the `Instruction_ToString()` test method
		auto output = new StringOutput();
		MasmFormatter tempVar;
		tempVar.Format(*this, output);
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		return output->ToString();
	}

	std::int32_t Instruction::GetStackPointerIncrement() const
	{
		switch (GetCode())
		{
			// GENERATOR-BEGIN: StackPointerIncrementTable
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::Pushad:
			return -32;
		case Code::Pushaw:
		case Code::Call_m1664:
			return -16;
		case Code::Push_r64:
		case Code::Pushq_imm32:
		case Code::Pushq_imm8:
		case Code::Call_ptr1632:
		case Code::Pushfq:
		case Code::Call_rel32_64:
		case Code::Call_rm64:
		case Code::Call_m1632:
		case Code::Push_rm64:
		case Code::Pushq_FS:
		case Code::Pushq_GS:
			return -8;
		case Code::Pushd_ES:
		case Code::Pushd_CS:
		case Code::Pushd_SS:
		case Code::Pushd_DS:
		case Code::Push_r32:
		case Code::Pushd_imm32:
		case Code::Pushd_imm8:
		case Code::Call_ptr1616:
		case Code::Pushfd:
		case Code::Call_rel32_32:
		case Code::Call_rm32:
		case Code::Call_m1616:
		case Code::Push_rm32:
		case Code::Pushd_FS:
		case Code::Pushd_GS:
			return -4;
		case Code::Pushw_ES:
		case Code::Pushw_CS:
		case Code::Pushw_SS:
		case Code::Pushw_DS:
		case Code::Push_r16:
		case Code::Push_imm16:
		case Code::Pushw_imm8:
		case Code::Pushfw:
		case Code::Call_rel16:
		case Code::Call_rm16:
		case Code::Push_rm16:
		case Code::Pushw_FS:
		case Code::Pushw_GS:
			return -2;
		case Code::Popw_ES:
		case Code::Popw_CS:
		case Code::Popw_SS:
		case Code::Popw_DS:
		case Code::Pop_r16:
		case Code::Pop_rm16:
		case Code::Popfw:
		case Code::Retnw:
		case Code::Popw_FS:
		case Code::Popw_GS:
			return 2;
		case Code::Popd_ES:
		case Code::Popd_SS:
		case Code::Popd_DS:
		case Code::Pop_r32:
		case Code::Pop_rm32:
		case Code::Popfd:
		case Code::Retnd:
		case Code::Retfw:
		case Code::Popd_FS:
		case Code::Popd_GS:
			return 4;
		case Code::Pop_r64:
		case Code::Pop_rm64:
		case Code::Popfq:
		case Code::Retnq:
		case Code::Retfd:
		case Code::Popq_FS:
		case Code::Popq_GS:
			return 8;
		case Code::Popaw:
		case Code::Retfq:
			return 16;
		case Code::Uiret:
			return 24;
		case Code::Popad:
			return 32;
		case Code::Iretq:
		case Code::Eretu:
		case Code::Erets:
			return 40;
		case Code::Enterw_imm16_imm8:
			return -(2 + (GetImmediate8_2nd() & 0x1F) * 2 + GetImmediate16());
		case Code::Enterd_imm16_imm8:
			return -(4 + (GetImmediate8_2nd() & 0x1F) * 4 + GetImmediate16());
		case Code::Enterq_imm16_imm8:
			return -(8 + (GetImmediate8_2nd() & 0x1F) * 8 + GetImmediate16());
		case Code::Iretw:
			return GetCodeSize() == CodeSize::Code64 ? 2 * 5 : 2 * 3;
		case Code::Iretd:
			return GetCodeSize() == CodeSize::Code64 ? 4 * 5 : 4 * 3;
		case Code::Retnw_imm16:
			return 2 + GetImmediate16();
		case Code::Retnd_imm16:
		case Code::Retfw_imm16:
			return 4 + GetImmediate16();
		case Code::Retnq_imm16:
		case Code::Retfd_imm16:
			return 8 + GetImmediate16();
		case Code::Retfq_imm16:
			return 16 + GetImmediate16();
			// GENERATOR-END: StackPointerIncrementTable
		default:
			return 0;
		}
	}

	FpuStackIncrementInfo Instruction::GetFpuStackIncrementInfo()
	{
		switch (GetCode())
		{
			// GENERATOR-BEGIN: FpuStackIncrementInfoTable
			// ⚠️This was generated by GENERATOR!🦹‍♂️
		case Code::Fld_m32fp:
		case Code::Fld_sti:
		case Code::Fld1:
		case Code::Fldl2t:
		case Code::Fldl2e:
		case Code::Fldpi:
		case Code::Fldlg2:
		case Code::Fldln2:
		case Code::Fldz:
		case Code::Fxtract:
		case Code::Fdecstp:
		case Code::Fild_m32int:
		case Code::Fld_m80fp:
		case Code::Fld_m64fp:
		case Code::Fild_m16int:
		case Code::Fbld_m80bcd:
		case Code::Fild_m64int:
			return FpuStackIncrementInfo(-1, false, true);
		case Code::Fptan:
		case Code::Fsincos:
			return FpuStackIncrementInfo(-1, true, true);
		case Code::Fldenv_m14byte:
		case Code::Fldenv_m28byte:
		case Code::Fninit:
		case Code::Finit:
		case Code::Frstor_m94byte:
		case Code::Frstor_m108byte:
		case Code::Fnsave_m94byte:
		case Code::Fsave_m94byte:
		case Code::Fnsave_m108byte:
		case Code::Fsave_m108byte:
			return FpuStackIncrementInfo(0, false, true);
		case Code::Fcomp_m32fp:
		case Code::Fcomp_st0_sti:
		case Code::Fstp_m32fp:
		case Code::Fstpnce_sti:
		case Code::Fyl2x:
		case Code::Fpatan:
		case Code::Fincstp:
		case Code::Fyl2xp1:
		case Code::Ficomp_m32int:
		case Code::Fisttp_m32int:
		case Code::Fistp_m32int:
		case Code::Fstp_m80fp:
		case Code::Fcomp_m64fp:
		case Code::Fcomp_st0_sti_DCD8:
		case Code::Fisttp_m64int:
		case Code::Fstp_m64fp:
		case Code::Fstp_sti:
		case Code::Fucomp_st0_sti:
		case Code::Ficomp_m16int:
		case Code::Faddp_sti_st0:
		case Code::Fmulp_sti_st0:
		case Code::Fcomp_st0_sti_DED0:
		case Code::Fsubrp_sti_st0:
		case Code::Fsubp_sti_st0:
		case Code::Fdivrp_sti_st0:
		case Code::Fdivp_sti_st0:
		case Code::Fisttp_m16int:
		case Code::Fistp_m16int:
		case Code::Fbstp_m80bcd:
		case Code::Fistp_m64int:
		case Code::Ffreep_sti:
		case Code::Fstp_sti_DFD0:
		case Code::Fstp_sti_DFD8:
		case Code::Fucomip_st0_sti:
		case Code::Fcomip_st0_sti:
		case Code::Ftstp:
			return FpuStackIncrementInfo(1, false, true);
		case Code::Fucompp:
		case Code::Fcompp:
			return FpuStackIncrementInfo(2, false, true);
			// GENERATOR-END: FpuStackIncrementInfoTable
		default:
			return Iced::Intel::FpuStackIncrementInfo();
		}
	}

	EncodingKind Instruction::GetEncoding() const
	{
		return Iced::Intel::InstructionInfoExtensions::Encoding(GetCode());
	}

	std::vector<CpuidFeature> Instruction::GetCpuidFeatures() const
	{
		auto code = GetCode();
		std::uint32_t flags2 = InstructionInfoInternal::InstrInfoTable::Data[static_cast<std::int32_t>(code) * 2 + 1];
		auto cpuidFeature = static_cast<InstructionInfoInternal::CpuidFeatureInternal>(flags2 >> static_cast<std::int32_t>(InstructionInfoInternal::InfoFlags2::CpuidFeatureInternalShift) & static_cast<std::uint32_t>(InstructionInfoInternal::InfoFlags2::CpuidFeatureInternalMask));
		return InstructionInfoInternal::CpuidFeatureInternalData::ToCpuidFeatures[static_cast<std::int32_t>(cpuidFeature)];
	}

	Iced::Intel::FlowControl Instruction::GetFlowControl() const
	{
		return Iced::Intel::InstructionInfoExtensions::FlowControl(GetCode());
	}

	bool Instruction::IsPrivileged() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsPrivileged(GetCode());
	}

	bool Instruction::IsStackInstruction() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsStackInstruction(GetCode());
	}

	bool Instruction::IsSaveRestoreInstruction() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsSaveRestoreInstruction(GetCode());
	}

	InstructionInfoInternal::RflagsInfo Instruction::GetRflagsInfo() const
	{
		auto flags1 = InstructionInfoInternal::InstrInfoTable::Data[static_cast<std::int32_t>(GetCode()) << 1];
		auto impliedAccess = static_cast<InstructionInfoInternal::ImpliedAccess>((flags1 >> static_cast<std::int32_t>(InstructionInfoInternal::InfoFlags1::ImpliedAccessShift)) & static_cast<std::uint32_t>(InstructionInfoInternal::InfoFlags1::ImpliedAccessMask));
		Static::Assert(InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9 + 1 == InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD11 ? 0 : -1);
		Static::Assert(InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9 + 2 == InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1F ? 0 : -1);
		Static::Assert(InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9 + 3 == InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK3F ? 0 : -1);
		Static::Assert(InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9 + 4 == InstructionInfoInternal::ImpliedAccess::Clear_rflags ? 0 : -1);
		auto result = static_cast<InstructionInfoInternal::RflagsInfo>((flags1 >> static_cast<std::int32_t>(InstructionInfoInternal::InfoFlags1::RflagsInfoShift)) & static_cast<std::uint32_t>(InstructionInfoInternal::InfoFlags1::RflagsInfoMask));
		auto e = static_cast<std::uint32_t>(impliedAccess - InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9);
		switch (e)
		{
		case InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9 - InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9:
		case InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD11 - InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9:
		{
			auto m = e == InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9 - InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9 ? 9 : 17;
			switch ((GetImmediate8() & 0x1F) % m)
			{
			case 0:
				return InstructionInfoInternal::RflagsInfo::None;
			case 1:
				return InstructionInfoInternal::RflagsInfo::R_c_W_co;
			}
			break;
		}
		case InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1F - InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9:
		case InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK3F - InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9:
		{
			auto mask = e == InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1F - InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9 ? 0x1F : 0x3F;
			switch (GetImmediate8() & mask)
			{
			case 0:
				return InstructionInfoInternal::RflagsInfo::None;
			case 1:
				if (result == InstructionInfoInternal::RflagsInfo::W_c_U_o)
				{
					return InstructionInfoInternal::RflagsInfo::W_co;
				}
				else if (result == InstructionInfoInternal::RflagsInfo::R_c_W_c_U_o)
				{
					return InstructionInfoInternal::RflagsInfo::R_c_W_co;
				}
				else
				{
					assert(result == InstructionInfoInternal::RflagsInfo::W_cpsz_U_ao);
					return InstructionInfoInternal::RflagsInfo::W_copsz_U_a;
				}
			}
			break;
		}
		case InstructionInfoInternal::ImpliedAccess::Clear_rflags - InstructionInfoInternal::ImpliedAccess::Shift_Ib_MASK1FMOD9:
			if (GetOp0Register() != GetOp1Register())
			{
				break;
			}
			if (GetOp0Kind() != OpKind::Register || GetOp1Kind() != OpKind::Register)
			{
				break;
			}
			if (GetMnemonic() == Mnemonic::Xor)
			{
				return InstructionInfoInternal::RflagsInfo::C_cos_S_pz_U_a;
			}
			else
			{
				return InstructionInfoInternal::RflagsInfo::C_acos_S_pz;
			}
		}
		return result;
	}

	RflagsBits Instruction::GetRflagsRead() const
	{
		// If the method call is used without a temp index, the jitter generates worse code.
		// It stores the array in a temp local, then it calls the method, and then it reads
		// the temp local and checks if we can read the array.
		std::int32_t index = static_cast<std::int32_t>(GetRflagsInfo());
		return static_cast<RflagsBits>(InstructionInfoInternal::RflagsInfoConstants::flagsRead[index]);
	}

	RflagsBits Instruction::GetRflagsWritten() const
	{
		// See RflagsRead for the reason why a temp index is used here
		std::int32_t index = static_cast<std::int32_t>(GetRflagsInfo());
		return static_cast<RflagsBits>(InstructionInfoInternal::RflagsInfoConstants::flagsWritten[index]);
	}

	RflagsBits Instruction::GetRflagsCleared() const
	{
		// See RflagsRead for the reason why a temp index is used here
		std::int32_t index = static_cast<std::int32_t>(GetRflagsInfo());
		return static_cast<RflagsBits>(InstructionInfoInternal::RflagsInfoConstants::flagsCleared[index]);
	}

	RflagsBits Instruction::GetRflagsSet() const
	{
		// See RflagsRead for the reason why a temp index is used here
		std::int32_t index = static_cast<std::int32_t>(GetRflagsInfo());
		return static_cast<RflagsBits>(InstructionInfoInternal::RflagsInfoConstants::flagsSet[index]);
	}

	RflagsBits Instruction::GetRflagsUndefined() const
	{
		// See RflagsRead for the reason why a temp index is used here
		std::int32_t index = static_cast<std::int32_t>(GetRflagsInfo());
		return static_cast<RflagsBits>(InstructionInfoInternal::RflagsInfoConstants::flagsUndefined[index]);
	}

	RflagsBits Instruction::GetRflagsModified() const
	{
		// See RflagsRead for the reason why a temp index is used here
		std::int32_t index = static_cast<std::int32_t>(GetRflagsInfo());
		return static_cast<RflagsBits>(InstructionInfoInternal::RflagsInfoConstants::flagsModified[index]);
	}

	bool Instruction::IsJccShortOrNear() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJccShortOrNear(GetCode());
	}

	bool Instruction::IsJccNear() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJccNear(GetCode());
	}

	bool Instruction::IsJcxShort() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJcxShort(GetCode());
	}

	bool Instruction::IsJccShort() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJccShort(GetCode());
	}

	bool Instruction::IsJmpShort() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJmpShort(GetCode());
	}

	bool Instruction::IsJmpNear() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJmpNear(GetCode());
	}

	bool Instruction::IsJmpShortOrNear() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJmpShortOrNear(GetCode());
	}

	bool Instruction::IsJmpFar() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJmpFar(GetCode());
	}

	bool Instruction::IsCallNear() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsCallNear(GetCode());
	}

	bool Instruction::IsCallFar() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsCallFar(GetCode());
	}

	bool Instruction::IsJmpNearIndirect() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJmpNearIndirect(GetCode());
	}

	bool Instruction::IsJmpFarIndirect() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJmpFarIndirect(GetCode());
	}

	bool Instruction::IsCallNearIndirect() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsCallNearIndirect(GetCode());
	}

	bool Instruction::IsCallFarIndirect() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsCallFarIndirect(GetCode());
	}

	bool Instruction::IsLoopcc() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsLoopcc(GetCode());
	}

	bool Instruction::IsLoop() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsLoop(GetCode());
	}

	bool Instruction::IsJkccShortOrNear() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJkccShortOrNear(GetCode());
	}

	bool Instruction::IsJkccNear() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJkccNear(GetCode());
	}

	bool Instruction::IsJkccShort() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsJkccShort(GetCode());
	}

	void Instruction::NegateConditionCode()
	{
		SetCode(Iced::Intel::InstructionInfoExtensions::NegateConditionCode(GetCode()));
	}

	void Instruction::ToShortBranch()
	{
		SetCode(Iced::Intel::InstructionInfoExtensions::ToShortBranch(GetCode()));
	}

	void Instruction::ToNearBranch()
	{
		SetCode(Iced::Intel::InstructionInfoExtensions::ToNearBranch(GetCode()));
	}

	Iced::Intel::ConditionCode Instruction::GetConditionCode() const
	{
		return Iced::Intel::InstructionInfoExtensions::ConditionCode(GetCode());
	}

	bool Instruction::IsStringInstruction() const
	{
		return Iced::Intel::InstructionInfoExtensions::IsStringInstruction(GetCode());
	}

	std::uint64_t Instruction::GetVirtualAddress(std::int32_t operand, std::int32_t elementIndex, VAGetRegisterValue getRegisterValue)
	{
		if (getRegisterValue == nullptr)
		{
			throw std::invalid_argument("getRegisterValue");
		}
		auto provider = new VARegisterValueProviderDelegateImpl(getRegisterValue);
		std::uint64_t result;
		if (TryGetVirtualAddress(operand, elementIndex, provider, result))
		{
			return result;
		}
		return 0;
	}

	std::uint64_t Instruction::GetVirtualAddress(std::int32_t operand, std::int32_t elementIndex, IVARegisterValueProvider* registerValueProvider)
	{
		if (registerValueProvider == nullptr)
		{
			throw std::invalid_argument("registerValueProvider");
		}
		auto provider = new VARegisterValueProviderAdapter(registerValueProvider);
		std::uint64_t result;
		if (TryGetVirtualAddress(operand, elementIndex, provider, result))
		{
			return result;
		}
		return 0;
	}

	bool Instruction::TryGetVirtualAddress(std::int32_t operand, std::int32_t elementIndex, std::uint64_t& result, VATryGetRegisterValue getRegisterValue)
	{
		if (getRegisterValue == nullptr)
		{
			throw std::invalid_argument("getRegisterValue");
		}
		auto provider = new VATryGetRegisterValueDelegateImpl(getRegisterValue);
		return TryGetVirtualAddress(operand, elementIndex, provider, result);
	}

	bool Instruction::TryGetVirtualAddress(std::int32_t operand, std::int32_t elementIndex, IVATryGetRegisterValueProvider* registerValueProvider, std::uint64_t& result)
	{
		if (registerValueProvider == nullptr)
		{
			throw std::invalid_argument("registerValueProvider");
		}
		std::uint64_t seg, base;
		switch (GetOpKind(operand))
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
			result = 0;
			return true;
		case OpKind::MemorySegSI:
			if (registerValueProvider->TryGetRegisterValue(GetMemorySegment(), 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::SI, 0, 0, base))
			{
				result = seg + static_cast<std::uint16_t>(base);
				return true;
			}
			break;
		case OpKind::MemorySegESI:
			if (registerValueProvider->TryGetRegisterValue(GetMemorySegment(), 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::ESI, 0, 0, base))
			{
				result = seg + static_cast<std::uint32_t>(base);
				return true;
			}
			break;
		case OpKind::MemorySegRSI:
			if (registerValueProvider->TryGetRegisterValue(GetMemorySegment(), 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::RSI, 0, 0, base))
			{
				result = seg + base;
				return true;
			}
			break;
		case OpKind::MemorySegDI:
			if (registerValueProvider->TryGetRegisterValue(GetMemorySegment(), 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::DI, 0, 0, base))
			{
				result = seg + static_cast<std::uint16_t>(base);
				return true;
			}
			break;
		case OpKind::MemorySegEDI:
			if (registerValueProvider->TryGetRegisterValue(GetMemorySegment(), 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::EDI, 0, 0, base))
			{
				result = seg + static_cast<std::uint32_t>(base);
				return true;
			}
			break;
		case OpKind::MemorySegRDI:
			if (registerValueProvider->TryGetRegisterValue(GetMemorySegment(), 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::RDI, 0, 0, base))
			{
				result = seg + base;
				return true;
			}
			break;
		case OpKind::MemoryESDI:
			if (registerValueProvider->TryGetRegisterValue(Register::ES, 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::DI, 0, 0, base))
			{
				result = seg + static_cast<std::uint16_t>(base);
				return true;
			}
			break;
		case OpKind::MemoryESEDI:
			if (registerValueProvider->TryGetRegisterValue(Register::ES, 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::EDI, 0, 0, base))
			{
				result = seg + static_cast<std::uint32_t>(base);
				return true;
			}
			break;
		case OpKind::MemoryESRDI:
			if (registerValueProvider->TryGetRegisterValue(Register::ES, 0, 0, seg) && registerValueProvider->TryGetRegisterValue(Register::RDI, 0, 0, base))
			{
				result = seg + base;
				return true;
			}
			break;
		case OpKind::Memory:
		{
			auto baseReg = GetMemoryBase();
			auto indexReg = GetMemoryIndex();
			std::int32_t addrSize = InstructionUtils::GetAddressSizeInBytes(baseReg, indexReg, GetMemoryDisplSize(), GetCodeSize());
			std::uint64_t offset = GetMemoryDisplacement64();
			std::uint64_t offsetMask;
			if (addrSize == 8)
			{
				offsetMask = std::numeric_limits<std::uint64_t>::max();
			}
			else if (addrSize == 4)
			{
				offsetMask = std::numeric_limits<std::uint32_t>::max();
			}
			else
			{
				assert(addrSize == 2);
				offsetMask = std::numeric_limits<std::uint16_t>::max();
			}
			if (baseReg != Register::None && baseReg != Register::RIP && baseReg != Register::EIP)
			{
				if (!registerValueProvider->TryGetRegisterValue(baseReg, 0, 0, base))
				{
					break;
				}
				offset += base;
			}
			auto code = GetCode();
			if (indexReg != Register::None && !Iced::Intel::CodeExtensions::IgnoresIndex(code) && !Iced::Intel::CodeExtensions::IsTileStrideIndex(code))
			{
				bool vsib64;
				if (TryGetVsib64(vsib64))
				{
					bool b;
					if (vsib64)
					{
						b = registerValueProvider->TryGetRegisterValue(indexReg, elementIndex, 8, base);
					}
					else
					{
						b = registerValueProvider->TryGetRegisterValue(indexReg, elementIndex, 4, base);
						base = static_cast<std::uint64_t>((std::int32_t)base);
					}
					if (!b)
					{
						break;
					}
					offset += base << GetInternalMemoryIndexScale();
				}
				else
				{
					if (!registerValueProvider->TryGetRegisterValue(indexReg, 0, 0, base))
					{
						break;
					}
					offset += base << GetInternalMemoryIndexScale();
				}
			}
			Static::Assert(Code::MVEX_Vloadunpackhd_zmm_k1_mt + 1 == Code::MVEX_Vloadunpackhq_zmm_k1_mt ? 0 : -1);
			Static::Assert(Code::MVEX_Vloadunpackhd_zmm_k1_mt + 2 == Code::MVEX_Vpackstorehd_mt_k1_zmm ? 0 : -1);
			Static::Assert(Code::MVEX_Vloadunpackhd_zmm_k1_mt + 3 == Code::MVEX_Vpackstorehq_mt_k1_zmm ? 0 : -1);
			Static::Assert(Code::MVEX_Vloadunpackhd_zmm_k1_mt + 4 == Code::MVEX_Vloadunpackhps_zmm_k1_mt ? 0 : -1);
			Static::Assert(Code::MVEX_Vloadunpackhd_zmm_k1_mt + 5 == Code::MVEX_Vloadunpackhpd_zmm_k1_mt ? 0 : -1);
			Static::Assert(Code::MVEX_Vloadunpackhd_zmm_k1_mt + 6 == Code::MVEX_Vpackstorehps_mt_k1_zmm ? 0 : -1);
			Static::Assert(Code::MVEX_Vloadunpackhd_zmm_k1_mt + 7 == Code::MVEX_Vpackstorehpd_mt_k1_zmm ? 0 : -1);
			if (code >= Code::MVEX_Vloadunpackhd_zmm_k1_mt && code <= Code::MVEX_Vpackstorehpd_mt_k1_zmm)
			{
				offset -= 0x40;
			}
			offset &= offsetMask;
			if (!Iced::Intel::CodeExtensions::IgnoresSegment(code))
			{
				if (!registerValueProvider->TryGetRegisterValue(GetMemorySegment(), 0, 0, seg))
				{
					break;
				}
				offset += seg;
			}
			result = offset;
			return true;
		}
		default:
			throw InvalidOperationException();
		}
		result = 0;
		return false;
	}
}
