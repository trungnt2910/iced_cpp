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

#include "EncoderInternal/Enums.h"
#include "EncoderInternal/OpCodeInfosEnums.h"
#include "Code.g.h"
#include "Mnemonic.g.h"
#include "EncodingKind.g.h"
#include "TupleType.g.h"
#include "MvexEHBit.g.h"
#include "MvexTupleTypeLutKind.g.h"
#include "MvexConvFn.g.h"
#include "MemorySize.g.h"
#include "DecoderOptions.g.h"
#include "OpCodeTableKind.g.h"
#include "MandatoryPrefix.g.h"
#include "OpCodeOperandKind.g.h"
#include <string>
#include <vector>
#include <limits>
#include <csharp/exceptionhelper.h>
#include <cassert>
#include <csharp/stringbuilder.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::EncoderInternal;
namespace Iced::Intel
{
	/// <summary>
	/// Opcode info
	/// </summary>
	class OpCodeInfo final
	{
		/* readonly */
	private:
		std::string toOpCodeStringValue;
		/* readonly */
		std::string toInstructionStringValue;
		/* readonly */
		EncFlags2 encFlags2 = static_cast<EncFlags2>(0);
		/* readonly */
		EncFlags3 encFlags3 = static_cast<EncFlags3>(0);
		/* readonly */
		OpCodeInfoFlags1 opcFlags1 = static_cast<OpCodeInfoFlags1>(0);
		/* readonly */
		OpCodeInfoFlags2 opcFlags2 = static_cast<OpCodeInfoFlags2>(0);
		/* readonly */
		std::uint16_t code = 0;
		/* readonly */
		std::uint8_t encoding = 0;
		/* readonly */
		std::uint8_t operandSize = 0;
		/* readonly */
		std::uint8_t addressSize = 0;
		/* readonly */
		std::uint8_t l = 0;
		/* readonly */
		std::uint8_t tupleType = 0;
		/* readonly */
		std::uint8_t table = 0;
		/* readonly */
		std::uint8_t mandatoryPrefix = 0;
		/* readonly */
		std::int8_t groupIndex = 0;
		/* readonly */
		std::int8_t rmGroupIndex = 0;
		/* readonly */
		std::uint8_t op0Kind = 0;
		/* readonly */
		std::uint8_t op1Kind = 0;
		/* readonly */
		std::uint8_t op2Kind = 0;
		/* readonly */
		std::uint8_t op3Kind = 0;
		/* readonly */
		std::uint8_t op4Kind = 0;
		/* readonly */
		Flags flags = static_cast<Flags>(0);
	private:
		enum class Flags : int
		{
			None = 0,
			IgnoresRoundingControl = 0x00000001,
			AmdLockRegBit = 0x00000002,
			LIG = 0x00000004,
			W = 0x00000008,
			WIG = 0x00000010,
			WIG32 = 0x00000020,
			CPL0 = 0x00000040,
			CPL1 = 0x00000080,
			CPL2 = 0x00000100,
			CPL3 = 0x00000200
		};
		DEFINE_FLAGS(Flags)
			DEFINE_COMP(Flags)
			DEFINE_ARITH(Flags)

