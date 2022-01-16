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

#include "ThrowHelper.h"

namespace Iced::Intel
{

	void ThrowHelper::ThrowArgumentException()
	{
		//C# TO C++ CONVERTER TODO TASK: This exception's constructor requires an argument:
		//ORIGINAL LINE: throw new ArgumentException();
		throw std::invalid_argument();
	}

	void ThrowHelper::ThrowInvalidOperationException()
	{
		throw InvalidOperationException();
	}

	void ThrowHelper::ThrowArgumentNullException_codeWriter()
	{
		throw std::invalid_argument("codeWriter");
	}

	void ThrowHelper::ThrowArgumentNullException_data()
	{
		throw std::invalid_argument("data");
	}

	void ThrowHelper::ThrowArgumentNullException_writer()
	{
		throw std::invalid_argument("writer");
	}

	void ThrowHelper::ThrowArgumentNullException_options()
	{
		throw std::invalid_argument("options");
	}

	void ThrowHelper::ThrowArgumentNullException_value()
	{
		throw std::invalid_argument("value");
	}

	void ThrowHelper::ThrowArgumentNullException_list()
	{
		throw std::invalid_argument("list");
	}

	void ThrowHelper::ThrowArgumentNullException_collection()
	{
		throw std::invalid_argument("collection");
	}

	void ThrowHelper::ThrowArgumentNullException_array()
	{
		throw std::invalid_argument("array");
	}

	void ThrowHelper::ThrowArgumentNullException_sb()
	{
		throw std::invalid_argument("sb");
	}

	void ThrowHelper::ThrowArgumentNullException_output()
	{
		throw std::invalid_argument("output");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_value()
	{
		throw ArgumentOutOfRangeException("value");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_index()
	{
		throw ArgumentOutOfRangeException("index");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_count()
	{
		throw ArgumentOutOfRangeException("count");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_length()
	{
		throw ArgumentOutOfRangeException("length");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_operand()
	{
		throw ArgumentOutOfRangeException("operand");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_instructionOperand()
	{
		throw ArgumentOutOfRangeException("instructionOperand");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_capacity()
	{
		throw ArgumentOutOfRangeException("capacity");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_memorySize()
	{
		throw ArgumentOutOfRangeException("memorySize");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_size()
	{
		throw ArgumentOutOfRangeException("size");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_elementSize()
	{
		throw ArgumentOutOfRangeException("elementSize");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_register()
	{
		throw ArgumentOutOfRangeException("register");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_code()
	{
		throw ArgumentOutOfRangeException("code");
	}

	void ThrowHelper::ThrowArgumentOutOfRangeException_data()
	{
		throw ArgumentOutOfRangeException("data");
	}
}
