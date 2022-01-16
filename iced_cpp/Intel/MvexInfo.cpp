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

#include "MvexInfo.h"
#include "MvexInfoData.g.h"
#include "MvexInfoFlags1.g.h"
#include "MvexInfoFlags2.g.h"
#include "Iced.Intel.IcedConstants.h"
#include "MvexTupleTypeLut.g.h"

namespace Iced::Intel
{

	MvexTupleTypeLutKind MvexInfo::GetTupleTypeLutKind() const
	{
		return static_cast<MvexTupleTypeLutKind>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::TupleTypeLutKindIndex]);
	}

	MvexEHBit MvexInfo::GetEHBit() const
	{
		return static_cast<MvexEHBit>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::EHBitIndex]);
	}

	MvexConvFn MvexInfo::GetConvFn() const
	{
		return static_cast<MvexConvFn>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::ConvFnIndex]);
	}

	std::uint32_t MvexInfo::GetInvalidConvFns() const
	{
		return MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::InvalidConvFnsIndex];
	}

	std::uint32_t MvexInfo::GetInvalidSwizzleFns() const
	{
		return MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::InvalidSwizzleFnsIndex];
	}

	bool MvexInfo::IsNDD() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::NDD)) != 0;
	}

	bool MvexInfo::IsNDS() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::NDS)) != 0;
	}

	bool MvexInfo::GetCanUseEvictionHint() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::EvictionHint)) != 0;
	}

	bool MvexInfo::GetCanUseImmRoundingControl() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::ImmRoundingControl)) != 0;
	}

	bool MvexInfo::GetCanUseRoundingControl() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::RoundingControl)) != 0;
	}

	bool MvexInfo::GetCanUseSuppressAllExceptions() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::SuppressAllExceptions)) != 0;
	}

	bool MvexInfo::GetIgnoresOpMaskRegister() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::IgnoresOpMaskRegister)) != 0;
	}

	bool MvexInfo::GetRequireOpMaskRegister() const
	{
		return (static_cast<MvexInfoFlags1>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags1Index] & MvexInfoFlags1::RequireOpMaskRegister)) != 0;
	}

	bool MvexInfo::GetNoSaeRc() const
	{
		return (static_cast<MvexInfoFlags2>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags2Index] & MvexInfoFlags2::NoSaeRoundingControl)) != 0;
	}

	bool MvexInfo::IsConvFn32() const
	{
		return (static_cast<MvexInfoFlags2>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags2Index] & MvexInfoFlags2::ConvFn32)) != 0;
	}

	bool MvexInfo::GetIgnoresEvictionHint() const
	{
		return (static_cast<MvexInfoFlags2>(MvexInfoData::Data[index * MvexInfoData::StructSize + MvexInfoData::Flags2Index] & MvexInfoFlags2::IgnoresEvictionHint)) != 0;
	}

	MvexInfo::MvexInfo(Code code)
	{
		index = static_cast<std::int32_t>(code) - static_cast<std::int32_t>(IcedConstants::MvexStart);
		assert(static_cast<std::uint32_t>(index) < IcedConstants::MvexLength);
	}

	TupleType MvexInfo::GetTupleType(std::int32_t sss)
	{
		return static_cast<TupleType>(MvexTupleTypeLut::Data[static_cast<std::int32_t>(GetTupleTypeLutKind()) * 8 + sss]);
	}
}
