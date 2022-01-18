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

#include "AssemblerMemoryOperand.h"

namespace Iced::Intel
{

	AssemblerMemoryOperand::AssemblerMemoryOperand(MemoryOperandSize size, Register segment, Register base, Register index, std::int32_t scale, std::int64_t displacement, AssemblerOperandFlags flags)
	{
		Size = size;
		Segment = segment;
		Base = base;
		Index = index;
		Scale = scale;
		Displacement = displacement;
		Flags = flags;
	}

	bool AssemblerMemoryOperand::IsBroadcast() const
	{
		return (Flags & AssemblerOperandFlags::Broadcast) != 0;
	}

	bool AssemblerMemoryOperand::IsDisplacementOnly() const
	{
		return Base == Register::None && Index == Register::None;
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::k1() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K1);
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::k2() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K2);
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::k3() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K3);
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::k4() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K4);
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::k5() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K5);
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::k6() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K6);
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::k7() const
	{
		return AssemblerMemoryOperand(Size, Segment, Base, Index, Scale, Displacement, (Flags & ~AssemblerOperandFlags::RegisterMask) | AssemblerOperandFlags::K7);
	}

	AssemblerMemoryOperand operator + (AssemblerRegister16 left, AssemblerMemoryOperand right)
	{
		auto hasBase = right.Base != Register::None;
		return AssemblerMemoryOperand(right.Size, Register::None, hasBase ? right.Base : left.Value, hasBase ? left.Value : right.Index, right.Scale, right.Displacement, right.Flags);
	}

	AssemblerMemoryOperand operator + (AssemblerRegister32 left, AssemblerMemoryOperand right)
	{
		auto hasBase = right.Base != Register::None;
		return AssemblerMemoryOperand(right.Size, Register::None, hasBase ? right.Base : left.Value, hasBase ? left.Value : right.Index, right.Scale, right.Displacement, right.Flags);
	}

	AssemblerMemoryOperand operator + (AssemblerRegister64 left, AssemblerMemoryOperand right)
	{
		auto hasBase = right.Base != Register::None;
		return AssemblerMemoryOperand(right.Size, Register::None, hasBase ? right.Base : left.Value, hasBase ? left.Value : right.Index, right.Scale, right.Displacement, right.Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::operator + (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(this->Size, Register::None, this->Base, this->Index, this->Scale, this->Displacement + displacement, this->Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperand::operator - (std::int64_t displacement)
	{
		return AssemblerMemoryOperand(this->Size, Register::None, this->Base, this->Index, this->Scale, this->Displacement - displacement, this->Flags);
	}

	MemoryOperand AssemblerMemoryOperand::ToMemoryOperand(std::int32_t bitness)
	{
		std::int32_t dispSize = 1;
		if (IsDisplacementOnly())
		{
			dispSize = bitness / 8;
		}
		else if (Displacement == 0)
		{
			dispSize = 0;
		}
		return MemoryOperand(Base, Index, Scale, Displacement, dispSize, (Flags & AssemblerOperandFlags::Broadcast) != 0, Segment);
	}

	bool AssemblerMemoryOperand::Equals(AssemblerMemoryOperand other)
	{
		return Size == other.Size && Segment == other.Segment && Base == other.Base && Index == other.Index && Scale == other.Scale && Displacement == other.Displacement && Flags == other.Flags;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public override bool Equals(Object? obj)
	bool AssemblerMemoryOperand::Equals(std::any obj)
	{
		AssemblerMemoryOperand* other = std::any_cast<AssemblerMemoryOperand>(&obj);
		return other != nullptr && Equals(other);
	}

	std::int32_t AssemblerMemoryOperand::GetHashCode()
	{
		//	 unchecked
		auto hashCode = static_cast<std::int32_t>(Size);
		hashCode = (hashCode * 397) ^ static_cast<std::int32_t>(Segment);
		hashCode = (hashCode * 397) ^ static_cast<std::int32_t>(Base);
		hashCode = (hashCode * 397) ^ static_cast<std::int32_t>(Index);
		hashCode = (hashCode * 397) ^ Scale;
		hashCode = (hashCode * 397) ^ ::GetHashCode(Displacement);
		hashCode = (hashCode * 397) ^ static_cast<std::int32_t>(Flags);
		return hashCode;
		//C# TO C++ CONVERTER TODO TASK: End of the original C# 'unchecked' block.
	}

	bool AssemblerMemoryOperand::operator == (AssemblerMemoryOperand right)
	{
		return this->Equals(right);
	}

	bool AssemblerMemoryOperand::operator != (AssemblerMemoryOperand right)
	{
		return !this->Equals(right);
	}
}
