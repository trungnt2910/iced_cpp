// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "../Iced.Intel.Instruction.h"
#include "Enums.h"
#include "../CodeSize.g.h"
#include "OpHandlers.defs.h"
#include "../Code.g.h"
#include "../TupleType.g.h"
#include "../IcedConstants.h"
#include <array>
#include <string>
#include <vector>
#include <limits>
#include <optional>
#include <format>
#include <cassert>
#include <tuple>

namespace Iced::Intel::EncoderInternal { class OpCodeHandler; class Op; }

namespace Iced::Intel { class Encoder; }

namespace Iced::Intel::EncoderInternal
{
	using TryConvertToDisp8NDelegate = bool(*)(Encoder& encoder, const OpCodeHandler* handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue);

	class OpContainer
	{
	private:
		const Op* _ops[IcedConstants::MaxOpCount] = { nullptr };
		std::size_t _size;
	public:
		constexpr OpContainer() : _size(0)
		{
		}
		template <std::size_t N, std::enable_if_t<(N <= IcedConstants::MaxOpCount), int> = 0>
		constexpr OpContainer(const std::array<const Op*, N>& arr)
		{
			std::copy(arr.begin(), arr.end(), _ops);
			_size = N;
		}
		constexpr const auto& operator[](const std::size_t index) const
		{
			return _ops[index];
		}
		constexpr const Op** begin()
		{
			return _ops;
		}
		constexpr const Op** end()
		{
			return begin() + size();
		}
		constexpr std::size_t size()
		{
			return _size;
		}
	};

