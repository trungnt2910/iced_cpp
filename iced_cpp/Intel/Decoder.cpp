// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Decoder.h"
#include "InstructionMemorySizes.g.h"
#include "DecoderInternal/OpCodeHandlers_D3NOW.h"
#include "InstructionOpCounts.g.h"
#include "MnemonicUtilsData.g.h"
#include "TupleTypeTable.h"
#include "RegisterExtensions.h"
#include "Iced.Intel.MemorySizeExtensions.h"
#include "InstructionInfoInternal/InstrInfoTable.g.h"
#include "InstructionInfoInternal/RflagsInfoConstants.g.h"
#include "InstructionInfoInternal/Iced.Intel.InstructionInfoInternal.CpuidFeatureInternalData.h"
#include "UsedRegister.h"
#include "InstructionInfoInternal/SimpleList.h"
#include "UsedMemory.h"
#include "DecoderInternal/Iced.Intel.DecoderInternal.OpCodeHandlersTables_Legacy.h"
#include "DecoderInternal/Iced.Intel.DecoderInternal.OpCodeHandlersTables_VEX.h"
#include "DecoderInternal/OpCodeHandlersTables_EVEX.h"
#include "DecoderInternal/Iced.Intel.DecoderInternal.OpCodeHandlersTables_XOP.h"
#include "DecoderInternal/Iced.Intel.DecoderInternal.OpCodeHandlersTables_MVEX.h"
#include "ByteArrayCodeReader.h"
#include "Iced.Intel.IcedConstants.h"
#include "Code.g.h"
#include "Static.h"
#include "VectorLength.g.h"
#include "OpKind.g.h"

using namespace Iced::Intel::DecoderInternal;

namespace Iced::Intel
{
	std::uint64_t Decoder::GetIP() const
	{
		return instructionPointer;
	}

	void Decoder::SetIP(std::uint64_t value)
	{
		instructionPointer = value;
	}

	std::int32_t Decoder::GetBitness() const
	{
		return Bitness;
	}

	Decoder::StaticConstructor::StaticConstructor()
	{
		// Initialize cctors that are used by decoder related methods. It doesn't speed up
		// decoding much, but getting instruction info is a little faster.
		// Is this relevant in C++?
		//_ = OpCodeHandler_Invalid::GetInstance();
		//_ = InstructionMemorySizes::SizesNormal;
		//_ = OpCodeHandler_D3NOW::CodeValues;
		//_ = InstructionOpCounts::OpCount;
		//_ = MnemonicUtilsData::toMnemonic;
		//_ = TupleTypeTable::tupleTypeData;
		//_ = RegisterExtensions::RegisterInfos;
		//_ = MemorySizeExtensions::MemorySizeInfos;
		//_ = InstructionInfoInternal::InstrInfoTable::Data;
		//_ = InstructionInfoInternal::RflagsInfoConstants::flagsCleared;
		//_ = InstructionInfoInternal::CpuidFeatureInternalData::ToCpuidFeatures;
		//_ = InstructionInfoInternal::SimpleList<UsedRegister>::Empty;
		//_ = InstructionInfoInternal::SimpleList<UsedMemory>::Empty;
	}

	Decoder::StaticConstructor Decoder::staticConstructor;

