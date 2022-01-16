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

#pragma once

#include "../OpAccess.g.h"
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::InstructionInfoInternal
{
	class OpAccesses final
	{
		// GENERATOR-BEGIN: OpAccesses
		// ⚠️This was generated by GENERATOR!🦹‍♂️
	public:
		static std::vector<OpAccess> Op1;
		static std::vector<OpAccess> Op2;
		// GENERATOR-END: OpAccesses
	};
	// GENERATOR-BEGIN: InstrInfoConstants
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	class InstrInfoConstants final
	{
	public:
		static constexpr std::int32_t OpInfo0_Count = 13;
		static constexpr std::int32_t OpInfo1_Count = 7;
		static constexpr std::int32_t OpInfo2_Count = 3;
		static constexpr std::int32_t OpInfo3_Count = 2;
		static constexpr std::int32_t OpInfo4_Count = 2;
		static constexpr std::int32_t RflagsInfo_Count = 79;
		static constexpr std::int32_t DefaultUsedRegisterCollCapacity = 10;
		static constexpr std::int32_t DefaultUsedMemoryCollCapacity = 8;
	};
	// GENERATOR-END: InstrInfoConstants
	// GENERATOR-BEGIN: InfoFlags1
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	enum class InfoFlags1 : uint
	{
		OpInfo0Shift = 0x00000000,
		OpInfo0Mask = 0x0000000F,
		OpInfo1Shift = 0x00000004,
		OpInfo1Mask = 0x00000007,
		OpInfo2Shift = 0x00000007,
		OpInfo2Mask = 0x00000003,
		OpInfo3Shift = 0x00000009,
		OpInfo3Mask = 0x00000001,
		OpInfo4Shift = 0x0000000A,
		OpInfo4Mask = 0x00000001,
		RflagsInfoShift = 0x0000000D,
		RflagsInfoMask = 0x0000007F,
		ImpliedAccessShift = 0x00000014,
		ImpliedAccessMask = 0x000000FF,
		IgnoresIndexVA = 0x20000000,
		OpMaskReadWrite = 0x40000000,
		IgnoresSegment = 0x80000000
	};
	DEFINE_FLAGS(InfoFlags1)
		DEFINE_COMP(InfoFlags1)
		DEFINE_ARITH(InfoFlags1)

		// GENERATOR-END: InfoFlags1
		// GENERATOR-BEGIN: InfoFlags2
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class InfoFlags2 : uint
	{
		EncodingShift = 0x00000000,
		EncodingMask = 0x00000007,
		SaveRestore = 0x00020000,
		StackInstruction = 0x00040000,
		Privileged = 0x00080000,
		FlowControlShift = 0x00000014,
		FlowControlMask = 0x0000000F,
		CpuidFeatureInternalShift = 0x00000018,
		CpuidFeatureInternalMask = 0x000000FF
	};
	DEFINE_FLAGS(InfoFlags2)
		DEFINE_COMP(InfoFlags2)
		DEFINE_ARITH(InfoFlags2)

		// GENERATOR-END: InfoFlags2
		// GENERATOR-BEGIN: OpInfo0
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class OpInfo0
	{
		None,
		CondWrite,
		CondWrite32_ReadWrite64,
		NoMemAccess,
		Read,
		ReadCondWrite,
		ReadWrite,
		Write,
		WriteVmm,
		ReadWriteVmm,
		WriteForce,
		WriteMem_ReadWriteReg,
		WriteForceP1
	};

	DEFINE_COMP(OpInfo0)
		DEFINE_ARITH(OpInfo0)

		// GENERATOR-END: OpInfo0
		// GENERATOR-BEGIN: OpInfo1
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class OpInfo1
	{
		None,
		CondRead,
		NoMemAccess,
		Read,
		ReadP3,
		ReadWrite,
		Write
	};

	DEFINE_COMP(OpInfo1)
		DEFINE_ARITH(OpInfo1)

		// GENERATOR-END: OpInfo1
		// GENERATOR-BEGIN: OpInfo2
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class OpInfo2
	{
		None,
		Read,
		ReadWrite
	};

	DEFINE_COMP(OpInfo2)
		DEFINE_ARITH(OpInfo2)

		// GENERATOR-END: OpInfo2
		// GENERATOR-BEGIN: OpInfo3
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class OpInfo3
	{
		None,
		Read
	};

	DEFINE_COMP(OpInfo3)
		DEFINE_ARITH(OpInfo3)

		// GENERATOR-END: OpInfo3
		// GENERATOR-BEGIN: OpInfo4
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class OpInfo4
	{
		None,
		Read
	};

	DEFINE_COMP(OpInfo4)
		DEFINE_ARITH(OpInfo4)

		// GENERATOR-END: OpInfo4
		// GENERATOR-BEGIN: ImpliedAccess
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class ImpliedAccess
	{
		None,
		Shift_Ib_MASK1FMOD9,
		Shift_Ib_MASK1FMOD11,
		Shift_Ib_MASK1F,
		Shift_Ib_MASK3F,
		Clear_rflags,
		t_push1x2,
		t_push1x4,
		t_pop1x2,
		t_pop1x4,
		t_RWal,
		t_RWax,
		t_push1x8,
		t_pop1x8,
		t_pusha2,
		t_pusha4,
		t_popa2,
		t_popa4,
		t_arpl,
		t_ins,
		t_outs,
		t_lea,
		t_gpr16,
		t_poprm2,
		t_poprm4,
		t_poprm8,
		t_Ral_Wah,
		t_Rax_Weax,
		t_RWeax,
		t_Rax_Wdx,
		t_Reax_Wedx,
		t_Rrax_Wrdx,
		t_push2x2,
		t_push2x4,
		t_Rah,
		t_Wah,
		t_movs,
		t_cmps,
		t_stos,
		t_lods,
		t_scas,
		t_Wes,
		t_Wds,
		t_CWeax,
		t_enter2,
		t_enter4,
		t_enter8,
		t_leave2,
		t_leave4,
		t_leave8,
		t_pop2x2,
		t_pop2x4,
		t_pop2x8,
		b64_t_Wss_pop5x2_f_pop3x2,
		b64_t_Wss_pop5x4_f_pop3x4,
		t_Wss_pop5x8,
		t_Ral_Wax,
		t_Wal,
		t_RWst0,
		t_Rst0,
		t_Rst0_RWst1,
		t_RCWst0,
		t_Rst1_RWst0,
		t_Rst0_Rst1,
		t_Wst0TOst7_Wmm0TOmm7,
		t_Rst0TOst7_Rmm0TOmm7,
		t_RWcx,
		t_RWecx,
		t_RWrcx,
		t_Rcx,
		t_Recx,
		t_Rrcx,
		t_Wdx_RWax,
		t_Wedx_RWeax,
		t_Wrdx_RWrax,
		t_RWax_RWdx,
		t_RWeax_RWedx,
		t_RWrax_RWrdx,
		t_push2x8,
		t_Rcr0,
		t_RWcr0,
		t_gpr16_RWcr0,
		t_RCWeax_b64_t_CRrcx_CRrdx_CRrbx_CWrcx_CWrdx_CWrbx_f_CRecx_CRedx_CRebx_CRds_CWecx_CWedx_CWebx,
		t_CWecx_CWedx_CWebx_RWeax_b64_t_CRrcx_CRrdx_CRrbx_f_CRecx_CRedx_CRebx_CRds,
		t_Rax_Recx_Redx_Rseg,
		t_Reax_Recx_Redx_Rseg,
		t_Recx_Redx_Rrax_Rseg,
		t_Reax_Recx,
		t_Recx_Weax_Wedx,
		t_Reax_Recx_Redx,
		t_Rax,
		t_Reax,
		t_Rrax,
		t_Rax_Wfs_Wgs,
		t_Reax_Wfs_Wgs,
		t_Rrax_Wfs_Wgs,
		t_Rax_Rfs_Rgs,
		t_Reax_Rfs_Rgs,
		t_Rrax_Rfs_Rgs,
		t_Reax_Wcr0_Wdr6_Wdr7_WesTOgs_Wcr2TOcr4_Wdr0TOdr3_b64_t_WraxTOr15_f_WeaxTOedi,
		t_Rax_Recx,
		t_Recx_Rrax,
		t_Weax_Wecx_Wedx,
		t_Reax_Recx_CRebx,
		t_Rax_Rseg,
		t_Reax_Rseg,
		t_Rrax_Rseg,
		t_Wecx_b64_t_Wr11,
		t_Redi_Res,
		t_Recx_Wcs_Wss_b64_t_Rr11d,
		t_Rr11d_Rrcx_Wcs_Wss,
		t_Weax_Wedx,
		t_Wesp,
		t_Recx_Redx_Wesp_Wcs_Wss,
		t_Rrcx_Rrdx_Wrsp_Wcs_Wss,
		t_zrrm,
		t_zrrrm,
		b64_t_RWxmm0TOxmm15_f_RWxmm0TOxmm7,
		b64_t_Wzmm0TOzmm15_f_Wzmm0TOzmm7,
		t_CRecx_Wecx_Wedx_Webx_RWeax,
		t_CRmem_CRsi_CReax_CRes_CWeax_CWedx_RCWecx,
		t_CRmem_CReax_CResi_CRes_CWeax_CWedx_RCWecx,
		t_CRmem_CReax_CRrsi_CRes_CWeax_CWedx_RCWrcx,
		t_CRmem_CRmem_CWmem_CRsi_CRdi_CRes_CWsi_RCWax_RCWcx,
		t_CRmem_CRmem_CWmem_CResi_CRedi_CRes_CWesi_RCWeax_RCWecx,
		t_CRmem_CRmem_CWmem_CRrsi_CRrdi_CRes_CWrsi_RCWrax_RCWrcx,
		t_Rcl_Rax,
		t_Rcl_Reax,
		t_xstore2,
		t_xstore4,
		t_xstore8,
		t_CRmem_CRmem_CRmem_CWmem_CRdx_CRbx_CRsi_CRdi_CRes_CWsi_CWdi_RCWcx,
		t_CRmem_CRmem_CRmem_CWmem_CRedx_CRebx_CResi_CRedi_CRes_CWesi_CWedi_RCWecx,
		t_CRmem_CRmem_CRmem_CWmem_CRrdx_CRrbx_CRrsi_CRrdi_CRes_CWrsi_CWrdi_RCWrcx,
		t_CRmem_CRmem_CRmem_CRmem_CWmem_CWmem_CRax_CRdx_CRbx_CRsi_CRdi_CRes_CWsi_CWdi_RCWcx,
		t_CRmem_CRmem_CRmem_CRmem_CWmem_CWmem_CReax_CRedx_CRebx_CResi_CRedi_CRes_CWesi_CWedi_RCWecx,
		t_CRmem_CRmem_CRmem_CRmem_CWmem_CWmem_CRrax_CRrdx_CRrbx_CRrsi_CRrdi_CRes_CWrsi_CWrdi_RCWrcx,
		t_RCWal,
		t_RCWax,
		t_RCWeax,
		t_Reax_Redx,
		t_gpr8,
		t_gpr32_Reax_Redx,
		t_Rmem_Rseg,
		t_RCWrax,
		t_Wss,
		t_Wfs,
		t_Wgs,
		t_CRecx_CRebx_RCWeax_RCWedx,
		t_CRrcx_CRrbx_RCWrax_RCWrdx,
		t_Wmem_RarDI_Rseg,
		t_Rxmm0,
		t_Redx,
		t_Rrdx,
		t_Wmem_Res,
		t_Reax_Redx_Wxmm0,
		t_Rrax_Rrdx_Wxmm0,
		t_Reax_Redx_Wecx,
		t_Rrax_Rrdx_Wecx,
		t_Wxmm0,
		t_Wecx,
		t_Rmem_Rds,
		t_Rrcx_Rrdx_RWrax,
		t_Rmem_Rrcx_Rseg_RWrax,
		t_RWrax,
		t_Rax_Recx_Redx_Weax,
		t_Recx_Redx_RWeax,
		t_Recx_Redx_RWrax,
		t_Rax_Recx_Redx,
		t_Recx_Redx_Rrax,
		t_Wtmm0TOtmm7,
		t_Reax_Rebx,
		t_Rebx_Weax,
		t_emmiW,
		t_emmiRW,
		t_emmiR,
		t_CRrcx_CRrdx_CRr8_CRr9_RWrax,
		t_RWxmm0TOxmm7,
		t_Reax_Rxmm0,
		t_Wxmm1_Wxmm2_RWxmm0_Wxmm4TOxmm6,
		t_RWxmm0_RWxmm1_Wxmm2TOxmm6,
		t_pop3x8,
		t_CRmem_CRmem_CWmem_CRbx_CRsi_CRdi_CRes_CWsi_RCWax_RCWcx,
		t_CRmem_CRmem_CWmem_CRebx_CResi_CRedi_CRes_CWesi_RCWeax_RCWecx,
		t_CRmem_CRmem_CWmem_CRrbx_CRrsi_CRrdi_CRes_CWrsi_RCWrax_RCWrcx,
		t_CRmem_CRmem_CRmem_CWmem_CRax_CRdx_CRbx_CRsi_CRdi_CRes_CWsi_CWdi_RCWcx,
		t_CRmem_CRmem_CRmem_CWmem_CReax_CRedx_CRebx_CResi_CRedi_CRes_CWesi_CWedi_RCWecx,
		t_CRmem_CRmem_CRmem_CWmem_CRrax_CRrdx_CRrbx_CRrsi_CRrdi_CRes_CWrsi_CWrdi_RCWrcx,
		t_gpr16_Wgs,
		t_Wrsp_Wcs_Wss_pop5x8,
		t_Wrsp_pop5x8,
		t_Reax_Recx_Wedx_Webx,
		t_Reax_Recx_Redx_CRebx_CWedx_CWebx,
		t_memdisplm64
	};

	DEFINE_COMP(ImpliedAccess)
		DEFINE_ARITH(ImpliedAccess)

		// GENERATOR-END: ImpliedAccess
		// GENERATOR-BEGIN: RflagsInfo
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		enum class RflagsInfo
	{
		None,
		C_0123,
		C_1_U_023,
		C_A,
		C_acopsz,
		C_acopszidA,
		C_acos_S_pz,
		C_c,
		C_cos_S_pz_U_a,
		C_d,
		C_i,
		C_u,
		R_0123_C_0123,
		R_0123_U_0123,
		R_a_W_ac_U_opsz,
		R_ac_W_acpsz_U_o,
		R_acopszid,
		R_acopszidA,
		R_acopszidA_W_acopszidA,
		R_acpsz,
		R_c,
		R_c_C_1_U_023,
		R_c_W_acopsz,
		R_c_W_c,
		R_c_W_c_U_o,
		R_c_W_co,
		R_cz,
		R_cz_C_1_U_023,
		R_d,
		R_d_W_acopsz,
		R_o,
		R_o_W_o,
		R_os,
		R_osz,
		R_p,
		R_p_C_1_U_023,
		R_s,
		R_u_W_c_C_aopsz,
		R_z,
		R_z_C_1_U_023,
		S_A,
		S_c,
		S_d,
		S_i,
		S_u,
		U_0123,
		U_acopsz,
		W_0123,
		W_023_C_1,
		W_12_U_03,
		W_1_U_023,
		W_acopsz,
		W_acopszdA_S_u,
		W_acopszid,
		W_acopszidA,
		W_acpsz,
		W_aopsz,
		W_c,
		W_c_C_aopsz,
		W_c_U_aops,
		W_c_U_o,
		W_co,
		W_co_U_apsz,
		W_copsz_U_a,
		W_cosz_C_ap,
		W_cpsz_U_ao,
		W_cpz_C_aos,
		W_cpz_C_aos1,
		W_cs_C_oz_U_ap,
		W_csz_C_o_U_ap,
		W_cz_C_aops,
		W_cz_U_aops,
		W_psz_C_co_U_a,
		W_psz_U_aco,
		W_sz_C_co_U_ap,
		W_z,
		W_z_C_acops,
		W_z_C_co_U_aps,
		W_z_U_acops
	};

	DEFINE_COMP(RflagsInfo)
		DEFINE_ARITH(RflagsInfo)

		// GENERATOR-END: RflagsInfo
}