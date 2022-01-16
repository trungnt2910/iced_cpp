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

#include "UsedRegister.h"

namespace Iced::Intel
{

	Iced::Intel::Register UsedRegister::GetRegister() const
	{
		return register_;
	}

	OpAccess UsedRegister::GetAccess() const
	{
		return access;
	}

	UsedRegister::UsedRegister(Iced::Intel::Register register_, OpAccess access)
	{
		this->register_ = register_;
		this->access = access;
	}

	std::string UsedRegister::ToString()
	{
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		return to_string(GetRegister()) + ":" + to_string(GetAccess());
	}
}
