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

#include "RegisterExtensions.1.h"
#include "Iced.Intel.RegisterExtensions.h"

namespace Iced::Intel
{

	Iced::Intel::Register RegisterInfo::GetRegister() const
	{
		return static_cast<Iced::Intel::Register>(register_);
	}

	Iced::Intel::Register RegisterInfo::GetBase() const
	{
		return static_cast<Iced::Intel::Register>(baseRegister);
	}

	std::int32_t RegisterInfo::GetNumber() const
	{
		return register_ - baseRegister;
	}

	Iced::Intel::Register RegisterInfo::GetFullRegister() const
	{
		return static_cast<Iced::Intel::Register>(fullRegister);
	}

	Iced::Intel::Register RegisterInfo::GetFullRegister32() const
	{
		auto fullRegister = static_cast<Iced::Intel::Register>(this->fullRegister);
		if (Iced::Intel::RegisterExtensions::IsGPR(fullRegister))
		{
			assert(Register::RAX <= fullRegister && fullRegister <= Register::R15);
			return (Register)(fullRegister - Register::RAX + Register::EAX);
		}
		return fullRegister;
	}

	std::int32_t RegisterInfo::GetSize() const
	{
		return size;
	}

	RegisterInfo::RegisterInfo(Iced::Intel::Register register_, Iced::Intel::Register baseRegister, Iced::Intel::Register fullRegister, std::int32_t size)
	{
		assert(baseRegister <= register_);
		assert(static_cast<std::uint32_t>(register_) <= std::numeric_limits<std::uint8_t>::max());
		this->register_ = static_cast<std::uint8_t>(register_);
		assert(static_cast<std::uint32_t>(baseRegister) <= std::numeric_limits<std::uint8_t>::max());
		this->baseRegister = static_cast<std::uint8_t>(baseRegister);
		assert(static_cast<std::uint32_t>(fullRegister) <= std::numeric_limits<std::uint8_t>::max());
		this->fullRegister = static_cast<std::uint8_t>(fullRegister);
		assert(static_cast<std::uint32_t>(size) <= std::numeric_limits<std::uint16_t>::max());
		this->size = static_cast<std::uint16_t>(size);
		pad1 = 0;
		pad2 = 0;
		pad3 = 0;
	}
}
