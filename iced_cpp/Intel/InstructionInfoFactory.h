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

#include "InstructionInfo.h"
#include "CodeSize.g.h"
#include "Register.g.h"
#include "InstructionInfoInternal/InfoHandlerFlags.h"
#include "Iced.Intel.Instruction.h"
#include "OpAccess.g.h"
#include "MemorySize.g.h"
#include <vector>
#include <limits>
#include <csharp/exceptionhelper.h>
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::InstructionInfoInternal;
namespace Iced::Intel
{
	/// <summary>
	/// Instruction info options used by <see cref="InstructionInfoFactory"/>
	/// </summary>
	enum class InstructionInfoOptions : uint
	{
		/// <summary>
		/// No option is enabled
		/// </summary>
		None = 0,

		/// <summary>
		/// Don't include memory usage, i.e., <see cref="InstructionInfo.GetUsedMemory"/> will return an empty iterator. All
		/// registers that are used by memory operands are still returned by <see cref="InstructionInfo.GetUsedRegisters"/>.
		/// </summary>
		NoMemoryUsage = 0x00000001,

		/// <summary>
		/// Don't include register usage, i.e., <see cref="InstructionInfo.GetUsedRegisters"/> will return an empty iterator
		/// </summary>
		NoRegisterUsage = 0x00000002
	};
	DEFINE_FLAGS(InstructionInfoOptions)
		DEFINE_COMP(InstructionInfoOptions)
		DEFINE_ARITH(InstructionInfoOptions)

		/// <summary>
		/// Creates <see cref="InstructionInfo"/>s.
		/// <br/>
		/// If you don't need memory and register usage, it's faster to call <see cref="Instruction"/> and <see cref="Code"/>
		/// methods/properties, eg. <see cref="Instruction.FlowControl"/>, etc instead of getting that info from this class.
		/// </summary>
		class InstructionInfoFactory final
	{
	private:
		static constexpr std::int32_t defaultRegisterArrayCount = 2;
		static constexpr std::int32_t defaultMemoryArrayCount = 1;
		InstructionInfo info;
	private:
		enum class Flags : int
		{
			None = 0,
			NoMemoryUsage = 0x00000001,
			NoRegisterUsage = 0x00000002,
			Is64Bit = 0x00000004,
			ZeroExtVecRegs = 0x00000008
		};
		DEFINE_FLAGS_FRIEND(Flags)
			DEFINE_COMP_FRIEND(Flags)
			DEFINE_ARITH_FRIEND(Flags)

