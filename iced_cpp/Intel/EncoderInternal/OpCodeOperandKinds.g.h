// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once
#if defined(ENCODER) && defined(OPCODE_INFO)
#include <array>

#include "../OpCodeOperandKind.g.h"

// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel::EncoderInternal
{
	class OpCodeOperandKinds final
	{
	public:
		static constexpr std::array LegacyOpKinds = std::to_array<std::uint8_t> ({ static_cast<std::uint8_t>(OpCodeOperandKind::None), static_cast<std::uint8_t>(OpCodeOperandKind::farbr2_2), static_cast<std::uint8_t>(OpCodeOperandKind::farbr4_2), static_cast<std::uint8_t>(OpCodeOperandKind::mem_offs), static_cast<std::uint8_t>(OpCodeOperandKind::mem), static_cast<std::uint8_t>(OpCodeOperandKind::mem_mpx), static_cast<std::uint8_t>(OpCodeOperandKind::mem_mib), static_cast<std::uint8_t>(OpCodeOperandKind::r8_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r16_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r32_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r32_or_mem_mpx), static_cast<std::uint8_t>(OpCodeOperandKind::r64_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r64_or_mem_mpx), static_cast<std::uint8_t>(OpCodeOperandKind::mm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::bnd_or_mem_mpx), static_cast<std::uint8_t>(OpCodeOperandKind::r8_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r8_opcode), static_cast<std::uint8_t>(OpCodeOperandKind::r16_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r16_reg_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r16_rm), static_cast<std::uint8_t>(OpCodeOperandKind::r16_opcode), static_cast<std::uint8_t>(OpCodeOperandKind::r32_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r32_reg_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r32_rm), static_cast<std::uint8_t>(OpCodeOperandKind::r32_opcode), static_cast<std::uint8_t>(OpCodeOperandKind::r64_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r64_reg_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r64_rm), static_cast<std::uint8_t>(OpCodeOperandKind::r64_opcode), static_cast<std::uint8_t>(OpCodeOperandKind::seg_reg), static_cast<std::uint8_t>(OpCodeOperandKind::mm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::mm_rm), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_rm), static_cast<std::uint8_t>(OpCodeOperandKind::cr_reg), static_cast<std::uint8_t>(OpCodeOperandKind::dr_reg), static_cast<std::uint8_t>(OpCodeOperandKind::tr_reg), static_cast<std::uint8_t>(OpCodeOperandKind::bnd_reg), static_cast<std::uint8_t>(OpCodeOperandKind::es), static_cast<std::uint8_t>(OpCodeOperandKind::cs), static_cast<std::uint8_t>(OpCodeOperandKind::ss), static_cast<std::uint8_t>(OpCodeOperandKind::ds), static_cast<std::uint8_t>(OpCodeOperandKind::fs), static_cast<std::uint8_t>(OpCodeOperandKind::gs), static_cast<std::uint8_t>(OpCodeOperandKind::al), static_cast<std::uint8_t>(OpCodeOperandKind::cl), static_cast<std::uint8_t>(OpCodeOperandKind::ax), static_cast<std::uint8_t>(OpCodeOperandKind::dx), static_cast<std::uint8_t>(OpCodeOperandKind::eax), static_cast<std::uint8_t>(OpCodeOperandKind::rax), static_cast<std::uint8_t>(OpCodeOperandKind::st0), static_cast<std::uint8_t>(OpCodeOperandKind::sti_opcode), static_cast<std::uint8_t>(OpCodeOperandKind::imm8), static_cast<std::uint8_t>(OpCodeOperandKind::imm8_const_1), static_cast<std::uint8_t>(OpCodeOperandKind::imm8sex16), static_cast<std::uint8_t>(OpCodeOperandKind::imm8sex32), static_cast<std::uint8_t>(OpCodeOperandKind::imm8sex64), static_cast<std::uint8_t>(OpCodeOperandKind::imm16), static_cast<std::uint8_t>(OpCodeOperandKind::imm32), static_cast<std::uint8_t>(OpCodeOperandKind::imm32sex64), static_cast<std::uint8_t>(OpCodeOperandKind::imm64), static_cast<std::uint8_t>(OpCodeOperandKind::seg_rSI), static_cast<std::uint8_t>(OpCodeOperandKind::es_rDI), static_cast<std::uint8_t>(OpCodeOperandKind::seg_rDI), static_cast<std::uint8_t>(OpCodeOperandKind::seg_rBX_al), static_cast<std::uint8_t>(OpCodeOperandKind::br16_1), static_cast<std::uint8_t>(OpCodeOperandKind::br32_1), static_cast<std::uint8_t>(OpCodeOperandKind::br64_1), static_cast<std::uint8_t>(OpCodeOperandKind::br16_2), static_cast<std::uint8_t>(OpCodeOperandKind::br32_4), static_cast<std::uint8_t>(OpCodeOperandKind::br64_4), static_cast<std::uint8_t>(OpCodeOperandKind::xbegin_2), static_cast<std::uint8_t>(OpCodeOperandKind::xbegin_4), static_cast<std::uint8_t>(OpCodeOperandKind::brdisp_2), static_cast<std::uint8_t>(OpCodeOperandKind::brdisp_4) });
		static constexpr std::array VexOpKinds = std::to_array<std::uint8_t> ({ static_cast<std::uint8_t>(OpCodeOperandKind::None), static_cast<std::uint8_t>(OpCodeOperandKind::mem), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib32x), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib64x), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib32y), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib64y), static_cast<std::uint8_t>(OpCodeOperandKind::r32_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r64_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::k_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r32_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r32_rm), static_cast<std::uint8_t>(OpCodeOperandKind::r32_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::r64_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r64_rm), static_cast<std::uint8_t>(OpCodeOperandKind::r64_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::k_reg), static_cast<std::uint8_t>(OpCodeOperandKind::k_rm), static_cast<std::uint8_t>(OpCodeOperandKind::k_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_rm), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_is4), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_is5), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_rm), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_is4), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_is5), static_cast<std::uint8_t>(OpCodeOperandKind::imm4_m2z), static_cast<std::uint8_t>(OpCodeOperandKind::imm8), static_cast<std::uint8_t>(OpCodeOperandKind::seg_rDI), static_cast<std::uint8_t>(OpCodeOperandKind::br64_1), static_cast<std::uint8_t>(OpCodeOperandKind::br64_4), static_cast<std::uint8_t>(OpCodeOperandKind::sibmem), static_cast<std::uint8_t>(OpCodeOperandKind::tmm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::tmm_rm), static_cast<std::uint8_t>(OpCodeOperandKind::tmm_vvvv) });
		static constexpr std::array XopOpKinds = std::to_array<std::uint8_t> ({ static_cast<std::uint8_t>(OpCodeOperandKind::None), static_cast<std::uint8_t>(OpCodeOperandKind::r32_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r64_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r32_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r32_rm), static_cast<std::uint8_t>(OpCodeOperandKind::r32_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::r64_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r64_rm), static_cast<std::uint8_t>(OpCodeOperandKind::r64_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_is4), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_is4), static_cast<std::uint8_t>(OpCodeOperandKind::imm8), static_cast<std::uint8_t>(OpCodeOperandKind::imm32) });
		static constexpr std::array EvexOpKinds = std::to_array<std::uint8_t> ({ static_cast<std::uint8_t>(OpCodeOperandKind::None), static_cast<std::uint8_t>(OpCodeOperandKind::mem), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib32x), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib64x), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib32y), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib64y), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib32z), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib64z), static_cast<std::uint8_t>(OpCodeOperandKind::r32_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r64_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::zmm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::r32_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r32_rm), static_cast<std::uint8_t>(OpCodeOperandKind::r64_reg), static_cast<std::uint8_t>(OpCodeOperandKind::r64_rm), static_cast<std::uint8_t>(OpCodeOperandKind::k_reg), static_cast<std::uint8_t>(OpCodeOperandKind::kp1_reg), static_cast<std::uint8_t>(OpCodeOperandKind::k_rm), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_rm), static_cast<std::uint8_t>(OpCodeOperandKind::xmm_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::xmmp3_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_rm), static_cast<std::uint8_t>(OpCodeOperandKind::ymm_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::zmm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::zmm_rm), static_cast<std::uint8_t>(OpCodeOperandKind::zmm_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::zmmp3_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::imm8) });
		static constexpr std::array MvexOpKinds = std::to_array<std::uint8_t> ({ static_cast<std::uint8_t>(OpCodeOperandKind::None), static_cast<std::uint8_t>(OpCodeOperandKind::mem), static_cast<std::uint8_t>(OpCodeOperandKind::mem_vsib32z), static_cast<std::uint8_t>(OpCodeOperandKind::zmm_or_mem), static_cast<std::uint8_t>(OpCodeOperandKind::k_reg), static_cast<std::uint8_t>(OpCodeOperandKind::k_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::zmm_reg), static_cast<std::uint8_t>(OpCodeOperandKind::zmm_vvvv), static_cast<std::uint8_t>(OpCodeOperandKind::imm8) });
	};
}
#endif