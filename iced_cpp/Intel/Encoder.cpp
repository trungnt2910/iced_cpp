// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Encoder.h"
#include "EncoderInternal/EncoderOpCodeHandler.h"
#include "ThrowHelper.h"
#include "EncoderInternal/OpCodeHandlers.h"
#include "EncoderException.h"
#include "CodeSize.g.h"
#include "IcedConstants.h"
#include "Static.h"
#include "MemorySizeExtensions.h"
#include "InstructionUtils.h"
#include "RegisterExtensions.h"

#include "EncoderInternal/EncoderOpCodeHandler.h"

using namespace Iced::Intel::EncoderInternal;

namespace Iced::Intel
{

	std::vector<std::uint32_t> Encoder::s_immSizes = { 0, 1, 2, 4, 8, 3, 2, 4, 6, 1, 1, 1, 2, 2, 2, 4, 4, 1, 1 };

	bool Encoder::GetPreventVEX2() const
	{
		return Internal_PreventVEX2 != 0;
	}

	void Encoder::SetPreventVEX2(bool value)
	{
		Internal_PreventVEX2 = value ? std::numeric_limits<std::uint32_t>::max() : 0;
	}

	std::uint32_t Encoder::GetVexWig() const
	{
		return (Internal_VEX_WIG_LIG >> 7) & 1;
	}

	void Encoder::SetVexWig(std::uint32_t value)
	{
		Internal_VEX_WIG_LIG = (Internal_VEX_WIG_LIG & ~0x80U) | ((value & 1) << 7);
	}

	std::uint32_t Encoder::GetVexLig() const
	{
		return (Internal_VEX_WIG_LIG >> 2) & 1;
	}

	void Encoder::SetVexLig(std::uint32_t value)
	{
		Internal_VEX_WIG_LIG = (Internal_VEX_WIG_LIG & ~4U) | ((value & 1) << 2);
		Internal_VEX_LIG = (value & 1) << 2;
	}

	std::uint32_t Encoder::GetEvexWig() const
	{
		return Internal_EVEX_WIG >> 7;
	}

	void Encoder::SetEvexWig(std::uint32_t value)
	{
		Internal_EVEX_WIG = (value & 1) << 7;
	}

	std::uint32_t Encoder::GetEvexLig() const
	{
		return Internal_EVEX_LIG >> 5;
	}

	void Encoder::SetEvexLig(std::uint32_t value)
	{
		Internal_EVEX_LIG = (value & 3) << 5;
	}

	std::uint32_t Encoder::GetMvexWig() const
	{
		return Internal_MVEX_WIG >> 7;
	}

	void Encoder::SetMvexWig(std::uint32_t value)
	{
		Internal_MVEX_WIG = (value & 1) << 7;
	}

	const std::string Encoder::ERROR_ONLY_1632_BIT_MODE = "The instruction can only be used in 16/32-bit mode";
	const std::string Encoder::ERROR_ONLY_64_BIT_MODE = "The instruction can only be used in 64-bit mode";

	std::int32_t Encoder::GetBitness() const
	{
		return bitness;
	}

	Encoder::Encoder(CodeWriter* writer, std::int32_t bitness)
	{
		assert(bitness == 16 || bitness == 32 || bitness == 64);
		if (writer == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_writer();
		}
		immSizes = s_immSizes;
		this->writer = writer;
		this->bitness = bitness;
		handler = nullptr; // It's initialized by TryEncode
		opSize16Flags = bitness != 16 ? EncoderFlags::P66 : EncoderFlags::None;
		opSize32Flags = bitness == 16 ? EncoderFlags::P66 : EncoderFlags::None;
		adrSize16Flags = bitness != 16 ? EncoderFlags::P67 : EncoderFlags::None;
		adrSize32Flags = bitness != 32 ? EncoderFlags::P67 : EncoderFlags::None;
	}

	Encoder Encoder::Create(std::int32_t bitness, CodeWriter* writer)
	{
		if (bitness == 16 || bitness == 32 || bitness == 64)
		{
			return Encoder(writer, bitness);
		}

		throw new std::invalid_argument("invalid bitness");
	}

	std::uint32_t Encoder::Encode(const Instruction& instruction, std::uint64_t rip)
	{
		std::uint32_t result;
		std::string errorMessage;
		if (!TryEncode(instruction, rip, result, errorMessage))
		{
			ThrowEncoderException(instruction, errorMessage);
		}
		return result;
	}

