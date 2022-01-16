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

#include "Instruction.VA.h"

namespace Iced::Intel
{

	VARegisterValueProviderDelegateImpl::VARegisterValueProviderDelegateImpl(VAGetRegisterValue getRegisterValue)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.getRegisterValue = getRegisterValue ?? throw new ArgumentNullException(nameof(getRegisterValue));
		this->getRegisterValue = (getRegisterValue != nullptr) ? getRegisterValue : throw std::invalid_argument("getRegisterValue");
	}

	bool VARegisterValueProviderDelegateImpl::TryGetRegisterValue(Register register_, std::int32_t elementIndex, std::int32_t elementSize, std::uint64_t& value)
	{
		value = getRegisterValue(register_, elementIndex, elementSize);
		return true;
	}

	VARegisterValueProviderAdapter::VARegisterValueProviderAdapter(IVARegisterValueProvider* provider)
	{
		this->provider = provider;
	}

	bool VARegisterValueProviderAdapter::TryGetRegisterValue(Register register_, std::int32_t elementIndex, std::int32_t elementSize, std::uint64_t& value)
	{
		value = provider->GetRegisterValue(register_, elementIndex, elementSize);
		return true;
	}

	VATryGetRegisterValueDelegateImpl::VATryGetRegisterValueDelegateImpl(VATryGetRegisterValue getRegisterValue)
	{
		this->getRegisterValue = getRegisterValue;
	}

	bool VATryGetRegisterValueDelegateImpl::TryGetRegisterValue(Register register_, std::int32_t elementIndex, std::int32_t elementSize, std::uint64_t& value)
	{
		return getRegisterValue(register_, elementIndex, elementSize, value);
	}
}
