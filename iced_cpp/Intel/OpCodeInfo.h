// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include <array>
#include <string>
#include <vector>

#include <csharp/enum.h>

#include "EncoderInternal/Enums.h"
#include "EncoderInternal/OpCodeOperandKinds.g.h"
#include "Code.g.h"
#include "DecoderOptions.g.h"
#include "MandatoryPrefix.g.h"
#include "Mnemonic.g.h"
#include "OpCodeTableKind.g.h"
#include "EncoderInternal/OpCodeInfosEnums.h"
#include "InstructionOpCounts.g.h"
#include "MvexInfo.h"
#include "MvexInfoData.g.h"
#include "EncoderInternal/InstructionFormatter.defs.h"
#include "EncoderInternal/OpCodeFormatter.defs.h"
#include "MemorySize.g.h"
#include "EncoderInternal/EncoderData.g.h"
#include "MnemonicUtils.h"
#include "EncodingKind.g.h"
#include "InstructionMemorySizes.g.h"
#include "MandatoryPrefixByte.g.h"
#include "CodeSize.g.h"

namespace Iced::Intel::EncoderInternal
{
	class OpCodeInfoStringsInternal;
	class OpCodeInfosInternal;
}

namespace Iced::Intel
{
	/// <summary>
	/// Opcode info
	/// </summary>
	class OpCodeInfo final
	{
		friend class EncoderInternal::OpCodeInfoStringsInternal;
		friend class EncoderInternal::OpCodeInfosInternal;
	private:
		enum class Flags : std::uint32_t
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
		DEFINE_FLAGS_FRIEND(Flags)
		DEFINE_COMP_FRIEND(Flags)
		DEFINE_ARITH_FRIEND(Flags)
		/* readonly */
	private:
		mutable bool isConstexprConstructed = false;
		union
		{
			mutable std::string toOpCodeStringValue;
			int toOpCodeStringIndex;
		};
		union
		{
			mutable std::string toInstructionStringValue;
			int toInstructionStringIndex;
		};
		/* readonly */
		EncoderInternal::EncFlags2 encFlags2 = static_cast<EncoderInternal::EncFlags2>(0);
		/* readonly */
		EncoderInternal::EncFlags3 encFlags3 = static_cast<EncoderInternal::EncFlags3>(0);
		/* readonly */
		EncoderInternal::OpCodeInfoFlags1 opcFlags1 = static_cast<EncoderInternal::OpCodeInfoFlags1>(0);
		/* readonly */
		EncoderInternal::OpCodeInfoFlags2 opcFlags2 = static_cast<EncoderInternal::OpCodeInfoFlags2>(0);
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
		EncoderInternal::LKind lkind = EncoderInternal::LKind::None;
	public:
		OpCodeInfo(::Iced::Intel::Code code, EncoderInternal::EncFlags1 encFlags1, EncoderInternal::EncFlags2 encFlags2, EncoderInternal::EncFlags3 encFlags3, EncoderInternal::OpCodeInfoFlags1 opcFlags1, EncoderInternal::OpCodeInfoFlags2 opcFlags2, std::string& sb);

		constexpr OpCodeInfo(::Iced::Intel::Code code, EncoderInternal::EncFlags1 encFlags1, EncoderInternal::EncFlags2 encFlags2, EncoderInternal::EncFlags3 encFlags3, EncoderInternal::OpCodeInfoFlags1 opcFlags1, EncoderInternal::OpCodeInfoFlags2 opcFlags2);

		constexpr OpCodeInfo(const OpCodeInfo& op);

		constexpr OpCodeInfo();

