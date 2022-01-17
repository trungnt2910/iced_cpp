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

#include "Iced.Intel.AssemblerRegister8.h"
#include "Iced.Intel.AssemblerRegister16.h"
#include "Iced.Intel.AssemblerRegister32.h"
#include "Iced.Intel.AssemblerRegister64.h"
#include "Iced.Intel.AssemblerRegisterSegment.h"
#include "Iced.Intel.AssemblerRegisterST.h"
#include "Iced.Intel.AssemblerRegisterCR.h"
#include "Iced.Intel.AssemblerRegisterDR.h"
#include "Iced.Intel.AssemblerRegisterTR.h"
#include "Iced.Intel.AssemblerRegisterBND.h"
#include "Iced.Intel.AssemblerRegisterK.h"
#include "Iced.Intel.AssemblerRegisterMM.h"
#include "Iced.Intel.AssemblerRegisterXMM.h"
#include "Iced.Intel.AssemblerRegisterYMM.h"
#include "Iced.Intel.AssemblerRegisterZMM.h"
#include "Iced.Intel.AssemblerRegisterTMM.h"
#include "Iced.Intel.AssemblerMemoryOperandFactory.h"

#include <concepts>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
// ⚠️This file was generated by GENERATOR!🦹‍♂️
namespace Iced::Intel
{
	/// <summary>
	/// Registers used for <see cref="Assembler"/>. 
	/// </summary>
	namespace AssemblerRegisters
	{
		extern AssemblerRegister8 al;
		extern AssemblerRegister8 cl;
		extern AssemblerRegister8 dl;
		extern AssemblerRegister8 bl;
		extern AssemblerRegister8 ah;
		extern AssemblerRegister8 ch;
		extern AssemblerRegister8 dh;
		extern AssemblerRegister8 bh;
		extern AssemblerRegister8 spl;
		extern AssemblerRegister8 bpl;
		extern AssemblerRegister8 sil;
		extern AssemblerRegister8 dil;
		extern AssemblerRegister8 r8b;
		extern AssemblerRegister8 r9b;
		extern AssemblerRegister8 r10b;
		extern AssemblerRegister8 r11b;
		extern AssemblerRegister8 r12b;
		extern AssemblerRegister8 r13b;
		extern AssemblerRegister8 r14b;
		extern AssemblerRegister8 r15b;
		extern AssemblerRegister16 ax;
		extern AssemblerRegister16 cx;
		extern AssemblerRegister16 dx;
		extern AssemblerRegister16 bx;
		extern AssemblerRegister16 sp;
		extern AssemblerRegister16 bp;
		extern AssemblerRegister16 si;
		extern AssemblerRegister16 di;
		extern AssemblerRegister16 r8w;
		extern AssemblerRegister16 r9w;
		extern AssemblerRegister16 r10w;
		extern AssemblerRegister16 r11w;
		extern AssemblerRegister16 r12w;
		extern AssemblerRegister16 r13w;
		extern AssemblerRegister16 r14w;
		extern AssemblerRegister16 r15w;
		extern AssemblerRegister32 eax;
		extern AssemblerRegister32 ecx;
		extern AssemblerRegister32 edx;
		extern AssemblerRegister32 ebx;
		extern AssemblerRegister32 esp;
		extern AssemblerRegister32 ebp;
		extern AssemblerRegister32 esi;
		extern AssemblerRegister32 edi;
		extern AssemblerRegister32 r8d;
		extern AssemblerRegister32 r9d;
		extern AssemblerRegister32 r10d;
		extern AssemblerRegister32 r11d;
		extern AssemblerRegister32 r12d;
		extern AssemblerRegister32 r13d;
		extern AssemblerRegister32 r14d;
		extern AssemblerRegister32 r15d;
		extern AssemblerRegister64 rax;
		extern AssemblerRegister64 rcx;
		extern AssemblerRegister64 rdx;
		extern AssemblerRegister64 rbx;
		extern AssemblerRegister64 rsp;
		extern AssemblerRegister64 rbp;
		extern AssemblerRegister64 rsi;
		extern AssemblerRegister64 rdi;
		extern AssemblerRegister64 r8;
		extern AssemblerRegister64 r9;
		extern AssemblerRegister64 r10;
		extern AssemblerRegister64 r11;
		extern AssemblerRegister64 r12;
		extern AssemblerRegister64 r13;
		extern AssemblerRegister64 r14;
		extern AssemblerRegister64 r15;
		extern AssemblerRegisterSegment es;
		extern AssemblerRegisterSegment cs;
		extern AssemblerRegisterSegment ss;
		extern AssemblerRegisterSegment ds;
		extern AssemblerRegisterSegment fs;
		extern AssemblerRegisterSegment gs;
		extern AssemblerRegisterST st0;
		extern AssemblerRegisterST st1;
		extern AssemblerRegisterST st2;
		extern AssemblerRegisterST st3;
		extern AssemblerRegisterST st4;
		extern AssemblerRegisterST st5;
		extern AssemblerRegisterST st6;
		extern AssemblerRegisterST st7;
		extern AssemblerRegisterCR cr0;
		extern AssemblerRegisterCR cr1;
		extern AssemblerRegisterCR cr2;
		extern AssemblerRegisterCR cr3;
		extern AssemblerRegisterCR cr4;
		extern AssemblerRegisterCR cr5;
		extern AssemblerRegisterCR cr6;
		extern AssemblerRegisterCR cr7;
		extern AssemblerRegisterCR cr8;
		extern AssemblerRegisterCR cr9;
		extern AssemblerRegisterCR cr10;
		extern AssemblerRegisterCR cr11;
		extern AssemblerRegisterCR cr12;
		extern AssemblerRegisterCR cr13;
		extern AssemblerRegisterCR cr14;
		extern AssemblerRegisterCR cr15;
		extern AssemblerRegisterDR dr0;
		extern AssemblerRegisterDR dr1;
		extern AssemblerRegisterDR dr2;
		extern AssemblerRegisterDR dr3;
		extern AssemblerRegisterDR dr4;
		extern AssemblerRegisterDR dr5;
		extern AssemblerRegisterDR dr6;
		extern AssemblerRegisterDR dr7;
		extern AssemblerRegisterDR dr8;
		extern AssemblerRegisterDR dr9;
		extern AssemblerRegisterDR dr10;
		extern AssemblerRegisterDR dr11;
		extern AssemblerRegisterDR dr12;
		extern AssemblerRegisterDR dr13;
		extern AssemblerRegisterDR dr14;
		extern AssemblerRegisterDR dr15;
		extern AssemblerRegisterTR tr0;
		extern AssemblerRegisterTR tr1;
		extern AssemblerRegisterTR tr2;
		extern AssemblerRegisterTR tr3;
		extern AssemblerRegisterTR tr4;
		extern AssemblerRegisterTR tr5;
		extern AssemblerRegisterTR tr6;
		extern AssemblerRegisterTR tr7;
		extern AssemblerRegisterBND bnd0;
		extern AssemblerRegisterBND bnd1;
		extern AssemblerRegisterBND bnd2;
		extern AssemblerRegisterBND bnd3;
		extern AssemblerRegisterK k0;
		extern AssemblerRegisterK k1;
		extern AssemblerRegisterK k2;
		extern AssemblerRegisterK k3;
		extern AssemblerRegisterK k4;
		extern AssemblerRegisterK k5;
		extern AssemblerRegisterK k6;
		extern AssemblerRegisterK k7;
		extern AssemblerRegisterMM mm0;
		extern AssemblerRegisterMM mm1;
		extern AssemblerRegisterMM mm2;
		extern AssemblerRegisterMM mm3;
		extern AssemblerRegisterMM mm4;
		extern AssemblerRegisterMM mm5;
		extern AssemblerRegisterMM mm6;
		extern AssemblerRegisterMM mm7;
		extern AssemblerRegisterXMM xmm0;
		extern AssemblerRegisterXMM xmm1;
		extern AssemblerRegisterXMM xmm2;
		extern AssemblerRegisterXMM xmm3;
		extern AssemblerRegisterXMM xmm4;
		extern AssemblerRegisterXMM xmm5;
		extern AssemblerRegisterXMM xmm6;
		extern AssemblerRegisterXMM xmm7;
		extern AssemblerRegisterXMM xmm8;
		extern AssemblerRegisterXMM xmm9;
		extern AssemblerRegisterXMM xmm10;
		extern AssemblerRegisterXMM xmm11;
		extern AssemblerRegisterXMM xmm12;
		extern AssemblerRegisterXMM xmm13;
		extern AssemblerRegisterXMM xmm14;
		extern AssemblerRegisterXMM xmm15;
		extern AssemblerRegisterXMM xmm16;
		extern AssemblerRegisterXMM xmm17;
		extern AssemblerRegisterXMM xmm18;
		extern AssemblerRegisterXMM xmm19;
		extern AssemblerRegisterXMM xmm20;
		extern AssemblerRegisterXMM xmm21;
		extern AssemblerRegisterXMM xmm22;
		extern AssemblerRegisterXMM xmm23;
		extern AssemblerRegisterXMM xmm24;
		extern AssemblerRegisterXMM xmm25;
		extern AssemblerRegisterXMM xmm26;
		extern AssemblerRegisterXMM xmm27;
		extern AssemblerRegisterXMM xmm28;
		extern AssemblerRegisterXMM xmm29;
		extern AssemblerRegisterXMM xmm30;
		extern AssemblerRegisterXMM xmm31;
		extern AssemblerRegisterYMM ymm0;
		extern AssemblerRegisterYMM ymm1;
		extern AssemblerRegisterYMM ymm2;
		extern AssemblerRegisterYMM ymm3;
		extern AssemblerRegisterYMM ymm4;
		extern AssemblerRegisterYMM ymm5;
		extern AssemblerRegisterYMM ymm6;
		extern AssemblerRegisterYMM ymm7;
		extern AssemblerRegisterYMM ymm8;
		extern AssemblerRegisterYMM ymm9;
		extern AssemblerRegisterYMM ymm10;
		extern AssemblerRegisterYMM ymm11;
		extern AssemblerRegisterYMM ymm12;
		extern AssemblerRegisterYMM ymm13;
		extern AssemblerRegisterYMM ymm14;
		extern AssemblerRegisterYMM ymm15;
		extern AssemblerRegisterYMM ymm16;
		extern AssemblerRegisterYMM ymm17;
		extern AssemblerRegisterYMM ymm18;
		extern AssemblerRegisterYMM ymm19;
		extern AssemblerRegisterYMM ymm20;
		extern AssemblerRegisterYMM ymm21;
		extern AssemblerRegisterYMM ymm22;
		extern AssemblerRegisterYMM ymm23;
		extern AssemblerRegisterYMM ymm24;
		extern AssemblerRegisterYMM ymm25;
		extern AssemblerRegisterYMM ymm26;
		extern AssemblerRegisterYMM ymm27;
		extern AssemblerRegisterYMM ymm28;
		extern AssemblerRegisterYMM ymm29;
		extern AssemblerRegisterYMM ymm30;
		extern AssemblerRegisterYMM ymm31;
		extern AssemblerRegisterZMM zmm0;
		extern AssemblerRegisterZMM zmm1;
		extern AssemblerRegisterZMM zmm2;
		extern AssemblerRegisterZMM zmm3;
		extern AssemblerRegisterZMM zmm4;
		extern AssemblerRegisterZMM zmm5;
		extern AssemblerRegisterZMM zmm6;
		extern AssemblerRegisterZMM zmm7;
		extern AssemblerRegisterZMM zmm8;
		extern AssemblerRegisterZMM zmm9;
		extern AssemblerRegisterZMM zmm10;
		extern AssemblerRegisterZMM zmm11;
		extern AssemblerRegisterZMM zmm12;
		extern AssemblerRegisterZMM zmm13;
		extern AssemblerRegisterZMM zmm14;
		extern AssemblerRegisterZMM zmm15;
		extern AssemblerRegisterZMM zmm16;
		extern AssemblerRegisterZMM zmm17;
		extern AssemblerRegisterZMM zmm18;
		extern AssemblerRegisterZMM zmm19;
		extern AssemblerRegisterZMM zmm20;
		extern AssemblerRegisterZMM zmm21;
		extern AssemblerRegisterZMM zmm22;
		extern AssemblerRegisterZMM zmm23;
		extern AssemblerRegisterZMM zmm24;
		extern AssemblerRegisterZMM zmm25;
		extern AssemblerRegisterZMM zmm26;
		extern AssemblerRegisterZMM zmm27;
		extern AssemblerRegisterZMM zmm28;
		extern AssemblerRegisterZMM zmm29;
		extern AssemblerRegisterZMM zmm30;
		extern AssemblerRegisterZMM zmm31;
		extern AssemblerRegisterTMM tmm0;
		extern AssemblerRegisterTMM tmm1;
		extern AssemblerRegisterTMM tmm2;
		extern AssemblerRegisterTMM tmm3;
		extern AssemblerRegisterTMM tmm4;
		extern AssemblerRegisterTMM tmm5;
		extern AssemblerRegisterTMM tmm6;
		extern AssemblerRegisterTMM tmm7;


