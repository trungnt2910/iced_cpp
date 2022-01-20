#pragma once

#include "MvexTupleTypeLutKind.g.h"
#include "MvexEHBit.g.h"
#include "MvexConvFn.g.h"
#include "Code.g.h"
#include "TupleType.g.h"
#include "MvexInfoData.g.h"
#include "MvexInfoFlags1.g.h"
#include "MvexInfoFlags2.g.h"
#include "MvexTupleTypeLut.g.h"
#include "Iced.Intel.IcedConstants.h"
#include <cassert>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/* readonly */
	class MvexInfo
	{
		/* readonly */
	private:
		std::int32_t index = 0;
	public:
		constexpr MvexTupleTypeLutKind GetTupleTypeLutKind() const;
		constexpr MvexEHBit GetEHBit() const;
		constexpr MvexConvFn GetConvFn() const;
		constexpr std::uint32_t GetInvalidConvFns() const;
		constexpr std::uint32_t GetInvalidSwizzleFns() const;
		constexpr bool IsNDD() const;
		constexpr bool IsNDS() const;
		constexpr bool GetCanUseEvictionHint() const;
		constexpr bool GetCanUseImmRoundingControl() const;
		constexpr bool GetCanUseRoundingControl() const;
		constexpr bool GetCanUseSuppressAllExceptions() const;
		constexpr bool GetIgnoresOpMaskRegister() const;
		constexpr bool GetRequireOpMaskRegister() const;
		constexpr bool GetNoSaeRc() const;
		constexpr bool IsConvFn32() const;
		constexpr bool GetIgnoresEvictionHint() const;
		constexpr MvexInfo(Code code);
		constexpr TupleType GetTupleType(std::int32_t sss);

		constexpr MvexInfo() = default;
	};

	inline static constexpr std::underlying_type_t<MvexInfoFlags1> operator&(std::uint8_t a, MvexInfoFlags1 flags)
	{
		return (std::underlying_type_t<MvexInfoFlags1>)a & (std::underlying_type_t<MvexInfoFlags1>)flags;
	}

	inline static constexpr std::underlying_type_t<MvexInfoFlags2> operator&(std::uint8_t a, MvexInfoFlags2 flags)
	{
		return (std::underlying_type_t<MvexInfoFlags2>)a & (std::underlying_type_t<MvexInfoFlags2>)flags;
	}

	constexpr MvexTupleTypeLutKind MvexInfo::GetTupleTypeLutKind() const
	{
		return static_cast<MvexTupleTypeLutKind>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::TupleTypeLutKindIndex]);
	}

	constexpr MvexEHBit MvexInfo::GetEHBit() const
	{
		return static_cast<MvexEHBit>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::EHBitIndex]);
	}

	constexpr MvexConvFn MvexInfo::GetConvFn() const
	{
		return static_cast<MvexConvFn>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::ConvFnIndex]);
	}

	constexpr std::uint32_t MvexInfo::GetInvalidConvFns() const
	{
		return MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::InvalidConvFnsIndex];
	}

	constexpr std::uint32_t MvexInfo::GetInvalidSwizzleFns() const
	{
		return MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::InvalidSwizzleFnsIndex];
	}

	constexpr bool MvexInfo::IsNDD() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::NDD)) != 0;
	}

	constexpr bool MvexInfo::IsNDS() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::NDS)) != 0;
	}

	constexpr bool MvexInfo::GetCanUseEvictionHint() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::EvictionHint)) != 0;
	}

	constexpr bool MvexInfo::GetCanUseImmRoundingControl() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::ImmRoundingControl)) != 0;
	}

	constexpr bool MvexInfo::GetCanUseRoundingControl() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::RoundingControl)) != 0;
	}

	constexpr bool MvexInfo::GetCanUseSuppressAllExceptions() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::SuppressAllExceptions)) != 0;
	}

	constexpr bool MvexInfo::GetIgnoresOpMaskRegister() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::IgnoresOpMaskRegister)) != 0;
	}

	constexpr bool MvexInfo::GetRequireOpMaskRegister() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::RequireOpMaskRegister)) != 0;
	}

	constexpr bool MvexInfo::GetNoSaeRc() const
	{
		return (static_cast<MvexInfoFlags2>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags2Index] & MvexInfoFlags2::NoSaeRoundingControl)) != 0;
	}

	constexpr bool MvexInfo::IsConvFn32() const
	{
		return (static_cast<MvexInfoFlags2>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags2Index] & MvexInfoFlags2::ConvFn32)) != 0;
	}

	constexpr bool MvexInfo::GetIgnoresEvictionHint() const
	{
		return (static_cast<MvexInfoFlags2>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags2Index] & MvexInfoFlags2::IgnoresEvictionHint)) != 0;
	}

	constexpr MvexInfo::MvexInfo(Code code)
	{
		index = static_cast<std::int32_t>(code) - static_cast<std::int32_t>(IcedConstants::MvexStart);
		assert(static_cast<std::uint32_t>(index) < IcedConstants::MvexLength);
	}

	constexpr TupleType MvexInfo::GetTupleType(std::int32_t sss)
	{
		return static_cast<TupleType>(MvexTupleTypeLut::Data[static_cast<std::int32_t>(GetTupleTypeLutKind()) * 8 + sss]);
	}

}