		constexpr ~OpCodeInfo();
	public:
		/// <summary>
		/// Gets the code
		/// </summary>
		constexpr ::Iced::Intel::Code GetCode() const;
		/// <summary>
		/// Gets the mnemonic
		/// </summary>
		constexpr ::Iced::Intel::Mnemonic GetMnemonic() const;
		/// <summary>
		/// Gets the encoding
		/// </summary>
		constexpr EncodingKind GetEncoding() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction, <see langword="false"/> if it's eg. <see cref="Code.INVALID"/>, <c>db</c>, <c>dw</c>, <c>dd</c>, <c>dq</c>
		/// </summary>
		constexpr bool IsInstruction() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction available in 16-bit mode
		/// </summary>
		constexpr bool GetMode16() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction available in 32-bit mode
		/// </summary>
		constexpr bool GetMode32() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction available in 64-bit mode
		/// </summary>
		constexpr bool GetMode64() const;
		/// <summary>
		/// <see langword="true"/> if an <c>FWAIT</c> (<c>9B</c>) instruction is added before the instruction
		/// </summary>
		constexpr bool GetFwait() const;
		/// <summary>
		/// (Legacy encoding) Gets the required operand size (16,32,64) or 0
		/// </summary>
		constexpr std::int32_t GetOperandSize() const;
		/// <summary>
		/// (Legacy encoding) Gets the required address size (16,32,64) or 0
		/// </summary>
		constexpr std::int32_t GetAddressSize() const;
		/// <summary>
		/// (VEX/XOP/EVEX) <c>L</c> / <c>L'L</c> value or default value if <see cref="IsLIG"/> is <see langword="true"/>
		/// </summary>
		constexpr std::uint32_t GetL() const;
		/// <summary>
		/// (VEX/XOP/EVEX/MVEX) <c>W</c> value or default value if <see cref="IsWIG"/> or <see cref="IsWIG32"/> is <see langword="true"/>
		/// </summary>
		constexpr std::uint32_t GetW() const;
		/// <summary>
		/// (VEX/XOP/EVEX) <see langword="true"/> if the <c>L</c> / <c>L'L</c> fields are ignored.
		/// <br/>
		/// EVEX: if reg-only ops and <c>{er}</c> (<c>EVEX.b</c> is set), <c>L'L</c> is the rounding control and not ignored.
		/// </summary>
		constexpr bool IsLIG() const;
		/// <summary>
		/// (VEX/XOP/EVEX/MVEX) <see langword="true"/> if the <c>W</c> field is ignored in 16/32/64-bit modes
		/// </summary>
		constexpr bool IsWIG() const;
		/// <summary>
		/// (VEX/XOP/EVEX/MVEX) <see langword="true"/> if the <c>W</c> field is ignored in 16/32-bit modes (but not 64-bit mode)
		/// </summary>
		constexpr bool IsWIG32() const;
		/// <summary>
		/// (EVEX/MVEX) Gets the tuple type
		/// </summary>
		constexpr ::Iced::Intel::TupleType GetTupleType() const;
		/// <summary>
		/// (MVEX) Gets the <c>EH</c> bit that's required to encode this instruction
		/// </summary>
		constexpr ::Iced::Intel::MvexEHBit GetMvexEHBit() const;
		/// <summary>
		/// (MVEX) <see langword="true"/> if the instruction supports eviction hint (if it has a memory operand)
		/// </summary>
		constexpr bool GetMvexCanUseEvictionHint() const;
		/// <summary>
		/// (MVEX) <see langword="true"/> if the instruction's rounding control bits are stored in <c>imm8[1:0]</c>
		/// </summary>
		constexpr bool GetMvexCanUseImmRoundingControl() const;
		/// <summary>
		/// (MVEX) <see langword="true"/> if the instruction ignores op mask registers (eg. <c>{k1}</c>)
		/// </summary>
		constexpr bool GetMvexIgnoresOpMaskRegister() const;
		/// <summary>
		/// (MVEX) <see langword="true"/> if the instruction must have <c>MVEX.SSS=000</c> if <c>MVEX.EH=1</c>
		/// </summary>
		constexpr bool GetMvexNoSaeRc() const;
		/// <summary>
		/// (MVEX) Gets the tuple type / conv lut kind
		/// </summary>
		constexpr ::Iced::Intel::MvexTupleTypeLutKind GetMvexTupleTypeLutKind() const;
		/// <summary>
		/// (MVEX) Gets the conversion function, eg. <c>Sf32</c>
		/// </summary>
		constexpr MvexConvFn GetMvexConversionFunc() const;
		/// <summary>
		/// (MVEX) Gets flags indicating which conversion functions are valid (bit 0 == func 0)
		/// </summary>
		constexpr std::uint8_t GetMvexValidConversionFuncsMask() const;
		/// <summary>
		/// (MVEX) Gets flags indicating which swizzle functions are valid (bit 0 == func 0)
		/// </summary>
		constexpr std::uint8_t GetMvexValidSwizzleFuncsMask() const;
		/// <summary>
		/// If it has a memory operand, gets the <see cref="MemorySize"/> (non-broadcast memory type)
		/// </summary>
		constexpr ::Iced::Intel::MemorySize GetMemorySize() const;
		/// <summary>
		/// If it has a memory operand, gets the <see cref="MemorySize"/> (broadcast memory type)
		/// </summary>
		constexpr ::Iced::Intel::MemorySize GetBroadcastMemorySize() const;
		/// <summary>
		/// (EVEX) <see langword="true"/> if the instruction supports broadcasting (<c>EVEX.b</c> bit) (if it has a memory operand)
		/// </summary>
		constexpr bool GetCanBroadcast() const;
		/// <summary>
		/// (EVEX/MVEX) <see langword="true"/> if the instruction supports rounding control
		/// </summary>
		constexpr bool GetCanUseRoundingControl() const;
		/// <summary>
		/// (EVEX/MVEX) <see langword="true"/> if the instruction supports suppress all exceptions
		/// </summary>
		constexpr bool GetCanSuppressAllExceptions() const;
		/// <summary>
		/// (EVEX/MVEX) <see langword="true"/> if an opmask register can be used
		/// </summary>
		constexpr bool GetCanUseOpMaskRegister() const;
		/// <summary>
		/// (EVEX/MVEX) <see langword="true"/> if a non-zero opmask register must be used
		/// </summary>
		constexpr bool GetRequireOpMaskRegister() const;
		/// <summary>
		/// (EVEX) <see langword="true"/> if the instruction supports zeroing masking (if one of the opmask registers <c>K1</c>-<c>K7</c> is used and destination operand is not a memory operand)
		/// </summary>
		constexpr bool GetCanUseZeroingMasking() const;
		/// <summary>
		/// <see langword="true"/> if the <c>LOCK</c> (<c>F0</c>) prefix can be used
		/// </summary>
		constexpr bool GetCanUseLockPrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>XACQUIRE</c> (<c>F2</c>) prefix can be used
		/// </summary>
		constexpr bool GetCanUseXacquirePrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>XRELEASE</c> (<c>F3</c>) prefix can be used
		/// </summary>
		constexpr bool GetCanUseXreleasePrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>REP</c> / <c>REPE</c> (<c>F3</c>) prefixes can be used
		/// </summary>
		constexpr bool GetCanUseRepPrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>REPNE</c> (<c>F2</c>) prefix can be used
		/// </summary>
		constexpr bool GetCanUseRepnePrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>BND</c> (<c>F2</c>) prefix can be used
		/// </summary>
		constexpr bool GetCanUseBndPrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>HINT-TAKEN</c> (<c>3E</c>) and <c>HINT-NOT-TAKEN</c> (<c>2E</c>) prefixes can be used
		/// </summary>
		constexpr bool GetCanUseHintTakenPrefix() const;
		/// <summary>
		/// <see langword="true"/> if the <c>NOTRACK</c> (<c>3E</c>) prefix can be used
		/// </summary>
		constexpr bool GetCanUseNotrackPrefix() const;
		/// <summary>
		/// <see langword="true"/> if rounding control is ignored (#UD is not generated)
		/// </summary>
		constexpr bool GetIgnoresRoundingControl() const;
		/// <summary>
		/// (AMD) <see langword="true"/> if the <c>LOCK</c> prefix can be used as an extra register bit (bit 3) to access registers 8-15 without a <c>REX</c> prefix (eg. in 32-bit mode)
		/// </summary>
		constexpr bool GetAmdLockRegBit() const;
		/// <summary>
		/// <see langword="true"/> if the default operand size is 64 in 64-bit mode. A <c>66</c> prefix can switch to 16-bit operand size.
		/// </summary>
		constexpr bool GetDefaultOpSize64() const;
		/// <summary>
		/// <see langword="true"/> if the operand size is always 64 in 64-bit mode. A <c>66</c> prefix is ignored.
		/// </summary>
		constexpr bool GetForceOpSize64() const;
		/// <summary>
		/// <see langword="true"/> if the Intel decoder forces 64-bit operand size. A <c>66</c> prefix is ignored.
		/// </summary>
		constexpr bool GetIntelForceOpSize64() const;
		/// <summary>
		/// <see langword="true"/> if it can only be executed when CPL=0
		/// </summary>
		constexpr bool GetMustBeCpl0() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed when CPL=0
		/// </summary>
		constexpr bool GetCpl0() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed when CPL=1
		/// </summary>
		constexpr bool GetCpl1() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed when CPL=2
		/// </summary>
		constexpr bool GetCpl2() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed when CPL=3
		/// </summary>
		constexpr bool GetCpl3() const;
		/// <summary>
		/// <see langword="true"/> if the instruction accesses the I/O address space (eg. <c>IN</c>, <c>OUT</c>, <c>INS</c>, <c>OUTS</c>)
		/// </summary>
		constexpr bool IsInputOutput() const;
		/// <summary>
		/// <see langword="true"/> if it's one of the many nop instructions (does not include FPU nop instructions, eg. <c>FNOP</c>)
		/// </summary>
		constexpr bool IsNop() const;
		/// <summary>
		/// <see langword="true"/> if it's one of the many reserved nop instructions (eg. <c>0F0D</c>, <c>0F18-0F1F</c>)
		/// </summary>
		constexpr bool IsReservedNop() const;
		/// <summary>
		/// <see langword="true"/> if it's a serializing instruction (Intel CPUs)
		/// </summary>
		constexpr bool IsSerializingIntel() const;
		/// <summary>
		/// <see langword="true"/> if it's a serializing instruction (AMD CPUs)
		/// </summary>
		constexpr bool IsSerializingAmd() const;
		/// <summary>
		/// <see langword="true"/> if the instruction requires either CPL=0 or CPL&lt;=3 depending on some CPU option (eg. <c>CR4.TSD</c>, <c>CR4.PCE</c>, <c>CR4.UMIP</c>)
		/// </summary>
		constexpr bool GetMayRequireCpl0() const;
		/// <summary>
		/// <see langword="true"/> if it's a tracked <c>JMP</c>/<c>CALL</c> indirect instruction (CET)
		/// </summary>
		constexpr bool IsCetTracked() const;
		/// <summary>
		/// <see langword="true"/> if it's a non-temporal hint memory access (eg. <c>MOVNTDQ</c>)
		/// </summary>
		constexpr bool IsNonTemporal() const;
		/// <summary>
		/// <see langword="true"/> if it's a no-wait FPU instruction, eg. <c>FNINIT</c>
		/// </summary>
		constexpr bool IsFpuNoWait() const;
		/// <summary>
		/// <see langword="true"/> if the mod bits are ignored and it's assumed <c>modrm[7:6] == 11b</c>
		/// </summary>
		constexpr bool GetIgnoresModBits() const;
		/// <summary>
		/// <see langword="true"/> if the <c>66</c> prefix is not allowed (it will #UD)
		/// </summary>
		constexpr bool GetNo66() const;
		/// <summary>
		/// <see langword="true"/> if the <c>F2</c>/<c>F3</c> prefixes aren't allowed
		/// </summary>
		constexpr bool GetNFx() const;
		/// <summary>
		/// <see langword="true"/> if the index reg's reg-num (vsib op) (if any) and register ops' reg-nums must be unique,
		/// eg. <c>MNEMONIC XMM1,YMM1,[RAX+ZMM1*2]</c> is invalid. Registers = <c>XMM</c>/<c>YMM</c>/<c>ZMM</c>/<c>TMM</c>.
		/// </summary>
		constexpr bool GetRequiresUniqueRegNums() const;
		/// <summary>
		/// <see langword="true"/> if the destination register's reg-num must not be present in any other operand, eg. <c>MNEMONIC XMM1,YMM1,[RAX+ZMM1*2]</c>
		/// is invalid. Registers = <c>XMM</c>/<c>YMM</c>/<c>ZMM</c>/<c>TMM</c>.
		/// </summary>
		constexpr bool GetRequiresUniqueDestRegNum() const;
		/// <summary>
		/// <see langword="true"/> if it's a privileged instruction (all CPL=0 instructions (except <c>VMCALL</c>) and IOPL instructions <c>IN</c>, <c>INS</c>, <c>OUT</c>, <c>OUTS</c>, <c>CLI</c>, <c>STI</c>)
		/// </summary>
		constexpr bool IsPrivileged() const;
		/// <summary>
		/// <see langword="true"/> if it reads/writes too many registers
		/// </summary>
		constexpr bool IsSaveRestore() const;
		/// <summary>
		/// <see langword="true"/> if it's an instruction that implicitly uses the stack register, eg. <c>CALL</c>, <c>POP</c>, etc
		/// </summary>
		constexpr bool IsStackInstruction() const;
		/// <summary>
		/// <see langword="true"/> if the instruction doesn't read the segment register if it uses a memory operand
		/// </summary>
		constexpr bool GetIgnoresSegment() const;
		/// <summary>
		/// <see langword="true"/> if the opmask register is read and written (instead of just read). This also implies that it can't be <c>K0</c>.
		/// </summary>
		constexpr bool IsOpMaskReadWrite() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in real mode
		/// </summary>
		constexpr bool GetRealMode() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in protected mode
		/// </summary>
		constexpr bool GetProtectedMode() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in virtual 8086 mode
		/// </summary>
		constexpr bool GetVirtual8086Mode() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in compatibility mode
		/// </summary>
		constexpr bool GetCompatibilityMode() const;
		/// <summary>
		/// <see langword="true"/> if it can be executed in 64-bit mode
		/// </summary>
		constexpr bool GetLongMode() const;
		/// <summary>
		/// <see langword="true"/> if it can be used outside SMM
		/// </summary>
		constexpr bool GetUseOutsideSmm() const;
		/// <summary>
		/// <see langword="true"/> if it can be used in SMM
		/// </summary>
		constexpr bool GetUseInSmm() const;
		/// <summary>
		/// <see langword="true"/> if it can be used outside an enclave (SGX)
		/// </summary>
		constexpr bool GetUseOutsideEnclaveSgx() const;
		/// <summary>
		/// <see langword="true"/> if it can be used inside an enclave (SGX1)
		/// </summary>
		constexpr bool GetUseInEnclaveSgx1() const;
		/// <summary>
		/// <see langword="true"/> if it can be used inside an enclave (SGX2)
		/// </summary>
		constexpr bool GetUseInEnclaveSgx2() const;
		/// <summary>
		/// <see langword="true"/> if it can be used outside VMX operation
		/// </summary>
		constexpr bool GetUseOutsideVmxOp() const;
		/// <summary>
		/// <see langword="true"/> if it can be used in VMX root operation
		/// </summary>
		constexpr bool GetUseInVmxRootOp() const;
		/// <summary>
		/// <see langword="true"/> if it can be used in VMX non-root operation
		/// </summary>
		constexpr bool GetUseInVmxNonRootOp() const;
		/// <summary>
		/// <see langword="true"/> if it can be used outside SEAM
		/// </summary>
		constexpr bool GetUseOutsideSeam() const;
		/// <summary>
		/// <see langword="true"/> if it can be used in SEAM
		/// </summary>
		constexpr bool GetUseInSeam() const;
		/// <summary>
		/// <see langword="true"/> if #UD is generated in TDX non-root operation
		/// </summary>
		constexpr bool GetTdxNonRootGenUd() const;
		/// <summary>
		/// <see langword="true"/> if #VE is generated in TDX non-root operation
		/// </summary>
		constexpr bool GetTdxNonRootGenVe() const;
		/// <summary>
		/// <see langword="true"/> if an exception (eg. #GP(0), #VE) may be generated in TDX non-root operation
		/// </summary>
		constexpr bool GetTdxNonRootMayGenEx() const;
		/// <summary>
		/// (Intel VMX) <see langword="true"/> if it causes a VM exit in VMX non-root operation
		/// </summary>
		constexpr bool GetIntelVmExit() const;
		/// <summary>
		/// (Intel VMX) <see langword="true"/> if it may cause a VM exit in VMX non-root operation
		/// </summary>
		constexpr bool GetIntelMayVmExit() const;
		/// <summary>
		/// (Intel VMX) <see langword="true"/> if it causes an SMM VM exit in VMX root operation (if dual-monitor treatment is activated)
		/// </summary>
		constexpr bool GetIntelSmmVmExit() const;
		/// <summary>
		/// (AMD SVM) <see langword="true"/> if it causes a #VMEXIT in guest mode
		/// </summary>
		constexpr bool GetAmdVmExit() const;
		/// <summary>
		/// (AMD SVM) <see langword="true"/> if it may cause a #VMEXIT in guest mode
		/// </summary>
		constexpr bool GetAmdMayVmExit() const;
		/// <summary>
		/// <see langword="true"/> if it causes a TSX abort inside a TSX transaction
		/// </summary>
		constexpr bool GetTsxAbort() const;
		/// <summary>
		/// <see langword="true"/> if it causes a TSX abort inside a TSX transaction depending on the implementation
		/// </summary>
		constexpr bool GetTsxImplAbort() const;
		/// <summary>
		/// <see langword="true"/> if it may cause a TSX abort inside a TSX transaction depending on some condition
		/// </summary>
		constexpr bool GetTsxMayAbort() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 16-bit Intel decoder
		/// </summary>
		constexpr bool GetIntelDecoder16() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 32-bit Intel decoder
		/// </summary>
		constexpr bool GetIntelDecoder32() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 64-bit Intel decoder
		/// </summary>
		constexpr bool GetIntelDecoder64() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 16-bit AMD decoder
		/// </summary>
		constexpr bool GetAmdDecoder16() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 32-bit AMD decoder
		/// </summary>
		constexpr bool GetAmdDecoder32() const;
		/// <summary>
		/// <see langword="true"/> if it's decoded by iced's 64-bit AMD decoder
		/// </summary>
		constexpr bool GetAmdDecoder64() const;
	private:
		inline static constexpr std::array toDecoderOptions = std::to_array({ DecoderOptions::None, DecoderOptions::ALTINST, DecoderOptions::Cl1invmb, DecoderOptions::Cmpxchg486A, DecoderOptions::Cyrix, DecoderOptions::Cyrix_DMI, DecoderOptions::Cyrix_SMINT_0F7E, DecoderOptions::Jmpe, DecoderOptions::Loadall286, DecoderOptions::Loadall386, DecoderOptions::MovTr, DecoderOptions::MPX, DecoderOptions::OldFpu, DecoderOptions::Pcommit, DecoderOptions::Umov, DecoderOptions::Xbts, DecoderOptions::Udbg, DecoderOptions::KNC });
		/// <summary>
		/// Gets the decoder option that's needed to decode the instruction or <see cref="DecoderOptions.None"/>
		/// </summary>
	public:
		constexpr DecoderOptions GetDecoderOption() const;
		/// <summary>
		/// Gets the opcode table
		/// </summary>
		constexpr OpCodeTableKind GetTable() const;
		/// <summary>
		/// Gets the mandatory prefix
		/// </summary>
		constexpr ::Iced::Intel::MandatoryPrefix GetMandatoryPrefix() const;
		/// <summary>
		/// Gets the opcode byte(s). The low byte(s) of this value is the opcode. The length is in <see cref="OpCodeLength"/>.
		/// It doesn't include the table value, see <see cref="Table"/>.
		/// <br/>
		/// Example values: <c>0xDFC0</c> (<see cref="Code.Ffreep_sti"/>), <c>0x01D8</c> (<see cref="Code.Vmrunw"/>), <c>0x2A</c> (<see cref="Code.Sub_r8_rm8"/>, <see cref="Code.Cvtpi2ps_xmm_mmm64"/>, etc).
		/// </summary>
		constexpr std::uint32_t GetOpCode() const;
		/// <summary>
		/// Gets the length of the opcode bytes (<see cref="OpCode"/>). The low bytes is the opcode value.
		/// </summary>
		constexpr std::int32_t GetOpCodeLength() const;
		/// <summary>
		/// <see langword="true"/> if it's part of a group
		/// </summary>
		constexpr bool IsGroup() const;
		/// <summary>
		/// Group index (0-7) or -1. If it's 0-7, it's stored in the <c>reg</c> field of the <c>modrm</c> byte.
		/// </summary>
		constexpr std::int32_t GetGroupIndex() const;
		/// <summary>
		/// <see langword="true"/> if it's part of a modrm.rm group
		/// </summary>
		constexpr bool IsRmGroup() const;
		/// <summary>
		/// modrm.rm group index (0-7) or -1. If it's 0-7, it's stored in the <c>rm</c> field of the <c>modrm</c> byte.
		/// </summary>
		constexpr std::int32_t GetRmGroupIndex() const;
		/// <summary>
		/// Gets the number of operands
		/// </summary>
		constexpr std::int32_t GetOpCount() const;
		/// <summary>
		/// Gets operand #0's opkind
		/// </summary>
		constexpr OpCodeOperandKind GetOp0Kind() const;
		/// <summary>
		/// Gets operand #1's opkind
		/// </summary>
		constexpr OpCodeOperandKind GetOp1Kind() const;
		/// <summary>
		/// Gets operand #2's opkind
		/// </summary>
		constexpr OpCodeOperandKind GetOp2Kind() const;
		/// <summary>
		/// Gets operand #3's opkind
		/// </summary>
		constexpr OpCodeOperandKind GetOp3Kind() const;
		/// <summary>
		/// Gets operand #4's opkind
		/// </summary>
		constexpr OpCodeOperandKind GetOp4Kind() const;
		/// <summary>
		/// Gets an operand's opkind
		/// </summary>
		/// <param name="operand">Operand number, 0-4</param>
		/// <returns></returns>
		constexpr OpCodeOperandKind GetOpKind(std::int32_t operand) const;
		/// <summary>
		/// Checks if the instruction is available in 16-bit mode, 32-bit mode or 64-bit mode
		/// </summary>
		/// <param name="bitness">16, 32 or 64</param>
		/// <returns></returns>
		constexpr bool IsAvailableInMode(std::int32_t bitness) const;
		/// <summary>
		/// Gets the opcode string, eg. <c>VEX.128.66.0F38.W0 78 /r</c>, see also <see cref="ToInstructionString()"/>
		/// </summary>
		/// <returns></returns>
		const char* ToOpCodeString() const;
		/// <summary>
		/// Gets the instruction string, eg. <c>VPBROADCASTB xmm1, xmm2/m8</c>, see also <see cref="ToOpCodeString()"/>
		/// </summary>
		/// <returns></returns>
		const char* ToInstructionString() const;
		/// <summary>
		/// Gets the instruction string, eg. <c>VPBROADCASTB xmm1, xmm2/m8</c>, see also <see cref="ToOpCodeString()"/>
		/// </summary>
		/// <returns></returns>
		const char* ToString() const;
	};

