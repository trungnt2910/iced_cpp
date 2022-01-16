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

#include "OpTables.g.h"

namespace Iced::Intel::EncoderInternal
{

	std::vector<Op*> OpHandlerData::LegacyOps =
	{
		new OpA(2),
		new OpA(4),
		new OpO(),
		new OpModRM_rm_mem_only(false),
		new OpModRM_rm_mem_only(false),
		new OpModRM_rm_mem_only(false),
		new OpModRM_rm(Register::AL, Register::R15L),
		new OpModRM_rm(Register::AX, Register::R15W),
		new OpModRM_rm(Register::EAX, Register::R15D),
		new OpModRM_rm(Register::EAX, Register::R15D),
		new OpModRM_rm(Register::RAX, Register::R15),
		new OpModRM_rm(Register::RAX, Register::R15),
		new OpModRM_rm(Register::MM0, Register::MM7),
		new OpModRM_rm(Register::XMM0, Register::XMM15),
		new OpModRM_rm(Register::BND0, Register::BND3),
		new OpModRM_reg(Register::AL, Register::R15L),
		new OpRegEmbed8(Register::AL, Register::R15L),
		new OpModRM_reg(Register::AX, Register::R15W),
		new OpModRM_reg_mem(Register::AX, Register::R15W),
		new OpModRM_rm_reg_only(Register::AX, Register::R15W),
		new OpRegEmbed8(Register::AX, Register::R15W),
		new OpModRM_reg(Register::EAX, Register::R15D),
		new OpModRM_reg_mem(Register::EAX, Register::R15D),
		new OpModRM_rm_reg_only(Register::EAX, Register::R15D),
		new OpRegEmbed8(Register::EAX, Register::R15D),
		new OpModRM_reg(Register::RAX, Register::R15),
		new OpModRM_reg_mem(Register::RAX, Register::R15),
		new OpModRM_rm_reg_only(Register::RAX, Register::R15),
		new OpRegEmbed8(Register::RAX, Register::R15),
		new OpModRM_reg(Register::ES, Register::GS),
		new OpModRM_reg(Register::MM0, Register::MM7),
		new OpModRM_rm_reg_only(Register::MM0, Register::MM7),
		new OpModRM_reg(Register::XMM0, Register::XMM15),
		new OpModRM_rm_reg_only(Register::XMM0, Register::XMM15),
		new OpModRM_regF0(Register::CR0, Register::CR15),
		new OpModRM_reg(Register::DR0, Register::DR15),
		new OpModRM_reg(Register::TR0, Register::TR7),
		new OpModRM_reg(Register::BND0, Register::BND3),
		new OpReg(Register::ES),
		new OpReg(Register::CS),
		new OpReg(Register::SS),
		new OpReg(Register::DS),
		new OpReg(Register::FS),
		new OpReg(Register::GS),
		new OpReg(Register::AL),
		new OpReg(Register::CL),
		new OpReg(Register::AX),
		new OpReg(Register::DX),
		new OpReg(Register::EAX),
		new OpReg(Register::RAX),
		new OpReg(Register::ST0),
		new OpRegSTi(),
		new OpIb(OpKind::Immediate8),
		new OpImm(1),
		new OpIb(OpKind::Immediate8to16),
		new OpIb(OpKind::Immediate8to32),
		new OpIb(OpKind::Immediate8to64),
		new OpIw(),
		new OpId(OpKind::Immediate32),
		new OpId(OpKind::Immediate32to64),
		new OpIq(),
		new OpX(),
		new OpY(),
		new OprDI(),
		new OpMRBX(),
		new OpJ(OpKind::NearBranch16, 1),
		new OpJ(OpKind::NearBranch32, 1),
		new OpJ(OpKind::NearBranch64, 1),
		new OpJ(OpKind::NearBranch16, 2),
		new OpJ(OpKind::NearBranch32, 4),
		new OpJ(OpKind::NearBranch64, 4),
		new OpJx(2),
		new OpJx(4),
		new OpJdisp(2),
		new OpJdisp(4)
	};
	std::vector<Op*> OpHandlerData::VexOps =
	{
		new OpModRM_rm_mem_only(false),
		new OpVsib(Register::XMM0, Register::XMM15),
		new OpVsib(Register::XMM0, Register::XMM15),
		new OpVsib(Register::YMM0, Register::YMM15),
		new OpVsib(Register::YMM0, Register::YMM15),
		new OpModRM_rm(Register::EAX, Register::R15D),
		new OpModRM_rm(Register::RAX, Register::R15),
		new OpModRM_rm(Register::XMM0, Register::XMM15),
		new OpModRM_rm(Register::YMM0, Register::YMM15),
		new OpModRM_rm(Register::K0, Register::K7),
		new OpModRM_reg(Register::EAX, Register::R15D),
		new OpModRM_rm_reg_only(Register::EAX, Register::R15D),
		new OpHx(Register::EAX, Register::R15D),
		new OpModRM_reg(Register::RAX, Register::R15),
		new OpModRM_rm_reg_only(Register::RAX, Register::R15),
		new OpHx(Register::RAX, Register::R15),
		new OpModRM_reg(Register::K0, Register::K7),
		new OpModRM_rm_reg_only(Register::K0, Register::K7),
		new OpHx(Register::K0, Register::K7),
		new OpModRM_reg(Register::XMM0, Register::XMM15),
		new OpModRM_rm_reg_only(Register::XMM0, Register::XMM15),
		new OpHx(Register::XMM0, Register::XMM15),
		new OpIsX(Register::XMM0, Register::XMM15),
		new OpIsX(Register::XMM0, Register::XMM15),
		new OpModRM_reg(Register::YMM0, Register::YMM15),
		new OpModRM_rm_reg_only(Register::YMM0, Register::YMM15),
		new OpHx(Register::YMM0, Register::YMM15),
		new OpIsX(Register::YMM0, Register::YMM15),
		new OpIsX(Register::YMM0, Register::YMM15),
		new OpI4(),
		new OpIb(OpKind::Immediate8),
		new OprDI(),
		new OpJ(OpKind::NearBranch64, 1),
		new OpJ(OpKind::NearBranch64, 4),
		new OpModRM_rm_mem_only(true),
		new OpModRM_reg(Register::TMM0, Register::TMM7),
		new OpModRM_rm_reg_only(Register::TMM0, Register::TMM7),
		new OpHx(Register::TMM0, Register::TMM7)
	};
	std::vector<Op*> OpHandlerData::XopOps =
	{
		new OpModRM_rm(Register::EAX, Register::R15D),
		new OpModRM_rm(Register::RAX, Register::R15),
		new OpModRM_rm(Register::XMM0, Register::XMM15),
		new OpModRM_rm(Register::YMM0, Register::YMM15),
		new OpModRM_reg(Register::EAX, Register::R15D),
		new OpModRM_rm_reg_only(Register::EAX, Register::R15D),
		new OpHx(Register::EAX, Register::R15D),
		new OpModRM_reg(Register::RAX, Register::R15),
		new OpModRM_rm_reg_only(Register::RAX, Register::R15),
		new OpHx(Register::RAX, Register::R15),
		new OpModRM_reg(Register::XMM0, Register::XMM15),
		new OpHx(Register::XMM0, Register::XMM15),
		new OpIsX(Register::XMM0, Register::XMM15),
		new OpModRM_reg(Register::YMM0, Register::YMM15),
		new OpHx(Register::YMM0, Register::YMM15),
		new OpIsX(Register::YMM0, Register::YMM15),
		new OpIb(OpKind::Immediate8),
		new OpId(OpKind::Immediate32)
	};
	std::vector<Op*> OpHandlerData::EvexOps =
	{
		new OpModRM_rm_mem_only(false),
		new OpVsib(Register::XMM0, Register::XMM31),
		new OpVsib(Register::XMM0, Register::XMM31),
		new OpVsib(Register::YMM0, Register::YMM31),
		new OpVsib(Register::YMM0, Register::YMM31),
		new OpVsib(Register::ZMM0, Register::ZMM31),
		new OpVsib(Register::ZMM0, Register::ZMM31),
		new OpModRM_rm(Register::EAX, Register::R15D),
		new OpModRM_rm(Register::RAX, Register::R15),
		new OpModRM_rm(Register::XMM0, Register::XMM31),
		new OpModRM_rm(Register::YMM0, Register::YMM31),
		new OpModRM_rm(Register::ZMM0, Register::ZMM31),
		new OpModRM_reg(Register::EAX, Register::R15D),
		new OpModRM_rm_reg_only(Register::EAX, Register::R15D),
		new OpModRM_reg(Register::RAX, Register::R15),
		new OpModRM_rm_reg_only(Register::RAX, Register::R15),
		new OpModRM_reg(Register::K0, Register::K7),
		new OpModRM_reg(Register::K0, Register::K7),
		new OpModRM_rm_reg_only(Register::K0, Register::K7),
		new OpModRM_reg(Register::XMM0, Register::XMM31),
		new OpModRM_rm_reg_only(Register::XMM0, Register::XMM31),
		new OpHx(Register::XMM0, Register::XMM31),
		new OpHx(Register::XMM0, Register::XMM31),
		new OpModRM_reg(Register::YMM0, Register::YMM31),
		new OpModRM_rm_reg_only(Register::YMM0, Register::YMM31),
		new OpHx(Register::YMM0, Register::YMM31),
		new OpModRM_reg(Register::ZMM0, Register::ZMM31),
		new OpModRM_rm_reg_only(Register::ZMM0, Register::ZMM31),
		new OpHx(Register::ZMM0, Register::ZMM31),
		new OpHx(Register::ZMM0, Register::ZMM31),
		new OpIb(OpKind::Immediate8)
	};
	std::vector<Op*> OpHandlerData::MvexOps =
	{
		new OpModRM_rm_mem_only(false),
		new OpVsib(Register::ZMM0, Register::ZMM31),
		new OpModRM_rm(Register::ZMM0, Register::ZMM31),
		new OpModRM_reg(Register::K0, Register::K7),
		new OpHx(Register::K0, Register::K7),
		new OpModRM_reg(Register::ZMM0, Register::ZMM31),
		new OpHx(Register::ZMM0, Register::ZMM31),
		new OpIb(OpKind::Immediate8)
	};
}
