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

#include "UsedMemory.h"

namespace Iced::Intel
{

	Register UsedMemory::GetSegment() const
	{
		return static_cast<Register>(segReg);
	}

	Register UsedMemory::GetBase() const
	{
		return static_cast<Register>(baseReg);
	}

	Register UsedMemory::GetIndex() const
	{
		return static_cast<Register>(indexReg);
	}

	std::int32_t UsedMemory::GetScale() const
	{
		return scale;
	}

	std::uint64_t UsedMemory::GetDisplacement() const
	{
		return displ;
	}

	Iced::Intel::MemorySize UsedMemory::GetMemorySize() const
	{
		return static_cast<Iced::Intel::MemorySize>(memorySize);
	}

	OpAccess UsedMemory::GetAccess() const
	{
		return static_cast<OpAccess>(access);
	}

	CodeSize UsedMemory::GetAddressSize() const
	{
		return static_cast<CodeSize>(addressSize);
	}

	std::int32_t UsedMemory::GetVsibSize() const
	{
		return vsibSize;
	}

	UsedMemory::UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access)
	{
		this->displ = static_cast<std::uint64_t>(displ);
		assert(static_cast<std::uint32_t>(segReg) <= std::numeric_limits<std::uint8_t>::max());
		this->segReg = static_cast<std::uint8_t>(segReg);
		assert(static_cast<std::uint32_t>(baseReg) <= std::numeric_limits<std::uint8_t>::max());
		this->baseReg = static_cast<std::uint8_t>(baseReg);
		assert(static_cast<std::uint32_t>(indexReg) <= std::numeric_limits<std::uint8_t>::max());
		this->indexReg = static_cast<std::uint8_t>(indexReg);
		assert(static_cast<std::uint32_t>(memorySize) <= std::numeric_limits<std::uint8_t>::max());
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
		this->scale = static_cast<std::uint8_t>(scale);
		assert(static_cast<std::uint32_t>(access) <= std::numeric_limits<std::uint8_t>::max());
		this->access = static_cast<std::uint8_t>(access);
		addressSize = static_cast<std::uint8_t>(CodeSize::Unknown);
		vsibSize = 0;
	}

	UsedMemory::UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access)
	{
		this->displ = displ;
		assert(static_cast<std::uint32_t>(segReg) <= std::numeric_limits<std::uint8_t>::max());
		this->segReg = static_cast<std::uint8_t>(segReg);
		assert(static_cast<std::uint32_t>(baseReg) <= std::numeric_limits<std::uint8_t>::max());
		this->baseReg = static_cast<std::uint8_t>(baseReg);
		assert(static_cast<std::uint32_t>(indexReg) <= std::numeric_limits<std::uint8_t>::max());
		this->indexReg = static_cast<std::uint8_t>(indexReg);
		assert(static_cast<std::uint32_t>(memorySize) <= std::numeric_limits<std::uint8_t>::max());
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
		this->scale = static_cast<std::uint8_t>(scale);
		assert(static_cast<std::uint32_t>(access) <= std::numeric_limits<std::uint8_t>::max());
		this->access = static_cast<std::uint8_t>(access);
		addressSize = static_cast<std::uint8_t>(CodeSize::Unknown);
		vsibSize = 0;
	}

	UsedMemory::UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::int64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize)
	{
		this->displ = static_cast<std::uint64_t>(displ);
		assert(static_cast<std::uint32_t>(segReg) <= std::numeric_limits<std::uint8_t>::max());
		this->segReg = static_cast<std::uint8_t>(segReg);
		assert(static_cast<std::uint32_t>(baseReg) <= std::numeric_limits<std::uint8_t>::max());
		this->baseReg = static_cast<std::uint8_t>(baseReg);
		assert(static_cast<std::uint32_t>(indexReg) <= std::numeric_limits<std::uint8_t>::max());
		this->indexReg = static_cast<std::uint8_t>(indexReg);
		assert(static_cast<std::uint32_t>(memorySize) <= std::numeric_limits<std::uint8_t>::max());
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
		this->scale = static_cast<std::uint8_t>(scale);
		assert(static_cast<std::uint32_t>(access) <= std::numeric_limits<std::uint8_t>::max());
		this->access = static_cast<std::uint8_t>(access);
		assert(static_cast<std::uint32_t>(addressSize) <= std::numeric_limits<std::uint8_t>::max());
		this->addressSize = static_cast<std::uint8_t>(addressSize);
		assert(vsibSize == 0 || vsibSize == 4 || vsibSize == 8);
		this->vsibSize = static_cast<std::uint8_t>(vsibSize);
	}

	UsedMemory::UsedMemory(Register segReg, Register baseReg, Register indexReg, std::int32_t scale, std::uint64_t displ, Iced::Intel::MemorySize memorySize, OpAccess access, CodeSize addressSize, std::int32_t vsibSize)
	{
		this->displ = displ;
		assert(static_cast<std::uint32_t>(segReg) <= std::numeric_limits<std::uint8_t>::max());
		this->segReg = static_cast<std::uint8_t>(segReg);
		assert(static_cast<std::uint32_t>(baseReg) <= std::numeric_limits<std::uint8_t>::max());
		this->baseReg = static_cast<std::uint8_t>(baseReg);
		assert(static_cast<std::uint32_t>(indexReg) <= std::numeric_limits<std::uint8_t>::max());
		this->indexReg = static_cast<std::uint8_t>(indexReg);
		assert(static_cast<std::uint32_t>(memorySize) <= std::numeric_limits<std::uint8_t>::max());
		this->memorySize = static_cast<std::uint8_t>(memorySize);
		assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
		this->scale = static_cast<std::uint8_t>(scale);
		assert(static_cast<std::uint32_t>(access) <= std::numeric_limits<std::uint8_t>::max());
		this->access = static_cast<std::uint8_t>(access);
		assert(static_cast<std::uint32_t>(addressSize) <= std::numeric_limits<std::uint8_t>::max());
		this->addressSize = static_cast<std::uint8_t>(addressSize);
		assert(vsibSize == 0 || vsibSize == 4 || vsibSize == 8);
		this->vsibSize = static_cast<std::uint8_t>(vsibSize);
	}

	std::uint64_t UsedMemory::GetVirtualAddress(std::int32_t elementIndex, VAGetRegisterValue getRegisterValue)
	{
		if (getRegisterValue == nullptr)
		{
			throw std::invalid_argument("getRegisterValue");
		}
		auto provider = new VARegisterValueProviderDelegateImpl(getRegisterValue);
		std::any result;
		if (TryGetVirtualAddress(elementIndex, provider, result))
		{
			return result;
		}
		return 0;
	}

	std::uint64_t UsedMemory::GetVirtualAddress(std::int32_t elementIndex, IVARegisterValueProvider* registerValueProvider)
	{
		if (registerValueProvider == nullptr)
		{
			throw std::invalid_argument("registerValueProvider");
		}
		auto provider = new VARegisterValueProviderAdapter(registerValueProvider);
		std::any result;
		if (TryGetVirtualAddress(elementIndex, provider, result))
		{
			return result;
		}
		return 0;
	}

	bool UsedMemory::TryGetVirtualAddress(std::int32_t elementIndex, std::uint64_t& result, VATryGetRegisterValue getRegisterValue)
	{
		if (getRegisterValue == nullptr)
		{
			throw std::invalid_argument("getRegisterValue");
		}
		auto provider = new VATryGetRegisterValueDelegateImpl(getRegisterValue);
		return TryGetVirtualAddress(elementIndex, provider, result);
	}

	bool UsedMemory::TryGetVirtualAddress(std::int32_t elementIndex, IVATryGetRegisterValueProvider* registerValueProvider, std::uint64_t& result)
	{
		if (registerValueProvider == nullptr)
		{
			throw std::invalid_argument("registerValueProvider");
		}
		result = 0;
		std::uint64_t tmpAddr = GetDisplacement();
		std::uint64_t tmpValue;
		auto reg = GetBase();
		if (reg != Register::None)
		{
			if (!registerValueProvider->TryGetRegisterValue(reg, 0, 0, tmpValue))
			{
				return false;
			}
			tmpAddr += tmpValue;
		}
		reg = GetIndex();
		if (reg != Register::None)
		{
			if (!registerValueProvider->TryGetRegisterValue(reg, elementIndex, vsibSize, tmpValue))
			{
				return false;
			}
			if (vsibSize == 4)
			{
				tmpValue = static_cast<std::uint64_t>(static_cast<std::int32_t>(tmpValue));
			}
			tmpAddr += tmpValue * static_cast<std::uint64_t>(static_cast<std::uint32_t>(GetScale()));
		}
		switch (GetAddressSize())
		{
		case CodeSize::Code16:
			tmpAddr = static_cast<std::uint16_t>(tmpAddr);
			break;
		case CodeSize::Code32:
			tmpAddr = static_cast<std::uint32_t>(tmpAddr);
			break;
		}
		reg = GetSegment();
		if (reg != Register::None)
		{
			if (!registerValueProvider->TryGetRegisterValue(reg, 0, 0, tmpValue))
			{
				return false;
			}
			tmpAddr += tmpValue;
		}
		result = tmpAddr;
		return true;
	}

	std::string UsedMemory::ToString()
	{
		auto sb = new StringBuilder();
		sb->append('[');
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		sb->append(to_string(GetSegment()));
		sb->append(':');
		bool needPlus = false;
		if (GetBase() != Register::None)
		{
			//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
			sb->append(to_string(GetBase()));
			needPlus = true;
		}
		if (GetIndex() != Register::None)
		{
			if (needPlus)
			{
				sb->append('+');
			}
			needPlus = true;
			//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
			sb->append(to_string(GetIndex()));
			if (GetScale() != 1)
			{
				sb->append('*');
				sb->append(static_cast<char>('0' + GetScale()));
			}
		}
		if (GetDisplacement() != 0 || !needPlus)
		{
			if (needPlus)
			{
				sb->append('+');
			}
			if (GetDisplacement() <= 9)
			{
				sb->append(GetDisplacement());
			}
			else
			{
				sb->append("0x");
				//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
				sb->append(GetDisplacement().ToString("X"));
			}
		}
		sb->append(';');
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		sb->append(to_string(GetMemorySize()));
		sb->append(';');
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		sb->append(to_string(GetAccess()));
		sb->append(']');
		return sb->toString();
	}
}