	void Encoder::ThrowEncoderException(const Instruction& instruction, const std::string& errorMessage)
	{
		throw EncoderException(errorMessage, instruction);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public bool TryEncode(in Instruction instruction, ulong rip, out uint encodedLength, [NotNullWhen(false)] out string? errorMessage)
	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	bool Encoder::TryEncode(const Instruction& instruction, std::uint64_t rip, std::uint32_t& encodedLength, std::string& errorMessage)
	{
		currentRip = rip;
		eip = static_cast<std::uint32_t>(rip);
		this->errorMessage = "";
		EncoderFlags = EncoderFlags::None;
		DisplSize = DisplSize::None;
		ImmSize = ImmSize::None;
		ModRM = 0;
		auto handler = OpCodeHandlers::Handlers[static_cast<std::int32_t>(instruction.GetCode())];
		this->handler = handler;
		OpCode = handler->OpCode;
		if (handler->GroupIndex >= 0)
		{
			assert(EncoderFlags == (Iced::Intel::EncoderInternal::EncoderFlags)0);
			EncoderFlags = EncoderFlags::ModRM;
			ModRM = static_cast<std::uint8_t>(handler->GroupIndex << 3);
		}
		if (handler->RmGroupIndex >= 0)
		{
			assert(EncoderFlags == (Iced::Intel::EncoderInternal::EncoderFlags)0 || EncoderFlags == EncoderFlags::ModRM);
			EncoderFlags = EncoderFlags::ModRM;
			ModRM |= static_cast<std::uint8_t>(handler->RmGroupIndex | 0xC0);
		}
		switch (handler->EncFlags3 & (EncFlags3::Bit16or32 | EncFlags3::Bit64))
		{
		case EncFlags3::Bit16or32 | EncFlags3::Bit64:
			break;
		case EncFlags3::Bit16or32:
			if (bitness == 64)
			{
				SetErrorMessage(ERROR_ONLY_1632_BIT_MODE);
			}
			break;
		case EncFlags3::Bit64:
			if (bitness != 64)
			{
				SetErrorMessage(ERROR_ONLY_64_BIT_MODE);
			}
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
		switch (handler->OpSize)
		{
		case CodeSize::Unknown:
			break;
		case CodeSize::Code16:
			EncoderFlags |= opSize16Flags;
			break;
		case CodeSize::Code32:
			EncoderFlags |= opSize32Flags;
			break;
		case CodeSize::Code64:
			if ((handler->EncFlags3 & EncFlags3::DefaultOpSize64) == 0)
			{
				EncoderFlags |= EncoderFlags::W;
			}
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
		switch (handler->AddrSize)
		{
		case CodeSize::Unknown:
			break;
		case CodeSize::Code16:
			EncoderFlags |= adrSize16Flags;
			break;
		case CodeSize::Code32:
			EncoderFlags |= adrSize32Flags;
			break;
		case CodeSize::Code64:
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
		if (!handler->IsDeclareData)
		{
			auto ops = handler->Operands;
			for (std::size_t i = 0; i < ops.size(); i++)
			{
				ops[i]->Encode(*this, instruction, i);
			}
			if ((handler->EncFlags3 & EncFlags3::Fwait) != 0)
			{
				WriteByteInternal(0x9B);
			}
			handler->Encode(*this, instruction);
			auto opCode = OpCode;
			if (!handler->Is2ByteOpCode)
			{
				WriteByteInternal(opCode);
			}
			else
			{
				WriteByteInternal(opCode >> 8);
				WriteByteInternal(opCode);
			}
			if ((EncoderFlags & (EncoderFlags::ModRM | EncoderFlags::Displ)) != 0)
			{
				WriteModRM();
			}
			if (ImmSize != ImmSize::None)
			{
				WriteImmediate();
			}
		}
		else
		{
			assert(dynamic_cast<const DeclareDataHandler*>(handler) != nullptr);
			handler->Encode(*this, instruction);
		}
		std::uint32_t instrLen = static_cast<std::uint32_t>(currentRip) - static_cast<std::uint32_t>(rip);
		if (instrLen > IcedConstants::MaxInstructionLength && !handler->IsDeclareData)
		{
			SetErrorMessage(std::format("Instruction length > {0:s} bytes", Iced::Intel::ToString(IcedConstants::MaxInstructionLength)));
		}
		errorMessage = this->errorMessage;
		if (errorMessage != "")
		{
			encodedLength = 0;
			return false;
		}
		encodedLength = instrLen;
		return true;
	}

	void Encoder::SetErrorMessage(const std::string& value)
	{
		if (errorMessage == "")
		{
			errorMessage = value;
		}
	}

	bool Encoder::Verify(std::int32_t operand, OpKind expected, OpKind actual)
	{
		if (expected == actual)
		{
			return true;
		}
		SetErrorMessage(std::format("Operand {0:s}: Expected: {1:s}, actual: {2:s}", Iced::Intel::ToString(operand), Iced::Intel::ToString(expected), Iced::Intel::ToString(actual)));
		return false;
	}

	bool Encoder::Verify(std::int32_t operand, Register expected, Register actual)
	{
		if (expected == actual)
		{
			return true;
		}
		SetErrorMessage(std::format("Operand {0:s}: Expected: {1:s}, actual: {2:s}", Iced::Intel::ToString(operand), Iced::Intel::ToString(expected), Iced::Intel::ToString(actual)));
		return false;
	}

	bool Encoder::Verify(std::int32_t operand, Register register_, Register regLo, Register regHi)
	{
		if (bitness != 64 && (std::underlying_type_t<Register>)regHi > regLo + 7)
		{
			regHi = (Register)(regLo + 7);
		}
		if (regLo <= register_ && register_ <= regHi)
		{
			return true;
		}
		SetErrorMessage(std::format("Operand {0:s}: Register {1:s} is not between {2:s} and {3:s} (inclusive)", Iced::Intel::ToString(operand), Iced::Intel::ToString(register_), Iced::Intel::ToString(regLo), Iced::Intel::ToString(regHi)));
		return false;
	}

	void Encoder::AddBranch(OpKind opKind, std::int32_t immSize, const Instruction& instruction, std::int32_t operand)
	{
		if (!Verify(operand, opKind, instruction.GetOpKind(operand)))
		{
			return;
		}
		std::uint64_t target;
		switch (immSize)
		{
		case 1:
			switch (opKind)
			{
			case OpKind::NearBranch16:
				EncoderFlags |= opSize16Flags;
				ImmSize = ImmSize::RipRelSize1_Target16;
				Immediate = instruction.GetNearBranch16();
				break;
			case OpKind::NearBranch32:
				EncoderFlags |= opSize32Flags;
				ImmSize = ImmSize::RipRelSize1_Target32;
				Immediate = instruction.GetNearBranch32();
				break;
			case OpKind::NearBranch64:
				ImmSize = ImmSize::RipRelSize1_Target64;
				target = instruction.GetNearBranch64();
				Immediate = static_cast<std::uint32_t>(target);
				ImmediateHi = static_cast<std::uint32_t>(target >> 32);
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
			break;
		case 2:
			switch (opKind)
			{
			case OpKind::NearBranch16:
				EncoderFlags |= opSize16Flags;
				ImmSize = ImmSize::RipRelSize2_Target16;
				Immediate = instruction.GetNearBranch16();
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
			break;
		case 4:
			switch (opKind)
			{
			case OpKind::NearBranch32:
				EncoderFlags |= opSize32Flags;
				ImmSize = ImmSize::RipRelSize4_Target32;
				Immediate = instruction.GetNearBranch32();
				break;
			case OpKind::NearBranch64:
				ImmSize = ImmSize::RipRelSize4_Target64;
				target = instruction.GetNearBranch64();
				Immediate = static_cast<std::uint32_t>(target);
				ImmediateHi = static_cast<std::uint32_t>(target >> 32);
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
	}

	void Encoder::AddBranchX(std::int32_t immSize, const Instruction& instruction, std::int32_t operand)
	{
		if (bitness == 64)
		{
			if (!Verify(operand, OpKind::NearBranch64, instruction.GetOpKind(operand)))
			{
				return;
			}
			auto target = instruction.GetNearBranch64();
			switch (immSize)
			{
			case 2:
				EncoderFlags |= EncoderFlags::P66;
				ImmSize = ImmSize::RipRelSize2_Target64;
				Immediate = static_cast<std::uint32_t>(target);
				ImmediateHi = static_cast<std::uint32_t>(target >> 32);
				break;
			case 4:
				ImmSize = ImmSize::RipRelSize4_Target64;
				Immediate = static_cast<std::uint32_t>(target);
				ImmediateHi = static_cast<std::uint32_t>(target >> 32);
				break;
			default:
				throw std::runtime_error("invalid operation");
			}
		}
		else
		{
			assert(bitness == 16 || bitness == 32);
			if (!Verify(operand, OpKind::NearBranch32, instruction.GetOpKind(operand)))
			{
				return;
			}
			switch (immSize)
			{
			case 2:
				Static::Assert(static_cast<std::int32_t>(EncoderFlags::P66) == 0x80 ? 0 : -1);
				EncoderFlags |= static_cast<enum EncoderFlags>((bitness & 0x20) << 2);
				ImmSize = ImmSize::RipRelSize2_Target32;
				Immediate = instruction.GetNearBranch32();
				break;
			case 4:
				Static::Assert(static_cast<std::int32_t>(EncoderFlags::P66) == 0x80 ? 0 : -1);
				EncoderFlags |= static_cast<enum EncoderFlags>((bitness & 0x10) << 3);
				ImmSize = ImmSize::RipRelSize4_Target32;
				Immediate = instruction.GetNearBranch32();
				break;
			case 8:
			default:
				throw std::runtime_error("invalid operation");
			}
		}
	}

	void Encoder::AddBranchDisp(std::int32_t displSize, const Instruction& instruction, std::int32_t operand)
	{
		assert(displSize == 2 || displSize == 4);
		OpKind opKind;
		switch (displSize)
		{
		case 2:
			opKind = OpKind::NearBranch16;
			ImmSize = ImmSize::Size2;
			Immediate = instruction.GetNearBranch16();
			break;
		case 4:
			opKind = OpKind::NearBranch32;
			ImmSize = ImmSize::Size4;
			Immediate = instruction.GetNearBranch32();
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
		if (!Verify(operand, opKind, instruction.GetOpKind(operand)))
		{
			return;
		}
	}

	void Encoder::AddFarBranch(const Instruction& instruction, std::int32_t operand, std::int32_t size)
	{
		if (size == 2)
		{
			if (!Verify(operand, OpKind::FarBranch16, instruction.GetOpKind(operand)))
			{
				return;
			}
			ImmSize = ImmSize::Size2_2;
			Immediate = instruction.GetFarBranch16();
			ImmediateHi = instruction.GetFarBranchSelector();
		}
		else
		{
			assert(size == 4);
			if (!Verify(operand, OpKind::FarBranch32, instruction.GetOpKind(operand)))
			{
				return;
			}
			ImmSize = ImmSize::Size4_2;
			Immediate = instruction.GetFarBranch32();
			ImmediateHi = instruction.GetFarBranchSelector();
		}
		if (bitness != size * 8)
		{
			EncoderFlags |= EncoderFlags::P66;
		}
	}

	void Encoder::SetAddrSize(std::int32_t regSize)
	{
		assert(regSize == 2 || regSize == 4 || regSize == 8);
		if (bitness == 64)
		{
			if (regSize == 2)
			{
				SetErrorMessage(std::format("Invalid register size: {0:s}, must be 32-bit or 64-bit", Iced::Intel::ToString(regSize * 8)));
			}
			else if (regSize == 4)
			{
				EncoderFlags |= EncoderFlags::P67;
			}
		}
		else
		{
			if (regSize == 8)
			{
				SetErrorMessage(std::format("Invalid register size: {0:s}, must be 16-bit or 32-bit", Iced::Intel::ToString(regSize * 8)));
			}
			else if (bitness == 16)
			{
				if (regSize == 4)
				{
					EncoderFlags |= EncoderFlags::P67;
				}
			}
			else
			{
				assert(bitness == 32);
				if (regSize == 2)
				{
					EncoderFlags |= EncoderFlags::P67;
				}
			}
		}
	}

	void Encoder::AddAbsMem(const Instruction& instruction, std::int32_t operand)
	{
		EncoderFlags |= EncoderFlags::Displ;
		auto opKind = instruction.GetOpKind(operand);
		if (opKind == OpKind::Memory)
		{
			if (instruction.GetMemoryBase() != Register::None || instruction.GetMemoryIndex() != Register::None)
			{
				SetErrorMessage(std::format("Operand {0:s}: Absolute addresses can't have base and/or index regs", Iced::Intel::ToString(operand)));
				return;
			}
			if (instruction.GetMemoryIndexScale() != 1)
			{
				SetErrorMessage(std::format("Operand {0:s}: Absolute addresses must have scale == *1", Iced::Intel::ToString(operand)));
				return;
			}
			switch (instruction.GetMemoryDisplSize())
			{
			case 2:
				if (bitness == 64)
				{
					SetErrorMessage(std::format("Operand {0:s}: 16-bit abs addresses can't be used in 64-bit mode", Iced::Intel::ToString(operand)));
					return;
				}
				if (bitness == 32)
				{
					EncoderFlags |= EncoderFlags::P67;
				}
				DisplSize = DisplSize::Size2;
				if (instruction.GetMemoryDisplacement64() > std::numeric_limits<std::uint16_t>::max())
				{
					SetErrorMessage(std::format("Operand {0:s}: Displacement must fit in a ushort", Iced::Intel::ToString(operand)));
					return;
				}
				Displ = instruction.GetMemoryDisplacement32();
				break;
			case 4:
				EncoderFlags |= adrSize32Flags;
				DisplSize = DisplSize::Size4;
				if (instruction.GetMemoryDisplacement64() > std::numeric_limits<std::uint32_t>::max())
				{
					SetErrorMessage(std::format("Operand {0:s}: Displacement must fit in a uint", Iced::Intel::ToString(operand)));
					return;
				}
				Displ = instruction.GetMemoryDisplacement32();
				break;
			case 8:
			{
				if (bitness != 64)
				{
					SetErrorMessage(std::format("Operand {0:s}: 64-bit abs address is only available in 64-bit mode", Iced::Intel::ToString(operand)));
					return;
				}
				DisplSize = DisplSize::Size8;
				std::uint64_t addr = instruction.GetMemoryDisplacement64();
				Displ = static_cast<std::uint32_t>(addr);
				DisplHi = static_cast<std::uint32_t>(addr >> 32);
				break;
			}
			default:
				SetErrorMessage(std::format("Operand {0:s}: {1:s}.{2:s} must be initialized to 2 (16-bit) or 4 (32-bit)", Iced::Intel::ToString(operand), "Instruction", "MemoryDisplSize"));
				break;
			}
		}
		else
		{
			SetErrorMessage(std::format("Operand {0:s}: Expected OpKind {1:s}, actual: {2:s}", Iced::Intel::ToString(operand), "Memory", Iced::Intel::ToString(opKind)));
		}
	}

	void Encoder::AddModRMRegister(const Instruction& instruction, std::int32_t operand, Register regLo, Register regHi)
	{
		if (!Verify(operand, OpKind::Register, instruction.GetOpKind(operand)))
		{
			return;
		}
		auto reg = instruction.GetOpRegister(operand);
		if (!Verify(operand, (Register)reg, regLo, regHi))
		{
			return;
		}
		std::uint32_t regNum = static_cast<std::uint32_t>(reg - regLo);
		if (regLo == Register::AL)
		{
			if (reg >= Register::SPL)
			{
				regNum -= 4;
				EncoderFlags |= EncoderFlags::REX;
			}
			else if (reg >= Register::AH)
			{
				EncoderFlags |= EncoderFlags::HighLegacy8BitRegs;
			}
		}
		assert(regNum <= 31);
		ModRM |= static_cast<std::uint8_t>((regNum & 7) << 3);
		EncoderFlags |= EncoderFlags::ModRM;
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::R) == 4 ? 0 : -1);
		EncoderFlags |= static_cast<enum EncoderFlags>((regNum & 8) >> 1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::R2) == 0x200 ? 0 : -1);
		EncoderFlags |= static_cast<enum EncoderFlags>((regNum & 0x10) << (9 - 4));
	}

	void Encoder::AddReg(const Instruction& instruction, std::int32_t operand, Register regLo, Register regHi)
	{
		if (!Verify(operand, OpKind::Register, instruction.GetOpKind(operand)))
		{
			return;
		}
		auto reg = instruction.GetOpRegister(operand);
		if (!Verify(operand, (Register)reg, regLo, regHi))
		{
			return;
		}
		std::uint32_t regNum = static_cast<std::uint32_t>(reg - regLo);
		if (regLo == Register::AL)
		{
			if (reg >= Register::SPL)
			{
				regNum -= 4;
				EncoderFlags |= EncoderFlags::REX;
			}
			else if (reg >= Register::AH)
			{
				EncoderFlags |= EncoderFlags::HighLegacy8BitRegs;
			}
		}
		assert(regNum <= 15);
		OpCode |= regNum & 7;
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::B) == 1 ? 0 : -1);
		assert(regNum <= 15);
		EncoderFlags |= static_cast<enum EncoderFlags>(regNum >> 3); // regNum <= 15, so no need to mask out anything
	}

	void Encoder::AddRegOrMem(const Instruction& instruction, std::int32_t operand, Register regLo, Register regHi, bool allowMemOp, bool allowRegOp)
	{
		AddRegOrMem(instruction, operand, regLo, regHi, Register::None, Register::None, allowMemOp, allowRegOp);
	}

	void Encoder::AddRegOrMem(const Instruction& instruction, std::int32_t operand, Register regLo, Register regHi, Register vsibIndexRegLo, Register vsibIndexRegHi, bool allowMemOp, bool allowRegOp)
	{
		auto opKind = instruction.GetOpKind(operand);
		EncoderFlags |= EncoderFlags::ModRM;
		if (opKind == OpKind::Register)
		{
			if (!allowRegOp)
			{
				SetErrorMessage(std::format("Operand {0:s}: register operand is not allowed", Iced::Intel::ToString(operand)));
				return;
			}
			auto reg = instruction.GetOpRegister(operand);
			if (!Verify(operand, (Register)reg, regLo, regHi))
			{
				return;
			}
			std::uint32_t regNum = static_cast<std::uint32_t>(reg - regLo);
			if (regLo == Register::AL)
			{
				if (reg >= Register::R8L)
				{
					regNum -= 4;
				}
				else if (reg >= Register::SPL)
				{
					regNum -= 4;
					EncoderFlags |= EncoderFlags::REX;
				}
				else if (reg >= Register::AH)
				{
					EncoderFlags |= EncoderFlags::HighLegacy8BitRegs;
				}
			}
			ModRM |= static_cast<std::uint8_t>(regNum & 7);
			ModRM |= 0xC0;
			Static::Assert(static_cast<std::int32_t>(EncoderFlags::B) == 1 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(EncoderFlags::X) == 2 ? 0 : -1);
			EncoderFlags |= static_cast<enum EncoderFlags>((regNum >> 3) & 3);
			assert(regNum <= 31);
		}
		else if (opKind == OpKind::Memory)
		{
			if (!allowMemOp)
			{
				SetErrorMessage(std::format("Operand {0:s}: memory operand is not allowed", Iced::Intel::ToString(operand)));
				return;
			}
			if (Iced::Intel::MemorySizeExtensions::IsBroadcast(instruction.GetMemorySize()))
			{
				EncoderFlags |= EncoderFlags::Broadcast;
			}
			auto codeSize = instruction.GetCodeSize();
			if (codeSize == CodeSize::Unknown)
			{
				if (bitness == 64)
				{
					codeSize = CodeSize::Code64;
				}
				else if (bitness == 32)
				{
					codeSize = CodeSize::Code32;
				}
				else
				{
					assert(bitness == 16);
					codeSize = CodeSize::Code16;
				}
			}
			std::int32_t addrSize = InstructionUtils::GetAddressSizeInBytes(instruction.GetMemoryBase(), instruction.GetMemoryIndex(), instruction.GetMemoryDisplSize(), codeSize) * 8;
			if (addrSize != bitness)
			{
				EncoderFlags |= EncoderFlags::P67;
			}
			if ((EncoderFlags & EncoderFlags::RegIsMemory) != 0)
			{
				auto regSize = GetRegisterOpSize(instruction);
				if (regSize != addrSize)
				{
					SetErrorMessage(std::format("Operand {0:s}: Register operand size must equal memory addressing mode (16/32/64)", Iced::Intel::ToString(operand)));
					return;
				}
			}
			if (addrSize == 16)
			{
				if (vsibIndexRegLo != Register::None)
				{
					SetErrorMessage(std::format("Operand {0:s}: VSIB operands can't use 16-bit addressing. It must be 32-bit or 64-bit addressing", Iced::Intel::ToString(operand)));
					return;
				}
				AddMemOp16(instruction, operand);
			}
			else
			{
				AddMemOp(instruction, operand, addrSize, vsibIndexRegLo, vsibIndexRegHi);
			}
		}
		else
		{
			SetErrorMessage(std::format("Operand {0:s}: Expected a register or memory operand, but opKind is {1:s}", Iced::Intel::ToString(operand), Iced::Intel::ToString(opKind)));
		}
	}

	std::int32_t Encoder::GetRegisterOpSize(const Instruction& instruction)
	{
		assert(instruction.GetOp0Kind() == OpKind::Register);
		if (instruction.GetOp0Kind() == OpKind::Register)
		{
			auto reg = instruction.GetOp0Register();
			if (Iced::Intel::RegisterExtensions::IsGPR64(reg))
			{
				return 64;
			}
			if (Iced::Intel::RegisterExtensions::IsGPR32(reg))
			{
				return 32;
			}
			if (Iced::Intel::RegisterExtensions::IsGPR16(reg))
			{
				return 16;
			}
		}
		return 0;
	}

	bool Encoder::TryConvertToDisp8N(const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue)
	{
		auto tryConvertToDisp8N = handler->TryConvertToDisp8N;
		if (tryConvertToDisp8N != nullptr)
		{
			return tryConvertToDisp8N(*this, handler, instruction, displ, compressedValue);
		}
		if (std::numeric_limits<std::int8_t>::min() <= displ && displ <= std::numeric_limits<std::int8_t>::max())
		{
			compressedValue = static_cast<std::int8_t>(displ);
			return true;
		}
		compressedValue = 0;
		return false;
	}

	void Encoder::AddMemOp16(const Instruction& instruction, std::int32_t operand)
	{
		if (bitness == 64)
		{
			SetErrorMessage(std::format("Operand {0:s}: 16-bit addressing can't be used by 64-bit code", Iced::Intel::ToString(operand)));
			return;
		}
		auto baseReg = instruction.GetMemoryBase();
		auto indexReg = instruction.GetMemoryIndex();
		auto displSize = instruction.GetMemoryDisplSize();
		if (baseReg == Register::BX && indexReg == Register::SI)
		{
			// Nothing
		}
		else if (baseReg == Register::BX && indexReg == Register::DI)
		{
			ModRM |= 1;
		}
		else if (baseReg == Register::BP && indexReg == Register::SI)
		{
			ModRM |= 2;
		}
		else if (baseReg == Register::BP && indexReg == Register::DI)
		{
			ModRM |= 3;
		}
		else if (baseReg == Register::SI && indexReg == Register::None)
		{
			ModRM |= 4;
		}
		else if (baseReg == Register::DI && indexReg == Register::None)
		{
			ModRM |= 5;
		}
		else if (baseReg == Register::BP && indexReg == Register::None)
		{
			ModRM |= 6;
		}
		else if (baseReg == Register::BX && indexReg == Register::None)
		{
			ModRM |= 7;
		}
		else if (baseReg == Register::None && indexReg == Register::None)
		{
			ModRM |= 6;
			DisplSize = DisplSize::Size2;
			if (instruction.GetMemoryDisplacement64() > std::numeric_limits<std::uint16_t>::max())
			{
				SetErrorMessage(std::format("Operand {0:s}: Displacement must fit in a ushort", Iced::Intel::ToString(operand)));
				return;
			}
			Displ = instruction.GetMemoryDisplacement32();
		}
		else
		{
			SetErrorMessage(std::format("Operand {0:s}: Invalid 16-bit base + index registers: base={1:s}, index={2:s}", Iced::Intel::ToString(operand), Iced::Intel::ToString(baseReg), Iced::Intel::ToString(indexReg)));
			return;
		}
		if (baseReg != Register::None || indexReg != Register::None)
		{
			if (static_cast<std::int64_t>(instruction.GetMemoryDisplacement64()) < std::numeric_limits<std::int16_t>::min() || static_cast<std::int64_t>(instruction.GetMemoryDisplacement64()) > std::numeric_limits<std::uint16_t>::max())
			{
				SetErrorMessage(std::format("Operand {0:s}: Displacement must fit in a short or a ushort", Iced::Intel::ToString(operand)));
				return;
			}
			Displ = instruction.GetMemoryDisplacement32();
			// [bp] => [bp+00]
			if (displSize == 0 && baseReg == Register::BP && indexReg == Register::None)
			{
				displSize = 1;
				if (Displ != 0)
				{
					SetErrorMessage(std::format("Operand {0:s}: Displacement must be 0 if displSize == 0", Iced::Intel::ToString(operand)));
					return;
				}
			}
			if (displSize == 1)
			{
				std::int8_t compressedValue;
				if (TryConvertToDisp8N(instruction, static_cast<std::int16_t>(Displ), compressedValue))
				{
					Displ = static_cast<std::uint32_t>(compressedValue);
				}
				else
				{
					displSize = 2;
				}
			}
			if (displSize == 0)
			{
				if (Displ != 0)
				{
					SetErrorMessage(std::format("Operand {0:s}: Displacement must be 0 if displSize == 0", Iced::Intel::ToString(operand)));
					return;
				}
			}
			else if (displSize == 1)
			{
				// This if check should never be true when we're here
				if (static_cast<std::int32_t>(Displ) < std::numeric_limits<std::int8_t>::min() || static_cast<std::int32_t>(Displ) > std::numeric_limits<std::int8_t>::max())
				{
					SetErrorMessage(std::format("Operand {0:s}: Displacement must fit in an sbyte", Iced::Intel::ToString(operand)));
					return;
				}
				ModRM |= 0x40;
				DisplSize = DisplSize::Size1;
			}
			else if (displSize == 2)
			{
				ModRM |= 0x80;
				DisplSize = DisplSize::Size2;
			}
			else
			{
				SetErrorMessage(std::format("Operand {0:s}: Invalid displacement size: {1:s}, must be 0, 1, or 2", Iced::Intel::ToString(operand), Iced::Intel::ToString(displSize)));
				return;
			}
		}
	}

	void Encoder::AddMemOp(const Instruction& instruction, std::int32_t operand, std::int32_t addrSize, Register vsibIndexRegLo, Register vsibIndexRegHi)
	{
		assert(addrSize == 32 || addrSize == 64);
		if (bitness != 64 && addrSize == 64)
		{
			SetErrorMessage(std::format("Operand {0:s}: 64-bit addressing can only be used in 64-bit mode", Iced::Intel::ToString(operand)));
			return;
		}
		auto baseReg = instruction.GetMemoryBase();
		auto indexReg = instruction.GetMemoryIndex();
		auto displSize = instruction.GetMemoryDisplSize();
		Register baseRegLo, baseRegHi;
		Register indexRegLo, indexRegHi;
		if (addrSize == 64)
		{
			baseRegLo = Register::RAX;
			baseRegHi = Register::R15;
		}
		else
		{
			assert(addrSize == 32);
			baseRegLo = Register::EAX;
			baseRegHi = Register::R15D;
		}
		if (vsibIndexRegLo != Register::None)
		{
			indexRegLo = vsibIndexRegLo;
			indexRegHi = vsibIndexRegHi;
		}
		else
		{
			indexRegLo = baseRegLo;
			indexRegHi = baseRegHi;
		}
		if (baseReg != Register::None && baseReg != Register::RIP && baseReg != Register::EIP && !Verify(operand, baseReg, baseRegLo, baseRegHi))
		{
			return;
		}
		if (indexReg != Register::None && !Verify(operand, indexReg, indexRegLo, indexRegHi))
		{
			return;
		}
		if (displSize != 0 && displSize != 1 && displSize != 4 && displSize != 8)
		{
			SetErrorMessage(std::format("Operand {0:s}: Invalid displ size: {1:s}, must be 0, 1, 4, 8", Iced::Intel::ToString(operand), Iced::Intel::ToString(displSize)));
			return;
		}
		if (baseReg == Register::RIP || baseReg == Register::EIP)
		{
			if (indexReg != Register::None)
			{
				SetErrorMessage(std::format("Operand {0:s}: RIP relative addressing can't use an index register", Iced::Intel::ToString(operand)));
				return;
			}
			if (instruction.GetInternalMemoryIndexScale() != 0)
			{
				SetErrorMessage(std::format("Operand {0:s}: RIP relative addressing must use scale *1", Iced::Intel::ToString(operand)));
				return;
			}
			if (bitness != 64)
			{
				SetErrorMessage(std::format("Operand {0:s}: RIP/EIP relative addressing is only available in 64-bit mode", Iced::Intel::ToString(operand)));
				return;
			}
			if ((EncoderFlags & EncoderFlags::MustUseSib) != 0)
			{
				SetErrorMessage(std::format("Operand {0:s}: RIP/EIP relative addressing isn't supported", Iced::Intel::ToString(operand)));
				return;
			}
			ModRM |= 5;
			std::uint64_t target = instruction.GetMemoryDisplacement64();
			if (baseReg == Register::RIP)
			{
				DisplSize = DisplSize::RipRelSize4_Target64;
				Displ = static_cast<std::uint32_t>(target);
				DisplHi = static_cast<std::uint32_t>(target >> 32);
			}
			else
			{
				DisplSize = DisplSize::RipRelSize4_Target32;
				if (target > std::numeric_limits<std::uint32_t>::max())
				{
					SetErrorMessage(std::format("Operand {0:s}: Target address doesn't fit in 32 bits: 0x{1:0>X}", Iced::Intel::ToString(operand), Iced::Intel::ToString(target)));
					return;
				}
				Displ = static_cast<std::uint32_t>(target);
			}
			return;
		}
		auto scale = instruction.GetInternalMemoryIndexScale();
		Displ = instruction.GetMemoryDisplacement32();
		if (addrSize == 64)
		{
			if (static_cast<std::int64_t>(instruction.GetMemoryDisplacement64()) < std::numeric_limits<std::int32_t>::min() || static_cast<std::int64_t>(instruction.GetMemoryDisplacement64()) > std::numeric_limits<std::int32_t>::max())
			{
				SetErrorMessage(std::format("Operand {0:s}: Displacement must fit in an int", Iced::Intel::ToString(operand)));
				return;
			}
		}
		else
		{
			assert(addrSize == 32);
			if (static_cast<std::int64_t>(instruction.GetMemoryDisplacement64()) < std::numeric_limits<std::int32_t>::min() || static_cast<std::int64_t>(instruction.GetMemoryDisplacement64()) > std::numeric_limits<std::uint32_t>::max())
			{
				SetErrorMessage(std::format("Operand {0:s}: Displacement must fit in an int or a uint", Iced::Intel::ToString(operand)));
				return;
			}
		}
		if (baseReg == Register::None && indexReg == Register::None)
		{
			if (vsibIndexRegLo != Register::None)
			{
				SetErrorMessage(std::format("Operand {0:s}: VSIB addressing can't use an offset-only address", Iced::Intel::ToString(operand)));
				return;
			}
			if (bitness == 64 || scale != 0 || (EncoderFlags & EncoderFlags::MustUseSib) != 0)
			{
				ModRM |= 4;
				DisplSize = DisplSize::Size4;
				EncoderFlags |= EncoderFlags::Sib;
				Sib = static_cast<std::uint8_t>(0x25 | (scale << 6));
				return;
			}
			else
			{
				ModRM |= 5;
				DisplSize = DisplSize::Size4;
				return;
			}
		}
		std::int32_t baseNum = baseReg == Register::None ? -1 : baseReg - baseRegLo;
		std::int32_t indexNum = indexReg == Register::None ? -1 : indexReg - indexRegLo;
		// [ebp]/[ebp+index*scale] => [ebp+00]/[ebp+index*scale+00]
		if (displSize == 0 && (baseNum & 7) == 5)
		{
			displSize = 1;
			if (Displ != 0)
			{
				SetErrorMessage(std::format("Operand {0:s}: Displacement must be 0 if displSize == 0", Iced::Intel::ToString(operand)));
				return;
			}
		}
		if (displSize == 1)
		{
			std::int8_t compressedValue;
			if (TryConvertToDisp8N(instruction, static_cast<std::int32_t>(Displ), compressedValue))
			{
				Displ = static_cast<std::uint32_t>(compressedValue);
			}
			else
			{
				displSize = addrSize / 8;
			}
		}
		if (baseReg == Register::None)
		{
			// Tested earlier in the method
			assert(indexReg != Register::None);
			DisplSize = DisplSize::Size4;
		}
		else if (displSize == 1)
		{
			// This if check should never be true when we're here
			if (static_cast<std::int32_t>(Displ) < std::numeric_limits<std::int8_t>::min() || static_cast<std::int32_t>(Displ) > std::numeric_limits<std::int8_t>::max())
			{
				SetErrorMessage(std::format("Operand {0:s}: Displacement must fit in an sbyte", Iced::Intel::ToString(operand)));
				return;
			}
			ModRM |= 0x40;
			DisplSize = DisplSize::Size1;
		}
		else if (displSize == addrSize / 8)
		{
			ModRM |= 0x80;
			DisplSize = DisplSize::Size4;
		}
		else if (displSize == 0)
		{
			if (Displ != 0)
			{
				SetErrorMessage(std::format("Operand {0:s}: Displacement must be 0 if displSize == 0", Iced::Intel::ToString(operand)));
				return;
			}
		}
		else
		{
			SetErrorMessage(std::format("Operand {0:s}: Invalid {1:s} value", Iced::Intel::ToString(operand), "MemoryDisplSize"));
			return;
		}
		if (indexReg == Register::None && (baseNum & 7) != 4 && scale == 0 && (EncoderFlags & EncoderFlags::MustUseSib) == 0)
		{
			// Tested earlier in the method
			assert(baseReg != Register::None);
			ModRM |= static_cast<std::uint8_t>(baseNum & 7);
		}
		else
		{
			EncoderFlags |= EncoderFlags::Sib;
			Sib = static_cast<std::uint8_t>(scale << 6);
			ModRM |= 4;
			if (indexReg == Register::RSP || indexReg == Register::ESP)
			{
				SetErrorMessage(std::format("Operand {0:s}: ESP/RSP can't be used as an index register", Iced::Intel::ToString(operand)));
				return;
			}
			if (baseNum < 0)
			{
				Sib |= 5;
			}
			else
			{
				Sib |= static_cast<std::uint8_t>(baseNum & 7);
			}
			if (indexNum < 0)
			{
				Sib |= 0x20;
			}
			else
			{
				Sib |= static_cast<std::uint8_t>((indexNum & 7) << 3);
			}
		}
		if (baseNum >= 0)
		{
			Static::Assert(static_cast<std::int32_t>(EncoderFlags::B) == 1 ? 0 : -1);
			assert(baseNum <= 15); // No '& 1' required below
			EncoderFlags |= static_cast<enum EncoderFlags>(baseNum >> 3);
		}
		if (indexNum >= 0)
		{
			Static::Assert(static_cast<std::int32_t>(EncoderFlags::X) == 2 ? 0 : -1);
			EncoderFlags |= static_cast<enum EncoderFlags>((indexNum >> 2) & 2);
			EncoderFlags |= static_cast<enum EncoderFlags>((indexNum & 0x10) << static_cast<std::int32_t>(EncoderFlags::VvvvvShift));
			assert(indexNum <= 31);
		}
	}

	std::vector<std::uint8_t> Encoder::SegmentOverrides = { 0x26, 0x2E, 0x36, 0x3E, 0x64, 0x65 };

	void Encoder::WritePrefixes(const Instruction& instruction, bool canWriteF3)
	{
		assert(!handler->IsDeclareData);
		auto seg = instruction.GetSegmentPrefix();
		if (seg != Register::None)
		{
			assert(static_cast<std::uint32_t>(seg - Register::ES) < static_cast<std::uint32_t>(SegmentOverrides.size()));
			WriteByteInternal(SegmentOverrides[seg - Register::ES]);
		}
		if ((EncoderFlags & EncoderFlags::PF0) != 0 || instruction.GetHasLockPrefix())
		{
			WriteByteInternal(0xF0);
		}
		if ((EncoderFlags & EncoderFlags::P66) != 0)
		{
			WriteByteInternal(0x66);
		}
		if ((EncoderFlags & EncoderFlags::P67) != 0)
		{
			WriteByteInternal(0x67);
		}
		if (canWriteF3 && instruction.GetHasRepePrefix())
		{
			WriteByteInternal(0xF3);
		}
		if (instruction.GetHasRepnePrefix())
		{
			WriteByteInternal(0xF2);
		}
	}

	void Encoder::WriteModRM()
	{
		assert(!handler->IsDeclareData);
		assert((EncoderFlags & (EncoderFlags::ModRM | EncoderFlags::Displ)) != 0);
		if ((EncoderFlags & EncoderFlags::ModRM) != 0)
		{
			WriteByteInternal(ModRM);
			if ((EncoderFlags & EncoderFlags::Sib) != 0)
			{
				WriteByteInternal(Sib);
			}
		}
		std::uint32_t diff4;
		displAddr = static_cast<std::uint32_t>(currentRip);
		switch (DisplSize)
		{
		case DisplSize::None:
			break;
		case DisplSize::Size1:
			WriteByteInternal(Displ);
			break;
		case DisplSize::Size2:
			diff4 = Displ;
			WriteByteInternal(diff4);
			WriteByteInternal(diff4 >> 8);
			break;
		case DisplSize::Size4:
			diff4 = Displ;
			WriteByteInternal(diff4);
			WriteByteInternal(diff4 >> 8);
			WriteByteInternal(diff4 >> 16);
			WriteByteInternal(diff4 >> 24);
			break;
		case DisplSize::Size8:
			diff4 = Displ;
			WriteByteInternal(diff4);
			WriteByteInternal(diff4 >> 8);
			WriteByteInternal(diff4 >> 16);
			WriteByteInternal(diff4 >> 24);
			diff4 = DisplHi;
			WriteByteInternal(diff4);
			WriteByteInternal(diff4 >> 8);
			WriteByteInternal(diff4 >> 16);
			WriteByteInternal(diff4 >> 24);
			break;
		case DisplSize::RipRelSize4_Target32:
		{
			std::uint32_t eip = static_cast<std::uint32_t>(currentRip) + 4 + immSizes[static_cast<std::int32_t>(ImmSize)];
			diff4 = Displ - eip;
			WriteByteInternal(diff4);
			WriteByteInternal(diff4 >> 8);
			WriteByteInternal(diff4 >> 16);
			WriteByteInternal(diff4 >> 24);
			break;
		}
		case DisplSize::RipRelSize4_Target64:
		{
			std::uint64_t rip = currentRip + 4 + immSizes[static_cast<std::int32_t>(ImmSize)];
			std::int64_t diff8 = static_cast<std::int64_t>((static_cast<std::uint64_t>(DisplHi) << 32) | static_cast<std::uint64_t>(Displ)) - static_cast<std::int64_t>(rip);
			if (diff8 < std::numeric_limits<std::int32_t>::min() || diff8 > std::numeric_limits<std::int32_t>::max())
			{
				SetErrorMessage(std::format("RIP relative distance is too far away: NextIP: 0x{0:0>.16X} target: 0x{1:0>.8X}{2:0>.8X}, diff = {3:s}, diff must fit in an Int32", Iced::Intel::ToString(rip), Iced::Intel::ToString(DisplHi), Iced::Intel::ToString(Displ), Iced::Intel::ToString(diff8)));
			}
			diff4 = static_cast<std::uint32_t>(diff8);
			WriteByteInternal(diff4);
			WriteByteInternal(diff4 >> 8);
			WriteByteInternal(diff4 >> 16);
			WriteByteInternal(diff4 >> 24);
			break;
		}
		default:
			throw std::runtime_error("invalid operation");
		}
	}

	void Encoder::WriteImmediate()
	{
		assert(!handler->IsDeclareData);
		std::uint16_t ip;
		std::uint32_t eip;
		std::uint64_t rip;
		std::int16_t diff2;
		std::int32_t diff4;
		std::int64_t diff8;
		std::uint32_t value;
		immAddr = static_cast<std::uint32_t>(currentRip);
		switch (ImmSize)
		{
		case ImmSize::None:
			break;
		case ImmSize::Size1:
		case ImmSize::SizeIbReg:
		case ImmSize::Size1OpCode:
			WriteByteInternal(Immediate);
			break;
		case ImmSize::Size2:
			value = Immediate;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			break;
		case ImmSize::Size4:
			value = Immediate;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			WriteByteInternal(value >> 16);
			WriteByteInternal(value >> 24);
			break;
		case ImmSize::Size8:
			value = Immediate;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			WriteByteInternal(value >> 16);
			WriteByteInternal(value >> 24);
			value = ImmediateHi;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			WriteByteInternal(value >> 16);
			WriteByteInternal(value >> 24);
			break;
		case ImmSize::Size2_1:
			value = Immediate;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			WriteByteInternal(ImmediateHi);
			break;
		case ImmSize::Size1_1:
			WriteByteInternal(Immediate);
			WriteByteInternal(ImmediateHi);
			break;
		case ImmSize::Size2_2:
			value = Immediate;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			value = ImmediateHi;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			break;
		case ImmSize::Size4_2:
			value = Immediate;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			WriteByteInternal(value >> 16);
			WriteByteInternal(value >> 24);
			value = ImmediateHi;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			break;
		case ImmSize::RipRelSize1_Target16:
			ip = static_cast<std::uint16_t>(static_cast<std::uint32_t>(currentRip) + 1);
			diff2 = static_cast<std::int16_t>(static_cast<std::int16_t>(Immediate) - static_cast<std::int16_t>(ip));
			if (diff2 < std::numeric_limits<std::int8_t>::min() || diff2 > std::numeric_limits<std::int8_t>::max())
			{
				SetErrorMessage(std::format("Branch distance is too far away: NextIP: 0x{0:0>.4X} target: 0x{1:0>.4X}, diff = {2:s}, diff must fit in an Int8", Iced::Intel::ToString(ip), Iced::Intel::ToString(static_cast<std::uint16_t>(Immediate)), Iced::Intel::ToString(diff2)));
			}
			WriteByteInternal(static_cast<std::uint32_t>(diff2));
			break;
		case ImmSize::RipRelSize1_Target32:
			eip = static_cast<std::uint32_t>(currentRip) + 1;
			diff4 = static_cast<std::int32_t>(Immediate) - static_cast<std::int32_t>(eip);
			if (diff4 < std::numeric_limits<std::int8_t>::min() || diff4 > std::numeric_limits<std::int8_t>::max())
			{
				SetErrorMessage(std::format("Branch distance is too far away: NextIP: 0x{0:0>.8X} target: 0x{1:0>.8X}, diff = {2:s}, diff must fit in an Int8", Iced::Intel::ToString(eip), Iced::Intel::ToString(Immediate), Iced::Intel::ToString(diff4)));
			}
			WriteByteInternal(static_cast<std::uint32_t>(diff4));
			break;
		case ImmSize::RipRelSize1_Target64:
			rip = currentRip + 1;
			diff8 = static_cast<std::int64_t>((static_cast<std::uint64_t>(ImmediateHi) << 32) | static_cast<std::uint64_t>(Immediate)) - static_cast<std::int64_t>(rip);
			if (diff8 < std::numeric_limits<std::int8_t>::min() || diff8 > std::numeric_limits<std::int8_t>::max())
			{
				SetErrorMessage(std::format("Branch distance is too far away: NextIP: 0x{0:0>.16X} target: 0x{1:0>.8X}{2:0>.8X}, diff = {3:s}, diff must fit in an Int8", Iced::Intel::ToString(rip), Iced::Intel::ToString(ImmediateHi), Iced::Intel::ToString(Immediate), Iced::Intel::ToString(diff8)));
			}
			WriteByteInternal(static_cast<std::uint32_t>(diff8));
			break;
		case ImmSize::RipRelSize2_Target16:
			eip = static_cast<std::uint32_t>(currentRip) + 2;
			value = Immediate - eip;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			break;
		case ImmSize::RipRelSize2_Target32:
			eip = static_cast<std::uint32_t>(currentRip) + 2;
			diff4 = static_cast<std::int32_t>(Immediate - eip);
			if (diff4 < std::numeric_limits<std::int16_t>::min() || diff4 > std::numeric_limits<std::int16_t>::max())
			{
				SetErrorMessage(std::format("Branch distance is too far away: NextIP: 0x{0:0>.8X} target: 0x{1:0>.8X}, diff = {2:s}, diff must fit in an Int16", Iced::Intel::ToString(eip), Iced::Intel::ToString(Immediate), Iced::Intel::ToString(diff4)));
			}
			value = static_cast<std::uint32_t>(diff4);
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			break;
		case ImmSize::RipRelSize2_Target64:
			rip = currentRip + 2;
			diff8 = static_cast<std::int64_t>((static_cast<std::uint64_t>(ImmediateHi) << 32) | static_cast<std::uint64_t>(Immediate)) - static_cast<std::int64_t>(rip);
			if (diff8 < std::numeric_limits<std::int16_t>::min() || diff8 > std::numeric_limits<std::int16_t>::max())
			{
				SetErrorMessage(std::format("Branch distance is too far away: NextIP: 0x{0:0>.16X} target: 0x{1:0>.8X}{2:0>.8X}, diff = {3:s}, diff must fit in an Int16", Iced::Intel::ToString(rip), Iced::Intel::ToString(ImmediateHi), Iced::Intel::ToString(Immediate), Iced::Intel::ToString(diff8)));
			}
			value = static_cast<std::uint32_t>(diff8);
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			break;
		case ImmSize::RipRelSize4_Target32:
			eip = static_cast<std::uint32_t>(currentRip) + 4;
			value = Immediate - eip;
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			WriteByteInternal(value >> 16);
			WriteByteInternal(value >> 24);
			break;
		case ImmSize::RipRelSize4_Target64:
			rip = currentRip + 4;
			diff8 = static_cast<std::int64_t>((static_cast<std::uint64_t>(ImmediateHi) << 32) | static_cast<std::uint64_t>(Immediate)) - static_cast<std::int64_t>(rip);
			if (diff8 < std::numeric_limits<std::int32_t>::min() || diff8 > std::numeric_limits<std::int32_t>::max())
			{
				SetErrorMessage(std::format("Branch distance is too far away: NextIP: 0x{0:0>.16X} target: 0x{1:0>.8X}{2:0>.8X}, diff = {3:s}, diff must fit in an Int32", Iced::Intel::ToString(rip), Iced::Intel::ToString(ImmediateHi), Iced::Intel::ToString(Immediate), Iced::Intel::ToString(diff8)));
			}
			value = static_cast<std::uint32_t>(diff8);
			WriteByteInternal(value);
			WriteByteInternal(value >> 8);
			WriteByteInternal(value >> 16);
			WriteByteInternal(value >> 24);
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
	}

	void Encoder::WriteByte(std::uint8_t value)
	{
		WriteByteInternal(value);
	}

	void Encoder::WriteByteInternal(std::uint32_t value)
	{
		writer->WriteByte(static_cast<std::uint8_t>(value));
		currentRip++;
	}

	ConstantOffsets Encoder::GetConstantOffsets()
	{
		ConstantOffsets constantOffsets = Iced::Intel::ConstantOffsets();
		switch (DisplSize)
		{
		case DisplSize::None:
			break;
		case DisplSize::Size1:
			constantOffsets.DisplacementSize = 1;
			constantOffsets.DisplacementOffset = static_cast<std::uint8_t>(displAddr - eip);
			break;
		case DisplSize::Size2:
			constantOffsets.DisplacementSize = 2;
			constantOffsets.DisplacementOffset = static_cast<std::uint8_t>(displAddr - eip);
			break;
		case DisplSize::Size4:
		case DisplSize::RipRelSize4_Target32:
		case DisplSize::RipRelSize4_Target64:
			constantOffsets.DisplacementSize = 4;
			constantOffsets.DisplacementOffset = static_cast<std::uint8_t>(displAddr - eip);
			break;
		case DisplSize::Size8:
			constantOffsets.DisplacementSize = 8;
			constantOffsets.DisplacementOffset = static_cast<std::uint8_t>(displAddr - eip);
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
		switch (ImmSize)
		{
		case ImmSize::None:
		case ImmSize::SizeIbReg:
		case ImmSize::Size1OpCode:
			break;
		case ImmSize::Size1:
		case ImmSize::RipRelSize1_Target16:
		case ImmSize::RipRelSize1_Target32:
		case ImmSize::RipRelSize1_Target64:
			constantOffsets.ImmediateSize = 1;
			constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(immAddr - eip);
			break;
		case ImmSize::Size1_1:
			constantOffsets.ImmediateSize = 1;
			constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(immAddr - eip);
			constantOffsets.ImmediateSize2 = 1;
			constantOffsets.ImmediateOffset2 = static_cast<std::uint8_t>(immAddr - eip + 1);
			break;
		case ImmSize::Size2:
		case ImmSize::RipRelSize2_Target16:
		case ImmSize::RipRelSize2_Target32:
		case ImmSize::RipRelSize2_Target64:
			constantOffsets.ImmediateSize = 2;
			constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(immAddr - eip);
			break;
		case ImmSize::Size2_1:
			constantOffsets.ImmediateSize = 2;
			constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(immAddr - eip);
			constantOffsets.ImmediateSize2 = 1;
			constantOffsets.ImmediateOffset2 = static_cast<std::uint8_t>(immAddr - eip + 2);
			break;
		case ImmSize::Size2_2:
			constantOffsets.ImmediateSize = 2;
			constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(immAddr - eip);
			constantOffsets.ImmediateSize2 = 2;
			constantOffsets.ImmediateOffset2 = static_cast<std::uint8_t>(immAddr - eip + 2);
			break;
		case ImmSize::Size4:
		case ImmSize::RipRelSize4_Target32:
		case ImmSize::RipRelSize4_Target64:
			constantOffsets.ImmediateSize = 4;
			constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(immAddr - eip);
			break;
		case ImmSize::Size4_2:
			constantOffsets.ImmediateSize = 4;
			constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(immAddr - eip);
			constantOffsets.ImmediateSize2 = 2;
			constantOffsets.ImmediateOffset2 = static_cast<std::uint8_t>(immAddr - eip + 4);
			break;
		case ImmSize::Size8:
			constantOffsets.ImmediateSize = 8;
			constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(immAddr - eip);
			break;
		default:
			throw std::runtime_error("invalid operation");
		}
		return constantOffsets;
	}
}