			/// <summary>
			/// Constructor
			/// </summary>
	public:
		InstructionInfoFactory();
		/// <summary>
		/// Creates an <see cref="InstructionInfo"/>. The return value is only valid until this instance creates a new <see cref="InstructionInfo"/> value.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER TODO TASK: 'ref return' methods are not converted by C# to C++ Converter:
	  //  public ref InstructionInfo GetInfo(in Instruction instruction)
	  //  {
	  //	  return ref Create(instruction, InstructionInfoOptions.None);
	  //  }
		/// <summary>
		/// Creates an <see cref="InstructionInfo"/>. The return value is only valid until this instance creates a new <see cref="InstructionInfo"/> value.
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="options">Options</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER TODO TASK: 'ref return' methods are not converted by C# to C++ Converter:
	  //  public ref InstructionInfo GetInfo(in Instruction instruction, InstructionInfoOptions options)
	  //  {
	  //	  return ref Create(instruction, options);
	  //  }
	  //C# TO C++ CONVERTER TODO TASK: 'ref return' methods are not converted by C# to C++ Converter:
	  //  ref InstructionInfo Create(in Instruction instruction, InstructionInfoOptions options)
	  //  {
	  //   info.usedRegisters.ValidLength = 0;
	  //   info.usedMemoryLocations.ValidLength = 0;
	  //   var data = InstrInfoTable.Data;
	  //   var index = (uint)instruction.Code << 1;
	  //   var flags1 = data[(int)index];
	  //   var flags2 = data[(int)index + 1];
	  //   var codeSize = instruction.CodeSize;
	  //   Static.Assert((uint)InstructionInfoOptions.NoMemoryUsage == (uint)Flags.NoMemoryUsage ? 0 : -1);
	  //   Static.Assert((uint)InstructionInfoOptions.NoRegisterUsage == (uint)Flags.NoRegisterUsage ? 0 : -1);
	  //   var flags = (Flags)options & (Flags.NoMemoryUsage | Flags.NoRegisterUsage);
	  //   if (codeSize == CodeSize.Code64 || codeSize == CodeSize.Unknown)
	  //	flags |= Flags.Is64Bit;
	  //   if ((flags2 & ((uint)InfoFlags2.EncodingMask << (int)InfoFlags2.EncodingShift)) != ((uint)EncodingKind.Legacy << (int)InfoFlags2.EncodingShift))
	  //	flags |= Flags.ZeroExtVecRegs;
	  //   OpAccess op0Access;
	  //   // If it fails, update InstrInfoTypesGen.GenerateOpInfoX()
	  //   Static.Assert(InstrInfoConstants.OpInfo0_Count == 13 ? 0 : -1);
	  //   var op0Info = (OpInfo0)((flags1 >> (int)InfoFlags1.OpInfo0Shift) & (uint)InfoFlags1.OpInfo0Mask);
	  //   switch (op0Info)
	  //   {
	  //   default:
	  //   case OpInfo0.None:
	  //	op0Access = OpAccess.None;
	  //	break;
	  //   case OpInfo0.Read:
	  //	op0Access = OpAccess.Read;
	  //	break;
	  //   case OpInfo0.Write:
	  //	if (instruction.HasOpMask && instruction.MergingMasking)
	  //	{
	  //	 if (instruction.Op0Kind != OpKind.Register)
	  //	  op0Access = OpAccess.CondWrite;
	  //	 else
	  //	  op0Access = OpAccess.ReadWrite;
	  //	}
	  //	else
	  //	 op0Access = OpAccess.Write;
	  //	break;
	  //   case OpInfo0.WriteVmm:
	  //	// If it's opmask+merging ({k1}) and dest is xmm/ymm/zmm, then access is one of:
	  //	//	k1			mem			xmm/ymm		zmm
	  //	//	----------------------------------------
	  //	//	all 1s		write		write		write		all bits are overwritten, upper bits in zmm (if xmm/ymm) are cleared
	  //	//	all 0s		no access	read/write	no access	no elem is written, but xmm/ymm's upper bits (in zmm) are cleared so
	  //	//													treat it as R lower bits + clear upper bits + W full reg
	  //	//	else		cond-write	read/write	r-c-w		some elems are unchanged, the others are overwritten
	  //	// If it's xmm/ymm, use RW, else use RCW. If it's mem, use CW
	  //	if (instruction.HasOpMask && instruction.MergingMasking)
	  //	{
	  //	 if (instruction.Op0Kind != OpKind.Register)
	  //	  op0Access = OpAccess.CondWrite;
	  //	 else
	  //	  op0Access = OpAccess.ReadCondWrite;
	  //	}
	  //	else
	  //	 op0Access = OpAccess.Write;
	  //	break;
	  //   case OpInfo0.WriteForce:
	  //   case OpInfo0.WriteForceP1:
	  //	op0Access = OpAccess.Write;
	  //	break;
	  //   case OpInfo0.CondWrite:
	  //	op0Access = OpAccess.CondWrite;
	  //	break;
	  //   case OpInfo0.CondWrite32_ReadWrite64:
	  //	if ((flags & Flags.Is64Bit) != 0)
	  //	 op0Access = OpAccess.ReadWrite;
	  //	else
	  //	 op0Access = OpAccess.CondWrite;
	  //	break;
	  //   case OpInfo0.ReadWrite:
	  //	op0Access = OpAccess.ReadWrite;
	  //	break;
	  //   case OpInfo0.ReadWriteVmm:
	  //	// If it's opmask+merging ({k1}) and dest is xmm/ymm/zmm, then access is one of:
	  //	//	k1			xmm/ymm		zmm
	  //	//	-------------------------------
	  //	//	all 1s		read/write	read/write	all bits are overwritten, upper bits in zmm (if xmm/ymm) are cleared
	  //	//	all 0s		read/write	no access	no elem is written, but xmm/ymm's upper bits (in zmm) are cleared so
	  //	//										treat it as R lower bits + clear upper bits + W full reg
	  //	//	else		read/write	r-c-w		some elems are unchanged, the others are overwritten
	  //	// If it's xmm/ymm, use RW, else use RCW
	  //	if (instruction.HasOpMask && instruction.MergingMasking)
	  //	 op0Access = OpAccess.ReadCondWrite;
	  //	else
	  //	 op0Access = OpAccess.ReadWrite;
	  //	break;
	  //   case OpInfo0.ReadCondWrite:
	  //	op0Access = OpAccess.ReadCondWrite;
	  //	break;
	  //   case OpInfo0.NoMemAccess:
	  //	op0Access = OpAccess.NoMemAccess;
	  //	break;
	  //   case OpInfo0.WriteMem_ReadWriteReg:
	  //	if (instruction.Internal_Op0IsNotReg_or_Op1IsNotReg)
	  //	 op0Access = OpAccess.Write;
	  //	else
	  //	 op0Access = OpAccess.ReadWrite;
	  //	break;
	  //   }
	  //   Debug.Assert(instruction.OpCount <= IcedConstants.MaxOpCount);
	  //   unsafe
	  //   {
	  //	   info.opAccesses[0] = (byte)op0Access;
	  //   }
	  //   var op1Info = (OpInfo1)((flags1 >> (int)InfoFlags1.OpInfo1Shift) & (uint)InfoFlags1.OpInfo1Mask);
	  //   unsafe
	  //   {
	  //	   info.opAccesses[1] = (byte)OpAccesses.Op1[(int)op1Info];
	  //   }
	  //   unsafe
	  //   {
	  //	   info.opAccesses[2] = (byte)OpAccesses.Op2[(int)((flags1 >> (int)InfoFlags1.OpInfo2Shift) & (uint)InfoFlags1.OpInfo2Mask)];
	  //   }
	  //   if ((flags1 & (((uint)InfoFlags1.OpInfo3Mask) << (int)InfoFlags1.OpInfo3Shift)) != 0)
	  //   {
	  //	Static.Assert((int)InstrInfoConstants.OpInfo3_Count == 2 ? 0 : -1);
	  //	unsafe
	  //	{
	  //		info.opAccesses[3] = (byte)OpAccess.Read;
	  //	}
	  //   }
	  //   else
	  //	unsafe
	  //{
	  //	info.opAccesses[3] = (byte)OpAccess.None;
	  //}
	  //   if ((flags1 & (((uint)InfoFlags1.OpInfo4Mask) << (int)InfoFlags1.OpInfo4Shift)) != 0)
	  //   {
	  //	Static.Assert((int)InstrInfoConstants.OpInfo4_Count == 2 ? 0 : -1);
	  //	unsafe
	  //	{
	  //		info.opAccesses[4] = (byte)OpAccess.Read;
	  //	}
	  //   }
	  //   else
	  //	unsafe
	  //{
	  //	info.opAccesses[4] = (byte)OpAccess.None;
	  //}
	  //   Static.Assert(IcedConstants.MaxOpCount == 5 ? 0 : -1);
	  //   int opCount = instruction.OpCount;
	  //   for (int i = 0; i < opCount; i++)
	  //   {
	  //	OpAccess access;
	  //	unsafe
	  //	{
	  //		access = (OpAccess)info.opAccesses[i];
	  //	}
	  //	if (access == OpAccess.None)
	  //	 continue;
	  //	switch (instruction.GetOpKind(i))
	  //	{
	  //	case OpKind.Register:
	  //	 if (access == OpAccess.NoMemAccess)
	  //	 {
	  //	  access = OpAccess.Read;
	  //	  unsafe
	  //	  {
	  //		  info.opAccesses[i] = (byte)OpAccess.Read;
	  //	  };
	  //	 }
	  //	 if ((flags & Flags.NoRegisterUsage) == 0)
	  //	 {
	  //	  if (i == 0 && op0Info == OpInfo0.WriteForceP1)
	  //	  {
	  //	   var reg = instruction.Op0Register;
	  //	   AddRegister(flags, reg, access);
	  //	   if (Register.K0 <= reg && reg <= Register.K7)
	  //		AddRegister(flags, ((reg - Register.K0) ^ 1) + Register.K0, access);
	  //	  }
	  //	  else if (i == 1 && op1Info == OpInfo1.ReadP3)
	  //	  {
	  //	   var reg = instruction.Op1Register;
	  //	   if (Register.XMM0 <= reg && reg <= IcedConstants.VMM_last)
	  //	   {
	  //		reg = IcedConstants.VMM_first + ((reg - IcedConstants.VMM_first) & ~3);
	  //		for (int j = 0; j < 4; j++)
	  //		 AddRegister(flags, reg + j, access);
	  //	   }
	  //	  }
	  //	  else
	  //	   AddRegister(flags, instruction.GetOpRegister(i), access);
	  //	 }
	  //	 break;
	  //	case OpKind.Memory:
	  //	 Static.Assert((uint)InfoFlags1.IgnoresSegment == (1U << 31) ? 0 : -1);
	  //	 Static.Assert(Register.None == 0 ? 0 : -1);
	  //	 var segReg = (Register)((uint)instruction.MemorySegment & ~(uint)((int)flags1 >> 31));
	  //	 var baseReg = instruction.MemoryBase;
	  //	 if (baseReg == Register.RIP)
	  //	 {
	  //	  if ((flags & Flags.NoMemoryUsage) == 0)
	  //	   AddMemory(segReg, Register.None, Register.None, 1, instruction.MemoryDisplacement64, instruction.MemorySize, access, CodeSize.Code64, 0);
	  //	  if ((flags & Flags.NoRegisterUsage) == 0 && segReg != Register.None)
	  //	   AddMemorySegmentRegister(flags, segReg, OpAccess.Read);
	  //	 }
	  //	 else if (baseReg == Register.EIP)
	  //	 {
	  //	  if ((flags & Flags.NoMemoryUsage) == 0)
	  //	   AddMemory(segReg, Register.None, Register.None, 1, instruction.MemoryDisplacement32, instruction.MemorySize, access, CodeSize.Code32, 0);
	  //	  if ((flags & Flags.NoRegisterUsage) == 0 && segReg != Register.None)
	  //	   AddMemorySegmentRegister(flags, segReg, OpAccess.Read);
	  //	 }
	  //	 else
	  //	 {
	  //	  int scale;
	  //	  Register indexReg;
	  //	  if ((flags1 & (uint)InfoFlags1.IgnoresIndexVA) != 0)
	  //	  {
	  //	   indexReg = instruction.MemoryIndex;
	  //	   if ((flags & Flags.NoRegisterUsage) == 0 && indexReg != Register.None)
	  //		AddRegister(flags, indexReg, OpAccess.Read);
	  //	   indexReg = Register.None;
	  //	   scale = 1;
	  //	  }
	  //	  else
	  //	  {
	  //	   indexReg = instruction.MemoryIndex;
	  //	   scale = instruction.MemoryIndexScale;
	  //	  }
	  //	  if ((flags & Flags.NoMemoryUsage) == 0)
	  //	  {
	  //	   var addrSizeBytes = InstructionUtils.GetAddressSizeInBytes(baseReg, indexReg, instruction.MemoryDisplSize, codeSize);
	  //	   var switchTempVar_0 = addrSizeBytes;
	  //
	  //
	  //	   var addrSize = (switchTempVar_0 == 2) ? CodeSize.Code16 : (switchTempVar_0 == 4) ? CodeSize.Code32 : (switchTempVar_0 == 8) ? CodeSize.Code64 : CodeSize.Unknown;
	  //	   int vsibSize = 0;
	  //	   if (indexReg.IsVectorRegister() && instruction.TryGetVsib64(out bool vsib64))
	  //		vsibSize = vsib64 ? 8 : 4;
	  //	   ulong displ;
	  //	   if (addrSizeBytes == 8)
	  //		displ = instruction.MemoryDisplacement64;
	  //	   else
	  //		displ = instruction.MemoryDisplacement32;
	  //	   AddMemory(segReg, baseReg, indexReg, scale, displ, instruction.MemorySize, access, addrSize, vsibSize);
	  //	  }
	  //	  if ((flags & Flags.NoRegisterUsage) == 0)
	  //	  {
	  //	   if (segReg != Register.None)
	  //		AddMemorySegmentRegister(flags, segReg, OpAccess.Read);
	  //	   if (baseReg != Register.None)
	  //		AddRegister(flags, baseReg, OpAccess.Read);
	  //	   if (indexReg != Register.None)
	  //		AddRegister(flags, indexReg, OpAccess.Read);
	  //	  }
	  //	 }
	  //	 break;
	  //	}
	  //   }
	  //   var impliedAccess = (ImpliedAccess)((flags1 >> (int)InfoFlags1.ImpliedAccessShift) & (uint)InfoFlags1.ImpliedAccessMask);
	  //   if (impliedAccess != ImpliedAccess.None)
	  //	AddImpliedAccesses(impliedAccess, instruction, flags);
	  //   if (instruction.HasOpMask && (flags & Flags.NoRegisterUsage) == 0)
	  //	AddRegister(flags, instruction.OpMask, (flags1 & (uint)InfoFlags1.OpMaskReadWrite) != 0 ? OpAccess.ReadWrite : OpAccess.Read);
	  //   return ref info;
	  //  }
	private:
		static Register GetXSP(CodeSize codeSize, std::uint64_t& xspMask, CodeSize& addressSize);
		void AddImpliedAccesses(ImpliedAccess impliedAccess, Instruction const instruction, Flags flags);
		static Register GetARDI(Instruction instruction);
		static Register GetSegDefaultDS(Instruction instruction);
		void CommandPush(Instruction const instruction, Flags flags, std::int32_t count, std::uint32_t opSize);
		void CommandPop(Instruction const instruction, Flags flags, std::int32_t count, std::uint32_t opSize);
		void CommandPopRm(Instruction const instruction, Flags flags, std::uint32_t opSize);
		void CommandPusha(Instruction const instruction, Flags flags, std::uint32_t opSize);
		void CommandPopa(Instruction const instruction, Flags flags, std::uint32_t opSize);
		void CommandIns(Instruction const instruction, Flags flags);
		void CommandOuts(Instruction const instruction, Flags flags);
		void CommandMovs(Instruction const instruction, Flags flags);
		void CommandCmps(Instruction const instruction, Flags flags);
		void CommandStos(Instruction const instruction, Flags flags);
		void CommandLods(Instruction const instruction, Flags flags);
		void CommandScas(Instruction const instruction, Flags flags);
		void CommandXstore(Instruction const instruction, Flags flags, std::uint32_t size);
		void CommandEnter(Instruction const instruction, Flags flags, std::uint32_t opSize);
		void CommandLeave(Instruction const instruction, Flags flags, std::uint32_t opSize);
		void CommandClearRflags(Instruction const instruction, Flags flags);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] static bool IsClearInstr(in Instruction instruction)
		static bool IsClearInstr(Instruction const instruction);
		void CommandClearRegRegmem(Instruction const instruction, Flags flags);
		void CommandClearRegRegRegmem(Instruction const instruction, Flags flags);
		void CommandArpl(Instruction const instruction, Flags flags);
		void CommandLastGpr(Instruction const instruction, Flags flags, Register baseReg);
		void CommandLea(Instruction const instruction, Flags flags);
		void CommandEmmi(Instruction const instruction, Flags flags, OpAccess opAccess);
		void CommandMemDispl(Flags flags, std::int32_t extraDispl);
		static std::int32_t TryGetGpr163264Index(Register register_);
		void AddMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] void AddMemorySegmentRegister(Flags flags, Register seg, OpAccess access)
		void AddMemorySegmentRegister(Flags flags, Register seg, OpAccess access);
		void AddRegister(Flags flags, Register reg, OpAccess access);
	};
}
