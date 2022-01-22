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

#include "EncoderOpCodeHandler.h"
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

#include "../Encoder.h"

namespace Iced::Intel::EncoderInternal
{
	OpCodeHandler::OpCodeHandler(EncFlags2 encFlags2, enum EncFlags3 encFlags3, bool isDeclareData, const std::optional<TryConvertToDisp8N_>& tryConvertToDisp8N, const std::vector<std::shared_ptr<Op>>& operands)
	{
		EncFlags3 = encFlags3;
		OpCode = GetOpCode(encFlags2);
		Is2ByteOpCode = (encFlags2 & EncFlags2::OpCodeIs2Bytes) != 0;
		GroupIndex = (encFlags2 & EncFlags2::HasGroupIndex) == 0 ? -1 : static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::GroupIndexShift)) & 7);
		RmGroupIndex = (encFlags3 & EncFlags3::HasRmGroupIndex) == 0 ? -1 : static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::GroupIndexShift)) & 7);
		IsDeclareData = isDeclareData;
		OpSize = static_cast<CodeSize>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::OperandSizeShift)) & static_cast<std::uint32_t>(EncFlags3::OperandSizeMask));
		AddrSize = static_cast<CodeSize>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::AddressSizeShift)) & static_cast<std::uint32_t>(EncFlags3::AddressSizeMask));
		// HACK: C++'s nullptr resovles to an std::optional _with_ a value but still invalid. Ignore that.
		TryConvertToDisp8N = (tryConvertToDisp8N.value_or(nullptr)) ? tryConvertToDisp8N : std::optional<TryConvertToDisp8N_>(std::nullopt);
		Operands = operands;
	}

	std::uint32_t OpCodeHandler::GetOpCode(EncFlags2 encFlags2)
	{
		return static_cast<std::uint16_t>(static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::OpCodeShift));
	}

	const std::string InvalidHandler::ERROR_MESSAGE = "Can't encode an invalid instruction";

	InvalidHandler::InvalidHandler() : OpCodeHandler(EncFlags2::None, EncFlags3::Bit16or32 | EncFlags3::Bit64, false, std::nullopt, std::vector<std::shared_ptr<Op>>())
	{
	}

	void InvalidHandler::Encode(Encoder& encoder, const Instruction& instruction)
	{
		encoder.SetErrorMessage(ERROR_MESSAGE);
	}

	DeclareDataHandler::DeclareDataHandler(Code code) : OpCodeHandler(EncFlags2::None, EncFlags3::Bit16or32 | EncFlags3::Bit64, true, std::nullopt, std::vector<std::shared_ptr<Op>>())
	{
		auto switchTempVar_0 = code;


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: elemLength = (switchTempVar_0 == Code.DeclareByte) ? (byte)1 : (switchTempVar_0 == Code.DeclareWord) ? (byte)2 : (switchTempVar_0 == Code.DeclareDword) ? (byte)4 : (switchTempVar_0 == Code.DeclareQword) ? (byte)8 : throw new InvalidOperationException();
		elemLength = (switchTempVar_0 == Code::DeclareByte) ? static_cast<std::uint8_t>(1) : (switchTempVar_0 == Code::DeclareWord) ? static_cast<std::uint8_t>(2) : (switchTempVar_0 == Code::DeclareDword) ? static_cast<std::uint8_t>(4) : (switchTempVar_0 == Code::DeclareQword) ? static_cast<std::uint8_t>(8) : throw InvalidOperationException();
		maxLength = 16 / elemLength;
	}

	void DeclareDataHandler::Encode(Encoder& encoder, const Instruction& instruction)
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

	std::vector<std::shared_ptr<Op>> LegacyHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask));
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetLegacyOps()[op0 - 1], OpHandlerData::GetLegacyOps()[op1 - 1], OpHandlerData::GetLegacyOps()[op2 - 1], OpHandlerData::GetLegacyOps()[op3 - 1]};
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetLegacyOps()[op0 - 1], OpHandlerData::GetLegacyOps()[op1 - 1], OpHandlerData::GetLegacyOps()[op2 - 1]};
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetLegacyOps()[op0 - 1], OpHandlerData::GetLegacyOps()[op1 - 1]};
		}
		if (op0 != 0)
		{
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetLegacyOps()[op0 - 1]};
		}
		return std::vector<std::shared_ptr<Op>>();
	}

	LegacyHandler::LegacyHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) : OpCodeHandler(encFlags2, encFlags3, false, nullptr, CreateOps(encFlags1))
	{
		switch (static_cast<LegacyOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask)))
		{
		case LegacyOpCodeTable::MAP0:
			tableByte1 = 0;
			tableByte2 = 0;
			break;
		case LegacyOpCodeTable::MAP0F:
			tableByte1 = 0x0F;
			tableByte2 = 0;
			break;
		case LegacyOpCodeTable::MAP0F38:
			tableByte1 = 0x0F;
			tableByte2 = 0x38;
			break;
		case LegacyOpCodeTable::MAP0F3A:
			tableByte1 = 0x0F;
			tableByte2 = 0x3A;
			break;
		default:
			throw InvalidOperationException();
		}
		auto switchTempVar_1 = static_cast<MandatoryPrefixByte>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::MandatoryPrefixShift)) & static_cast<std::uint32_t>(EncFlags2::MandatoryPrefixMask));


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: mandatoryPrefix = (switchTempVar_1 == MandatoryPrefixByte.None) ? (byte)0x0 : (switchTempVar_1 == MandatoryPrefixByte.P66) ? (byte)0x66 : (switchTempVar_1 == MandatoryPrefixByte.PF3) ? (byte)0xF3 : (switchTempVar_1 == MandatoryPrefixByte.PF2) ? (byte)0xF2 : throw new InvalidOperationException();
		mandatoryPrefix = (switchTempVar_1 == MandatoryPrefixByte::None) ? static_cast<std::uint8_t>(0x0) : (switchTempVar_1 == MandatoryPrefixByte::P66) ? static_cast<std::uint8_t>(0x66) : (switchTempVar_1 == MandatoryPrefixByte::PF3) ? static_cast<std::uint8_t>(0xF3) : (switchTempVar_1 == MandatoryPrefixByte::PF2) ? static_cast<std::uint8_t>(0xF2) : throw InvalidOperationException();
	}

	void LegacyHandler::Encode(Encoder& encoder, const Instruction& instruction)
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

	std::vector<std::shared_ptr<Op>> VexHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		auto op4 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op4Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask));
		if (op4 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0 && op3 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetVexOps()[op0 - 1], OpHandlerData::GetVexOps()[op1 - 1], OpHandlerData::GetVexOps()[op2 - 1], OpHandlerData::GetVexOps()[op3 - 1], OpHandlerData::GetVexOps()[op4 - 1]};
		}
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetVexOps()[op0 - 1], OpHandlerData::GetVexOps()[op1 - 1], OpHandlerData::GetVexOps()[op2 - 1], OpHandlerData::GetVexOps()[op3 - 1]};
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetVexOps()[op0 - 1], OpHandlerData::GetVexOps()[op1 - 1], OpHandlerData::GetVexOps()[op2 - 1]};
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetVexOps()[op0 - 1], OpHandlerData::GetVexOps()[op1 - 1]};
		}
		if (op0 != 0)
		{
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetVexOps()[op0 - 1]};
		}
		return std::vector<std::shared_ptr<Op>>();
	}

	VexHandler::VexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) : OpCodeHandler(encFlags2, encFlags3, false, nullptr, CreateOps(encFlags1))
	{
		table = (static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask);
		auto wbit = static_cast<WBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::WBitShift)) & static_cast<std::uint32_t>(EncFlags2::WBitMask));
		W1 = wbit == WBit::W1 ? std::numeric_limits<std::uint32_t>::max() : 0;
		auto lbit = static_cast<LBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::LBitShift)) & static_cast<std::int32_t>(EncFlags2::LBitMask));
		switch (lbit)
		{
		case LBit::L1:
		case LBit::L256:
			lastByte = 4;
			break;
		}
		if (W1 != 0)
		{
			lastByte |= 0x80;
		}
		lastByte |= (static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::MandatoryPrefixShift)) & static_cast<std::uint32_t>(EncFlags2::MandatoryPrefixMask);
		if (wbit == WBit::WIG)
		{
			mask_W_L |= 0x80;
		}
		if (lbit == LBit::LIG)
		{
			mask_W_L |= 4;
			mask_L |= 4;
		}
	}

	void VexHandler::Encode(Encoder& encoder, const Instruction& instruction)
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

	std::vector<std::shared_ptr<Op>> XopHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask));
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetXopOps()[op0 - 1], OpHandlerData::GetXopOps()[op1 - 1], OpHandlerData::GetXopOps()[op2 - 1], OpHandlerData::GetXopOps()[op3 - 1]};
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetXopOps()[op0 - 1], OpHandlerData::GetXopOps()[op1 - 1], OpHandlerData::GetXopOps()[op2 - 1]};
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetXopOps()[op0 - 1], OpHandlerData::GetXopOps()[op1 - 1]};
		}
		if (op0 != 0)
		{
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetXopOps()[op0 - 1]};
		}
		return std::vector<std::shared_ptr<Op>>();
	}

	XopHandler::XopHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) : OpCodeHandler(encFlags2, encFlags3, false, nullptr, CreateOps(encFlags1))
	{
		Static::Assert(static_cast<std::int32_t>(XopOpCodeTable::MAP8) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(XopOpCodeTable::MAP9) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(XopOpCodeTable::MAP10) == 2 ? 0 : -1);
		table = 8 + ((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask));
		assert(table == 8 || table == 9 || table == 10);
		switch (static_cast<LBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::LBitShift)) & static_cast<std::int32_t>(EncFlags2::LBitMask)))
		{
		case LBit::L1:
		case LBit::L256:
			lastByte = 4;
			break;
		}
		auto wbit = static_cast<WBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::WBitShift)) & static_cast<std::uint32_t>(EncFlags2::WBitMask));
		if (wbit == WBit::W1)
		{
			lastByte |= 0x80;
		}
		lastByte |= (static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::MandatoryPrefixShift)) & static_cast<std::uint32_t>(EncFlags2::MandatoryPrefixMask);
	}

	void XopHandler::Encode(Encoder& encoder, const Instruction& instruction)
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

	std::vector<std::shared_ptr<Op>> EvexHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask));
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetEvexOps()[op0 - 1], OpHandlerData::GetEvexOps()[op1 - 1], OpHandlerData::GetEvexOps()[op2 - 1], OpHandlerData::GetEvexOps()[op3 - 1]};
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetEvexOps()[op0 - 1], OpHandlerData::GetEvexOps()[op1 - 1], OpHandlerData::GetEvexOps()[op2 - 1]};
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetEvexOps()[op0 - 1], OpHandlerData::GetEvexOps()[op1 - 1]};
		}
		if (op0 != 0)
		{
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetEvexOps()[op0 - 1]};
		}
		return std::vector<std::shared_ptr<Op>>();
	}

	TryConvertToDisp8N EvexHandler::tryConvertToDisp8N = TryConvertToDisp8NImpl::TryConvertToDisp8N;

	EvexHandler::EvexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) : OpCodeHandler(encFlags2, encFlags3, false, tryConvertToDisp8N, CreateOps(encFlags1))
	{
		tupleType = static_cast<TupleType>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::TupleTypeShift)) & static_cast<std::uint32_t>(EncFlags3::TupleTypeMask));
		table = (static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		p1Bits = 4 | ((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::MandatoryPrefixShift)) & static_cast<std::uint32_t>(EncFlags2::MandatoryPrefixMask));
		wbit = static_cast<WBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::WBitShift)) & static_cast<std::uint32_t>(EncFlags2::WBitMask));
		if (wbit == WBit::W1)
		{
			p1Bits |= 0x80;
		}
		switch (static_cast<LBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::LBitShift)) & static_cast<std::int32_t>(EncFlags2::LBitMask)))
		{
		case LBit::LIG:
			llBits = 0 << 5;
			mask_LL = 3 << 5;
			break;
		case LBit::L0:
		case LBit::LZ:
		case LBit::L128:
			llBits = 0 << 5;
			break;
		case LBit::L1:
		case LBit::L256:
			llBits = 1 << 5;
			break;
		case LBit::L512:
			llBits = 2 << 5;
			break;
		default:
			throw InvalidOperationException();
		}
		if (wbit == WBit::WIG)
		{
			mask_W |= 0x80;
		}
	}

	bool EvexHandler::TryConvertToDisp8NImpl::TryConvertToDisp8N(Encoder& encoder, std::shared_ptr<OpCodeHandler> handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue)
	{
		auto evexHandler = std::dynamic_pointer_cast<EvexHandler>(handler);
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

	void EvexHandler::Encode(Encoder& encoder, const Instruction& instruction)
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

	std::vector<std::shared_ptr<Op>> MvexHandler::CreateOps(EncFlags1 encFlags1)
	{
		auto op0 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask));
		auto op1 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask));
		auto op2 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask));
		auto op3 = static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask));
		if (op3 != 0)
		{
			assert(op0 != 0 && op1 != 0 && op2 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetMvexOps()[op0 - 1], OpHandlerData::GetMvexOps()[op1 - 1], OpHandlerData::GetMvexOps()[op2 - 1], OpHandlerData::GetMvexOps()[op3 - 1]};
		}
		if (op2 != 0)
		{
			assert(op0 != 0 && op1 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetMvexOps()[op0 - 1], OpHandlerData::GetMvexOps()[op1 - 1], OpHandlerData::GetMvexOps()[op2 - 1]};
		}
		if (op1 != 0)
		{
			assert(op0 != 0);
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetMvexOps()[op0 - 1], OpHandlerData::GetMvexOps()[op1 - 1]};
		}
		if (op0 != 0)
		{
			return std::vector<std::shared_ptr<Op>> {OpHandlerData::GetMvexOps()[op0 - 1]};
		}
		return std::vector<std::shared_ptr<Op>>();
	}

	TryConvertToDisp8N MvexHandler::tryConvertToDisp8N = TryConvertToDisp8NImpl::TryConvertToDisp8N;

	MvexHandler::MvexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) : OpCodeHandler(encFlags2, encFlags3, false, tryConvertToDisp8N, CreateOps(encFlags1))
	{
		table = (static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
		Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
		p1Bits = (static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::MandatoryPrefixShift)) & static_cast<std::uint32_t>(EncFlags2::MandatoryPrefixMask);
		wbit = static_cast<WBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::WBitShift)) & static_cast<std::uint32_t>(EncFlags2::WBitMask));
		if (wbit == WBit::W1)
		{
			p1Bits |= 0x80;
		}
		if (wbit == WBit::WIG)
		{
			mask_W |= 0x80;
		}
	}

	bool MvexHandler::TryConvertToDisp8NImpl::TryConvertToDisp8N(Encoder& encoder, std::shared_ptr<OpCodeHandler> handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue)
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

	void MvexHandler::Encode(Encoder& encoder, const Instruction& instruction)
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

	std::vector<std::shared_ptr<Op>> D3nowHandler::operands =
	{
		std::make_shared<OpModRM_reg>(Register::MM0, Register::MM7),
		std::make_shared<OpModRM_rm>(Register::MM0, Register::MM7)
	};

	D3nowHandler::D3nowHandler(EncFlags2 encFlags2, EncFlags3 encFlags3) : OpCodeHandler(static_cast<EncFlags2>((static_cast<std::uint32_t>(encFlags2) & ~(0xFFFF << static_cast<std::int32_t>(EncFlags2::OpCodeShift))) | (0x000F << static_cast<std::int32_t>(EncFlags2::OpCodeShift))), encFlags3, false, nullptr, operands)
	{
		immediate = GetOpCode(encFlags2);
		assert(immediate <= std::numeric_limits<std::uint8_t>::max());
	}

	void D3nowHandler::Encode(Encoder& encoder, const Instruction& instruction)
	{
		encoder.WritePrefixes(instruction);
		encoder.WriteByteInternal(0x0F);
		encoder.ImmSize = ImmSize::Size1OpCode;
		encoder.Immediate = immediate;
	}
}
