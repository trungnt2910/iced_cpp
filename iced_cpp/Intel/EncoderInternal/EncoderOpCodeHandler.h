#pragma once

// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "EncoderOpCodeHandler.defs.h"
#include "OpTables.g.h"
#include "../MandatoryPrefixByte.g.h"
#include "../Static.h"
#include "../TupleTypeTable.h"
#include "../RoundingControl.g.h"
#include "../MvexInfo.h"
#include "../MvexTupleTypeLut.g.h"
#include "../OpKind.g.h"
#include "../MvexRegMemConv.g.h"
#include "../MvexEHBit.g.h"
#include "OpHandlers.h"

#include "../Encoder.h"

namespace Iced::Intel::EncoderInternal
{
	inline void InvalidHandler::Encode(Encoder& encoder, const Instruction& instruction) const
	{
		encoder.SetErrorMessage(std::string(ERROR_MESSAGE));
	}

	inline void DeclareDataHandler::Encode(Encoder& encoder, const Instruction& instruction) const
	{
		auto declDataCount = instruction.GetDeclareDataCount();
		if (declDataCount < 1 || declDataCount > maxLength)
		{
			encoder.SetErrorMessage(std::format("Invalid db/dw/dd/dq data count. Count = {0:s}, max count = {1:s}", declDataCount, maxLength));
			return;
		}
		std::int32_t length = declDataCount * elemLength;
		for (std::int32_t i = 0; i < length; i++)
		{
			encoder.WriteByteInternal(instruction.GetDeclareByteValue(i));
		}
	}

