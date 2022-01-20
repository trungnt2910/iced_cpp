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

	std::uint64_t UsedMemory::GetVirtualAddress(std::int32_t elementIndex, VAGetRegisterValue getRegisterValue) const
	{
		if (getRegisterValue == nullptr)
		{
			throw std::invalid_argument("getRegisterValue");
		}
		auto provider = new VARegisterValueProviderDelegateImpl(getRegisterValue);
		std::uint64_t result;
		if (TryGetVirtualAddress(elementIndex, provider, result))
		{
			return result;
		}
		return 0;
	}

	std::uint64_t UsedMemory::GetVirtualAddress(std::int32_t elementIndex, IVARegisterValueProvider* registerValueProvider) const
	{
		if (registerValueProvider == nullptr)
		{
			throw std::invalid_argument("registerValueProvider");
		}
		auto provider = new VARegisterValueProviderAdapter(registerValueProvider);
		std::uint64_t result;
		if (TryGetVirtualAddress(elementIndex, provider, result))
		{
			return result;
		}
		return 0;
	}

	bool UsedMemory::TryGetVirtualAddress(std::int32_t elementIndex, std::uint64_t& result, VATryGetRegisterValue getRegisterValue) const
	{
		if (getRegisterValue == nullptr)
		{
			throw std::invalid_argument("getRegisterValue");
		}
		auto provider = new VATryGetRegisterValueDelegateImpl(getRegisterValue);
		return TryGetVirtualAddress(elementIndex, provider, result);
	}

	bool UsedMemory::TryGetVirtualAddress(std::int32_t elementIndex, IVATryGetRegisterValueProvider* registerValueProvider, std::uint64_t& result) const
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
}