	public:
		OpCodeInfo(Iced::Intel::Code code, EncFlags1 encFlags1, EncFlags2 encFlags2, EncFlags3 encFlags3, OpCodeInfoFlags1 opcFlags1, OpCodeInfoFlags2 opcFlags2, StringBuilder* sb);
		/// <summary>
		/// Gets the code
		/// </summary>
		Iced::Intel::Code GetCode() const;
		/// <summary>
		/// Gets the mnemonic
		/// </summary>
		Iced::Intel::Mnemonic GetMnemonic() const;
		/// <summary>
		/// Gets the encoding
		/// </summary>
		EncodingKind GetEncoding() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction, <see langword="false"/> if it's eg. <see cref="Code.INVALID"/>, <c>db</c>, <c>dw</c>, <c>dd</c>, <c>dq</c>
		/// </summary>
		bool IsInstruction() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction available in 16-bit mode
		/// </summary>
		bool GetMode16() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction available in 32-bit mode
		/// </summary>
		bool GetMode32() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction available in 64-bit mode
		/// </summary>
		bool GetMode64() const;
		/// <summary>
		/// <see langword="true"/> if an <c>FWAIT</c> (<c>9B</c>) instruction is added before the instruction
		/// </summary>
		bool GetFwait() const;
		/// <summary>
		/// (Legacy encoding) Gets the required operand size (16,32,64) or 0
		/// </summary>
		std::int32_t GetOperandSize() const;
		/// <summary>
		/// (Legacy encoding) Gets the required address size (16,32,64) or 0
		/// </summary>
		std::int32_t GetAddressSize() const;
		/// <summary>
		/// (VEX/XOP/EVEX) <c>L</c> / <c>L'L</c> value or default value if <see cref="IsLIG"/> is <see langword="true"/>
		/// </summary>
		std::uint32_t GetL() const;
		/// <summary>
		/// (VEX/XOP/EVEX/MVEX) <c>W</c> value or default value if <see cref="IsWIG"/> or <see cref="IsWIG32"/> is <see langword="true"/>
		/// </summary>
		std::uint32_t GetW() const;
		/// <summary>
		/// (VEX/XOP/EVEX) <see langword="true"/> if the <c>L</c> / <c>L'L</c> fields are ignored.
		/// <br/>
		/// EVEX: if reg-only ops and <c>{er}</c> (<c>EVEX.b</c> is set), <c>L'L</c> is the rounding control and not ignored.
		/// </summary>
		bool IsLIG() const;
		/// <summary>
		/// (VEX/XOP/EVEX/MVEX) <see langword="true"/> if the <c>W</c> field is ignored in 16/32/64-bit modes
		/// </summary>
		bool IsWIG() const;
		/// <summary>
		/// (VEX/XOP/EVEX/MVEX) <see langword="true"/> if the <c>W</c> field is ignored in 16/32-bit modes (but not 64-bit mode)
		/// </summary>
		bool IsWIG32() const;
		/// <summary>
		/// (EVEX/MVEX) Gets the tuple type
		/// </summary>
		Iced::Intel::TupleType GetTupleType() const;
		/// <summary>
		/// (MVEX) Gets the <c>EH</c> bit that's required to encode this instruction
		/// </summary>
		Iced::Intel::MvexEHBit GetMvexEHBit() const;
		/// <summary>
		/// (MVEX) <see langword="true"/> if the instruction supports eviction hint (if it has a memory operand)
		/// </summary>
		bool GetMvexCanUseEvictionHint() const;
		/// <summary>
		/// (MVEX) <see langword="true"/> if the instruction's rounding control bits are stored in <c>imm8[1:0]</c>
		/// </summary>
		bool GetMvexCanUseImmRoundingControl() const;
		/// <summary>
		/// (MVEX) <see langword="true"/> if the instruction ignores op mask registers (eg. <c>{k1}</c>)
		/// </summary>
		bool GetMvexIgnoresOpMaskRegister() const;
		/// <summary>
		/// (MVEX) <see langword="true"/> if the instruction must have <c>MVEX.SSS=000</c> if <c>MVEX.EH=1</c>
		/// </summary>
		bool GetMvexNoSaeRc() const;
		/// <summary>
		/// (MVEX) Gets the tuple type / conv lut kind
		/// </summary>
		Iced::Intel::MvexTupleTypeLutKind GetMvexTupleTypeLutKind() const;
		/// <summary>
		/// (MVEX) Gets the conversion function, eg. <c>Sf32</c>
		/// </summary>
		MvexConvFn GetMvexConversionFunc() const;
		/// <summary>
		/// (MVEX) Gets flags indicating which conversion functions are valid (bit 0 == func 0)
		/// </summary>
		std::uint8_t GetMvexValidConversionFuncsMask() const;
		/// <summary>
		/// (MVEX) Gets flags indicating which swizzle functions are valid (bit 0 == func 0)
		/// </summary>
		std::uint8_t GetMvexValidSwizzleFuncsMask() const;
		/// <summary>
		/// If it has a memory operand, gets the <see cref="MemorySize"/> (non-broadcast memory type)
		/// </summary>
		Iced::Intel::MemorySize GetMemorySize() const;
		/// <summary>
		/// If it has a memory operand, gets the <see cref="MemorySize"/> (broadcast memory type)
		/// </summary>
		Iced::Intel::MemorySize GetBroadcastMemorySize() const;
		/// <summary>
		/// (EVEX) <see langword="true"/> if the instruction supports broadcasting (<c>EVEX.b</c> bit) (if it has a memory operand)
		/// </summary>
		bool GetCanBroadcast() const;
		/// <summary>
		/// (EVEX/MVEX) <see langword="true"/> if the instruction supports rounding control
		/// </summary>
		bool GetCanUseRoundingControl() const;
		/// <summary>
		/// (EVEX/MVEX) <see langword="true"/> if the instruction supports suppress all exceptions
		/// </summary>
		bool GetCanSuppressAllExceptions() const;
		/// <summary>
		/// (EVEX/MVEX) <see langword="true"/> if an opmask register can be used
		/// </summary>
		bool GetCanUseOpMaskRegister() const;
		/// <summary>
		/// (EVEX/MVEX) <see langword="true"/> if a non-zero opmask register must be used
		/// </summary>
		bool GetRequireOpMaskRegister() const;
		/// <summary>
		/// (EVEX) <see langword="true"/> if the instruction supports zeroing masking (if one of the opmask registers <c>K1</c>-<c>K7</c> is used and destination operand is not a memory operand)
		/// </summary>
		bool GetCanUseZeroingMasking() const;
		/// <summary>
		/// <see langword="true"/> if the <c>LOCK</c> (<c>F0</c>) prefix can be used
		/// </summary>
		bool GetCanUseLockPrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>XACQUIRE</c> (<c>F2</c>) prefix can be used
		/// </summary>
		bool GetCanUseXacquirePrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>XRELEASE</c> (<c>F3</c>) prefix can be used
		/// </summary>
		bool GetCanUseXreleasePrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>REP</c> / <c>REPE</c> (<c>F3</c>) prefixes can be used
		/// </summary>
		bool GetCanUseRepPrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>REPNE</c> (<c>F2</c>) prefix can be used
		/// </summary>
		bool GetCanUseRepnePrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>BND</c> (<c>F2</c>) prefix can be used
		/// </summary>
		bool GetCanUseBndPrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>HINT-TAKEN</c> (<c>3E</c>) and <c>HINT-NOT-TAKEN</c> (<c>2E</c>) prefixes can be used
		/// </summary>
		bool GetCanUseHintTakenPrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>NOTRACK</c> (<c>3E</c>) prefix can be used
		/// </summary>
		bool GetCanUseNotrackPrefix() const;
		/// <summary>
		/// <see langword="true"/> if rounding control is ignored (#UD is not generated)
		/// </summary>
		bool GetIgnoresRoundingControl() const;
		/// <summary>
		/// (AMD) <see langword="true"/> if the <c>LOCK</c> prefix can be used as an extra register bit (bit 3) to access registers 8-15 without a <c>REX</c> prefix (eg. in 32-bit mode)
		/// </summary>
		bool GetAmdLockRegBit() const;
		/// <summary>
		/// <see langword="true"/> if the default operand size is 64 in 64-bit mode. A <c>66</c> prefix can switch to 16-bit operand size.
		/// </summary>
		bool GetDefaultOpSize64() const;
		/// <summary>
		/// <see langword="true"/> if the operand size is always 64 in 64-bit mode. A <c>66</c> prefix is ignored.
		/// </summary>
		bool GetForceOpSize64() const;
		/// <summary>
		/// <see langword="true"/> if the Intel decoder forces 64-bit operand size. A <c>66</c> prefix is ignored.
		/// </summary>
		bool GetIntelForceOpSize64() const;
		/// <summary>
		/// <see langword="true"/> if it can only be executed when CPL=0
		/// </summary>
		bool GetMustBeCpl0() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed when CPL=0
		/// </summary>
		bool GetCpl0() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed when CPL=1
		/// </summary>
		bool GetCpl1() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed when CPL=2
		/// </summary>
		bool GetCpl2() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed when CPL=3
		/// </summary>
		bool GetCpl3() const;
		/// <summary>
		/// <see langword="true"/> if the instruction accesses the I/O address space (eg. <c>IN</c>, <c>OUT</c>, <c>INS</c>, <c>OUTS</c>)
		/// </summary>
		bool IsInputOutput() const;
		/// <summary>
		/// <see langword="true"/> if it's one of the many nop instructions (does not include FPU nop instructions, eg. <c>FNOP</c>)
		/// </summary>
		bool IsNop() const;
		/// <summary>
		/// <see langword="true"/> if it's one of the many reserved nop instructions (eg. <c>0F0D</c>, <c>0F18-0F1F</c>)
		/// </summary>
		bool IsReservedNop() const;
		/// <summary>
		/// <see langword="true"/> if it's a serializing instruction (Intel CPUs)
		/// </summary>
		bool IsSerializingIntel() const;
		/// <summary>
		/// <see langword="true"/> if it's a serializing instruction (AMD CPUs)
		/// </summary>
		bool IsSerializingAmd() const;
		/// <summary>
		/// <see langword="true"/> if the instruction requires either CPL=0 or CPL&lt;=3 depending on some CPU option (eg. <c>CR4.TSD</c>, <c>CR4.PCE</c>, <c>CR4.UMIP</c>)
		/// </summary>
		bool GetMayRequireCpl0() const;
		/// <summary>
		/// <see langword="true"/> if it's a tracked <c>JMP</c>/<c>CALL</c> indirect instruction (CET)
		/// </summary>
		bool IsCetTracked() const;
		/// <summary>
		/// <see langword="true"/> if it's a non-temporal hint memory access (eg. <c>MOVNTDQ</c>)
		/// </summary>
		bool IsNonTemporal() const;
		/// <summary>
		/// <see langword="true"/> if it's a no-wait FPU instruction, eg. <c>FNINIT</c>
		/// </summary>
		bool IsFpuNoWait() const;
		/// <summary>
		/// <see langword="true"/> if the mod bits are ignored and it's assumed <c>modrm[7:6] == 11b</c>
		/// </summary>
		bool GetIgnoresModBits() const;
		/// <summary>
		/// <see langword="true"/> if the <c>66</c> prefix is not allowed (it will #UD)
		/// </summary>
		bool GetNo66() const;
		/// <summary>
		/// <see langword="true"/> if the <c>F2</c>/<c>F3</c> prefixes aren't allowed
		/// </summary>
		bool GetNFx() const;
		/// <summary>
		/// <see langword="true"/> if the index reg's reg-num (vsib op) (if any) and register ops' reg-nums must be unique,
		/// eg. <c>MNEMONIC XMM1,YMM1,[RAX+ZMM1*2]</c> is invalid. Registers = <c>XMM</c>/<c>YMM</c>/<c>ZMM</c>/<c>TMM</c>.
		/// </summary>
		bool GetRequiresUniqueRegNums() const;
		/// <summary>
		/// <see langword="true"/> if the destination register's reg-num must not be present in any other operand, eg. <c>MNEMONIC XMM1,YMM1,[RAX+ZMM1*2]</c>
		/// is invalid. Registers = <c>XMM</c>/<c>YMM</c>/<c>ZMM</c>/<c>TMM</c>.
		/// </summary>
		bool GetRequiresUniqueDestRegNum() const;
		/// <summary>
		/// <see langword="true"/> if it's a privileged instruction (all CPL=0 instructions (except <c>VMCALL</c>) and IOPL instructions <c>IN</c>, <c>INS</c>, <c>OUT</c>, <c>OUTS</c>, <c>CLI</c>, <c>STI</c>)
		/// </summary>
		bool IsPrivileged() const;
		/// <summary>
		/// <see langword="true"/> if it reads/writes too many registers
		/// </summary>
		bool IsSaveRestore() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction that implicitly uses the stack register, eg. <c>CALL</c>, <c>POP</c>, etc
		/// </summary>
		bool IsStackInstruction() const;
		/// <summary>
		/// <see langword="true"/> if the instruction doesn't read the segment register if it uses a memory operand
		/// </summary>
		bool GetIgnoresSegment() const;
		/// <summary>
		/// <see langword="true"/> if the opmask register is read and written (instead of just read). This also implies that it can't be <c>K0</c>.
		/// </summary>
		bool IsOpMaskReadWrite() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in real mode
		/// </summary>
		bool GetRealMode() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in protected mode
		/// </summary>
		bool GetProtectedMode() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in virtual 8086 mode
		/// </summary>
		bool GetVirtual8086Mode() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in compatibility mode
		/// </summary>
		bool GetCompatibilityMode() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in 64-bit mode
		/// </summary>
		bool GetLongMode() const;
		/// <summary>
		/// <see langword="true"/> if it can be used outside SMM
		/// </summary>
		bool GetUseOutsideSmm() const;
		/// <summary>
		/// <see langword="true"/> if it can be used in SMM
		/// </summary>
		bool GetUseInSmm() const;
		/// <summary>
		/// <see langword="true"/> if it can be used outside an enclave (SGX)
		/// </summary>
		bool GetUseOutsideEnclaveSgx() const;
		/// <summary>
		/// <see langword="true"/> if it can be used inside an enclave (SGX1)
		/// </summary>
		bool GetUseInEnclaveSgx1() const;
		/// <summary>
		/// <see langword="true"/> if it can be used inside an enclave (SGX2)
		/// </summary>
		bool GetUseInEnclaveSgx2() const;
		/// <summary>
		/// <see langword="true"/> if it can be used outside VMX operation
		/// </summary>
		bool GetUseOutsideVmxOp() const;
		/// <summary>
		/// <see langword="true"/> if it can be used in VMX root operation
		/// </summary>
		bool GetUseInVmxRootOp() const;
		/// <summary>
		/// <see langword="true"/> if it can be used in VMX non-root operation
		/// </summary>
		bool GetUseInVmxNonRootOp() const;
		/// <summary>
		/// <see langword="true"/> if it can be used outside SEAM
		/// </summary>
		bool GetUseOutsideSeam() const;
		/// <summary>
		/// <see langword="true"/> if it can be used in SEAM
		/// </summary>
		bool GetUseInSeam() const;
		/// <summary>
		/// <see langword="true"/> if #UD is generated in TDX non-root operation
		/// </summary>
		bool GetTdxNonRootGenUd() const;
		/// <summary>
		/// <see langword="true"/> if #VE is generated in TDX non-root operation
		/// </summary>
		bool GetTdxNonRootGenVe() const;
		/// <summary>
		/// <see langword="true"/> if an exception (eg. #GP(0), #VE) may be generated in TDX non-root operation
		/// </summary>
		bool GetTdxNonRootMayGenEx() const;
		/// <summary>
		/// (Intel VMX) <see langword="true"/> if it causes a VM exit in VMX non-root operation
		/// </summary>
		bool GetIntelVmExit() const;
		/// <summary>
		/// (Intel VMX) <see langword="true"/> if it may cause a VM exit in VMX non-root operation
		/// </summary>
		bool GetIntelMayVmExit() const;
		/// <summary>
		/// (Intel VMX) <see langword="true"/> if it causes an SMM VM exit in VMX root operation (if dual-monitor treatment is activated)
		/// </summary>
		bool GetIntelSmmVmExit() const;
		/// <summary>
		/// (AMD SVM) <see langword="true"/> if it causes a #VMEXIT in guest mode
		/// </summary>
		bool GetAmdVmExit() const;
		/// <summary>
		/// (AMD SVM) <see langword="true"/> if it may cause a #VMEXIT in guest mode
		/// </summary>
		bool GetAmdMayVmExit() const;
		/// <summary>
		/// <see langword="true"/> if it causes a TSX abort inside a TSX transaction
		/// </summary>
		bool GetTsxAbort() const;
		/// <summary>
		/// <see langword="true"/> if it causes a TSX abort inside a TSX transaction depending on the implementation
		/// </summary>
		bool GetTsxImplAbort() const;
		/// <summary>
		/// <see langword="true"/> if it may cause a TSX abort inside a TSX transaction depending on some condition
		/// </summary>
		bool GetTsxMayAbort() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 16-bit Intel decoder
		/// </summary>
		bool GetIntelDecoder16() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 32-bit Intel decoder
		/// </summary>
		bool GetIntelDecoder32() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 64-bit Intel decoder
		/// </summary>
		bool GetIntelDecoder64() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 16-bit AMD decoder
		/// </summary>
		bool GetAmdDecoder16() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 32-bit AMD decoder
		/// </summary>
		bool GetAmdDecoder32() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 64-bit AMD decoder
		/// </summary>
		bool GetAmdDecoder64() const;
	private:
		static std::vector<DecoderOptions> toDecoderOptions;
		/// <summary>
		/// Gets the decoder option that's needed to decode the instruction or <see cref="DecoderOptions.None"/>
		/// </summary>
	public:
		DecoderOptions GetDecoderOption() const;
		/// <summary>
		/// Gets the opcode table
		/// </summary>
		OpCodeTableKind GetTable() const;
		/// <summary>
		/// Gets the mandatory prefix
		/// </summary>
		Iced::Intel::MandatoryPrefix GetMandatoryPrefix() const;
		/// <summary>
		/// Gets the opcode byte(s). The low byte(s) of this value is the opcode. The length is in <see cref="OpCodeLength"/>.
		/// It doesn't include the table value, see <see cref="Table"/>.
		/// <br/>
		/// Example values: <c>0xDFC0</c> (<see cref="Code.Ffreep_sti"/>), <c>0x01D8</c> (<see cref="Code.Vmrunw"/>), <c>0x2A</c> (<see cref="Code.Sub_r8_rm8"/>, <see cref="Code.Cvtpi2ps_xmm_mmm64"/>, etc).
		/// </summary>
		std::uint32_t GetOpCode() const;
		/// <summary>
		/// Gets the length of the opcode bytes (<see cref="OpCode"/>). The low bytes is the opcode value.
		/// </summary>
		std::int32_t GetOpCodeLength() const;
		/// <summary>
		/// <see langword="true"/> if it's part of a group
		/// </summary>
		bool IsGroup() const;
		/// <summary>
		/// Group index (0-7) or -1. If it's 0-7, it's stored in the <c>reg</c> field of the <c>modrm</c> byte.
		/// </summary>
		std::int32_t GetGroupIndex() const;
		/// <summary>
		/// <see langword="true"/> if it's part of a modrm.rm group
		/// </summary>
		bool IsRmGroup() const;
		/// <summary>
		/// modrm.rm group index (0-7) or -1. If it's 0-7, it's stored in the <c>rm</c> field of the <c>modrm</c> byte.
		/// </summary>
		std::int32_t GetRmGroupIndex() const;
		/// <summary>
		/// Gets the number of operands
		/// </summary>
		std::int32_t GetOpCount() const;
		/// <summary>
		/// Gets operand #0's opkind
		/// </summary>
		OpCodeOperandKind GetOp0Kind() const;
		/// <summary>
		/// Gets operand #1's opkind
		/// </summary>
		OpCodeOperandKind GetOp1Kind() const;
		/// <summary>
		/// Gets operand #2's opkind
		/// </summary>
		OpCodeOperandKind GetOp2Kind() const;
		/// <summary>
		/// Gets operand #3's opkind
		/// </summary>
		OpCodeOperandKind GetOp3Kind() const;
		/// <summary>
		/// Gets operand #4's opkind
		/// </summary>
		OpCodeOperandKind GetOp4Kind() const;
		/// <summary>
		/// Gets an operand's opkind
		/// </summary>
		/// <param name="operand">Operand number, 0-4</param>
		/// <returns></returns>
		OpCodeOperandKind GetOpKind(std::int32_t operand);
		/// <summary>
		/// Checks if the instruction is available in 16-bit mode, 32-bit mode or 64-bit mode
		/// </summary>
		/// <param name="bitness">16, 32 or 64</param>
		/// <returns></returns>
		bool IsAvailableInMode(std::int32_t bitness);
		/// <summary>
		/// Gets the opcode string, eg. <c>VEX.128.66.0F38.W0 78 /r</c>, see also <see cref="ToInstructionString()"/>
		/// </summary>
		/// <returns></returns>
		std::string ToOpCodeString();
		/// <summary>
		/// Gets the instruction string, eg. <c>VPBROADCASTB xmm1, xmm2/m8</c>, see also <see cref="ToOpCodeString()"/>
		/// </summary>
		/// <returns></returns>
		std::string ToInstructionString();
		/// <summary>
		/// Gets the instruction string, eg. <c>VPBROADCASTB xmm1, xmm2/m8</c>, see also <see cref="ToOpCodeString()"/>
		/// </summary>
		/// <returns></returns>
		std::string ToString();
	};
}
