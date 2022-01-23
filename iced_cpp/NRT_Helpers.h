#pragma once

#include <cassert>
#include <iostream>
#include <string>

namespace System::Diagnostics
{
	class Debug2 final
	{
	public:
		static void Assert(bool condition)
		{
			assert(condition);
		}

		static void Fail(const std::string& str)
		{
			std::cerr << "Fail: " << str << std::endl;
		}

	};
}
