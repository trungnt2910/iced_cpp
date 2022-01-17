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

#include "FastStringOutput.h"

namespace Iced::Intel
{

	std::int32_t FastStringOutput::GetLength() const
	{
		return bufferLen;
	}

	FastStringOutput::FastStringOutput()
	{
		buffer = std::vector<char>(64);
	}

	FastStringOutput::FastStringOutput(std::int32_t capacity)
	{
		buffer = std::vector<char>(capacity);
	}

	void FastStringOutput::Append(char c)
	{
		auto buffer = this->buffer;
		auto bufferLen = this->bufferLen;
		if (static_cast<std::uint32_t>(bufferLen) >= static_cast<std::uint32_t>(buffer.size()))
		{
			Resize(1);
			buffer = this->buffer;
		}
		buffer[bufferLen] = c;
		this->bufferLen = bufferLen + 1;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public void Append(string? value)
	void FastStringOutput::Append(const std::string& value)
	{
		if (value != "")
		{
			AppendNotNull(value);
		}
	}

	void FastStringOutput::AppendNotNull(const std::string& value)
	{
		auto buffer = this->buffer;
		auto bufferLen = this->bufferLen;
		if (static_cast<std::uint32_t>(bufferLen) + value.length() > static_cast<std::uint32_t>(buffer.size()))
		{
			Resize((std::int32_t)value.length());
			buffer = this->buffer;
		}
		for (std::int32_t i = 0; i < value.length(); i++)
		{
			buffer[bufferLen] = value[i];
			bufferLen++;
		}
		this->bufferLen = bufferLen;
	}

	void FastStringOutput::Resize(std::int32_t extraCount)
	{
		std::int32_t capacity = (std::int32_t)buffer.size();
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'checked' in this context:
		//ORIGINAL LINE: int newCount = checked(Math.Max(capacity * 2, capacity + extraCount));
		std::int32_t newCount = std::max(capacity * 2, capacity + extraCount);
		buffer.resize(newCount);
	}

	void FastStringOutput::CopyTo(std::vector<char>& array, std::int32_t arrayIndex)
	{
		std::copy_n(buffer.begin(), bufferLen, array.begin() + arrayIndex);
	}

	void FastStringOutput::Clear()
	{
		bufferLen = 0;
	}

	std::string FastStringOutput::ToString()
	{
		return std::string(buffer, 0, bufferLen);
	}
}
