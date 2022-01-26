// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#if defined(ENCODER) && defined(OPCODE_INFO)
#pragma once
#include <cstdint>
#include "../ToString.h"

namespace Iced::Intel::EncoderInternal
{
	// GENERATOR-BEGIN: OpCodeInfoFlags1
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	enum class OpCodeInfoFlags1 : std::uint32_t {
		None  = 0x00000000,
		Cpl0Only  = 0x00000001,
		Cpl3Only  = 0x00000002,
		InputOutput  = 0x00000004,
		Nop  = 0x00000008,
		ReservedNop  = 0x00000010,
		SerializingIntel  = 0x00000020,
		SerializingAmd  = 0x00000040,
		MayRequireCpl0  = 0x00000080,
		CetTracked  = 0x00000100,
		NonTemporal  = 0x00000200,
		FpuNoWait  = 0x00000400,
		IgnoresModBits  = 0x00000800,
		No66  = 0x00001000,
		NFx  = 0x00002000,
		RequiresUniqueRegNums  = 0x00004000,
		Privileged  = 0x00008000,
		SaveRestore  = 0x00010000,
		StackInstruction  = 0x00020000,
		IgnoresSegment  = 0x00040000,
		OpMaskReadWrite  = 0x00080000,
		ModRegRmString  = 0x00100000,
		DecOptionValueMask  = 0x0000001F,
		DecOptionValueShift  = 0x00000015,
		ForceOpSize64  = 0x40000000,
		RequiresUniqueDestRegNum  = 0x80000000,
	};
	constexpr OpCodeInfoFlags1& operator^=(OpCodeInfoFlags1& a, const OpCodeInfoFlags1& b) { return a = (OpCodeInfoFlags1)((std::uint32_t)a ^ (std::uint32_t)b); }
	constexpr OpCodeInfoFlags1 operator^(const OpCodeInfoFlags1& a, const OpCodeInfoFlags1& b) { return (OpCodeInfoFlags1)((std::uint32_t)a ^ (std::uint32_t)b); }
	constexpr OpCodeInfoFlags1& operator|=(OpCodeInfoFlags1& a, const OpCodeInfoFlags1& b) { return a = (OpCodeInfoFlags1)((std::uint32_t)a | (std::uint32_t)b); }
	constexpr OpCodeInfoFlags1 operator|(const OpCodeInfoFlags1& a, const OpCodeInfoFlags1& b) { return (OpCodeInfoFlags1)((std::uint32_t)a | (std::uint32_t)b); }
	constexpr OpCodeInfoFlags1& operator&=(OpCodeInfoFlags1& a, const OpCodeInfoFlags1& b) { return a = (OpCodeInfoFlags1)((std::uint32_t)a & (std::uint32_t)b); }
	constexpr OpCodeInfoFlags1 operator&(const OpCodeInfoFlags1& a, const OpCodeInfoFlags1& b) { return (OpCodeInfoFlags1)((std::uint32_t)a & (std::uint32_t)b); }
	constexpr OpCodeInfoFlags1 operator~(const OpCodeInfoFlags1& a) { return (OpCodeInfoFlags1)(~((std::uint32_t)a)); }
	constexpr std::uint32_t operator+(const OpCodeInfoFlags1& a, const OpCodeInfoFlags1& b) { return ((std::uint32_t)a + (std::uint32_t)b); }
	constexpr std::uint32_t operator+(const OpCodeInfoFlags1& a, const std::uint32_t& b) { return ((std::uint32_t)a + b); }
	constexpr std::uint32_t operator+(const std::uint32_t& a, const OpCodeInfoFlags1& b) { return (a + (std::uint32_t)b); }
	constexpr std::uint32_t operator-(const OpCodeInfoFlags1& a, const OpCodeInfoFlags1& b) { return ((std::uint32_t)a - (std::uint32_t)b); }
	constexpr std::uint32_t operator-(const OpCodeInfoFlags1& a, const std::uint32_t& b) { return ((std::uint32_t)a - b); }
	constexpr std::uint32_t operator-(const std::uint32_t& a, const OpCodeInfoFlags1& b) { return (a - (std::uint32_t)b); }
	constexpr OpCodeInfoFlags1 operator++(OpCodeInfoFlags1& a, int) { auto temp = a; a = OpCodeInfoFlags1(a + 1); return temp; }
	constexpr OpCodeInfoFlags1& operator++(OpCodeInfoFlags1& a) { return a = OpCodeInfoFlags1(a + 1); }
	constexpr OpCodeInfoFlags1 operator--(OpCodeInfoFlags1& a, int) { auto temp = a; a = OpCodeInfoFlags1(a - 1); return temp; }
	constexpr OpCodeInfoFlags1& operator--(OpCodeInfoFlags1& a) { return a = OpCodeInfoFlags1(a - 1); }
	constexpr bool operator==(const OpCodeInfoFlags1& a, const std::uint32_t& b) { return ((std::uint32_t)a == b); }
	constexpr bool operator==(const std::uint32_t& a, const OpCodeInfoFlags1& b) { return (a == (std::uint32_t)b); }
	constexpr bool operator>=(const OpCodeInfoFlags1& a, const std::uint32_t& b) { return ((std::uint32_t)a >= b); }
	constexpr bool operator>=(const std::uint32_t& a, const OpCodeInfoFlags1& b) { return (a >= (std::uint32_t)b); }
	constexpr bool operator<=(const OpCodeInfoFlags1& a, const std::uint32_t& b) { return ((std::uint32_t)a <= b); }
	constexpr bool operator<=(const std::uint32_t& a, const OpCodeInfoFlags1& b) { return (a <= (std::uint32_t)b); }
	constexpr bool operator>(const OpCodeInfoFlags1& a, const std::uint32_t& b) { return ((std::uint32_t)a > b); }
	constexpr bool operator>(const std::uint32_t& a, const OpCodeInfoFlags1& b) { return (a > (std::uint32_t)b); }
	constexpr bool operator<(const OpCodeInfoFlags1& a, const std::uint32_t& b) { return ((std::uint32_t)a < b); }
	constexpr bool operator<(const std::uint32_t& a, const OpCodeInfoFlags1& b) { return (a < (std::uint32_t)b); }
	constexpr bool operator!=(const OpCodeInfoFlags1& a, const std::uint32_t& b) { return ((std::uint32_t)a != b); }
	constexpr bool operator!=(const std::uint32_t& a, const OpCodeInfoFlags1& b) { return (a != (std::uint32_t)b); }
	// GENERATOR-END: OpCodeInfoFlags1
	// GENERATOR-BEGIN: OpCodeInfoFlags2
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	enum class OpCodeInfoFlags2 : std::uint32_t {
		None  = 0x00000000,
		RealMode  = 0x00000001,
		ProtectedMode  = 0x00000002,
		Virtual8086Mode  = 0x00000004,
		CompatibilityMode  = 0x00000008,
		UseOutsideSmm  = 0x00000010,
		UseInSmm  = 0x00000020,
		UseOutsideEnclaveSgx  = 0x00000040,
		UseInEnclaveSgx1  = 0x00000080,
		UseInEnclaveSgx2  = 0x00000100,
		UseOutsideVmxOp  = 0x00000200,
		UseInVmxRootOp  = 0x00000400,
		UseInVmxNonRootOp  = 0x00000800,
		UseOutsideSeam  = 0x00001000,
		UseInSeam  = 0x00002000,
		TdxNonRootGenUd  = 0x00004000,
		TdxNonRootGenVe  = 0x00008000,
		TdxNonRootMayGenEx  = 0x00010000,
		IntelVmExit  = 0x00020000,
		IntelMayVmExit  = 0x00040000,
		IntelSmmVmExit  = 0x00080000,
		AmdVmExit  = 0x00100000,
		AmdMayVmExit  = 0x00200000,
		TsxAbort  = 0x00400000,
		TsxImplAbort  = 0x00800000,
		TsxMayAbort  = 0x01000000,
		IntelDecoder16or32  = 0x02000000,
		IntelDecoder64  = 0x04000000,
		AmdDecoder16or32  = 0x08000000,
		AmdDecoder64  = 0x10000000,
		InstrStrFmtOptionMask  = 0x00000007,
		InstrStrFmtOptionShift  = 0x0000001D,
	};
	constexpr OpCodeInfoFlags2& operator^=(OpCodeInfoFlags2& a, const OpCodeInfoFlags2& b) { return a = (OpCodeInfoFlags2)((std::uint32_t)a ^ (std::uint32_t)b); }
	constexpr OpCodeInfoFlags2 operator^(const OpCodeInfoFlags2& a, const OpCodeInfoFlags2& b) { return (OpCodeInfoFlags2)((std::uint32_t)a ^ (std::uint32_t)b); }
	constexpr OpCodeInfoFlags2& operator|=(OpCodeInfoFlags2& a, const OpCodeInfoFlags2& b) { return a = (OpCodeInfoFlags2)((std::uint32_t)a | (std::uint32_t)b); }
	constexpr OpCodeInfoFlags2 operator|(const OpCodeInfoFlags2& a, const OpCodeInfoFlags2& b) { return (OpCodeInfoFlags2)((std::uint32_t)a | (std::uint32_t)b); }
	constexpr OpCodeInfoFlags2& operator&=(OpCodeInfoFlags2& a, const OpCodeInfoFlags2& b) { return a = (OpCodeInfoFlags2)((std::uint32_t)a & (std::uint32_t)b); }
	constexpr OpCodeInfoFlags2 operator&(const OpCodeInfoFlags2& a, const OpCodeInfoFlags2& b) { return (OpCodeInfoFlags2)((std::uint32_t)a & (std::uint32_t)b); }
	constexpr OpCodeInfoFlags2 operator~(const OpCodeInfoFlags2& a) { return (OpCodeInfoFlags2)(~((std::uint32_t)a)); }
	constexpr std::uint32_t operator+(const OpCodeInfoFlags2& a, const OpCodeInfoFlags2& b) { return ((std::uint32_t)a + (std::uint32_t)b); }
	constexpr std::uint32_t operator+(const OpCodeInfoFlags2& a, const std::uint32_t& b) { return ((std::uint32_t)a + b); }
	constexpr std::uint32_t operator+(const std::uint32_t& a, const OpCodeInfoFlags2& b) { return (a + (std::uint32_t)b); }
	constexpr std::uint32_t operator-(const OpCodeInfoFlags2& a, const OpCodeInfoFlags2& b) { return ((std::uint32_t)a - (std::uint32_t)b); }
	constexpr std::uint32_t operator-(const OpCodeInfoFlags2& a, const std::uint32_t& b) { return ((std::uint32_t)a - b); }
	constexpr std::uint32_t operator-(const std::uint32_t& a, const OpCodeInfoFlags2& b) { return (a - (std::uint32_t)b); }
	constexpr OpCodeInfoFlags2 operator++(OpCodeInfoFlags2& a, int) { auto temp = a; a = OpCodeInfoFlags2(a + 1); return temp; }
	constexpr OpCodeInfoFlags2& operator++(OpCodeInfoFlags2& a) { return a = OpCodeInfoFlags2(a + 1); }
	constexpr OpCodeInfoFlags2 operator--(OpCodeInfoFlags2& a, int) { auto temp = a; a = OpCodeInfoFlags2(a - 1); return temp; }
	constexpr OpCodeInfoFlags2& operator--(OpCodeInfoFlags2& a) { return a = OpCodeInfoFlags2(a - 1); }
	constexpr bool operator==(const OpCodeInfoFlags2& a, const std::uint32_t& b) { return ((std::uint32_t)a == b); }
	constexpr bool operator==(const std::uint32_t& a, const OpCodeInfoFlags2& b) { return (a == (std::uint32_t)b); }
	constexpr bool operator>=(const OpCodeInfoFlags2& a, const std::uint32_t& b) { return ((std::uint32_t)a >= b); }
	constexpr bool operator>=(const std::uint32_t& a, const OpCodeInfoFlags2& b) { return (a >= (std::uint32_t)b); }
	constexpr bool operator<=(const OpCodeInfoFlags2& a, const std::uint32_t& b) { return ((std::uint32_t)a <= b); }
	constexpr bool operator<=(const std::uint32_t& a, const OpCodeInfoFlags2& b) { return (a <= (std::uint32_t)b); }
	constexpr bool operator>(const OpCodeInfoFlags2& a, const std::uint32_t& b) { return ((std::uint32_t)a > b); }
	constexpr bool operator>(const std::uint32_t& a, const OpCodeInfoFlags2& b) { return (a > (std::uint32_t)b); }
	constexpr bool operator<(const OpCodeInfoFlags2& a, const std::uint32_t& b) { return ((std::uint32_t)a < b); }
	constexpr bool operator<(const std::uint32_t& a, const OpCodeInfoFlags2& b) { return (a < (std::uint32_t)b); }
	constexpr bool operator!=(const OpCodeInfoFlags2& a, const std::uint32_t& b) { return ((std::uint32_t)a != b); }
	constexpr bool operator!=(const std::uint32_t& a, const OpCodeInfoFlags2& b) { return (a != (std::uint32_t)b); }
	// GENERATOR-END: OpCodeInfoFlags2
	// GENERATOR-BEGIN: InstrStrFmtOption
	// ⚠️This was generated by GENERATOR!🦹‍♂️
	enum class InstrStrFmtOption {
		None ,
		OpMaskIsK1_or_NoGprSuffix ,
		IncVecIndex ,
		NoVecIndex ,
		SwapVecIndex12 ,
		SkipOp0 ,
		VecIndexSameAsOpIndex ,
	};
	constexpr int operator+(const InstrStrFmtOption& a, const InstrStrFmtOption& b) { return ((int)a + (int)b); }
	constexpr int operator+(const InstrStrFmtOption& a, const int& b) { return ((int)a + b); }
	constexpr int operator+(const int& a, const InstrStrFmtOption& b) { return (a + (int)b); }
	constexpr int operator-(const InstrStrFmtOption& a, const InstrStrFmtOption& b) { return ((int)a - (int)b); }
	constexpr int operator-(const InstrStrFmtOption& a, const int& b) { return ((int)a - b); }
	constexpr int operator-(const int& a, const InstrStrFmtOption& b) { return (a - (int)b); }
	constexpr InstrStrFmtOption operator++(InstrStrFmtOption& a, int) { auto temp = a; a = InstrStrFmtOption(a + 1); return temp; }
	constexpr InstrStrFmtOption& operator++(InstrStrFmtOption& a) { return a = InstrStrFmtOption(a + 1); }
	constexpr InstrStrFmtOption operator--(InstrStrFmtOption& a, int) { auto temp = a; a = InstrStrFmtOption(a - 1); return temp; }
	constexpr InstrStrFmtOption& operator--(InstrStrFmtOption& a) { return a = InstrStrFmtOption(a - 1); }
	constexpr bool operator==(const InstrStrFmtOption& a, const int& b) { return ((int)a == b); }
	constexpr bool operator==(const int& a, const InstrStrFmtOption& b) { return (a == (int)b); }
	constexpr bool operator>=(const InstrStrFmtOption& a, const int& b) { return ((int)a >= b); }
	constexpr bool operator>=(const int& a, const InstrStrFmtOption& b) { return (a >= (int)b); }
	constexpr bool operator<=(const InstrStrFmtOption& a, const int& b) { return ((int)a <= b); }
	constexpr bool operator<=(const int& a, const InstrStrFmtOption& b) { return (a <= (int)b); }
	constexpr bool operator>(const InstrStrFmtOption& a, const int& b) { return ((int)a > b); }
	constexpr bool operator>(const int& a, const InstrStrFmtOption& b) { return (a > (int)b); }
	constexpr bool operator<(const InstrStrFmtOption& a, const int& b) { return ((int)a < b); }
	constexpr bool operator<(const int& a, const InstrStrFmtOption& b) { return (a < (int)b); }
	constexpr bool operator!=(const InstrStrFmtOption& a, const int& b) { return ((int)a != b); }
	constexpr bool operator!=(const int& a, const InstrStrFmtOption& b) { return (a != (int)b); }
	// GENERATOR-END: InstrStrFmtOption
}
#endif