		/// <summary>
		/// Gets a memory operand with no size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __;
		/// <summary>
		/// Gets a memory operand with a <c>BYTE PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __byte_ptr;
		/// <summary>
		/// Gets a memory operand with a <c>WORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __word_ptr;
		/// <summary>
		/// Gets a memory operand with a <c>DWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __dword_ptr;
		/// <summary>
		/// Gets a memory operand with a <c>QWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __qword_ptr;
		/// <summary>
		/// Gets a memory operand with an <c>MMWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __mmword_ptr;
		/// <summary>
		/// Gets a memory operand with a <c>TBYTE PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __tbyte_ptr;
		/// <summary>
		/// Gets a memory operand with a <c>TWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __tword_ptr;
		/// <summary>
		/// Gets a memory operand with an <c>FWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __fword_ptr;
		/// <summary>
		/// Gets a memory operand with an <c>OWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __oword_ptr;
		/// <summary>
		/// Gets a memory operand with an <c>XMMWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __xmmword_ptr;
		/// <summary>
		/// Gets a memory operand with a <c>YMMWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __ymmword_ptr;
		/// <summary>
		/// Gets a memory operand with a <c>ZMMWORD PTR</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __zmmword_ptr;
		/// <summary>
		/// Gets a broadcast memory operand with no size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __bcst;
		/// <summary>
		/// Gets a broadcast memory operand with a <c>WORD BCST</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __word_bcst;
		/// <summary>
		/// Gets a broadcast memory operand with a <c>DWORD BCST</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __dword_bcst;
		/// <summary>
		/// Gets a broadcast memory operand with a <c>QWORD BCST</c> size hint
		/// </summary>
		extern AssemblerMemoryOperandFactory __qword_bcst;
	};
}