	constexpr OpContainer LegacyHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask));
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::LegacyOps[op0 - 1], OpHandlerData::LegacyOps[op1 - 1], OpHandlerData::LegacyOps[op2 - 1], OpHandlerData::LegacyOps[op3 - 1]}));
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::LegacyOps[op0 - 1], OpHandlerData::LegacyOps[op1 - 1], OpHandlerData::LegacyOps[op2 - 1]}));
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::LegacyOps[op0 - 1], OpHandlerData::LegacyOps[op1 - 1]}));
		}
		if (op0 != 0)
		{
			return OpContainer(std::to_array<const Op*>({OpHandlerData::LegacyOps[op0 - 1]}));
		}
		return OpContainer();
	}

	inline void LegacyHandler::Encode(Encoder& encoder, const Instruction& instruction) const
	{
		std::uint32_t b = mandatoryPrefix;
		encoder.WritePrefixes(instruction, b != 0xF3);
		if (b != 0)
		{
			encoder.WriteByteInternal(b);
		}
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::B) == 0x01 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::X) == 0x02 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::R) == 0x04 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::W) == 0x08 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::REX) == 0x40 ? 0 : -1);
		b = static_cast<std::uint32_t>(encoder.EncoderFlags);
		b &= 0x4F;
		if (b != 0)
		{
			if ((encoder.EncoderFlags & EncoderFlags::HighLegacy8BitRegs) != 0)
			{
				encoder.SetErrorMessage("Registers AH, CH, DH, BH can't be used if there's a REX prefix. Use AL, CL, DL, BL, SPL, BPL, SIL, DIL, R8L-R15L instead.");
			}
			b |= 0x40;
			encoder.WriteByteInternal(b);
		}
		if ((b = tableByte1) != 0)
		{
			encoder.WriteByteInternal(b);
			if ((b = tableByte2) != 0)
			{
				encoder.WriteByteInternal(b);
			}
		}
	}

	constexpr OpContainer VexHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		auto op4 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op4Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		if (op4 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0 && op3 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::VexOps[op0 - 1], OpHandlerData::VexOps[op1 - 1], OpHandlerData::VexOps[op2 - 1], OpHandlerData::VexOps[op3 - 1], OpHandlerData::VexOps[op4 - 1]}));
		}
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::VexOps[op0 - 1], OpHandlerData::VexOps[op1 - 1], OpHandlerData::VexOps[op2 - 1], OpHandlerData::VexOps[op3 - 1]}));
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::VexOps[op0 - 1], OpHandlerData::VexOps[op1 - 1], OpHandlerData::VexOps[op2 - 1]}));
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::VexOps[op0 - 1], OpHandlerData::VexOps[op1 - 1]}));
		}
		if (op0 != 0)
		{
			return OpContainer(std::to_array<const Op*>({OpHandlerData::VexOps[op0 - 1]}));
		}
		return OpContainer();
	}

	inline void VexHandler::Encode(Encoder& encoder, const Instruction& instruction) const
	{
		encoder.WritePrefixes(instruction);
		std::uint32_t encoderFlags = static_cast<std::uint32_t>(encoder.EncoderFlags);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		std::uint32_t b = lastByte;
		b |= (~encoderFlags >> (static_cast<std::int32_t>(EncoderFlags::VvvvvShift) - 3)) & 0x78;
		if ((encoder.Internal_PreventVEX2 | W1 | (table - static_cast<std::uint32_t>(VexOpCodeTable::MAP0F)) | (encoderFlags & static_cast<std::uint32_t>(EncoderFlags::X | EncoderFlags::B | EncoderFlags::W))) != 0)
		{
			encoder.WriteByteInternal(0xC4);
			Static::Assert(static_cast<std::int32_t>(VexOpCodeTable::MAP0F) == 1 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(VexOpCodeTable::MAP0F38) == 2 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(VexOpCodeTable::MAP0F3A) == 3 ? 0 : -1);
			std::uint32_t b2 = table;
			Static::Assert(static_cast<std::int32_t>(EncoderFlags::B) == 1 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(EncoderFlags::X) == 2 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(EncoderFlags::R) == 4 ? 0 : -1);
			b2 |= (~encoderFlags & 7) << 5;
			encoder.WriteByteInternal(b2);
			b |= mask_W_L & encoder.Internal_VEX_WIG_LIG;
			encoder.WriteByteInternal(b);
		}
		else
		{
			encoder.WriteByteInternal(0xC5);
			Static::Assert(static_cast<std::int32_t>(EncoderFlags::R) == 4 ? 0 : -1);
			b |= (~encoderFlags & 4) << 5;
			b |= mask_L & encoder.Internal_VEX_LIG;
			encoder.WriteByteInternal(b);
		}
	}

	constexpr OpContainer XopHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask));
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::XopOps[op0 - 1], OpHandlerData::XopOps[op1 - 1], OpHandlerData::XopOps[op2 - 1], OpHandlerData::XopOps[op3 - 1]}));
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::XopOps[op0 - 1], OpHandlerData::XopOps[op1 - 1], OpHandlerData::XopOps[op2 - 1]}));
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::XopOps[op0 - 1], OpHandlerData::XopOps[op1 - 1]}));
		}
		if (op0 != 0)
		{
			return OpContainer(std::to_array<const Op*>({OpHandlerData::XopOps[op0 - 1]}));
		}
		return OpContainer();
	}

	inline void XopHandler::Encode(Encoder& encoder, const Instruction& instruction) const
	{
		encoder.WritePrefixes(instruction);
		encoder.WriteByteInternal(0x8F);
		std::uint32_t encoderFlags = static_cast<std::uint32_t>(encoder.EncoderFlags);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		std::uint32_t b = table;
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::B) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::X) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::R) == 4 ? 0 : -1);
		b |= (~encoderFlags & 7) << 5;
		encoder.WriteByteInternal(b);
		b = lastByte;
		b |= (~encoderFlags >> (static_cast<std::int32_t>(EncoderFlags::VvvvvShift) - 3)) & 0x78;
		encoder.WriteByteInternal(b);
	}

	constexpr OpContainer EvexHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask));
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::EvexOps[op0 - 1], OpHandlerData::EvexOps[op1 - 1], OpHandlerData::EvexOps[op2 - 1], OpHandlerData::EvexOps[op3 - 1]}));
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::EvexOps[op0 - 1], OpHandlerData::EvexOps[op1 - 1], OpHandlerData::EvexOps[op2 - 1]}));
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::EvexOps[op0 - 1], OpHandlerData::EvexOps[op1 - 1]}));
		}
		if (op0 != 0)
		{
			return OpContainer(std::to_array<const Op*>({OpHandlerData::EvexOps[op0 - 1]}));
		}
		return OpContainer();
	}

	inline bool EvexHandler::TryConvertToDisp8NImpl::TryConvertToDisp8N(Encoder& encoder, const OpCodeHandler* handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue)
	{
		auto evexHandler = dynamic_cast<const EvexHandler*>(handler);
		std::int32_t n = static_cast<std::int32_t>(TupleTypeTable::GetDisp8N(evexHandler->tupleType, (encoder.EncoderFlags & EncoderFlags::Broadcast) != 0));
		std::int32_t res = displ / n;
		if (res * n == displ && std::numeric_limits<std::int8_t>::min() <= res && res <= std::numeric_limits<std::int8_t>::max())
		{
			compressedValue = static_cast<std::int8_t>(res);
			return true;
		}
		compressedValue = 0;
		return false;
	}

	inline void EvexHandler::Encode(Encoder& encoder, const Instruction& instruction) const
	{
		encoder.WritePrefixes(instruction);
		std::uint32_t encoderFlags = static_cast<std::uint32_t>(encoder.EncoderFlags);
		encoder.WriteByteInternal(0x62);
		Static::Assert(static_cast<std::int32_t>(EvexOpCodeTable::MAP0F) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EvexOpCodeTable::MAP0F38) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EvexOpCodeTable::MAP0F3A) == 3 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EvexOpCodeTable::MAP5) == 5 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EvexOpCodeTable::MAP6) == 6 ? 0 : -1);
		std::uint32_t b = table;
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::B) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::X) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::R) == 4 ? 0 : -1);
		b |= (encoderFlags & 7) << 5;
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::R2) == 0x00000200 ? 0 : -1);
		b |= (encoderFlags >> (9 - 4)) & 0x10;
		b ^= ~0xFU;
		encoder.WriteByteInternal(b);
		b = p1Bits;
		b |= (~encoderFlags >> (static_cast<std::int32_t>(EncoderFlags::VvvvvShift) - 3)) & 0x78;
		b |= mask_W & encoder.Internal_EVEX_WIG;
		encoder.WriteByteInternal(b);
		b = instruction.GetInternalOpMask();
		if (b != 0)
		{
			if ((EncFlags3 & EncFlags3::OpMaskRegister) == 0)
			{
				encoder.SetErrorMessage("The instruction doesn't support opmask registers");
			}
		}
		else
		{
			if ((EncFlags3 & EncFlags3::RequireOpMaskRegister) != 0)
			{
				encoder.SetErrorMessage("The instruction must use an opmask register");
			}
		}
		b |= (encoderFlags >> (static_cast<std::int32_t>(EncoderFlags::VvvvvShift) + 4 - 3)) & 8;
		if (instruction.GetSuppressAllExceptions())
		{
			if ((EncFlags3 & EncFlags3::SuppressAllExceptions) == 0)
			{
				encoder.SetErrorMessage("The instruction doesn't support suppress-all-exceptions");
			}
			b |= 0x10;
		}
		auto rc = instruction.GetRoundingControl();
		if (rc != RoundingControl::None)
		{
			if ((EncFlags3 & EncFlags3::RoundingControl) == 0)
			{
				encoder.SetErrorMessage("The instruction doesn't support rounding control");
			}
			b |= 0x10;
			Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
			b |= static_cast<std::uint32_t>(rc - RoundingControl::RoundToNearest) << 5;
		}
		else if ((EncFlags3 & EncFlags3::SuppressAllExceptions) == 0 || !instruction.GetSuppressAllExceptions())
		{
			b |= llBits;
		}
		if ((encoderFlags & static_cast<std::uint32_t>(EncoderFlags::Broadcast)) != 0)
		{
			b |= 0x10;
		}
		else if (instruction.IsBroadcast())
		{
			encoder.SetErrorMessage("The instruction doesn't support broadcasting");
		}
		if (instruction.GetZeroingMasking())
		{
			if ((EncFlags3 & EncFlags3::ZeroingMasking) == 0)
			{
				encoder.SetErrorMessage("The instruction doesn't support zeroing masking");
			}
			b |= 0x80;
		}
		b ^= 8;
		b |= mask_LL & encoder.Internal_EVEX_LIG;
		encoder.WriteByteInternal(b);
	}

	constexpr OpContainer MvexHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask));
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::MvexOps[op0 - 1], OpHandlerData::MvexOps[op1 - 1], OpHandlerData::MvexOps[op2 - 1], OpHandlerData::MvexOps[op3 - 1]}));
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::MvexOps[op0 - 1], OpHandlerData::MvexOps[op1 - 1], OpHandlerData::MvexOps[op2 - 1]}));
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return OpContainer(std::to_array<const Op*>({OpHandlerData::MvexOps[op0 - 1], OpHandlerData::MvexOps[op1 - 1]}));
		}
		if (op0 != 0)
		{
			return OpContainer(std::to_array<const Op*>({OpHandlerData::MvexOps[op0 - 1]}));
		}
		return OpContainer();
	}

	inline bool MvexHandler::TryConvertToDisp8NImpl::TryConvertToDisp8N(Encoder& encoder, const OpCodeHandler* handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue)
	{
		auto mvex = MvexInfo(instruction.GetCode());
		std::int32_t sss = (static_cast<std::int32_t>(instruction.GetMvexRegMemConv()) - static_cast<std::int32_t>(MvexRegMemConv::MemConvNone)) & 7;
		auto tupleType = static_cast<TupleType>(MvexTupleTypeLut::Data[static_cast<std::int32_t>(mvex.GetTupleTypeLutKind()) * 8 + sss]);
		std::int32_t n = static_cast<std::int32_t>(TupleTypeTable::GetDisp8N(tupleType, false));
		std::int32_t res = displ / n;
		if (res * n == displ && std::numeric_limits<std::int8_t>::min() <= res && res <= std::numeric_limits<std::int8_t>::max())
		{
			compressedValue = static_cast<std::int8_t>(res);
			return true;
		}
		compressedValue = 0;
		return false;
	}

	inline void MvexHandler::Encode(Encoder& encoder, const Instruction& instruction) const
	{
		encoder.WritePrefixes(instruction);
		std::uint32_t encoderFlags = static_cast<std::uint32_t>(encoder.EncoderFlags);
		encoder.WriteByteInternal(0x62);
		Static::Assert(static_cast<std::int32_t>(MvexOpCodeTable::MAP0F) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MvexOpCodeTable::MAP0F38) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MvexOpCodeTable::MAP0F3A) == 3 ? 0 : -1);
		std::uint32_t b = table;
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::B) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::X) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::R) == 4 ? 0 : -1);
		b |= (encoderFlags & 7) << 5;
		Static::Assert(static_cast<std::int32_t>(EncoderFlags::R2) == 0x00000200 ? 0 : -1);
		b |= (encoderFlags >> (9 - 4)) & 0x10;
		b ^= ~0xFU;
		encoder.WriteByteInternal(b);
		b = p1Bits;
		b |= (~encoderFlags >> (static_cast<std::int32_t>(EncoderFlags::VvvvvShift) - 3)) & 0x78;
		b |= mask_W & encoder.Internal_MVEX_WIG;
		encoder.WriteByteInternal(b);
		b = instruction.GetInternalOpMask();
		if (b != 0)
		{
			if ((EncFlags3 & EncFlags3::OpMaskRegister) == 0)
			{
				encoder.SetErrorMessage("The instruction doesn't support opmask registers");
			}
		}
		else
		{
			if ((EncFlags3 & EncFlags3::RequireOpMaskRegister) != 0)
			{
				encoder.SetErrorMessage("The instruction must use an opmask register");
			}
		}
		b |= (encoderFlags >> (static_cast<std::int32_t>(EncoderFlags::VvvvvShift) + 4 - 3)) & 8;
		auto mvex = MvexInfo(instruction.GetCode());
		auto conv = instruction.GetMvexRegMemConv();
		// Memory ops can only be op0-op2, never op3 (imm8)
		if (instruction.GetOp0Kind() == OpKind::Memory || instruction.GetOp1Kind() == OpKind::Memory || instruction.GetOp2Kind() == OpKind::Memory)
		{
			if (conv >= MvexRegMemConv::MemConvNone && conv <= MvexRegMemConv::MemConvSint16)
			{
				b |= (static_cast<std::uint32_t>(conv) - static_cast<std::uint32_t>(MvexRegMemConv::MemConvNone)) << 4;
			}
			else if (conv == MvexRegMemConv::None)
			{
				// Nothing, treat it as MvexRegMemConv.MemConvNone
			}
			else
			{
				encoder.SetErrorMessage("Memory operands must use a valid MvexRegMemConv variant, eg. MvexRegMemConv.MemConvNone");
			}
			if (instruction.IsMvexEvictionHint())
			{
				if (mvex.GetCanUseEvictionHint())
				{
					b |= 0x80;
				}
				else
				{
					encoder.SetErrorMessage("This instruction doesn't support eviction hint (`{eh}`)");
				}
			}
		}
		else
		{
			if (instruction.IsMvexEvictionHint())
			{
				encoder.SetErrorMessage("Only memory operands can enable eviction hint (`{eh}`)");
			}
			if (conv == MvexRegMemConv::None)
			{
				b |= 0x80;
				if (instruction.GetSuppressAllExceptions())
				{
					b |= 0x40;
					if ((EncFlags3 & EncFlags3::SuppressAllExceptions) == 0)
					{
						encoder.SetErrorMessage("The instruction doesn't support suppress-all-exceptions");
					}
				}
				auto rc = instruction.GetRoundingControl();
				if (rc == RoundingControl::None)
				{
					// Nothing
				}
				else
				{
					if ((EncFlags3 & EncFlags3::RoundingControl) == 0)
					{
						encoder.SetErrorMessage("The instruction doesn't support rounding control");
					}
					else
					{
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundToNearest) == 1 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundDown) == 2 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundUp) == 3 ? 0 : -1);
						Static::Assert(static_cast<std::int32_t>(RoundingControl::RoundTowardZero) == 4 ? 0 : -1);
						b |= (static_cast<std::uint32_t>(rc) - static_cast<std::uint32_t>(RoundingControl::RoundToNearest)) << 4;
					}
				}
			}
			else if (conv >= MvexRegMemConv::RegSwizzleNone && conv <= MvexRegMemConv::RegSwizzleDddd)
			{
				if (instruction.GetSuppressAllExceptions())
				{
					encoder.SetErrorMessage("Can't use {sae} with register swizzles");
				}
				else if (instruction.GetRoundingControl() != RoundingControl::None)
				{
					encoder.SetErrorMessage("Can't use rounding control with register swizzles");
				}
				b |= ((static_cast<std::uint32_t>(conv) - static_cast<std::uint32_t>(MvexRegMemConv::RegSwizzleNone)) & 7) << 4;
			}
			else
			{
				encoder.SetErrorMessage("Register operands can't use memory up/down conversions");
			}
		}
		if (mvex.GetEHBit() == MvexEHBit::EH1)
		{
			b |= 0x80;
		}
		b ^= 8;
		encoder.WriteByteInternal(b);
	}

	inline void D3nowHandler::Encode(Encoder& encoder, const Instruction& instruction) const
	{
		encoder.WritePrefixes(instruction);
		encoder.WriteByteInternal(0x0F);
		encoder.ImmSize = ImmSize::Size1OpCode;
		encoder.Immediate = immediate;
	}
}