	constexpr OpCodeInfo::OpCodeInfo()
	{
		if (std::is_constant_evaluated())
		{
			isConstexprConstructed = true;
			toOpCodeStringIndex = toInstructionStringIndex = -1;
		}
		else
		{
			isConstexprConstructed = false;
			toOpCodeStringValue = toInstructionStringValue = "";
		}
	}

	constexpr OpCodeInfo::OpCodeInfo(::Iced::Intel::Code code, EncoderInternal::EncFlags1 encFlags1, EncoderInternal::EncFlags2 encFlags2, EncoderInternal::EncFlags3 encFlags3, EncoderInternal::OpCodeInfoFlags1 opcFlags1, EncoderInternal::OpCodeInfoFlags2 opcFlags2)
		: OpCodeInfo()
	{
		this->code = static_cast<std::uint16_t>(code);
		this->encFlags2 = encFlags2;
		this->encFlags3 = encFlags3;
		this->opcFlags1 = opcFlags1;
		this->opcFlags2 = opcFlags2;
		if ((encFlags1 & EncoderInternal::EncFlags1::IgnoresRoundingControl) != 0)
		{
			flags |= Flags::IgnoresRoundingControl;
		}
		if ((encFlags1 & EncoderInternal::EncFlags1::AmdLockRegBit) != 0)
		{
			flags |= Flags::AmdLockRegBit;
		}
		auto switchTempVar_0 = (opcFlags1 & (EncoderInternal::OpCodeInfoFlags1::Cpl0Only | EncoderInternal::OpCodeInfoFlags1::Cpl3Only));


		flags |= (switchTempVar_0 == EncoderInternal::OpCodeInfoFlags1::Cpl0Only) ? Flags::CPL0 : (switchTempVar_0 == EncoderInternal::OpCodeInfoFlags1::Cpl3Only) ? Flags::CPL3 : Flags::CPL0 | Flags::CPL1 | Flags::CPL2 | Flags::CPL3;
		encoding = static_cast<std::uint8_t>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncoderInternal::EncFlags3::EncodingShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags3::EncodingMask));
		auto switchTempVar_1 = static_cast<MandatoryPrefixByte>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::MandatoryPrefixShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags2::MandatoryPrefixMask));


		mandatoryPrefix = (switchTempVar_1 == MandatoryPrefixByte::None) ? static_cast<std::uint8_t>((encFlags2 & EncoderInternal::EncFlags2::HasMandatoryPrefix) != 0 ? MandatoryPrefix::PNP : MandatoryPrefix::None) : (switchTempVar_1 == MandatoryPrefixByte::P66) ? static_cast<std::uint8_t>(MandatoryPrefix::P66) : (switchTempVar_1 == MandatoryPrefixByte::PF3) ? static_cast<std::uint8_t>(MandatoryPrefix::PF3) : (switchTempVar_1 == MandatoryPrefixByte::PF2) ? static_cast<std::uint8_t>(MandatoryPrefix::PF2) : throw InvalidOperationException();
		auto switchTempVar_2 = static_cast<CodeSize>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncoderInternal::EncFlags3::OperandSizeShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags3::OperandSizeMask));


		operandSize = (switchTempVar_2 == CodeSize::Unknown) ? static_cast<std::uint8_t>(0) : (switchTempVar_2 == CodeSize::Code16) ? static_cast<std::uint8_t>(16) : (switchTempVar_2 == CodeSize::Code32) ? static_cast<std::uint8_t>(32) : (switchTempVar_2 == CodeSize::Code64) ? static_cast<std::uint8_t>(64) : throw InvalidOperationException();
		auto switchTempVar_3 = static_cast<CodeSize>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncoderInternal::EncFlags3::AddressSizeShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags3::AddressSizeMask));


		addressSize = (switchTempVar_3 == CodeSize::Unknown) ? static_cast<std::uint8_t>(0) : (switchTempVar_3 == CodeSize::Code16) ? static_cast<std::uint8_t>(16) : (switchTempVar_3 == CodeSize::Code32) ? static_cast<std::uint8_t>(32) : (switchTempVar_3 == CodeSize::Code64) ? static_cast<std::uint8_t>(64) : throw InvalidOperationException();
		groupIndex = static_cast<std::int8_t>((encFlags2 & EncoderInternal::EncFlags2::HasGroupIndex) == 0 ? -1 : static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::GroupIndexShift)) & 7));
		rmGroupIndex = static_cast<std::int8_t>((encFlags3 & EncoderInternal::EncFlags3::HasRmGroupIndex) == 0 ? -1 : static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::GroupIndexShift)) & 7));
		tupleType = static_cast<std::uint8_t>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncoderInternal::EncFlags3::TupleTypeShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags3::TupleTypeMask));

		switch (static_cast<EncoderInternal::LBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::LBitShift)) & static_cast<std::int32_t>(EncoderInternal::EncFlags2::LBitMask)))
		{
		case EncoderInternal::LBit::LZ:
			lkind = EncoderInternal::LKind::LZ;
			l = 0;
			break;
		case EncoderInternal::LBit::L0:
			lkind = EncoderInternal::LKind::L0;
			l = 0;
			break;
		case EncoderInternal::LBit::L1:
			lkind = EncoderInternal::LKind::L0;
			l = 1;
			break;
		case EncoderInternal::LBit::L128:
			lkind = EncoderInternal::LKind::L128;
			l = 0;
			break;
		case EncoderInternal::LBit::L256:
			lkind = EncoderInternal::LKind::L128;
			l = 1;
			break;
		case EncoderInternal::LBit::L512:
			lkind = EncoderInternal::LKind::L128;
			l = 2;
			break;
		case EncoderInternal::LBit::LIG:
			lkind = EncoderInternal::LKind::None;
			l = 0;
			flags |= Flags::LIG;
			break;
		default:
			throw InvalidOperationException();
		}
		switch (static_cast<EncoderInternal::WBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::WBitShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags2::WBitMask)))
		{
		case EncoderInternal::WBit::W0:
			break;
		case EncoderInternal::WBit::W1:
			flags |= Flags::W;
			break;
		case EncoderInternal::WBit::WIG:
			flags |= Flags::WIG;
			break;
		case EncoderInternal::WBit::WIG32:
			flags |= Flags::WIG32;
			break;
		default:
			throw InvalidOperationException();
		}
		switch (static_cast<EncodingKind>(encoding))
		{
		case EncodingKind::Legacy:
		{
			const auto& opKinds = EncoderInternal::OpCodeOperandKinds::LegacyOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::Legacy_Op0Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::Legacy_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::Legacy_Op1Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::Legacy_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::Legacy_Op2Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::Legacy_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::Legacy_Op3Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::Legacy_OpMask))];
			auto switchTempVar_4 = static_cast<EncoderInternal::LegacyOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_4 == LegacyOpCodeTable.MAP0) ? (std::uint8_t)OpCodeTableKind.Normal : (switchTempVar_4 == LegacyOpCodeTable.MAP0F) ? (std::uint8_t)OpCodeTableKind.T0F : (switchTempVar_4 == LegacyOpCodeTable.MAP0F38) ? (std::uint8_t)OpCodeTableKind.T0F38 : (switchTempVar_4 == LegacyOpCodeTable.MAP0F3A) ? (std::uint8_t)OpCodeTableKind.T0F3A : throw new InvalidOperationException();
			table = (switchTempVar_4 == EncoderInternal::LegacyOpCodeTable::MAP0) ? static_cast<std::uint8_t>(OpCodeTableKind::Normal) : (switchTempVar_4 == EncoderInternal::LegacyOpCodeTable::MAP0F) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F) : (switchTempVar_4 == EncoderInternal::LegacyOpCodeTable::MAP0F38) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F38) : (switchTempVar_4 == EncoderInternal::LegacyOpCodeTable::MAP0F3A) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F3A) : throw InvalidOperationException();
			break;
		}
		case EncodingKind::VEX:
		{
			const auto& opKinds = EncoderInternal::OpCodeOperandKinds::VexOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::VEX_Op0Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::VEX_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::VEX_Op1Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::VEX_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::VEX_Op2Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::VEX_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::VEX_Op3Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::VEX_OpMask))];
			op4Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::VEX_Op4Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::VEX_OpMask))];
			auto switchTempVar_5 = static_cast<EncoderInternal::VexOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_5 == VexOpCodeTable.MAP0) ? (std::uint8_t)OpCodeTableKind.Normal : (switchTempVar_5 == VexOpCodeTable.MAP0F) ? (std::uint8_t)OpCodeTableKind.T0F : (switchTempVar_5 == VexOpCodeTable.MAP0F38) ? (std::uint8_t)OpCodeTableKind.T0F38 : (switchTempVar_5 == VexOpCodeTable.MAP0F3A) ? (std::uint8_t)OpCodeTableKind.T0F3A : throw new InvalidOperationException();
			table = (switchTempVar_5 == EncoderInternal::VexOpCodeTable::MAP0) ? static_cast<std::uint8_t>(OpCodeTableKind::Normal) : (switchTempVar_5 == EncoderInternal::VexOpCodeTable::MAP0F) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F) : (switchTempVar_5 == EncoderInternal::VexOpCodeTable::MAP0F38) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F38) : (switchTempVar_5 == EncoderInternal::VexOpCodeTable::MAP0F3A) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F3A) : throw InvalidOperationException();
			break;
		}
		case EncodingKind::EVEX:
		{
			const auto& opKinds = EncoderInternal::OpCodeOperandKinds::EvexOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::EVEX_Op0Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::EVEX_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::EVEX_Op1Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::EVEX_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::EVEX_Op2Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::EVEX_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::EVEX_Op3Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::EVEX_OpMask))];
			auto switchTempVar_6 = static_cast<EncoderInternal::EvexOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_6 == EvexOpCodeTable.MAP0F) ? (std::uint8_t)OpCodeTableKind.T0F : (switchTempVar_6 == EvexOpCodeTable.MAP0F38) ? (std::uint8_t)OpCodeTableKind.T0F38 : (switchTempVar_6 == EvexOpCodeTable.MAP0F3A) ? (std::uint8_t)OpCodeTableKind.T0F3A : (switchTempVar_6 == EvexOpCodeTable.MAP5) ? (std::uint8_t)OpCodeTableKind.MAP5 : (switchTempVar_6 == EvexOpCodeTable.MAP6) ? (std::uint8_t)OpCodeTableKind.MAP6 : throw new InvalidOperationException();
			table = (switchTempVar_6 == EncoderInternal::EvexOpCodeTable::MAP0F) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F) : (switchTempVar_6 == EncoderInternal::EvexOpCodeTable::MAP0F38) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F38) : (switchTempVar_6 == EncoderInternal::EvexOpCodeTable::MAP0F3A) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F3A) : (switchTempVar_6 == EncoderInternal::EvexOpCodeTable::MAP5) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP5) : (switchTempVar_6 == EncoderInternal::EvexOpCodeTable::MAP6) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP6) : throw InvalidOperationException();
			break;
		}
		case EncodingKind::XOP:
		{
			const auto& opKinds = EncoderInternal::OpCodeOperandKinds::XopOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::XOP_Op0Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::XOP_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::XOP_Op1Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::XOP_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::XOP_Op2Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::XOP_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::XOP_Op3Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::XOP_OpMask))];
			auto switchTempVar_7 = static_cast<EncoderInternal::XopOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_7 == XopOpCodeTable.MAP8) ? (std::uint8_t)OpCodeTableKind.MAP8 : (switchTempVar_7 == XopOpCodeTable.MAP9) ? (std::uint8_t)OpCodeTableKind.MAP9 : (switchTempVar_7 == XopOpCodeTable.MAP10) ? (std::uint8_t)OpCodeTableKind.MAP10 : throw new InvalidOperationException();
			table = (switchTempVar_7 == EncoderInternal::XopOpCodeTable::MAP8) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP8) : (switchTempVar_7 == EncoderInternal::XopOpCodeTable::MAP9) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP9) : (switchTempVar_7 == EncoderInternal::XopOpCodeTable::MAP10) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP10) : throw InvalidOperationException();
			break;
		}
		case EncodingKind::D3NOW:
			op0Kind = static_cast<std::uint8_t>(OpCodeOperandKind::mm_reg);
			op1Kind = static_cast<std::uint8_t>(OpCodeOperandKind::mm_or_mem);
			table = static_cast<std::uint8_t>(OpCodeTableKind::T0F);
			break;
		case EncodingKind::MVEX:
		{
			const auto& opKinds = EncoderInternal::OpCodeOperandKinds::MvexOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::MVEX_Op0Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::MVEX_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::MVEX_Op1Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::MVEX_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::MVEX_Op2Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::MVEX_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncoderInternal::EncFlags1::MVEX_Op3Shift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags1::MVEX_OpMask))];
			auto switchTempVar_8 = static_cast<EncoderInternal::MvexOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncoderInternal::EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_8 == EncoderInternal::MvexOpCodeTable.MAP0F) ? (std::uint8_t)OpCodeTableKind.T0F : (switchTempVar_8 == EncoderInternal::MvexOpCodeTable.MAP0F38) ? (std::uint8_t)OpCodeTableKind.T0F38 : (switchTempVar_8 == EncoderInternal::MvexOpCodeTable.MAP0F3A) ? (std::uint8_t)OpCodeTableKind.T0F3A : throw new InvalidOperationException();
			table = (switchTempVar_8 == EncoderInternal::MvexOpCodeTable::MAP0F) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F) : (switchTempVar_8 == EncoderInternal::MvexOpCodeTable::MAP0F38) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F38) : (switchTempVar_8 == EncoderInternal::MvexOpCodeTable::MAP0F3A) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F3A) : throw InvalidOperationException();
			break;
		}
		default:
			throw InvalidOperationException();
		}
	}

	constexpr OpCodeInfo::OpCodeInfo(const OpCodeInfo& other)
	{
		if (std::is_constant_evaluated())
		{
			isConstexprConstructed = true;
			toOpCodeStringIndex = other.toOpCodeStringIndex;
			toInstructionStringIndex = other.toInstructionStringIndex;
		}
		else
		{
			isConstexprConstructed = false;
			toOpCodeStringValue = other.toOpCodeStringValue;
			toInstructionStringValue = other.toInstructionStringValue;
		}

		encFlags2 = other.encFlags2;
		encFlags3 = other.encFlags3;
		opcFlags1 = other.opcFlags1;
		opcFlags2 = other.opcFlags2;
		code = other.code;
		encoding = other.encoding;
		operandSize = other.operandSize;
		addressSize = other.addressSize;
		l = other.l;
		tupleType = other.tupleType;
		table = other.table;
		mandatoryPrefix = other.mandatoryPrefix;
		groupIndex = other.groupIndex;
		rmGroupIndex = other.rmGroupIndex;
		op0Kind = other.op0Kind;
		op1Kind = other.op1Kind;
		op2Kind = other.op2Kind;
		op3Kind = other.op3Kind;
		op4Kind = other.op4Kind;
		flags = other.flags;
		lkind = other.lkind;
	}

	constexpr OpCodeInfo::~OpCodeInfo()
	{
		if (!isConstexprConstructed)
		{
			toOpCodeStringValue.~basic_string();
			toInstructionStringValue.~basic_string();
		}
	}
}

