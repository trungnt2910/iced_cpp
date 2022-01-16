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

#include "MemoryOperand.h"

namespace Iced::Intel
{

	MemoryOperand::MemoryOperand(Register base, Register index, std::int32_t scale, std::int64_t displacement, std::int32_t displSize, bool isBroadcast, Register segmentPrefix)
	{
		SegmentPrefix = segmentPrefix;
		Base = base;
		Index = index;
		Scale = scale;
		Displacement = displacement;
		DisplSize = displSize;
		IsBroadcast = isBroadcast;
	}

	MemoryOperand::MemoryOperand(Register base, Register index, std::int32_t scale, bool isBroadcast, Register segmentPrefix)
	{
		SegmentPrefix = segmentPrefix;
		Base = base;
		Index = index;
		Scale = scale;
		Displacement = 0;
		DisplSize = 0;
		IsBroadcast = isBroadcast;
	}

	MemoryOperand::MemoryOperand(Register base, std::int64_t displacement, std::int32_t displSize, bool isBroadcast, Register segmentPrefix)
	{
		SegmentPrefix = segmentPrefix;
		Base = base;
		Index = Register::None;
		Scale = 1;
		Displacement = displacement;
		DisplSize = displSize;
		IsBroadcast = isBroadcast;
	}

	MemoryOperand::MemoryOperand(Register index, std::int32_t scale, std::int64_t displacement, std::int32_t displSize, bool isBroadcast, Register segmentPrefix)
	{
		SegmentPrefix = segmentPrefix;
		Base = Register::None;
		Index = index;
		Scale = scale;
		Displacement = displacement;
		DisplSize = displSize;
		IsBroadcast = isBroadcast;
	}

	MemoryOperand::MemoryOperand(Register base, std::int64_t displacement, bool isBroadcast, Register segmentPrefix)
	{
		SegmentPrefix = segmentPrefix;
		Base = base;
		Index = Register::None;
		Scale = 1;
		Displacement = displacement;
		DisplSize = 1;
		IsBroadcast = isBroadcast;
	}

	MemoryOperand::MemoryOperand(Register base, Register index, std::int32_t scale, std::int64_t displacement, std::int32_t displSize)
	{
		SegmentPrefix = Register::None;
		Base = base;
		Index = index;
		Scale = scale;
		Displacement = displacement;
		DisplSize = displSize;
		IsBroadcast = false;
	}

	MemoryOperand::MemoryOperand(Register base, Register index, std::int32_t scale)
	{
		SegmentPrefix = Register::None;
		Base = base;
		Index = index;
		Scale = scale;
		Displacement = 0;
		DisplSize = 0;
		IsBroadcast = false;
	}

	MemoryOperand::MemoryOperand(Register base, Register index)
	{
		SegmentPrefix = Register::None;
		Base = base;
		Index = index;
		Scale = 1;
		Displacement = 0;
		DisplSize = 0;
		IsBroadcast = false;
	}

	MemoryOperand::MemoryOperand(Register base, std::int64_t displacement, std::int32_t displSize)
	{
		SegmentPrefix = Register::None;
		Base = base;
		Index = Register::None;
		Scale = 1;
		Displacement = displacement;
		DisplSize = displSize;
		IsBroadcast = false;
	}

	MemoryOperand::MemoryOperand(Register index, std::int32_t scale, std::int64_t displacement, std::int32_t displSize)
	{
		SegmentPrefix = Register::None;
		Base = Register::None;
		Index = index;
		Scale = scale;
		Displacement = displacement;
		DisplSize = displSize;
		IsBroadcast = false;
	}

	MemoryOperand::MemoryOperand(Register base, std::int64_t displacement)
	{
		SegmentPrefix = Register::None;
		Base = base;
		Index = Register::None;
		Scale = 1;
		Displacement = displacement;
		DisplSize = 1;
		IsBroadcast = false;
	}

	MemoryOperand::MemoryOperand(Register base)
	{
		SegmentPrefix = Register::None;
		Base = base;
		Index = Register::None;
		Scale = 1;
		Displacement = 0;
		DisplSize = 0;
		IsBroadcast = false;
	}

	MemoryOperand::MemoryOperand(std::uint64_t displacement, std::int32_t displSize)
	{
		SegmentPrefix = Register::None;
		Base = Register::None;
		Index = Register::None;
		Scale = 1;
		Displacement = static_cast<std::int64_t>(displacement);
		DisplSize = displSize;
		IsBroadcast = false;
	}
}