	class OpCodeHandler
	{
	public:
		std::uint32_t OpCode = 0;
		bool Is2ByteOpCode = false;
		std::int32_t GroupIndex = 0;
		std::int32_t RmGroupIndex = 0;
		bool IsDeclareData = false;
		enum EncFlags3 EncFlags3 = static_cast<enum EncFlags3>(0);
		CodeSize OpSize = static_cast<CodeSize>(0);
		CodeSize AddrSize = static_cast<CodeSize>(0);
		TryConvertToDisp8NDelegate TryConvertToDisp8N;
		OpContainer Operands;
	protected:
		constexpr static std::uint32_t GetOpCode(EncFlags2 encFlags2)
		{
			return static_cast<std::uint16_t>(static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::OpCodeShift));
		}
		constexpr OpCodeHandler(EncFlags2 encFlags2, enum EncFlags3 encFlags3, bool isDeclareData, TryConvertToDisp8NDelegate tryConvertToDisp8N, const OpContainer& operands)
		{
			EncFlags3 = encFlags3;
			OpCode = GetOpCode(encFlags2);
			Is2ByteOpCode = (encFlags2 & EncFlags2::OpCodeIs2Bytes) != 0;
			GroupIndex = (encFlags2 & EncFlags2::HasGroupIndex) == 0 ? -1 : static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::GroupIndexShift)) & 7);
			RmGroupIndex = (encFlags3 & EncFlags3::HasRmGroupIndex) == 0 ? -1 : static_cast<std::int32_t>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::GroupIndexShift)) & 7);
			IsDeclareData = isDeclareData;
			OpSize = static_cast<CodeSize>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::OperandSizeShift)) & static_cast<std::uint32_t>(EncFlags3::OperandSizeMask));
			AddrSize = static_cast<CodeSize>((static_cast<std::uint32_t>(encFlags3) >> static_cast<std::int32_t>(EncFlags3::AddressSizeShift)) & static_cast<std::uint32_t>(EncFlags3::AddressSizeMask));
			TryConvertToDisp8N = tryConvertToDisp8N;
			Operands = operands;
		}
	public:
		constexpr virtual void Encode(Encoder& encoder, const Instruction& instruction) const = 0;
	};
	class InvalidHandler final : public OpCodeHandler
	{
	public:
		inline static const std::string_view ERROR_MESSAGE = "Can't encode an invalid instruction";
		constexpr InvalidHandler()
			: OpCodeHandler(EncFlags2::None, EncFlags3::Bit16or32 | EncFlags3::Bit64, false, nullptr, OpContainer())
		{
		}

		inline void Encode(Encoder& encoder, const Instruction& instruction) const override;
	};
	class DeclareDataHandler final : public OpCodeHandler
	{
	private:
		std::int32_t elemLength = 0;
		std::int32_t maxLength = 0;
	public:
		constexpr DeclareDataHandler(Code code) 
			: OpCodeHandler(EncFlags2::None, EncFlags3::Bit16or32 | EncFlags3::Bit64, true, nullptr, OpContainer())
		{
			auto switchTempVar_0 = code;

			elemLength = (switchTempVar_0 == Code::DeclareByte) ? static_cast<std::uint8_t>(1) : (switchTempVar_0 == Code::DeclareWord) ? static_cast<std::uint8_t>(2) : (switchTempVar_0 == Code::DeclareDword) ? static_cast<std::uint8_t>(4) : (switchTempVar_0 == Code::DeclareQword) ? static_cast<std::uint8_t>(8) : throw std::runtime_error("invalid operation");
			maxLength = 16 / elemLength;
		}
		inline void Encode(Encoder& encoder, const Instruction& instruction) const override;
	};
	class LegacyHandler final : public OpCodeHandler
	{
	private:
		std::uint32_t tableByte1 = 0, tableByte2 = 0;
		std::uint32_t mandatoryPrefix = 0;
		static constexpr OpContainer CreateOps(EncFlags1 encFlags1);
	public:
		constexpr LegacyHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) 
			: OpCodeHandler(encFlags2, encFlags3, false, nullptr, CreateOps(encFlags1))
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
				throw std::runtime_error("invalid operation");
			}
			auto switchTempVar_1 = static_cast<MandatoryPrefixByte>((static_cast<std::uint32_t>(encFlags2) >> static_cast<std::int32_t>(EncFlags2::MandatoryPrefixShift)) & static_cast<std::uint32_t>(EncFlags2::MandatoryPrefixMask));

			mandatoryPrefix = (switchTempVar_1 == MandatoryPrefixByte::None) ? static_cast<std::uint8_t>(0x0) : (switchTempVar_1 == MandatoryPrefixByte::P66) ? static_cast<std::uint8_t>(0x66) : (switchTempVar_1 == MandatoryPrefixByte::PF3) ? static_cast<std::uint8_t>(0xF3) : (switchTempVar_1 == MandatoryPrefixByte::PF2) ? static_cast<std::uint8_t>(0xF2) : throw std::runtime_error("invalid operation");
		}
		inline void Encode(Encoder& encoder, const Instruction& instruction) const override;
	};
	class VexHandler final : public OpCodeHandler
	{
	private:
		std::uint32_t table = 0;
		std::uint32_t lastByte = 0;
		std::uint32_t mask_W_L = 0;
		std::uint32_t mask_L = 0;
		std::uint32_t W1 = 0;
		static constexpr OpContainer CreateOps(EncFlags1 encFlags1);
	public:
		constexpr VexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) 
			: OpCodeHandler(encFlags2, encFlags3, false, nullptr, CreateOps(encFlags1))
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
		inline void Encode(Encoder& encoder, const Instruction& instruction) const override;
	};
	class XopHandler final : public OpCodeHandler
	{
	private:
	private:
		std::uint32_t table = 0;
		std::uint32_t lastByte = 0;
		static constexpr OpContainer CreateOps(EncFlags1 encFlags1);
	public:
		constexpr XopHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) : OpCodeHandler(encFlags2, encFlags3, false, nullptr, CreateOps(encFlags1))
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
		inline void Encode(Encoder& encoder, const Instruction& instruction) const override;
	};
	class EvexHandler final : public OpCodeHandler
	{
	private:
		class TryConvertToDisp8NImpl final
		{
		public:
			static bool TryConvertToDisp8N(Encoder& encoder, const OpCodeHandler* handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue);
		};
	private:
		WBit wbit = static_cast<WBit>(0);
		TupleType tupleType = static_cast<TupleType>(0);
		std::uint32_t table = 0;
		std::uint32_t p1Bits = 0;
		std::uint32_t llBits = 0;
		std::uint32_t mask_W = 0;
		std::uint32_t mask_LL = 0;
		static constexpr OpContainer CreateOps(EncFlags1 encFlags1);
		inline static constexpr TryConvertToDisp8NDelegate tryConvertToDisp8N = TryConvertToDisp8NImpl::TryConvertToDisp8N;
	public:
		constexpr EvexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) 
			: OpCodeHandler(encFlags2, encFlags3, false, tryConvertToDisp8N, CreateOps(encFlags1))
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
				throw std::runtime_error("invalid operation");
			}
			if (wbit == WBit::WIG)
			{
				mask_W |= 0x80;
			}
		}
	public:
		inline void Encode(Encoder& encoder, const Instruction& instruction) const override;
	};
	class MvexHandler final : public OpCodeHandler
	{
	private:
		class TryConvertToDisp8NImpl final
		{
		public:
			inline static bool TryConvertToDisp8N(Encoder& encoder, const OpCodeHandler* handler, const Instruction& instruction, std::int32_t displ, std::int8_t& compressedValue);
		};
	private:
		WBit wbit = static_cast<WBit>(0);
		std::uint32_t table = 0;
		std::uint32_t p1Bits = 0;
		std::uint32_t mask_W = 0;
		static constexpr OpContainer CreateOps(EncFlags1 encFlags1);
		inline static constexpr TryConvertToDisp8NDelegate tryConvertToDisp8N = TryConvertToDisp8NImpl::TryConvertToDisp8N;
	public:
		constexpr MvexHandler(EncFlags1 encFlags1, EncFlags2 encFlags2, enum EncFlags3 encFlags3) 
			: OpCodeHandler(encFlags2, encFlags3, false, tryConvertToDisp8N, CreateOps(encFlags1))
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
	public:
		inline void Encode(Encoder& encoder, const Instruction& instruction) const override;
	};
	class D3nowHandler final : public OpCodeHandler
	{
	private:
		using EncFlags3 = ::Iced::Intel::EncoderInternal::EncFlags3;
	private:
		inline static constexpr std::tuple operandsData = std::make_tuple(
			OpModRM_reg(Register::MM0, Register::MM7),
			OpModRM_rm(Register::MM0, Register::MM7)
		);
		inline static constexpr std::array operands = std::to_array<const Op*>(
		{
			(const Op*)&std::get<0>(operandsData),
			(const Op*)&std::get<1>(operandsData)
		});
		std::uint32_t immediate = 0;
	public:
		constexpr D3nowHandler(EncFlags2 encFlags2, EncFlags3 encFlags3)
			: OpCodeHandler(
				static_cast<EncFlags2>((static_cast<std::uint32_t>(encFlags2) & ~(0xFFFF << static_cast<std::int32_t>(EncFlags2::OpCodeShift))) | (0x000F << static_cast<std::int32_t>(EncFlags2::OpCodeShift))),
				encFlags3, false, nullptr, OpContainer(operands))
		{
			immediate = GetOpCode(encFlags2);
			assert(immediate <= std::numeric_limits<std::uint8_t>::max());
		}
		inline void Encode(Encoder& encoder, const Instruction& instruction) const override;
	};
}
