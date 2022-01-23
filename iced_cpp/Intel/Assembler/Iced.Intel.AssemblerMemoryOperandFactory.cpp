// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Iced.Intel.AssemblerMemoryOperandFactory.h"

namespace Iced::Intel
{

	AssemblerMemoryOperandFactory::AssemblerMemoryOperandFactory(MemoryOperandSize size)
	{
		Segment = Register::None;
		Size = size;
		Flags = AssemblerOperandFlags::None;
	}

	AssemblerMemoryOperandFactory::AssemblerMemoryOperandFactory(MemoryOperandSize size, Register segment, AssemblerOperandFlags flags)
	{
		Size = size;
		Segment = segment;
		Flags = flags;
	}

	AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::GetEs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::ES, Flags);
	}

	AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::GetCs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::CS, Flags);
	}

	AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::GetSs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::SS, Flags);
	}

	AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::GetDs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::DS, Flags);
	}

	AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::GetFs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::FS, Flags);
	}

	AssemblerMemoryOperandFactory AssemblerMemoryOperandFactory::GetGs() const
	{
		return AssemblerMemoryOperandFactory(Size, Register::GS, Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](AssemblerMemoryOperand operand)
	{
		return AssemblerMemoryOperand(Size, Segment, operand.Base, operand.Index, operand.Scale, operand.Displacement, Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](std::int64_t offset)
	{
		return AssemblerMemoryOperand(Size, Segment, Register::None, Register::None, 1, offset, Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](std::uint64_t offset)
	{
		return AssemblerMemoryOperand(Size, Segment, Register::None, Register::None, 1, static_cast<std::int64_t>(offset), Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](const Label& label)
	{
		return AssemblerMemoryOperand(Size, Segment, Register::RIP, Register::None, 1, static_cast<std::int64_t>(label.GetId()), Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](AssemblerRegister16 register_)
	{
		return AssemblerMemoryOperand(Size, Segment, register_, Register::None, 1, 0, Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](AssemblerRegister32 register_)
	{
		return AssemblerMemoryOperand(Size, Segment, register_, Register::None, 1, 0, Flags);
	}

	AssemblerMemoryOperand AssemblerMemoryOperandFactory::operator [](AssemblerRegister64 register_)
	{
		return AssemblerMemoryOperand(Size, Segment, register_, Register::None, 1, 0, Flags);
	}
}
