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

#include "StringOutput.h"
#include "ThrowHelper.h"

namespace Iced::Intel
{

	StringOutput::StringOutput()
	{
		sb = new StringBuilder();
	}

	StringOutput::StringOutput(StringBuilder* sb)
	{
		if (sb == nullptr)
		{
			ThrowHelper::ThrowArgumentNullException_sb();
		}
		this->sb = sb;
	}

	void StringOutput::Write(const std::string& text, FormatterTextKind kind)
	{
		sb->append(text);
	}

	void StringOutput::Reset()
	{
		sb->setLength(0);
	}

	std::string StringOutput::ToStringAndReset()
	{
		auto result = ToString();
		Reset();
		return result;
	}

	std::string StringOutput::ToString()
	{
		return sb->toString();
	}
}
