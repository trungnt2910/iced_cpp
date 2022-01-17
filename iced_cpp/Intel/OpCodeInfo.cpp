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

#include "OpCodeInfo.h"
#include "Iced.Intel.IcedConstants.h"
#include "MandatoryPrefixByte.g.h"
#include "InstructionOpCounts.g.h"
#include "CodeSize.g.h"
#include "EncoderInternal/OpCodeFormatter.h"
#include "MvexInfo.h"
#include "EncoderInternal/OpCodeOperandKinds.g.h"
#include "EncoderInternal/InstructionFormatter.h"
#include "MnemonicUtils.h"
#include "InstructionMemorySizes.g.h"

using namespace Iced::Intel::EncoderInternal;

namespace Iced::Intel
{

	OpCodeInfo::OpCodeInfo(Iced::Intel::Code code, EncFlags1 encFlags1, EncFlags2 encFlags2, EncFlags3 encFlags3, OpCodeInfoFlags1 opcFlags1, OpCodeInfoFlags2 opcFlags2, StringBuilder* sb)
	{
		assert(static_cast<std::uint32_t>(code) < static_cast<std::uint32_t>(IcedConstants::CodeEnumCount));
		assert(static_cast<std::uint32_t>(code) <= std::numeric_limits<std::uint16_t>::max());
		this->code = static_cast<std::uint16_t>(code);
		this->encFlags2 = encFlags2;
		this->encFlags3 = encFlags3;
		this->opcFlags1 = opcFlags1;
		this->opcFlags2 = opcFlags2;
		if ((encFlags1 & EncFlags1::IgnoresRoundingControl) != 0)
		{
			flags |= Flags::IgnoresRoundingControl;
		}
		if ((encFlags1 & EncFlags1::AmdLockRegBit) != 0)
		{
			flags |= Flags::AmdLockRegBit;
		}
		auto switchTempVar_0 = (opcFlags1 & (OpCodeInfoFlags1::Cpl0Only | OpCodeInfoFlags1::Cpl3Only));


		flags |= (switchTempVar_0 == OpCodeInfoFlags1::Cpl0Only) ? Flags::CPL0 : (switchTempVar_0 == OpCodeInfoFlags1::Cpl3Only) ? Flags::CPL3 : Flags::CPL0 | Flags::CPL1 | Flags::CPL2 | Flags::CPL3;
		encoding = static_cast<std::uint8_t>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::EncodingShift)) & static_cast<std::uint32_t>(EncFlags3::EncodingMask));
		auto switchTempVar_1 = static_cast<MandatoryPrefixByte>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::MandatoryPrefixShift)) & static_cast<std::uint32_t>(EncFlags2::MandatoryPrefixMask));


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: mandatoryPrefix = (switchTempVar_1 == MandatoryPrefixByte.None) ? (byte)((encFlags2 & EncFlags2.HasMandatoryPrefix) != 0 ? MandatoryPrefix.PNP : MandatoryPrefix.None) : (switchTempVar_1 == MandatoryPrefixByte.P66) ? (byte)MandatoryPrefix.P66 : (switchTempVar_1 == MandatoryPrefixByte.PF3) ? (byte)MandatoryPrefix.PF3 : (switchTempVar_1 == MandatoryPrefixByte.PF2) ? (byte)MandatoryPrefix.PF2 : throw new InvalidOperationException();
		mandatoryPrefix = (switchTempVar_1 == MandatoryPrefixByte::None) ? static_cast<std::uint8_t>((encFlags2 & EncFlags2::HasMandatoryPrefix) != 0 ? MandatoryPrefix::PNP : MandatoryPrefix::None) : (switchTempVar_1 == MandatoryPrefixByte::P66) ? static_cast<std::uint8_t>(MandatoryPrefix::P66) : (switchTempVar_1 == MandatoryPrefixByte::PF3) ? static_cast<std::uint8_t>(MandatoryPrefix::PF3) : (switchTempVar_1 == MandatoryPrefixByte::PF2) ? static_cast<std::uint8_t>(MandatoryPrefix::PF2) : throw InvalidOperationException();
		auto switchTempVar_2 = static_cast<CodeSize>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::OperandSizeShift)) & static_cast<std::uint32_t>(EncFlags3::OperandSizeMask));


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: operandSize = (switchTempVar_2 == CodeSize.Unknown) ? (byte)0 : (switchTempVar_2 == CodeSize.Code16) ? (byte)16 : (switchTempVar_2 == CodeSize.Code32) ? (byte)32 : (switchTempVar_2 == CodeSize.Code64) ? (byte)64 : throw new InvalidOperationException();
		operandSize = (switchTempVar_2 == CodeSize::Unknown) ? static_cast<std::uint8_t>(0) : (switchTempVar_2 == CodeSize::Code16) ? static_cast<std::uint8_t>(16) : (switchTempVar_2 == CodeSize::Code32) ? static_cast<std::uint8_t>(32) : (switchTempVar_2 == CodeSize::Code64) ? static_cast<std::uint8_t>(64) : throw InvalidOperationException();
		auto switchTempVar_3 = static_cast<CodeSize>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::AddressSizeShift)) & static_cast<std::uint32_t>(EncFlags3::AddressSizeMask));


		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: addressSize = (switchTempVar_3 == CodeSize.Unknown) ? (byte)0 : (switchTempVar_3 == CodeSize.Code16) ? (byte)16 : (switchTempVar_3 == CodeSize.Code32) ? (byte)32 : (switchTempVar_3 == CodeSize.Code64) ? (byte)64 : throw new InvalidOperationException();
		addressSize = (switchTempVar_3 == CodeSize::Unknown) ? static_cast<std::uint8_t>(0) : (switchTempVar_3 == CodeSize::Code16) ? static_cast<std::uint8_t>(16) : (switchTempVar_3 == CodeSize::Code32) ? static_cast<std::uint8_t>(32) : (switchTempVar_3 == CodeSize::Code64) ? static_cast<std::uint8_t>(64) : throw InvalidOperationException();
		groupIndex = static_cast<std::int8_t>((encFlags2 & EncFlags2::HasGroupIndex) == 0 ? -1 : static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::GroupIndexShift)) & 7));
		rmGroupIndex = static_cast<std::int8_t>((encFlags3 & EncFlags3::HasRmGroupIndex) == 0 ? -1 : static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::GroupIndexShift)) & 7));
		tupleType = static_cast<std::uint8_t>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::TupleTypeShift)) & static_cast<std::uint32_t>(EncFlags3::TupleTypeMask));
		LKind lkind;
		switch (static_cast<LBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::LBitShift)) & static_cast<std::int32_t>(EncFlags2::LBitMask)))
		{
		case LBit::LZ:
			lkind = LKind::LZ;
			l = 0;
			break;
		case LBit::L0:
			lkind = LKind::L0;
			l = 0;
			break;
		case LBit::L1:
			lkind = LKind::L0;
			l = 1;
			break;
		case LBit::L128:
			lkind = LKind::L128;
			l = 0;
			break;
		case LBit::L256:
			lkind = LKind::L128;
			l = 1;
			break;
		case LBit::L512:
			lkind = LKind::L128;
			l = 2;
			break;
		case LBit::LIG:
			lkind = LKind::None;
			l = 0;
			flags |= Flags::LIG;
			break;
		default:
			throw InvalidOperationException();
		}
		switch (static_cast<WBit>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::WBitShift)) & static_cast<std::uint32_t>(EncFlags2::WBitMask)))
		{
		case WBit::W0:
			break;
		case WBit::W1:
			flags |= Flags::W;
			break;
		case WBit::WIG:
			flags |= Flags::WIG;
			break;
		case WBit::WIG32:
			flags |= Flags::WIG32;
			break;
		default:
			throw InvalidOperationException();
		}
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: string? toOpCodeStringValue = null;
		std::string toOpCodeStringValue = "";
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: string? toInstructionStringValue = null;
		std::string toInstructionStringValue = "";
		switch (static_cast<EncodingKind>(encoding))
		{
		case EncodingKind::Legacy:
		{
			const auto &opKinds = OpCodeOperandKinds::LegacyOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::Legacy_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::Legacy_OpMask))];
			auto switchTempVar_4 = static_cast<LegacyOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_4 == LegacyOpCodeTable.MAP0) ? (byte)OpCodeTableKind.Normal : (switchTempVar_4 == LegacyOpCodeTable.MAP0F) ? (byte)OpCodeTableKind.T0F : (switchTempVar_4 == LegacyOpCodeTable.MAP0F38) ? (byte)OpCodeTableKind.T0F38 : (switchTempVar_4 == LegacyOpCodeTable.MAP0F3A) ? (byte)OpCodeTableKind.T0F3A : throw new InvalidOperationException();
			table = (switchTempVar_4 == LegacyOpCodeTable::MAP0) ? static_cast<std::uint8_t>(OpCodeTableKind::Normal) : (switchTempVar_4 == LegacyOpCodeTable::MAP0F) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F) : (switchTempVar_4 == LegacyOpCodeTable::MAP0F38) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F38) : (switchTempVar_4 == LegacyOpCodeTable::MAP0F3A) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F3A) : throw InvalidOperationException();
			break;
		}
		case EncodingKind::VEX:
		{
			const auto& opKinds = OpCodeOperandKinds::VexOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask))];
			op4Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::VEX_Op4Shift)) & static_cast<std::uint32_t>(EncFlags1::VEX_OpMask))];
			auto switchTempVar_5 = static_cast<VexOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_5 == VexOpCodeTable.MAP0) ? (byte)OpCodeTableKind.Normal : (switchTempVar_5 == VexOpCodeTable.MAP0F) ? (byte)OpCodeTableKind.T0F : (switchTempVar_5 == VexOpCodeTable.MAP0F38) ? (byte)OpCodeTableKind.T0F38 : (switchTempVar_5 == VexOpCodeTable.MAP0F3A) ? (byte)OpCodeTableKind.T0F3A : throw new InvalidOperationException();
			table = (switchTempVar_5 == VexOpCodeTable::MAP0) ? static_cast<std::uint8_t>(OpCodeTableKind::Normal) : (switchTempVar_5 == VexOpCodeTable::MAP0F) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F) : (switchTempVar_5 == VexOpCodeTable::MAP0F38) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F38) : (switchTempVar_5 == VexOpCodeTable::MAP0F3A) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F3A) : throw InvalidOperationException();
			break;
		}
		case EncodingKind::EVEX:
		{
			const auto& opKinds = OpCodeOperandKinds::EvexOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::EVEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::EVEX_OpMask))];
			auto switchTempVar_6 = static_cast<EvexOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_6 == EvexOpCodeTable.MAP0F) ? (byte)OpCodeTableKind.T0F : (switchTempVar_6 == EvexOpCodeTable.MAP0F38) ? (byte)OpCodeTableKind.T0F38 : (switchTempVar_6 == EvexOpCodeTable.MAP0F3A) ? (byte)OpCodeTableKind.T0F3A : (switchTempVar_6 == EvexOpCodeTable.MAP5) ? (byte)OpCodeTableKind.MAP5 : (switchTempVar_6 == EvexOpCodeTable.MAP6) ? (byte)OpCodeTableKind.MAP6 : throw new InvalidOperationException();
			table = (switchTempVar_6 == EvexOpCodeTable::MAP0F) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F) : (switchTempVar_6 == EvexOpCodeTable::MAP0F38) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F38) : (switchTempVar_6 == EvexOpCodeTable::MAP0F3A) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F3A) : (switchTempVar_6 == EvexOpCodeTable::MAP5) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP5) : (switchTempVar_6 == EvexOpCodeTable::MAP6) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP6) : throw InvalidOperationException();
			break;
		}
		case EncodingKind::XOP:
		{
			const auto& opKinds = OpCodeOperandKinds::XopOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::XOP_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::XOP_OpMask))];
			auto switchTempVar_7 = static_cast<XopOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_7 == XopOpCodeTable.MAP8) ? (byte)OpCodeTableKind.MAP8 : (switchTempVar_7 == XopOpCodeTable.MAP9) ? (byte)OpCodeTableKind.MAP9 : (switchTempVar_7 == XopOpCodeTable.MAP10) ? (byte)OpCodeTableKind.MAP10 : throw new InvalidOperationException();
			table = (switchTempVar_7 == XopOpCodeTable::MAP8) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP8) : (switchTempVar_7 == XopOpCodeTable::MAP9) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP9) : (switchTempVar_7 == XopOpCodeTable::MAP10) ? static_cast<std::uint8_t>(OpCodeTableKind::MAP10) : throw InvalidOperationException();
			break;
		}
		case EncodingKind::D3NOW:
			op0Kind = static_cast<std::uint8_t>(OpCodeOperandKind::mm_reg);
			op1Kind = static_cast<std::uint8_t>(OpCodeOperandKind::mm_or_mem);
			table = static_cast<std::uint8_t>(OpCodeTableKind::T0F);
			break;
		case EncodingKind::MVEX:
		{
			const auto& opKinds = OpCodeOperandKinds::MvexOpKinds;
			op0Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op0Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask))];
			op1Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op1Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask))];
			op2Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op2Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask))];
			op3Kind = opKinds[static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags1) >> static_cast<std::int32_t>(EncFlags1::MVEX_Op3Shift)) & static_cast<std::uint32_t>(EncFlags1::MVEX_OpMask))];
			auto switchTempVar_8 = static_cast<MvexOpCodeTable>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::TableShift)) & static_cast<std::uint32_t>(EncFlags2::TableMask));


			//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
			//ORIGINAL LINE: table = (switchTempVar_8 == MvexOpCodeTable.MAP0F) ? (byte)OpCodeTableKind.T0F : (switchTempVar_8 == MvexOpCodeTable.MAP0F38) ? (byte)OpCodeTableKind.T0F38 : (switchTempVar_8 == MvexOpCodeTable.MAP0F3A) ? (byte)OpCodeTableKind.T0F3A : throw new InvalidOperationException();
			table = (switchTempVar_8 == MvexOpCodeTable::MAP0F) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F) : (switchTempVar_8 == MvexOpCodeTable::MAP0F38) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F38) : (switchTempVar_8 == MvexOpCodeTable::MAP0F3A) ? static_cast<std::uint8_t>(OpCodeTableKind::T0F3A) : throw InvalidOperationException();
			break;
		}
		default:
			throw InvalidOperationException();
		}
		this->toOpCodeStringValue = (toOpCodeStringValue != "") ? toOpCodeStringValue : (OpCodeFormatter(this, sb, lkind, (opcFlags1 & OpCodeInfoFlags1::ModRegRmString) != 0)).Format();
		auto fmtOption = static_cast<InstrStrFmtOption>((static_cast<std::uint32_t>(opcFlags2) >> static_cast<std::int32_t>(OpCodeInfoFlags2::InstrStrFmtOptionShift)) & static_cast<std::uint32_t>(OpCodeInfoFlags2::InstrStrFmtOptionMask));
		this->toInstructionStringValue = (toInstructionStringValue != "") ? toInstructionStringValue : (InstructionFormatter(this, fmtOption, sb)).Format();
	}

	Iced::Intel::Code OpCodeInfo::GetCode() const
	{
		return static_cast<Iced::Intel::Code>(code);
	}

	Iced::Intel::Mnemonic OpCodeInfo::GetMnemonic() const
	{
		return Iced::Intel::MnemonicUtils::Mnemonic(GetCode());
	}

	EncodingKind OpCodeInfo::GetEncoding() const
	{
		return static_cast<EncodingKind>(encoding);
	}

	bool OpCodeInfo::IsInstruction() const
	{
		return code > static_cast<std::uint16_t>(Code::DeclareQword);
	}

	bool OpCodeInfo::GetMode16() const
	{
		return (encFlags3 & EncFlags3::Bit16or32) != 0;
	}

	bool OpCodeInfo::GetMode32() const
	{
		return (encFlags3 & EncFlags3::Bit16or32) != 0;
	}

	bool OpCodeInfo::GetMode64() const
	{
		return (encFlags3 & EncFlags3::Bit64) != 0;
	}

	bool OpCodeInfo::GetFwait() const
	{
		return (encFlags3 & EncFlags3::Fwait) != 0;
	}

	std::int32_t OpCodeInfo::GetOperandSize() const
	{
		return operandSize;
	}

	std::int32_t OpCodeInfo::GetAddressSize() const
	{
		return addressSize;
	}

	std::uint32_t OpCodeInfo::GetL() const
	{
		return l;
	}

	std::uint32_t OpCodeInfo::GetW() const
	{
		return (flags & Flags::W) != 0 ? 1U : 0;
	}

	bool OpCodeInfo::IsLIG() const
	{
		return (flags & Flags::LIG) != 0;
	}

	bool OpCodeInfo::IsWIG() const
	{
		return (flags & Flags::WIG) != 0;
	}

	bool OpCodeInfo::IsWIG32() const
	{
		return (flags & Flags::WIG32) != 0;
	}

	Iced::Intel::TupleType OpCodeInfo::GetTupleType() const
	{
		return static_cast<Iced::Intel::TupleType>(tupleType);
	}

	Iced::Intel::MvexEHBit OpCodeInfo::GetMvexEHBit() const
	{
		return GetEncoding() == EncodingKind::MVEX ? (MvexInfo(GetCode())).GetEHBit() : MvexEHBit::None;
	}

	bool OpCodeInfo::GetMvexCanUseEvictionHint() const
	{
		return GetEncoding() == EncodingKind::MVEX && (MvexInfo(GetCode())).GetCanUseEvictionHint();
	}

	bool OpCodeInfo::GetMvexCanUseImmRoundingControl() const
	{
		return GetEncoding() == EncodingKind::MVEX && (MvexInfo(GetCode())).GetCanUseImmRoundingControl();
	}

	bool OpCodeInfo::GetMvexIgnoresOpMaskRegister() const
	{
		return GetEncoding() == EncodingKind::MVEX && (MvexInfo(GetCode())).GetIgnoresOpMaskRegister();
	}

	bool OpCodeInfo::GetMvexNoSaeRc() const
	{
		return GetEncoding() == EncodingKind::MVEX && (MvexInfo(GetCode())).GetNoSaeRc();
	}

	Iced::Intel::MvexTupleTypeLutKind OpCodeInfo::GetMvexTupleTypeLutKind() const
	{
		return GetEncoding() == EncodingKind::MVEX ? (MvexInfo(GetCode())).GetTupleTypeLutKind() : MvexTupleTypeLutKind::Int32;
	}

	MvexConvFn OpCodeInfo::GetMvexConversionFunc() const
	{
		return GetEncoding() == EncodingKind::MVEX ? (MvexInfo(GetCode())).GetConvFn() : MvexConvFn::None;
	}

	std::uint8_t OpCodeInfo::GetMvexValidConversionFuncsMask() const
	{
		return static_cast<std::uint8_t>(GetEncoding() == EncodingKind::MVEX ? ~(MvexInfo(GetCode())).GetInvalidConvFns() : 0);
	}

	std::uint8_t OpCodeInfo::GetMvexValidSwizzleFuncsMask() const
	{
		return static_cast<std::uint8_t>(GetEncoding() == EncodingKind::MVEX ? ~(MvexInfo(GetCode())).GetInvalidSwizzleFns() : 0);
	}

	Iced::Intel::MemorySize OpCodeInfo::GetMemorySize() const
	{
		return static_cast<Iced::Intel::MemorySize>(InstructionMemorySizes::SizesNormal[static_cast<std::int32_t>(code)]);
	}

	Iced::Intel::MemorySize OpCodeInfo::GetBroadcastMemorySize() const
	{
		return static_cast<Iced::Intel::MemorySize>(InstructionMemorySizes::SizesBcst[static_cast<std::int32_t>(code)]);
	}

	bool OpCodeInfo::GetCanBroadcast() const
	{
		return (encFlags3 & EncFlags3::Broadcast) != 0;
	}

	bool OpCodeInfo::GetCanUseRoundingControl() const
	{
		return (encFlags3 & EncFlags3::RoundingControl) != 0;
	}

	bool OpCodeInfo::GetCanSuppressAllExceptions() const
	{
		return (encFlags3 & EncFlags3::SuppressAllExceptions) != 0;
	}

	bool OpCodeInfo::GetCanUseOpMaskRegister() const
	{
		return (encFlags3 & EncFlags3::OpMaskRegister) != 0;
	}

	bool OpCodeInfo::GetRequireOpMaskRegister() const
	{
		return (encFlags3 & EncFlags3::RequireOpMaskRegister) != 0;
	}

	bool OpCodeInfo::GetCanUseZeroingMasking() const
	{
		return (encFlags3 & EncFlags3::ZeroingMasking) != 0;
	}

	bool OpCodeInfo::GetCanUseLockPrefix() const
	{
		return (encFlags3 & EncFlags3::Lock) != 0;
	}

	bool OpCodeInfo::GetCanUseXacquirePrefix() const
	{
		return (encFlags3 & EncFlags3::Xacquire) != 0;
	}

	bool OpCodeInfo::GetCanUseXreleasePrefix() const
	{
		return (encFlags3 & EncFlags3::Xrelease) != 0;
	}

	bool OpCodeInfo::GetCanUseRepPrefix() const
	{
		return (encFlags3 & EncFlags3::Rep) != 0;
	}

	bool OpCodeInfo::GetCanUseRepnePrefix() const
	{
		return (encFlags3 & EncFlags3::Repne) != 0;
	}

	bool OpCodeInfo::GetCanUseBndPrefix() const
	{
		return (encFlags3 & EncFlags3::Bnd) != 0;
	}

	bool OpCodeInfo::GetCanUseHintTakenPrefix() const
	{
		return (encFlags3 & EncFlags3::HintTaken) != 0;
	}

	bool OpCodeInfo::GetCanUseNotrackPrefix() const
	{
		return (encFlags3 & EncFlags3::Notrack) != 0;
	}

	bool OpCodeInfo::GetIgnoresRoundingControl() const
	{
		return (flags & Flags::IgnoresRoundingControl) != 0;
	}

	bool OpCodeInfo::GetAmdLockRegBit() const
	{
		return (flags & Flags::AmdLockRegBit) != 0;
	}

	bool OpCodeInfo::GetDefaultOpSize64() const
	{
		return (encFlags3 & EncFlags3::DefaultOpSize64) != 0;
	}

	bool OpCodeInfo::GetForceOpSize64() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::ForceOpSize64) != 0;
	}

	bool OpCodeInfo::GetIntelForceOpSize64() const
	{
		return (encFlags3 & EncFlags3::IntelForceOpSize64) != 0;
	}

	bool OpCodeInfo::GetMustBeCpl0() const
	{
		return (flags & (Flags::CPL0 | Flags::CPL1 | Flags::CPL2 | Flags::CPL3)) == Flags::CPL0;
	}

	bool OpCodeInfo::GetCpl0() const
	{
		return (flags & Flags::CPL0) != 0;
	}

	bool OpCodeInfo::GetCpl1() const
	{
		return (flags & Flags::CPL1) != 0;
	}

	bool OpCodeInfo::GetCpl2() const
	{
		return (flags & Flags::CPL2) != 0;
	}

	bool OpCodeInfo::GetCpl3() const
	{
		return (flags & Flags::CPL3) != 0;
	}

	bool OpCodeInfo::IsInputOutput() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::InputOutput) != 0;
	}

	bool OpCodeInfo::IsNop() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::Nop) != 0;
	}

	bool OpCodeInfo::IsReservedNop() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::ReservedNop) != 0;
	}

	bool OpCodeInfo::IsSerializingIntel() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::SerializingIntel) != 0;
	}

	bool OpCodeInfo::IsSerializingAmd() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::SerializingAmd) != 0;
	}

	bool OpCodeInfo::GetMayRequireCpl0() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::MayRequireCpl0) != 0;
	}

	bool OpCodeInfo::IsCetTracked() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::CetTracked) != 0;
	}

	bool OpCodeInfo::IsNonTemporal() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::NonTemporal) != 0;
	}

	bool OpCodeInfo::IsFpuNoWait() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::FpuNoWait) != 0;
	}

	bool OpCodeInfo::GetIgnoresModBits() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::IgnoresModBits) != 0;
	}

	bool OpCodeInfo::GetNo66() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::No66) != 0;
	}

	bool OpCodeInfo::GetNFx() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::NFx) != 0;
	}

	bool OpCodeInfo::GetRequiresUniqueRegNums() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::RequiresUniqueRegNums) != 0;
	}

	bool OpCodeInfo::GetRequiresUniqueDestRegNum() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::RequiresUniqueDestRegNum) != 0;
	}

	bool OpCodeInfo::IsPrivileged() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::Privileged) != 0;
	}

	bool OpCodeInfo::IsSaveRestore() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::SaveRestore) != 0;
	}

	bool OpCodeInfo::IsStackInstruction() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::StackInstruction) != 0;
	}

	bool OpCodeInfo::GetIgnoresSegment() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::IgnoresSegment) != 0;
	}

	bool OpCodeInfo::IsOpMaskReadWrite() const
	{
		return (opcFlags1 & OpCodeInfoFlags1::OpMaskReadWrite) != 0;
	}

	bool OpCodeInfo::GetRealMode() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::RealMode) != 0;
	}

	bool OpCodeInfo::GetProtectedMode() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::ProtectedMode) != 0;
	}

	bool OpCodeInfo::GetVirtual8086Mode() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::Virtual8086Mode) != 0;
	}

	bool OpCodeInfo::GetCompatibilityMode() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::CompatibilityMode) != 0;
	}

	bool OpCodeInfo::GetLongMode() const
	{
		return (encFlags3 & EncFlags3::Bit64) != 0;
	}

	bool OpCodeInfo::GetUseOutsideSmm() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseOutsideSmm) != 0;
	}

	bool OpCodeInfo::GetUseInSmm() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseInSmm) != 0;
	}

	bool OpCodeInfo::GetUseOutsideEnclaveSgx() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseOutsideEnclaveSgx) != 0;
	}

	bool OpCodeInfo::GetUseInEnclaveSgx1() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseInEnclaveSgx1) != 0;
	}

	bool OpCodeInfo::GetUseInEnclaveSgx2() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseInEnclaveSgx2) != 0;
	}

	bool OpCodeInfo::GetUseOutsideVmxOp() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseOutsideVmxOp) != 0;
	}

	bool OpCodeInfo::GetUseInVmxRootOp() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseInVmxRootOp) != 0;
	}

	bool OpCodeInfo::GetUseInVmxNonRootOp() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseInVmxNonRootOp) != 0;
	}

	bool OpCodeInfo::GetUseOutsideSeam() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseOutsideSeam) != 0;
	}

	bool OpCodeInfo::GetUseInSeam() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::UseInSeam) != 0;
	}

	bool OpCodeInfo::GetTdxNonRootGenUd() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::TdxNonRootGenUd) != 0;
	}

	bool OpCodeInfo::GetTdxNonRootGenVe() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::TdxNonRootGenVe) != 0;
	}

	bool OpCodeInfo::GetTdxNonRootMayGenEx() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::TdxNonRootMayGenEx) != 0;
	}

	bool OpCodeInfo::GetIntelVmExit() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::IntelVmExit) != 0;
	}

	bool OpCodeInfo::GetIntelMayVmExit() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::IntelMayVmExit) != 0;
	}

	bool OpCodeInfo::GetIntelSmmVmExit() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::IntelSmmVmExit) != 0;
	}

	bool OpCodeInfo::GetAmdVmExit() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::AmdVmExit) != 0;
	}

	bool OpCodeInfo::GetAmdMayVmExit() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::AmdMayVmExit) != 0;
	}

	bool OpCodeInfo::GetTsxAbort() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::TsxAbort) != 0;
	}

	bool OpCodeInfo::GetTsxImplAbort() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::TsxImplAbort) != 0;
	}

	bool OpCodeInfo::GetTsxMayAbort() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::TsxMayAbort) != 0;
	}

	bool OpCodeInfo::GetIntelDecoder16() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::IntelDecoder16or32) != 0;
	}

	bool OpCodeInfo::GetIntelDecoder32() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::IntelDecoder16or32) != 0;
	}

	bool OpCodeInfo::GetIntelDecoder64() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::IntelDecoder64) != 0;
	}

	bool OpCodeInfo::GetAmdDecoder16() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::AmdDecoder16or32) != 0;
	}

	bool OpCodeInfo::GetAmdDecoder32() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::AmdDecoder16or32) != 0;
	}

	bool OpCodeInfo::GetAmdDecoder64() const
	{
		return (opcFlags2 & OpCodeInfoFlags2::AmdDecoder64) != 0;
	}

	std::vector<DecoderOptions> OpCodeInfo::toDecoderOptions = { DecoderOptions::None, DecoderOptions::ALTINST, DecoderOptions::Cl1invmb, DecoderOptions::Cmpxchg486A, DecoderOptions::Cyrix, DecoderOptions::Cyrix_DMI, DecoderOptions::Cyrix_SMINT_0F7E, DecoderOptions::Jmpe, DecoderOptions::Loadall286, DecoderOptions::Loadall386, DecoderOptions::MovTr, DecoderOptions::MPX, DecoderOptions::OldFpu, DecoderOptions::Pcommit, DecoderOptions::Umov, DecoderOptions::Xbts, DecoderOptions::Udbg, DecoderOptions::KNC };

	DecoderOptions OpCodeInfo::GetDecoderOption() const
	{
		return toDecoderOptions[static_cast<std::int32_t>((static_cast<std::uint32_t>(opcFlags1) >> static_cast<std::int32_t>(OpCodeInfoFlags1::DecOptionValueShift)) & static_cast<std::uint32_t>(OpCodeInfoFlags1::DecOptionValueMask))];
	}

	OpCodeTableKind OpCodeInfo::GetTable() const
	{
		return static_cast<OpCodeTableKind>(table);
	}

	Iced::Intel::MandatoryPrefix OpCodeInfo::GetMandatoryPrefix() const
	{
		return static_cast<Iced::Intel::MandatoryPrefix>(mandatoryPrefix);
	}

	std::uint32_t OpCodeInfo::GetOpCode() const
	{
		return static_cast<std::uint16_t>(static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::OpCodeShift));
	}

	std::int32_t OpCodeInfo::GetOpCodeLength() const
	{
		return (encFlags2 & EncFlags2::OpCodeIs2Bytes) != 0 ? 2 : 1;
	}

	bool OpCodeInfo::IsGroup() const
	{
		return GetGroupIndex() >= 0;
	}

	std::int32_t OpCodeInfo::GetGroupIndex() const
	{
		return groupIndex;
	}

	bool OpCodeInfo::IsRmGroup() const
	{
		return GetRmGroupIndex() >= 0;
	}

	std::int32_t OpCodeInfo::GetRmGroupIndex() const
	{
		return rmGroupIndex;
	}

	std::int32_t OpCodeInfo::GetOpCount() const
	{
		return InstructionOpCounts::OpCount[code];
	}

	OpCodeOperandKind OpCodeInfo::GetOp0Kind() const
	{
		return static_cast<OpCodeOperandKind>(op0Kind);
	}

	OpCodeOperandKind OpCodeInfo::GetOp1Kind() const
	{
		return static_cast<OpCodeOperandKind>(op1Kind);
	}

	OpCodeOperandKind OpCodeInfo::GetOp2Kind() const
	{
		return static_cast<OpCodeOperandKind>(op2Kind);
	}

	OpCodeOperandKind OpCodeInfo::GetOp3Kind() const
	{
		return static_cast<OpCodeOperandKind>(op3Kind);
	}

	OpCodeOperandKind OpCodeInfo::GetOp4Kind() const
	{
		return static_cast<OpCodeOperandKind>(op4Kind);
	}

	OpCodeOperandKind OpCodeInfo::GetOpKind(std::int32_t operand) const
	{
		auto switchTempVar_9 = operand;

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_9 == 0) ? Op0Kind : (switchTempVar_9 == 1) ? Op1Kind : (switchTempVar_9 == 2) ? Op2Kind : (switchTempVar_9 == 3) ? Op3Kind : (switchTempVar_9 == 4) ? Op4Kind : throw new ArgumentOutOfRangeException(nameof(operand));
		return (switchTempVar_9 == 0) ? GetOp0Kind() : (switchTempVar_9 == 1) ? GetOp1Kind() : (switchTempVar_9 == 2) ? GetOp2Kind() : (switchTempVar_9 == 3) ? GetOp3Kind() : (switchTempVar_9 == 4) ? GetOp4Kind() : throw ArgumentOutOfRangeException("operand");
	}

	bool OpCodeInfo::IsAvailableInMode(std::int32_t bitness)
	{
		auto switchTempVar_10 = bitness;

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_10 == 16) ? Mode16 : (switchTempVar_10 == 32) ? Mode32 : (switchTempVar_10 == 64) ? Mode64 : throw new ArgumentOutOfRangeException(nameof(bitness));
		return (switchTempVar_10 == 16) ? GetMode16() : (switchTempVar_10 == 32) ? GetMode32() : (switchTempVar_10 == 64) ? GetMode64() : throw ArgumentOutOfRangeException("bitness");
	}

	std::string OpCodeInfo::ToOpCodeString()
	{
		return toOpCodeStringValue;
	}

	std::string OpCodeInfo::ToInstructionString()
	{
		return toInstructionStringValue;
	}

	std::string OpCodeInfo::ToString()
	{
		return ToInstructionString();
	}
}