	Decoder::Decoder(CodeReader* reader, std::uint64_t ip, DecoderOptions options, std::int32_t bitness)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.reader = reader ?? throw new ArgumentNullException(nameof(reader));
		this->reader = (reader != nullptr) ? reader : throw std::invalid_argument("reader");
		instructionPointer = ip;
		this->options = options;
		invalidCheckMask = (options & DecoderOptions::NoInvalidCheck) == 0 ? std::numeric_limits<std::uint32_t>::max() : 0;
		Bitness = bitness;
		if (bitness == 64)
		{
			is64bMode = true;
			defaultCodeSize = CodeSize::Code64;
			defaultOperandSize = OpSize::Size32;
			defaultInvertedOperandSize = OpSize::Size16;
			defaultAddressSize = OpSize::Size64;
			defaultInvertedAddressSize = OpSize::Size32;
			mask64b = std::numeric_limits<std::uint32_t>::max();
		}
		else if (bitness == 32)
		{
			is64bMode = false;
			defaultCodeSize = CodeSize::Code32;
			defaultOperandSize = OpSize::Size32;
			defaultInvertedOperandSize = OpSize::Size16;
			defaultAddressSize = OpSize::Size32;
			defaultInvertedAddressSize = OpSize::Size16;
			mask64b = 0;
		}
		else
		{
			assert(bitness == 16);
			is64bMode = false;
			defaultCodeSize = CodeSize::Code16;
			defaultOperandSize = OpSize::Size16;
			defaultInvertedOperandSize = OpSize::Size32;
			defaultAddressSize = OpSize::Size16;
			defaultInvertedAddressSize = OpSize::Size32;
			mask64b = 0;
		}
		is64bMode_and_W = is64bMode ? static_cast<std::uint32_t>(StateFlags::W) : 0;
		reg15Mask = is64bMode ? 0xFU : 0x7;
		handlers_MAP0 = OpCodeHandlersTables_Legacy::Handlers_MAP0;
		handlers_VEX_MAP0 = OpCodeHandlersTables_VEX::Handlers_MAP0;
		handlers_VEX_0F = OpCodeHandlersTables_VEX::Handlers_0F;
		handlers_VEX_0F38 = OpCodeHandlersTables_VEX::Handlers_0F38;
		handlers_VEX_0F3A = OpCodeHandlersTables_VEX::Handlers_0F3A;
		handlers_XOP_MAP8 = OpCodeHandlersTables_XOP::Handlers_MAP8;
		handlers_XOP_MAP9 = OpCodeHandlersTables_XOP::Handlers_MAP9;
		handlers_XOP_MAP10 = OpCodeHandlersTables_XOP::Handlers_MAP10;
		handlers_MVEX_0F = OpCodeHandlersTables_MVEX::Handlers_0F;
		handlers_MVEX_0F38 = OpCodeHandlersTables_MVEX::Handlers_0F38;
		handlers_MVEX_0F3A = OpCodeHandlersTables_MVEX::Handlers_0F3A;
	}

	Decoder Decoder::Create(std::int32_t bitness, CodeReader* reader, std::uint64_t ip, DecoderOptions options)
	{
		if (bitness == 16 || bitness == 32 || bitness == 64)
		{
			return Decoder(reader, ip, options, bitness);
		}

		throw std::invalid_argument("invalid bitness");
	}

	Decoder Decoder::Create(std::int32_t bitness, std::vector<std::uint8_t>& data, std::uint64_t ip, DecoderOptions options)
	{
		ByteArrayCodeReader tempVar(data);
		return Create(bitness, &tempVar, ip, options);
	}

	Decoder Decoder::Create(std::int32_t bitness, CodeReader* reader, DecoderOptions options)
	{
		return Create(bitness, reader, 0, options);
	}

	Decoder Decoder::Create(std::int32_t bitness, std::vector<std::uint8_t>& data, DecoderOptions options)
	{
		ByteArrayCodeReader tempVar(data);
		return Create(bitness, &tempVar, 0, options);
	}

	std::uint32_t Decoder::ReadByte()
	{
		std::uint32_t instrLen = state.instructionLength;
		if (instrLen < IcedConstants::MaxInstructionLength)
		{
			std::uint32_t b = static_cast<std::uint32_t>(reader->ReadByte());
			assert(b <= std::numeric_limits<std::uint8_t>::max() || b > (std::uint32_t)std::numeric_limits<std::int32_t>::max());
			if (b <= std::numeric_limits<std::uint8_t>::max())
			{
				state.instructionLength = instrLen + 1;
				return b;
			}
			state.flags |= StateFlags::NoMoreBytes;
		}
		state.flags |= StateFlags::IsInvalid;
		return 0;
	}

	std::uint32_t Decoder::ReadUInt16()
	{
		return ReadByte() | (ReadByte() << 8);
	}

	std::uint32_t Decoder::ReadUInt32()
	{
		return ReadByte() | (ReadByte() << 8) | (ReadByte() << 16) | (ReadByte() << 24);
	}

	std::uint64_t Decoder::ReadUInt64()
	{
		return static_cast<std::uint64_t>(ReadUInt32()) | (static_cast<std::uint64_t>(ReadUInt32()) << 32);
	}

	DecoderError Decoder::GetLastError() const
	{
		// NoMoreBytes error has highest priority
		if ((state.flags & StateFlags::NoMoreBytes) != 0)
		{
			return DecoderError::NoMoreBytes;
		}
		if ((state.flags & StateFlags::IsInvalid) != 0)
		{
			return DecoderError::InvalidInstruction;
		}
		return DecoderError::None;
	}

	Instruction Decoder::Decode()
	{
		Instruction instr;
		Decode(instr);
		return instr;
	}

	void Decoder::Decode(Instruction& instruction)
	{
		instruction = Iced::Intel::Instruction();
		state.instructionLength = 0;
		state.extraRegisterBase = 0;
		state.extraIndexRegisterBase = 0;
		state.extraBaseRegisterBase = 0;
		state.extraIndexRegisterBaseVSIB = 0;
		state.flags = (Iced::Intel::StateFlags)0;
		state.mandatoryPrefix = (Iced::Intel::MandatoryPrefixByte)0;
		state.segmentPrio = 0;
		state.operandSize = defaultOperandSize;
		state.addressSize = defaultAddressSize;
		std::uint32_t b = ReadByte();
		if (((b >> 4) & mask64b) == 4)
		{
			if ((b & 8) != 0)
			{
				state.operandSize = OpSize::Size64;
				state.flags |= StateFlags::HasRex | StateFlags::W;
			}
			else
			{
				state.flags |= StateFlags::HasRex;
			}
			state.extraRegisterBase = (b & 4) << 1;
			state.extraIndexRegisterBase = (b & 2) << 2;
			state.extraBaseRegisterBase = (b & 1) << 3;
			b = ReadByte();
		}
		DecodeTable(handlers_MAP0[b], instruction);
		auto flags = state.flags;
		if ((flags & (StateFlags::IsInvalid | StateFlags::Lock)) != 0)
		{
			if ((flags & StateFlags::IsInvalid) != 0 || ((static_cast<std::uint32_t>((uint32_t)(flags & (StateFlags::Lock | StateFlags::AllowLock)) & invalidCheckMask)) == static_cast<std::uint32_t>(StateFlags::Lock)))
			{
				instruction = Iced::Intel::Instruction();
				Static::Assert(Code::INVALID == (Iced::Intel::Code)0 ? 0 : -1);
				//instruction.Code = Code.INVALID;
				state.flags = flags | StateFlags::IsInvalid;
			}
		}
		instruction.SetInternalCodeSize(defaultCodeSize);
		std::uint32_t instrLen = state.instructionLength;
		assert(0 <= instrLen && instrLen <= IcedConstants::MaxInstructionLength); // Could be 0 if there were no bytes available
		instruction.SetLength(static_cast<std::int32_t>(instrLen));
		auto ip = instructionPointer;
		ip += instrLen;
		instructionPointer = ip;
		instruction.SetNextIP(ip);
		if ((state.flags & StateFlags::IpRel64) != 0)
		{
			instruction.SetMemoryDisplacement64(instruction.GetMemoryDisplacement64() + ip);
		}
		else if ((state.flags & StateFlags::IpRel32) != 0)
		{
			instruction.SetMemoryDisplacement64(static_cast<std::uint32_t>(ip) + instruction.GetMemoryDisplacement32());
		}
	}

	void Decoder::ResetRexPrefixState()
	{
		state.flags &= ~(StateFlags::HasRex | StateFlags::W);
		if ((state.flags & StateFlags::Has66) == 0)
		{
			state.operandSize = defaultOperandSize;
		}
		else
		{
			state.operandSize = defaultInvertedOperandSize;
		}
		state.extraRegisterBase = 0;
		state.extraIndexRegisterBase = 0;
		state.extraBaseRegisterBase = 0;
	}

	void Decoder::CallOpCodeHandlerXXTable(Instruction& instruction)
	{
		auto b = ReadByte();
		DecodeTable(handlers_MAP0[b], instruction);
	}

	std::uint32_t Decoder::GetCurrentInstructionPointer32()
	{
		return static_cast<std::uint32_t>(instructionPointer) + state.instructionLength;
	}

	std::uint64_t Decoder::GetCurrentInstructionPointer64()
	{
		return instructionPointer + state.instructionLength;
	}

	void Decoder::ClearMandatoryPrefix(Instruction& instruction)
	{
		assert(state.GetEncoding() == EncodingKind::Legacy);
		instruction.InternalClearHasRepeRepnePrefix();
	}

	void Decoder::SetXacquireXrelease(Instruction& instruction)
	{
		if (instruction.GetHasLockPrefix())
		{
			if (state.mandatoryPrefix == MandatoryPrefixByte::PF2)
			{
				ClearMandatoryPrefixF2(instruction);
				instruction.InternalSetHasXacquirePrefix();
			}
			else if (state.mandatoryPrefix == MandatoryPrefixByte::PF3)
			{
				ClearMandatoryPrefixF3(instruction);
				instruction.InternalSetHasXreleasePrefix();
			}
		}
	}

	void Decoder::ClearMandatoryPrefixF3(Instruction& instruction)
	{
		assert(state.GetEncoding() == EncodingKind::Legacy);
		assert(state.mandatoryPrefix == MandatoryPrefixByte::PF3);
		instruction.InternalClearHasRepePrefix();
	}

	void Decoder::ClearMandatoryPrefixF2(Instruction& instruction)
	{
		assert(state.GetEncoding() == EncodingKind::Legacy);
		assert(state.mandatoryPrefix == MandatoryPrefixByte::PF2);
		instruction.InternalClearHasRepnePrefix();
	}

	void Decoder::SetInvalidInstruction()
	{
		state.flags |= StateFlags::IsInvalid;
	}

	void Decoder::DecodeTable(const std::span<const OpCodeHandler* const>& table, Instruction& instruction)
	{
		DecodeTable(table[static_cast<std::int32_t>(ReadByte())], instruction);
	}

	void Decoder::DecodeTable(const OpCodeHandler* handler, Instruction& instruction)
	{
		if (handler->HasModRM)
		{
			std::uint32_t m = ReadByte();
			state.modrm = m;
			state.mod = m >> 6;
			state.reg = (m >> 3) & 7;
			state.rm = m & 7;
		}
		handler->Decode(*this, instruction);
	}

	void Decoder::ReadModRM()
	{
		std::uint32_t m = ReadByte();
		state.modrm = m;
		state.mod = m >> 6;
		state.reg = (m >> 3) & 7;
		state.rm = m & 7;
	}

	void Decoder::VEX2(Instruction& instruction)
	{
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::HasRex) | static_cast<std::uint32_t>(state.mandatoryPrefix)) & invalidCheckMask) != 0)
		{
			SetInvalidInstruction();
		}
		// Undo what Decode() did if it got a REX prefix
		state.flags &= ~StateFlags::W;
		state.extraIndexRegisterBase = 0;
		state.extraBaseRegisterBase = 0;
		std::uint32_t b = state.modrm;
		state.extraRegisterBase = ((b >> 4) ^ 8) & 8;
		Static::Assert(static_cast<std::int32_t>(VectorLength::L128) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L256) == 1 ? 0 : -1);
		state.vectorLength = (b >> 2) & 1;
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		state.mandatoryPrefix = static_cast<MandatoryPrefixByte>(b & 3);
		// Bit 6 can only be 1 if it's 16/32-bit mode, so we don't need to change the mask
		b = (~b >> 3) & 0x0F;
		state.vvvv = b;
		state.vvvv_invalidCheck = b;
		DecodeTable(handlers_VEX_0F, instruction);
	}

	void Decoder::VEX3(Instruction& instruction)
	{
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::HasRex) | static_cast<std::uint32_t>(state.mandatoryPrefix)) & invalidCheckMask) != 0)
		{
			SetInvalidInstruction();
		}
		// Undo what Decode() did if it got a REX prefix
		state.flags &= ~StateFlags::W;
		std::uint32_t b1 = state.modrm;
		std::uint32_t b2 = ReadByte();
		Static::Assert(static_cast<std::int32_t>(StateFlags::W) == 0x80 ? 0 : -1);
		state.flags |= static_cast<StateFlags>(b2 & 0x80);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L128) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L256) == 1 ? 0 : -1);
		state.vectorLength = (b2 >> 2) & 1;
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		state.mandatoryPrefix = static_cast<MandatoryPrefixByte>(b2 & 3);
		b2 = (~b2 >> 3) & 0x0F;
		if (is64bMode)
		{
			state.vvvv = b2;
			state.vvvv_invalidCheck = b2;
			std::uint32_t b1x = ~b1;
			state.extraRegisterBase = (b1x >> 4) & 8;
			state.extraIndexRegisterBase = (b1x >> 3) & 8;
			state.extraBaseRegisterBase = (b1x >> 2) & 8;
		}
		else
		{
			state.vvvv_invalidCheck = b2;
			state.vvvv = b2 & 0x07;
		}
		std::int32_t table = static_cast<std::int32_t>(b1 & 0x1F);
		if (table == 1)
		{
			DecodeTable(handlers_VEX_0F, instruction);
		}
		else if (table == 2)
		{
			DecodeTable(handlers_VEX_0F38, instruction);
		}
		else if (table == 3)
		{
			DecodeTable(handlers_VEX_0F3A, instruction);
		}
		else if (table == 0)
		{
			DecodeTable(handlers_VEX_MAP0, instruction);
		}
		else
		{
			SetInvalidInstruction();
		}
	}

	void Decoder::XOP(Instruction& instruction)
	{
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::HasRex) | static_cast<std::uint32_t>(state.mandatoryPrefix)) & invalidCheckMask) != 0)
		{
			SetInvalidInstruction();
		}
		// Undo what Decode() did if it got a REX prefix
		state.flags &= ~StateFlags::W;
		std::uint32_t b1 = state.modrm;
		std::uint32_t b2 = ReadByte();
		Static::Assert(static_cast<std::int32_t>(StateFlags::W) == 0x80 ? 0 : -1);
		state.flags |= static_cast<StateFlags>(b2 & 0x80);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L128) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(VectorLength::L256) == 1 ? 0 : -1);
		state.vectorLength = (b2 >> 2) & 1;
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		state.mandatoryPrefix = static_cast<MandatoryPrefixByte>(b2 & 3);
		b2 = (~b2 >> 3) & 0x0F;
		if (is64bMode)
		{
			state.vvvv = b2;
			state.vvvv_invalidCheck = b2;
			std::uint32_t b1x = ~b1;
			state.extraRegisterBase = (b1x >> 4) & 8;
			state.extraIndexRegisterBase = (b1x >> 3) & 8;
			state.extraBaseRegisterBase = (b1x >> 2) & 8;
		}
		else
		{
			state.vvvv_invalidCheck = b2;
			state.vvvv = b2 & 0x07;
		}
		std::int32_t table = static_cast<std::int32_t>(b1 & 0x1F);
		if (table == 8)
		{
			DecodeTable(handlers_XOP_MAP8, instruction);
		}
		else if (table == 9)
		{
			DecodeTable(handlers_XOP_MAP9, instruction);
		}
		else if (table == 10)
		{
			DecodeTable(handlers_XOP_MAP10, instruction);
		}
		else
		{
			SetInvalidInstruction();
		}
	}

	void Decoder::EVEX_MVEX(Instruction& instruction)
	{
		if (((static_cast<std::uint32_t>(state.flags & StateFlags::HasRex) | static_cast<std::uint32_t>(state.mandatoryPrefix)) & invalidCheckMask) != 0)
		{
			SetInvalidInstruction();
		}
		// Undo what Decode() did if it got a REX prefix
		state.flags &= ~StateFlags::W;
		std::uint32_t p0 = state.modrm;
		std::uint32_t p1 = ReadByte();
		std::uint32_t p2 = ReadByte();
		if ((p1 & 4) != 0)
		{
			if ((p0 & 8) == 0)
			{
#if !defined(NDEBUG)
				state.flags |= (StateFlags)((std::uint32_t)EncodingKind::EVEX << (std::int32_t)StateFlags::EncodingShift);
#endif

				Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
				state.mandatoryPrefix = static_cast<MandatoryPrefixByte>(p1 & 3);
				Static::Assert(static_cast<std::int32_t>(StateFlags::W) == 0x80 ? 0 : -1);
				state.flags |= static_cast<StateFlags>(p1 & 0x80);
				std::uint32_t aaa = p2 & 7;
				state.aaa = aaa;
				instruction.SetInternalOpMask(aaa);
				if ((p2 & 0x80) != 0)
				{
					// invalid if aaa == 0 and if we check for invalid instructions (it's all 1s)
					if ((aaa ^ invalidCheckMask) == std::numeric_limits<std::uint32_t>::max())
					{
						SetInvalidInstruction();
					}
					state.flags |= StateFlags::z;
					instruction.InternalSetZeroingMasking();
				}
				Static::Assert(static_cast<std::int32_t>(StateFlags::b) == 0x10 ? 0 : -1);
				state.flags |= static_cast<StateFlags>(p2 & 0x10);
				Static::Assert(static_cast<std::int32_t>(VectorLength::L128) == 0 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(VectorLength::L256) == 1 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(VectorLength::L512) == 2 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(VectorLength::Unknown) == 3 ? 0 : -1);
				state.vectorLength = (p2 >> 5) & 3;
				p1 = (~p1 >> 3) & 0x0F;
				if (is64bMode)
				{
					std::uint32_t tmp = (~p2 & 8) << 1;
					state.extraIndexRegisterBaseVSIB = tmp;
					tmp += p1;
					state.vvvv = tmp;
					state.vvvv_invalidCheck = tmp;
					std::uint32_t p0x = ~p0;
					state.extraRegisterBase = (p0x >> 4) & 8;
					state.extraIndexRegisterBase = (p0x >> 3) & 8;
					state.extraRegisterBaseEVEX = p0x & 0x10;
					p0x >>= 2;
					state.extraBaseRegisterBaseEVEX = p0x & 0x18;
					state.extraBaseRegisterBase = p0x & 8;
				}
				else
				{
					state.vvvv_invalidCheck = p1;
					state.vvvv = p1 & 0x07;
					Static::Assert(static_cast<std::int32_t>(StateFlags::IsInvalid) == 0x40 ? 0 : -1);
					state.flags |= static_cast<StateFlags>((~p2 & 8) << 3);
				}
				std::span<const OpCodeHandler* const> handlers;
				switch (static_cast<std::int32_t>(p0 & 7))
				{
#define MAKE_SPAN(x) (std::span((x).begin(), (x).size()))
				case 1:
					handlers = MAKE_SPAN(OpCodeHandlersTables_EVEX::Handlers_0F);
					break;
				case 2:
					handlers = MAKE_SPAN(OpCodeHandlersTables_EVEX::Handlers_0F38);
					break;
				case 3:
					handlers = MAKE_SPAN(OpCodeHandlersTables_EVEX::Handlers_0F3A);
					break;
				case 5:
					handlers = MAKE_SPAN(OpCodeHandlersTables_EVEX::Handlers_MAP5);
					break;
				case 6:
					handlers = MAKE_SPAN(OpCodeHandlersTables_EVEX::Handlers_MAP6);
					break;
#undef MAKE_SPAN
				default:
					SetInvalidInstruction();
					return;
				}
				auto handler = handlers[static_cast<std::int32_t>(ReadByte())];
				assert(handler->HasModRM);
				std::uint32_t m = ReadByte();
				state.modrm = m;
				state.mod = m >> 6;
				state.reg = (m >> 3) & 7;
				state.rm = m & 7;
				// Invalid if LL=3 and no rc
				Static::Assert(static_cast<std::uint32_t>(StateFlags::b) > 3 ? 0 : -1);
				if (((static_cast<std::uint32_t>(state.flags & StateFlags::b) | state.vectorLength) & invalidCheckMask) == 3)
				{
					SetInvalidInstruction();
				}
				handler->Decode(*this, instruction);
			}
			else
			{
				SetInvalidInstruction();
			}
		}
		else
		{
			if ((options & DecoderOptions::KNC) == 0 || !is64bMode)
			{
				SetInvalidInstruction();
			}
			else
			{
				Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
				state.mandatoryPrefix = static_cast<MandatoryPrefixByte>(p1 & 3);
				Static::Assert(static_cast<std::int32_t>(StateFlags::W) == 0x80 ? 0 : -1);
				state.flags |= static_cast<StateFlags>(p1 & 0x80);
				std::uint32_t aaa = p2 & 7;
				state.aaa = aaa;
				instruction.SetInternalOpMask(aaa);
				Static::Assert(static_cast<std::int32_t>(StateFlags::MvexSssShift) == 16 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(StateFlags::MvexSssMask) == 7 ? 0 : -1);
				Static::Assert(static_cast<std::int32_t>(StateFlags::MvexEH) == 1 << (static_cast<std::int32_t>(StateFlags::MvexSssShift) + 3) ? 0 : -1);
				state.flags |= static_cast<StateFlags>((p2 & 0xF0) << (static_cast<std::int32_t>(StateFlags::MvexSssShift) - 4));
				p1 = (~p1 >> 3) & 0x0F;
				std::uint32_t tmp = (~p2 & 8) << 1;
				state.extraIndexRegisterBaseVSIB = tmp;
				tmp += p1;
				state.vvvv = tmp;
				state.vvvv_invalidCheck = tmp;
				std::uint32_t p0x = ~p0;
				state.extraRegisterBase = (p0x >> 4) & 8;
				state.extraIndexRegisterBase = (p0x >> 3) & 8;
				state.extraRegisterBaseEVEX = p0x & 0x10;
				p0x >>= 2;
				state.extraBaseRegisterBaseEVEX = p0x & 0x18;
				state.extraBaseRegisterBase = p0x & 8;
				std::vector<const OpCodeHandler*> handlers;
				switch (static_cast<std::int32_t>(p0 & 0xF))
				{
				case 1:
					handlers = handlers_MVEX_0F;
					break;
				case 2:
					handlers = handlers_MVEX_0F38;
					break;
				case 3:
					handlers = handlers_MVEX_0F3A;
					break;
				default:
					SetInvalidInstruction();
					return;
				}
				auto handler = handlers[static_cast<std::int32_t>(ReadByte())];
				assert(handler->HasModRM);
				std::uint32_t m = ReadByte();
				state.modrm = m;
				state.mod = m >> 6;
				state.reg = (m >> 3) & 7;
				state.rm = m & 7;
				handler->Decode(*this, instruction);
			}
		}
	}

	Register Decoder::ReadOpSegReg()
	{
		std::uint32_t reg = state.reg;
		if (reg < 6)
		{
			return (Register)(Register::ES + static_cast<std::int32_t>(reg));
		}
		SetInvalidInstruction();
		return Register::None;
	}

	bool Decoder::ReadOpMem(Instruction& instruction)
	{
		assert(state.GetEncoding() != EncodingKind::EVEX && state.GetEncoding() != EncodingKind::MVEX);
		if (state.addressSize == OpSize::Size64)
		{
			return ReadOpMem32Or64(instruction, Register::RAX, Register::RAX, TupleType::N1, false);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			return ReadOpMem32Or64(instruction, Register::EAX, Register::EAX, TupleType::N1, false);
		}
		else
		{
			ReadOpMem16(instruction, TupleType::N1);
			return false;
		}
	}

	void Decoder::ReadOpMemSib(Instruction& instruction)
	{
		assert(state.GetEncoding() != EncodingKind::EVEX && state.GetEncoding() != EncodingKind::MVEX);
		bool isValid;
		if (state.addressSize == OpSize::Size64)
		{
			isValid = ReadOpMem32Or64(instruction, Register::RAX, Register::RAX, TupleType::N1, false);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			isValid = ReadOpMem32Or64(instruction, Register::EAX, Register::EAX, TupleType::N1, false);
		}
		else
		{
			ReadOpMem16(instruction, TupleType::N1);
			isValid = false;
		}
		if (invalidCheckMask != 0 && !isValid)
		{
			SetInvalidInstruction();
		}
	}

	void Decoder::ReadOpMem_MPX(Instruction& instruction)
	{
		assert(state.GetEncoding() != EncodingKind::EVEX && state.GetEncoding() != EncodingKind::MVEX);
		if (is64bMode)
		{
			state.addressSize = OpSize::Size64;
			ReadOpMem32Or64(instruction, Register::RAX, Register::RAX, TupleType::N1, false);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			ReadOpMem32Or64(instruction, Register::EAX, Register::EAX, TupleType::N1, false);
		}
		else
		{
			ReadOpMem16(instruction, TupleType::N1);
			if (invalidCheckMask != 0)
			{
				SetInvalidInstruction();
			}
		}
	}

	void Decoder::ReadOpMem(Instruction& instruction, TupleType tupleType)
	{
		assert(state.GetEncoding() == EncodingKind::EVEX || state.GetEncoding() == EncodingKind::MVEX);
		if (state.addressSize == OpSize::Size64)
		{
			ReadOpMem32Or64(instruction, Register::RAX, Register::RAX, tupleType, false);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			ReadOpMem32Or64(instruction, Register::EAX, Register::EAX, tupleType, false);
		}
		else
		{
			ReadOpMem16(instruction, tupleType);
		}
	}

	void Decoder::ReadOpMem_VSIB(Instruction& instruction, Register vsibIndex, TupleType tupleType)
	{
		bool isValid;
		if (state.addressSize == OpSize::Size64)
		{
			isValid = ReadOpMem32Or64(instruction, Register::RAX, vsibIndex, tupleType, true);
		}
		else if (state.addressSize == OpSize::Size32)
		{
			isValid = ReadOpMem32Or64(instruction, Register::EAX, vsibIndex, tupleType, true);
		}
		else
		{
			ReadOpMem16(instruction, tupleType);
			isValid = false;
		}
		if (invalidCheckMask != 0 && !isValid)
		{
			SetInvalidInstruction();
		}
	}

	void Decoder::ReadOpMem16(Instruction& instruction, TupleType tupleType)
	{
		assert(state.addressSize == OpSize::Size16);
		//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
		//ORIGINAL LINE: var(baseReg, indexReg) = memRegs16[(int)state.rm];
		auto [baseReg, indexReg] = s_memRegs16[static_cast<std::int32_t>(state.rm)];
		switch (static_cast<std::int32_t>(state.mod))
		{
		case 0:
			if (state.rm == 6)
			{
				instruction.InternalSetMemoryDisplSize(2);
				displIndex = state.instructionLength;
				instruction.SetMemoryDisplacement64(ReadUInt16());
				baseReg = Register::None;
				assert(indexReg == Register::None);
			}
			break;
		case 1:
			instruction.InternalSetMemoryDisplSize(1);
			displIndex = state.instructionLength;
			if (tupleType == TupleType::N1)
			{
				instruction.SetMemoryDisplacement64(static_cast<std::uint16_t>(static_cast<std::int8_t>(ReadByte())));
			}
			else
			{
				instruction.SetMemoryDisplacement64(static_cast<std::uint16_t>(GetDisp8N(tupleType) * static_cast<std::uint32_t>(static_cast<std::int8_t>(ReadByte()))));
			}
			break;
		default:
			assert(state.mod == 2);
			instruction.InternalSetMemoryDisplSize(2);
			displIndex = state.instructionLength;
			instruction.SetMemoryDisplacement64(ReadUInt16());
			break;
		}
		instruction.SetInternalMemoryBase(baseReg);
		instruction.SetInternalMemoryIndex(indexReg);
	}

	bool Decoder::ReadOpMem32Or64(Instruction& instruction, Register baseReg, Register indexReg, TupleType tupleType, bool isVsib)
	{
		assert(state.addressSize == OpSize::Size32 || state.addressSize == OpSize::Size64);
		std::uint32_t sib;
		std::uint32_t displSizeScale, displ;
		switch (static_cast<std::int32_t>(state.mod))
		{
		case 0:
			if (state.rm == 4)
			{
				sib = ReadByte();
				displSizeScale = 0;
				displ = 0;
				break;
			}
			else if (state.rm == 5)
			{
				displIndex = state.instructionLength;
				if (state.addressSize == OpSize::Size64)
				{
					instruction.SetMemoryDisplacement64(static_cast<std::uint64_t>(static_cast<std::int32_t>(ReadUInt32())));
					instruction.InternalSetMemoryDisplSize(4);
				}
				else
				{
					instruction.SetMemoryDisplacement64(ReadUInt32());
					instruction.InternalSetMemoryDisplSize(3);
				}
				if (is64bMode)
				{
					if (state.addressSize == OpSize::Size64)
					{
						state.flags |= StateFlags::IpRel64;
						instruction.SetInternalMemoryBase(Register::RIP);
					}
					else
					{
						state.flags |= StateFlags::IpRel32;
						instruction.SetInternalMemoryBase(Register::EIP);
					}
				}
				return false;
			}
			else
			{
				assert(0 <= state.rm && state.rm <= 7 && state.rm != 4 && state.rm != 5);
				instruction.SetInternalMemoryBase((Register)(static_cast<std::int32_t>(state.extraBaseRegisterBase + state.rm) + baseReg));
				return false;
			}
		case 1:
			if (state.rm == 4)
			{
				sib = ReadByte();
				displSizeScale = 1;
				displIndex = state.instructionLength;
				if (tupleType == TupleType::N1)
				{
					displ = static_cast<std::uint32_t>(static_cast<std::int8_t>(ReadByte()));
				}
				else
				{
					displ = GetDisp8N(tupleType) * static_cast<std::uint32_t>(static_cast<std::int8_t>(ReadByte()));
				}
				break;
			}
			else
			{
				assert(0 <= state.rm && state.rm <= 7 && state.rm != 4);
				instruction.InternalSetMemoryDisplSize(1);
				displIndex = state.instructionLength;
				if (state.addressSize == OpSize::Size64)
				{
					if (tupleType == TupleType::N1)
					{
						instruction.SetMemoryDisplacement64(static_cast<std::uint64_t>(static_cast<std::int8_t>(ReadByte())));
					}
					else
					{
						instruction.SetMemoryDisplacement64(static_cast<std::uint64_t>(GetDisp8N(tupleType)) * static_cast<std::uint64_t>(static_cast<std::int8_t>(ReadByte())));
					}
				}
				else
				{
					if (tupleType == TupleType::N1)
					{
						instruction.SetMemoryDisplacement64(static_cast<std::uint32_t>(static_cast<std::int8_t>(ReadByte())));
					}
					else
					{
						instruction.SetMemoryDisplacement64(GetDisp8N(tupleType) * static_cast<std::uint32_t>(static_cast<std::int8_t>(ReadByte())));
					}
				}
				instruction.SetInternalMemoryBase((Register)(static_cast<std::int32_t>(state.extraBaseRegisterBase + state.rm) + baseReg));
				return false;
			}
		default:
			assert(state.mod == 2);
			if (state.rm == 4)
			{
				sib = ReadByte();
				displSizeScale = state.addressSize == OpSize::Size64 ? 4U : 3;
				displIndex = state.instructionLength;
				displ = ReadUInt32();
				break;
			}
			else
			{
				assert(0 <= state.rm && state.rm <= 7 && state.rm != 4);
				displIndex = state.instructionLength;
				if (state.addressSize == OpSize::Size64)
				{
					instruction.SetMemoryDisplacement64(static_cast<std::uint64_t>(static_cast<std::int32_t>(ReadUInt32())));
					instruction.InternalSetMemoryDisplSize(4);
				}
				else
				{
					instruction.SetMemoryDisplacement64(ReadUInt32());
					instruction.InternalSetMemoryDisplSize(3);
				}
				instruction.SetInternalMemoryBase((Register)(static_cast<std::int32_t>(state.extraBaseRegisterBase + state.rm) + baseReg));
				return false;
			}
		}
		std::uint32_t index = ((sib >> 3) & 7) + state.extraIndexRegisterBase;
		std::uint32_t base = sib & 7;
		instruction.SetInternalMemoryIndexScale(static_cast<std::int32_t>(sib >> 6));
		if (!isVsib)
		{
			if (index != 4)
			{
				instruction.SetInternalMemoryIndex((Register)(static_cast<std::int32_t>(index) + indexReg));
			}
		}
		else
		{
			instruction.SetInternalMemoryIndex((Register)(static_cast<std::int32_t>(index + state.extraIndexRegisterBaseVSIB) + indexReg));
		}
		if (base == 5 && state.mod == 0)
		{
			displIndex = state.instructionLength;
			if (state.addressSize == OpSize::Size64)
			{
				instruction.SetMemoryDisplacement64(static_cast<std::uint64_t>(static_cast<std::int32_t>(ReadUInt32())));
				instruction.InternalSetMemoryDisplSize(4);
			}
			else
			{
				instruction.SetMemoryDisplacement64(ReadUInt32());
				instruction.InternalSetMemoryDisplSize(3);
			}
		}
		else
		{
			instruction.SetInternalMemoryBase((Register)(static_cast<std::int32_t>(base + state.extraBaseRegisterBase) + baseReg));
			instruction.InternalSetMemoryDisplSize(displSizeScale);
			if (state.addressSize == OpSize::Size64)
			{
				instruction.SetMemoryDisplacement64(static_cast<std::uint64_t>(static_cast<std::int32_t>(displ)));
			}
			else
			{
				instruction.SetMemoryDisplacement64(displ);
			}
		}
		return true;
	}

	std::uint32_t Decoder::GetDisp8N(TupleType tupleType)
	{
		return TupleTypeTable::GetDisp8N(tupleType, (state.flags & StateFlags::b) != 0);
	}

	ConstantOffsets Decoder::GetConstantOffsets(const Instruction& instruction)
	{
		ConstantOffsets constantOffsets = Iced::Intel::ConstantOffsets();
		std::int32_t displSize = instruction.GetMemoryDisplSize();
		if (displSize != 0)
		{
			constantOffsets.DisplacementOffset = static_cast<std::uint8_t>(displIndex);
			if (displSize == 8 && (state.flags & StateFlags::Addr64) == 0)
			{
				constantOffsets.DisplacementSize = 4;
			}
			else
			{
				constantOffsets.DisplacementSize = static_cast<std::uint8_t>(displSize);
			}
		}
		if ((state.flags & StateFlags::NoImm) == 0)
		{
			std::int32_t extraImmSub = 0;
			for (std::int32_t i = instruction.GetOpCount() - 1; i >= 0; i--)
			{
				switch (instruction.GetOpKind(i))
				{
				case OpKind::Immediate8:
				case OpKind::Immediate8to16:
				case OpKind::Immediate8to32:
				case OpKind::Immediate8to64:
					constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - extraImmSub - 1);
					constantOffsets.ImmediateSize = 1;
					goto after_imm_loop;
				case OpKind::Immediate16:
					constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - extraImmSub - 2);
					constantOffsets.ImmediateSize = 2;
					goto after_imm_loop;
				case OpKind::Immediate32:
				case OpKind::Immediate32to64:
					constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - extraImmSub - 4);
					constantOffsets.ImmediateSize = 4;
					goto after_imm_loop;
				case OpKind::Immediate64:
					constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - extraImmSub - 8);
					constantOffsets.ImmediateSize = 8;
					goto after_imm_loop;
				case OpKind::Immediate8_2nd:
					constantOffsets.ImmediateOffset2 = static_cast<std::uint8_t>(instruction.GetLength() - 1);
					constantOffsets.ImmediateSize2 = 1;
					extraImmSub = 1;
					break;
				case OpKind::NearBranch16:
					if ((state.flags & StateFlags::BranchImm8) != 0)
					{
						constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - 1);
						constantOffsets.ImmediateSize = 1;
					}
					else if ((state.flags & StateFlags::Xbegin) == 0)
					{
						constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - 2);
						constantOffsets.ImmediateSize = 2;
					}
					else
					{
						assert((state.flags & StateFlags::Xbegin) != 0);
						if (state.operandSize != OpSize::Size16)
						{
							constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - 4);
							constantOffsets.ImmediateSize = 4;
						}
						else
						{
							constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - 2);
							constantOffsets.ImmediateSize = 2;
						}
					}
					break;
				case OpKind::NearBranch32:
				case OpKind::NearBranch64:
					if ((state.flags & StateFlags::BranchImm8) != 0)
					{
						constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - 1);
						constantOffsets.ImmediateSize = 1;
					}
					else if ((state.flags & StateFlags::Xbegin) == 0)
					{
						constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - 4);
						constantOffsets.ImmediateSize = 4;
					}
					else
					{
						assert((state.flags & StateFlags::Xbegin) != 0);
						if (state.operandSize != OpSize::Size16)
						{
							constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - 4);
							constantOffsets.ImmediateSize = 4;
						}
						else
						{
							constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - 2);
							constantOffsets.ImmediateSize = 2;
						}
					}
					break;
				case OpKind::FarBranch16:
					constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - (2 + 2));
					constantOffsets.ImmediateSize = 2;
					constantOffsets.ImmediateOffset2 = static_cast<std::uint8_t>(instruction.GetLength() - 2);
					constantOffsets.ImmediateSize2 = 2;
					break;
				case OpKind::FarBranch32:
					constantOffsets.ImmediateOffset = static_cast<std::uint8_t>(instruction.GetLength() - (4 + 2));
					constantOffsets.ImmediateSize = 4;
					constantOffsets.ImmediateOffset2 = static_cast<std::uint8_t>(instruction.GetLength() - 2);
					constantOffsets.ImmediateSize2 = 2;
					break;
				}
			}
		}
	after_imm_loop:
		return constantOffsets;
	}
}
