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

#include "OpHandlers.h"
#include "Enums.h"
#include "../Code.g.h"

namespace Iced::Intel::EncoderInternal
{

	Iced::Intel::OpKind Op::GetImmediateOpKind()
	{
		return static_cast<OpKind>(-1);
	}

	Iced::Intel::OpKind Op::GetNearBranchOpKind()
	{
		return static_cast<OpKind>(-1);
	}

	Iced::Intel::OpKind Op::GetFarBranchOpKind()
	{
		return static_cast<OpKind>(-1);
	}

	OpModRM_rm_mem_only::OpModRM_rm_mem_only(bool mustUseSib)
	{
		this->mustUseSib = mustUseSib;
	}

	void OpModRM_rm_mem_only::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (mustUseSib)
		{
			encoder->EncoderFlags |= EncoderFlags::MustUseSib;
		}
		encoder->AddRegOrMem(instruction, operand, Register::None, Register::None, true, false);
	}

	OpModRM_rm::OpModRM_rm(Register regLo, Register regHi)
	{
		this->regLo = regLo;
		this->regHi = regHi;
	}

	void OpModRM_rm::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddRegOrMem(instruction, operand, regLo, regHi, true, true);
	}

	OpRegEmbed8::OpRegEmbed8(Register regLo, Register regHi)
	{
		this->regLo = regLo;
		this->regHi = regHi;
	}

	void OpRegEmbed8::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddReg(instruction, operand, regLo, regHi);
	}

	OpModRM_rm_reg_only::OpModRM_rm_reg_only(Register regLo, Register regHi)
	{
		this->regLo = regLo;
		this->regHi = regHi;
	}

	void OpModRM_rm_reg_only::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddRegOrMem(instruction, operand, regLo, regHi, false, true);
	}

	OpModRM_reg::OpModRM_reg(Register regLo, Register regHi)
	{
		this->regLo = regLo;
		this->regHi = regHi;
	}

	void OpModRM_reg::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddModRMRegister(instruction, operand, regLo, regHi);
	}

	OpModRM_reg_mem::OpModRM_reg_mem(Register regLo, Register regHi)
	{
		this->regLo = regLo;
		this->regHi = regHi;
	}

	void OpModRM_reg_mem::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddModRMRegister(instruction, operand, regLo, regHi);
		encoder->EncoderFlags |= EncoderFlags::RegIsMemory;
	}

	OpModRM_regF0::OpModRM_regF0(Register regLo, Register regHi)
	{
		this->regLo = regLo;
		this->regHi = regHi;
	}

	void OpModRM_regF0::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (encoder->GetBitness() != 64 && instruction.GetOpKind(operand) == OpKind::Register && instruction.GetOpRegister(operand) >= regLo + 8 && instruction.GetOpRegister(operand) <= regLo + 15)
		{
			encoder->EncoderFlags |= EncoderFlags::PF0;
			encoder->AddModRMRegister(instruction, operand, regLo + 8, regLo + 15);
		}
		else
		{
			encoder->AddModRMRegister(instruction, operand, regLo, regHi);
		}
	}

	OpReg::OpReg(Register register_)
	{
		this->register_ = register_;
	}

	void OpReg::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->Verify(operand, OpKind::Register, instruction.GetOpKind(operand));
		encoder->Verify(operand, register_, instruction.GetOpRegister(operand));
	}

	void OpRegSTi::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (!encoder->Verify(operand, OpKind::Register, instruction.GetOpKind(operand)))
		{
			return;
		}
		auto reg = instruction.GetOpRegister(operand);
		if (!encoder->Verify(operand, reg, Register::ST0, Register::ST7))
		{
			return;
		}
		assert((encoder->OpCode & 7) == 0);
		encoder->OpCode |= static_cast<std::uint32_t>(reg - Register::ST0);
	}

	std::int32_t OprDI::GetRegSize(OpKind opKind)
	{
		if (opKind == OpKind::MemorySegRDI)
		{
			return 8;
		}
		if (opKind == OpKind::MemorySegEDI)
		{
			return 4;
		}
		if (opKind == OpKind::MemorySegDI)
		{
			return 2;
		}
		return 0;
	}

	void OprDI::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		auto regSize = GetRegSize(instruction.GetOpKind(operand));
		if (regSize == 0)
		{
			encoder->SetErrorMessage(std::format("Operand {0:s}: expected OpKind = {1:s}, {2:s} or {3:s}", operand, "MemorySegDI", "MemorySegEDI", "MemorySegRDI"));
			return;
		}
		encoder->SetAddrSize(regSize);
	}

	OpIb::OpIb(OpKind opKind)
	{
		this->opKind = opKind;
	}

	void OpIb::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		switch (encoder->ImmSize)
		{
		case ImmSize::Size1:
			if (!encoder->Verify(operand, OpKind::Immediate8_2nd, instruction.GetOpKind(operand)))
			{
				return;
			}
			encoder->ImmSize = ImmSize::Size1_1;
			encoder->ImmediateHi = instruction.GetImmediate8_2nd();
			break;
		case ImmSize::Size2:
			if (!encoder->Verify(operand, OpKind::Immediate8_2nd, instruction.GetOpKind(operand)))
			{
				return;
			}
			encoder->ImmSize = ImmSize::Size2_1;
			encoder->ImmediateHi = instruction.GetImmediate8_2nd();
			break;
		default:
			auto opImmKind = instruction.GetOpKind(operand);
			if (!encoder->Verify(operand, opKind, opImmKind))
			{
				return;
			}
			encoder->ImmSize = ImmSize::Size1;
			encoder->Immediate = instruction.GetImmediate8();
			break;
		}
	}

	Iced::Intel::OpKind OpIb::GetImmediateOpKind()
	{
		return opKind;
	}

	void OpIw::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (!encoder->Verify(operand, OpKind::Immediate16, instruction.GetOpKind(operand)))
		{
			return;
		}
		encoder->ImmSize = ImmSize::Size2;
		encoder->Immediate = instruction.GetImmediate16();
	}

	Iced::Intel::OpKind OpIw::GetImmediateOpKind()
	{
		return OpKind::Immediate16;
	}

	OpId::OpId(OpKind opKind)
	{
		this->opKind = opKind;
	}

	void OpId::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		auto opImmKind = instruction.GetOpKind(operand);
		if (!encoder->Verify(operand, opKind, opImmKind))
		{
			return;
		}
		encoder->ImmSize = ImmSize::Size4;
		encoder->Immediate = instruction.GetImmediate32();
	}

	Iced::Intel::OpKind OpId::GetImmediateOpKind()
	{
		return opKind;
	}

	void OpIq::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (!encoder->Verify(operand, OpKind::Immediate64, instruction.GetOpKind(operand)))
		{
			return;
		}
		encoder->ImmSize = ImmSize::Size8;
		std::uint64_t imm = instruction.GetImmediate64();
		encoder->Immediate = static_cast<std::uint32_t>(imm);
		encoder->ImmediateHi = static_cast<std::uint32_t>(imm >> 32);
	}

	Iced::Intel::OpKind OpIq::GetImmediateOpKind()
	{
		return OpKind::Immediate64;
	}

	void OpI4::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		auto opImmKind = instruction.GetOpKind(operand);
		if (!encoder->Verify(operand, OpKind::Immediate8, opImmKind))
		{
			return;
		}
		assert(encoder->ImmSize == ImmSize::SizeIbReg);
		assert((encoder->Immediate & 0xF) == 0);
		if (instruction.GetImmediate8() > 0xF)
		{
			encoder->SetErrorMessage(std::format("Operand {0:s}: Immediate value must be 0-15, but value is 0x{1:0>.2X}", operand, instruction.GetImmediate8()));
			return;
		}
		encoder->ImmSize = ImmSize::Size1;
		encoder->Immediate |= instruction.GetImmediate8();
	}

	Iced::Intel::OpKind OpI4::GetImmediateOpKind()
	{
		return OpKind::Immediate8;
	}

	std::int32_t OpX::GetXRegSize(OpKind opKind)
	{
		if (opKind == OpKind::MemorySegRSI)
		{
			return 8;
		}
		if (opKind == OpKind::MemorySegESI)
		{
			return 4;
		}
		if (opKind == OpKind::MemorySegSI)
		{
			return 2;
		}
		return 0;
	}

	std::int32_t OpX::GetYRegSize(OpKind opKind)
	{
		if (opKind == OpKind::MemoryESRDI)
		{
			return 8;
		}
		if (opKind == OpKind::MemoryESEDI)
		{
			return 4;
		}
		if (opKind == OpKind::MemoryESDI)
		{
			return 2;
		}
		return 0;
	}

	void OpX::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		auto regXSize = GetXRegSize(instruction.GetOpKind(operand));
		if (regXSize == 0)
		{
			encoder->SetErrorMessage(std::format("Operand {0:s}: expected OpKind = {1:s}, {2:s} or {3:s}", operand, "MemorySegSI", "MemorySegESI", "MemorySegRSI"));
			return;
		}
		switch (instruction.GetCode())
		{
		case Code::Movsb_m8_m8:
		case Code::Movsw_m16_m16:
		case Code::Movsd_m32_m32:
		case Code::Movsq_m64_m64:
		{
			auto regYSize = GetYRegSize(instruction.GetOp0Kind());
			if (regXSize != regYSize)
			{
				encoder->SetErrorMessage(std::format("Same sized register must be used: reg #1 size = {0:s}, reg #2 size = {1:s}", regYSize * 8, regXSize * 8));
				return;
			}
			break;
		}
		}
		encoder->SetAddrSize(regXSize);
	}

	void OpY::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		auto regYSize = OpX::GetYRegSize(instruction.GetOpKind(operand));
		if (regYSize == 0)
		{
			encoder->SetErrorMessage(std::format("Operand {0:s}: expected OpKind = {1:s}, {2:s} or {3:s}", operand, "MemoryESDI", "MemoryESEDI", "MemoryESRDI"));
			return;
		}
		switch (instruction.GetCode())
		{
		case Code::Cmpsb_m8_m8:
		case Code::Cmpsw_m16_m16:
		case Code::Cmpsd_m32_m32:
		case Code::Cmpsq_m64_m64:
		{
			auto regXSize = OpX::GetXRegSize(instruction.GetOp0Kind());
			if (regXSize != regYSize)
			{
				encoder->SetErrorMessage(std::format("Same sized register must be used: reg #1 size = {0:s}, reg #2 size = {1:s}", regXSize * 8, regYSize * 8));
				return;
			}
			break;
		}
		}
		encoder->SetAddrSize(regYSize);
	}

	void OpMRBX::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (!encoder->Verify(operand, OpKind::Memory, instruction.GetOpKind(operand)))
		{
			return;
		}
		auto baseReg = instruction.GetMemoryBase();
		if (instruction.GetMemoryDisplSize() != 0 || instruction.GetMemoryDisplacement64() != 0 || instruction.GetMemoryIndexScale() != 1 || instruction.GetMemoryIndex() != Register::AL || (baseReg != Register::BX && baseReg != Register::EBX && baseReg != Register::RBX))
		{
			encoder->SetErrorMessage(std::format("Operand {0:s}: Operand must be [bx+al], [ebx+al], or [rbx+al]", operand));
			return;
		}
		std::int32_t regSize;
		if (baseReg == Register::RBX)
		{
			regSize = 8;
		}
		else if (baseReg == Register::EBX)
		{
			regSize = 4;
		}
		else
		{
			assert(baseReg == Register::BX);
			regSize = 2;
		}
		encoder->SetAddrSize(regSize);
	}

	OpJ::OpJ(OpKind opKind, std::int32_t immSize)
	{
		this->opKind = opKind;
		this->immSize = immSize;
	}

	void OpJ::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddBranch(opKind, immSize, instruction, operand);
	}

	Iced::Intel::OpKind OpJ::GetNearBranchOpKind()
	{
		return opKind;
	}

	OpJx::OpJx(std::int32_t immSize)
	{
		this->immSize = immSize;
	}

	void OpJx::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddBranchX(immSize, instruction, operand);
	}

	Iced::Intel::OpKind OpJx::GetNearBranchOpKind()
	{
		// xbegin is special and doesn't mask the target IP. We need to know the code size to return the correct value.
		// Instruction.CreateXbegin() should be used to create the instruction and this method should never be called.
		Debug::Fail("Call Instruction.CreateXbegin()");
		return Op::GetNearBranchOpKind();
	}

	OpJdisp::OpJdisp(std::int32_t displSize)
	{
		this->displSize = displSize;
	}

	void OpJdisp::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddBranchDisp(displSize, instruction, operand);
	}

	Iced::Intel::OpKind OpJdisp::GetNearBranchOpKind()
	{
		return displSize == 2 ? OpKind::NearBranch16 : OpKind::NearBranch32;
	}

	OpA::OpA(std::int32_t size)
	{
		assert(size == 2 || size == 4);
		this->size = size;
	}

	void OpA::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddFarBranch(instruction, operand, size);
	}

	Iced::Intel::OpKind OpA::GetFarBranchOpKind()
	{
		assert(size == 2 || size == 4);
		return size == 2 ? OpKind::FarBranch16 : OpKind::FarBranch32;
	}

	void OpO::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->AddAbsMem(instruction, operand);
	}

	OpImm::OpImm(std::uint8_t value)
	{
		this->value = value;
	}

	void OpImm::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (!encoder->Verify(operand, OpKind::Immediate8, instruction.GetOpKind(operand)))
		{
			return;
		}
		if (instruction.GetImmediate8() != value)
		{
			encoder->SetErrorMessage(std::format("Operand {0:s}: Expected 0x{1:0>.2X}, actual: 0x{2:0>.2X}", operand, value, instruction.GetImmediate8()));
			return;
		}
	}

	Iced::Intel::OpKind OpImm::GetImmediateOpKind()
	{
		return OpKind::Immediate8;
	}

	OpHx::OpHx(Register regLo, Register regHi)
	{
		this->regLo = regLo;
		this->regHi = regHi;
	}

	void OpHx::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (!encoder->Verify(operand, OpKind::Register, instruction.GetOpKind(operand)))
		{
			return;
		}
		auto reg = instruction.GetOpRegister(operand);
		if (!encoder->Verify(operand, reg, regLo, regHi))
		{
			return;
		}
		encoder->EncoderFlags |= static_cast<EncoderFlags>(static_cast<std::uint32_t>(reg - regLo) << static_cast<std::int32_t>(EncoderFlags::VvvvvShift));
	}

	OpVsib::OpVsib(Register regLo, Register regHi)
	{
		vsibIndexRegLo = regLo;
		vsibIndexRegHi = regHi;
	}

	void OpVsib::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		encoder->EncoderFlags |= EncoderFlags::MustUseSib;
		encoder->AddRegOrMem(instruction, operand, Register::None, Register::None, vsibIndexRegLo, vsibIndexRegHi, true, false);
	}

	OpIsX::OpIsX(Register regLo, Register regHi)
	{
		this->regLo = regLo;
		this->regHi = regHi;
	}

	void OpIsX::Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand)
	{
		if (!encoder->Verify(operand, OpKind::Register, instruction.GetOpKind(operand)))
		{
			return;
		}
		auto reg = instruction.GetOpRegister(operand);
		if (!encoder->Verify(operand, reg, regLo, regHi))
		{
			return;
		}
		encoder->ImmSize = ImmSize::SizeIbReg;
		encoder->Immediate = static_cast<std::uint32_t>(reg - regLo) << 4;
	}
}