namespace Iced::Intel
{
	constexpr ::Iced::Intel::Code OpCodeInfo::GetCode() const
	{
		return static_cast<::Iced::Intel::Code>(code);
	}

	constexpr ::Iced::Intel::Mnemonic OpCodeInfo::GetMnemonic() const
	{
		return ::Iced::Intel::MnemonicUtils::Mnemonic(GetCode());
	}

	constexpr EncodingKind OpCodeInfo::GetEncoding() const
	{
		return static_cast<EncodingKind>(encoding);
	}

	constexpr bool OpCodeInfo::IsInstruction() const
	{
		return code > static_cast<std::uint16_t>(Code::DeclareQword);
	}

	constexpr bool OpCodeInfo::GetMode16() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Bit16or32) != 0;
	}

	constexpr bool OpCodeInfo::GetMode32() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Bit16or32) != 0;
	}

	constexpr bool OpCodeInfo::GetMode64() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Bit64) != 0;
	}

	constexpr bool OpCodeInfo::GetFwait() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Fwait) != 0;
	}

	constexpr std::int32_t OpCodeInfo::GetOperandSize() const
	{
		return operandSize;
	}

	constexpr std::int32_t OpCodeInfo::GetAddressSize() const
	{
		return addressSize;
	}

	constexpr std::uint32_t OpCodeInfo::GetL() const
	{
		return l;
	}

	constexpr std::uint32_t OpCodeInfo::GetW() const
	{
		return (flags & Flags::W) != 0 ? 1U : 0;
	}

	constexpr bool OpCodeInfo::IsLIG() const
	{
		return (flags & Flags::LIG) != 0;
	}

	constexpr bool OpCodeInfo::IsWIG() const
	{
		return (flags & Flags::WIG) != 0;
	}

	constexpr bool OpCodeInfo::IsWIG32() const
	{
		return (flags & Flags::WIG32) != 0;
	}

	constexpr ::Iced::Intel::TupleType OpCodeInfo::GetTupleType() const
	{
		return static_cast<::Iced::Intel::TupleType>(tupleType);
	}

	constexpr ::Iced::Intel::MvexEHBit OpCodeInfo::GetMvexEHBit() const
	{
		return GetEncoding() == EncodingKind::MVEX ? (MvexInfo(GetCode())).GetEHBit() : MvexEHBit::None;
	}

	constexpr bool OpCodeInfo::GetMvexCanUseEvictionHint() const
	{
		return GetEncoding() == EncodingKind::MVEX && (MvexInfo(GetCode())).GetCanUseEvictionHint();
	}

	constexpr bool OpCodeInfo::GetMvexCanUseImmRoundingControl() const
	{
		return GetEncoding() == EncodingKind::MVEX && (MvexInfo(GetCode())).GetCanUseImmRoundingControl();
	}

	constexpr bool OpCodeInfo::GetMvexIgnoresOpMaskRegister() const
	{
		return GetEncoding() == EncodingKind::MVEX && (MvexInfo(GetCode())).GetIgnoresOpMaskRegister();
	}

	constexpr bool OpCodeInfo::GetMvexNoSaeRc() const
	{
		return GetEncoding() == EncodingKind::MVEX && (MvexInfo(GetCode())).GetNoSaeRc();
	}

	constexpr ::Iced::Intel::MvexTupleTypeLutKind OpCodeInfo::GetMvexTupleTypeLutKind() const
	{
		return GetEncoding() == EncodingKind::MVEX ? (MvexInfo(GetCode())).GetTupleTypeLutKind() : MvexTupleTypeLutKind::Int32;
	}

	constexpr MvexConvFn OpCodeInfo::GetMvexConversionFunc() const
	{
		return GetEncoding() == EncodingKind::MVEX ? (MvexInfo(GetCode())).GetConvFn() : MvexConvFn::None;
	}

	constexpr std::uint8_t OpCodeInfo::GetMvexValidConversionFuncsMask() const
	{
		return static_cast<std::uint8_t>(GetEncoding() == EncodingKind::MVEX ? ~(MvexInfo(GetCode())).GetInvalidConvFns() : 0);
	}

	constexpr std::uint8_t OpCodeInfo::GetMvexValidSwizzleFuncsMask() const
	{
		return static_cast<std::uint8_t>(GetEncoding() == EncodingKind::MVEX ? ~(MvexInfo(GetCode())).GetInvalidSwizzleFns() : 0);
	}

	constexpr ::Iced::Intel::MemorySize OpCodeInfo::GetMemorySize() const
	{
		return static_cast<::Iced::Intel::MemorySize>(InstructionMemorySizes::SizesNormal[static_cast<std::int32_t>(code)]);
	}

	constexpr ::Iced::Intel::MemorySize OpCodeInfo::GetBroadcastMemorySize() const
	{
		return static_cast<::Iced::Intel::MemorySize>(InstructionMemorySizes::SizesBcst[static_cast<std::int32_t>(code)]);
	}

	constexpr bool OpCodeInfo::GetCanBroadcast() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Broadcast) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseRoundingControl() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::RoundingControl) != 0;
	}

	constexpr bool OpCodeInfo::GetCanSuppressAllExceptions() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::SuppressAllExceptions) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseOpMaskRegister() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::OpMaskRegister) != 0;
	}

	constexpr bool OpCodeInfo::GetRequireOpMaskRegister() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::RequireOpMaskRegister) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseZeroingMasking() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::ZeroingMasking) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseLockPrefix() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Lock) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseXacquirePrefix() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Xacquire) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseXreleasePrefix() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Xrelease) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseRepPrefix() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Rep) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseRepnePrefix() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Repne) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseBndPrefix() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Bnd) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseHintTakenPrefix() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::HintTaken) != 0;
	}

	constexpr bool OpCodeInfo::GetCanUseNotrackPrefix() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Notrack) != 0;
	}

	constexpr bool OpCodeInfo::GetIgnoresRoundingControl() const
	{
		return (flags & Flags::IgnoresRoundingControl) != 0;
	}

	constexpr bool OpCodeInfo::GetAmdLockRegBit() const
	{
		return (flags & Flags::AmdLockRegBit) != 0;
	}

	constexpr bool OpCodeInfo::GetDefaultOpSize64() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::DefaultOpSize64) != 0;
	}

	constexpr bool OpCodeInfo::GetForceOpSize64() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::ForceOpSize64) != 0;
	}

	constexpr bool OpCodeInfo::GetIntelForceOpSize64() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::IntelForceOpSize64) != 0;
	}

	constexpr bool OpCodeInfo::GetMustBeCpl0() const
	{
		return (flags & (Flags::CPL0 | Flags::CPL1 | Flags::CPL2 | Flags::CPL3)) == Flags::CPL0;
	}

	constexpr bool OpCodeInfo::GetCpl0() const
	{
		return (flags & Flags::CPL0) != 0;
	}

	constexpr bool OpCodeInfo::GetCpl1() const
	{
		return (flags & Flags::CPL1) != 0;
	}

	constexpr bool OpCodeInfo::GetCpl2() const
	{
		return (flags & Flags::CPL2) != 0;
	}

	constexpr bool OpCodeInfo::GetCpl3() const
	{
		return (flags & Flags::CPL3) != 0;
	}

	constexpr bool OpCodeInfo::IsInputOutput() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::InputOutput) != 0;
	}

	constexpr bool OpCodeInfo::IsNop() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::Nop) != 0;
	}

	constexpr bool OpCodeInfo::IsReservedNop() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::ReservedNop) != 0;
	}

	constexpr bool OpCodeInfo::IsSerializingIntel() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::SerializingIntel) != 0;
	}

	constexpr bool OpCodeInfo::IsSerializingAmd() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::SerializingAmd) != 0;
	}

	constexpr bool OpCodeInfo::GetMayRequireCpl0() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::MayRequireCpl0) != 0;
	}

	constexpr bool OpCodeInfo::IsCetTracked() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::CetTracked) != 0;
	}

	constexpr bool OpCodeInfo::IsNonTemporal() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::NonTemporal) != 0;
	}

	constexpr bool OpCodeInfo::IsFpuNoWait() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::FpuNoWait) != 0;
	}

	constexpr bool OpCodeInfo::GetIgnoresModBits() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::IgnoresModBits) != 0;
	}

	constexpr bool OpCodeInfo::GetNo66() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::No66) != 0;
	}

	constexpr bool OpCodeInfo::GetNFx() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::NFx) != 0;
	}

	constexpr bool OpCodeInfo::GetRequiresUniqueRegNums() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::RequiresUniqueRegNums) != 0;
	}

	constexpr bool OpCodeInfo::GetRequiresUniqueDestRegNum() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::RequiresUniqueDestRegNum) != 0;
	}

	constexpr bool OpCodeInfo::IsPrivileged() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::Privileged) != 0;
	}

	constexpr bool OpCodeInfo::IsSaveRestore() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::SaveRestore) != 0;
	}

	constexpr bool OpCodeInfo::IsStackInstruction() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::StackInstruction) != 0;
	}

	constexpr bool OpCodeInfo::GetIgnoresSegment() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::IgnoresSegment) != 0;
	}

	constexpr bool OpCodeInfo::IsOpMaskReadWrite() const
	{
		return (opcFlags1 & EncoderInternal::OpCodeInfoFlags1::OpMaskReadWrite) != 0;
	}

	constexpr bool OpCodeInfo::GetRealMode() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::RealMode) != 0;
	}

	constexpr bool OpCodeInfo::GetProtectedMode() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::ProtectedMode) != 0;
	}

	constexpr bool OpCodeInfo::GetVirtual8086Mode() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::Virtual8086Mode) != 0;
	}

	constexpr bool OpCodeInfo::GetCompatibilityMode() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::CompatibilityMode) != 0;
	}

	constexpr bool OpCodeInfo::GetLongMode() const
	{
		return (encFlags3 & EncoderInternal::EncFlags3::Bit64) != 0;
	}

	constexpr bool OpCodeInfo::GetUseOutsideSmm() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseOutsideSmm) != 0;
	}

	constexpr bool OpCodeInfo::GetUseInSmm() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseInSmm) != 0;
	}

	constexpr bool OpCodeInfo::GetUseOutsideEnclaveSgx() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseOutsideEnclaveSgx) != 0;
	}

	constexpr bool OpCodeInfo::GetUseInEnclaveSgx1() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseInEnclaveSgx1) != 0;
	}

	constexpr bool OpCodeInfo::GetUseInEnclaveSgx2() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseInEnclaveSgx2) != 0;
	}

	constexpr bool OpCodeInfo::GetUseOutsideVmxOp() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseOutsideVmxOp) != 0;
	}

	constexpr bool OpCodeInfo::GetUseInVmxRootOp() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseInVmxRootOp) != 0;
	}

	constexpr bool OpCodeInfo::GetUseInVmxNonRootOp() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseInVmxNonRootOp) != 0;
	}

	constexpr bool OpCodeInfo::GetUseOutsideSeam() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseOutsideSeam) != 0;
	}

	constexpr bool OpCodeInfo::GetUseInSeam() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::UseInSeam) != 0;
	}

	constexpr bool OpCodeInfo::GetTdxNonRootGenUd() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::TdxNonRootGenUd) != 0;
	}

	constexpr bool OpCodeInfo::GetTdxNonRootGenVe() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::TdxNonRootGenVe) != 0;
	}

	constexpr bool OpCodeInfo::GetTdxNonRootMayGenEx() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::TdxNonRootMayGenEx) != 0;
	}

	constexpr bool OpCodeInfo::GetIntelVmExit() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::IntelVmExit) != 0;
	}

	constexpr bool OpCodeInfo::GetIntelMayVmExit() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::IntelMayVmExit) != 0;
	}

	constexpr bool OpCodeInfo::GetIntelSmmVmExit() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::IntelSmmVmExit) != 0;
	}

	constexpr bool OpCodeInfo::GetAmdVmExit() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::AmdVmExit) != 0;
	}

	constexpr bool OpCodeInfo::GetAmdMayVmExit() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::AmdMayVmExit) != 0;
	}

	constexpr bool OpCodeInfo::GetTsxAbort() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::TsxAbort) != 0;
	}

	constexpr bool OpCodeInfo::GetTsxImplAbort() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::TsxImplAbort) != 0;
	}

	constexpr bool OpCodeInfo::GetTsxMayAbort() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::TsxMayAbort) != 0;
	}

	constexpr bool OpCodeInfo::GetIntelDecoder16() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::IntelDecoder16or32) != 0;
	}

	constexpr bool OpCodeInfo::GetIntelDecoder32() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::IntelDecoder16or32) != 0;
	}

	constexpr bool OpCodeInfo::GetIntelDecoder64() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::IntelDecoder64) != 0;
	}

	constexpr bool OpCodeInfo::GetAmdDecoder16() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::AmdDecoder16or32) != 0;
	}

	constexpr bool OpCodeInfo::GetAmdDecoder32() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::AmdDecoder16or32) != 0;
	}

	constexpr bool OpCodeInfo::GetAmdDecoder64() const
	{
		return (opcFlags2 & EncoderInternal::OpCodeInfoFlags2::AmdDecoder64) != 0;
	}

	constexpr DecoderOptions OpCodeInfo::GetDecoderOption() const
	{
		return toDecoderOptions[static_cast<std::int32_t>((static_cast<std::uint32_t>(opcFlags1) >> static_cast<std::int32_t>(EncoderInternal::OpCodeInfoFlags1::DecOptionValueShift)) & static_cast<std::uint32_t>(EncoderInternal::OpCodeInfoFlags1::DecOptionValueMask))];
	}

	constexpr OpCodeTableKind OpCodeInfo::GetTable() const
	{
		return static_cast<OpCodeTableKind>(table);
	}

	constexpr ::Iced::Intel::MandatoryPrefix OpCodeInfo::GetMandatoryPrefix() const
	{
		return static_cast<::Iced::Intel::MandatoryPrefix>(mandatoryPrefix);
	}

	constexpr std::uint32_t OpCodeInfo::GetOpCode() const
	{
		return static_cast<std::uint16_t>(static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncoderInternal::EncFlags2::OpCodeShift));
	}

	constexpr std::int32_t OpCodeInfo::GetOpCodeLength() const
	{
		return (encFlags2 & EncoderInternal::EncFlags2::OpCodeIs2Bytes) != 0 ? 2 : 1;
	}

	constexpr bool OpCodeInfo::IsGroup() const
	{
		return GetGroupIndex() >= 0;
	}

	constexpr std::int32_t OpCodeInfo::GetGroupIndex() const
	{
		return groupIndex;
	}

	constexpr bool OpCodeInfo::IsRmGroup() const
	{
		return GetRmGroupIndex() >= 0;
	}

	constexpr std::int32_t OpCodeInfo::GetRmGroupIndex() const
	{
		return rmGroupIndex;
	}

	constexpr std::int32_t OpCodeInfo::GetOpCount() const
	{
		return InstructionOpCounts::OpCount[code];
	}

	constexpr OpCodeOperandKind OpCodeInfo::GetOp0Kind() const
	{
		return static_cast<OpCodeOperandKind>(op0Kind);
	}

	constexpr OpCodeOperandKind OpCodeInfo::GetOp1Kind() const
	{
		return static_cast<OpCodeOperandKind>(op1Kind);
	}

	constexpr OpCodeOperandKind OpCodeInfo::GetOp2Kind() const
	{
		return static_cast<OpCodeOperandKind>(op2Kind);
	}

	constexpr OpCodeOperandKind OpCodeInfo::GetOp3Kind() const
	{
		return static_cast<OpCodeOperandKind>(op3Kind);
	}

	constexpr OpCodeOperandKind OpCodeInfo::GetOp4Kind() const
	{
		return static_cast<OpCodeOperandKind>(op4Kind);
	}

	constexpr OpCodeOperandKind OpCodeInfo::GetOpKind(std::int32_t operand) const
	{
		auto switchTempVar_9 = operand;

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_9 == 0) ? Op0Kind : (switchTempVar_9 == 1) ? Op1Kind : (switchTempVar_9 == 2) ? Op2Kind : (switchTempVar_9 == 3) ? Op3Kind : (switchTempVar_9 == 4) ? Op4Kind : throw new ArgumentOutOfRangeException(nameof(operand));
		return (switchTempVar_9 == 0) ? GetOp0Kind() : (switchTempVar_9 == 1) ? GetOp1Kind() : (switchTempVar_9 == 2) ? GetOp2Kind() : (switchTempVar_9 == 3) ? GetOp3Kind() : (switchTempVar_9 == 4) ? GetOp4Kind() : throw ArgumentOutOfRangeException("operand");
	}

	constexpr bool OpCodeInfo::IsAvailableInMode(std::int32_t bitness) const
	{
		auto switchTempVar_10 = bitness;

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_10 == 16) ? Mode16 : (switchTempVar_10 == 32) ? Mode32 : (switchTempVar_10 == 64) ? Mode64 : throw new ArgumentOutOfRangeException(nameof(bitness));
		return (switchTempVar_10 == 16) ? GetMode16() : (switchTempVar_10 == 32) ? GetMode32() : (switchTempVar_10 == 64) ? GetMode64() : throw std::invalid_argument("invalid bitness");
	}
}

#include "EncoderInternal/InstructionFormatter.h"
#include "EncoderInternal/OpCodeFormatter.h"