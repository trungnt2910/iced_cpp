// C# helper headers

#include <csharp/enum.h>



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

	void FastStringOutput::Append(const char* value)
	{
		if (value != nullptr)
		{
			AppendNotNull(value);
		}
	}

	void FastStringOutput::AppendNotNull(const std::string& value)
	{
		AppendNotNull(value.c_str(), (std::int32_t)value.size());
	}

	void FastStringOutput::AppendNotNull(const std::string_view& value)
	{
		AppendNotNull(value.data(), (std::int32_t)value.size());
	}

	void FastStringOutput::AppendNotNull(const char* value, std::int32_t length)
	{
		if (length < 0)
		{
			length = (std::int32_t)strlen(value);
		}
		auto buffer = this->buffer;
		auto bufferLen = this->bufferLen;
		if (static_cast<std::uint32_t>(bufferLen) + length > static_cast<std::uint32_t>(buffer.size()))
		{
			Resize(length);
			buffer = this->buffer;
		}
		for (std::int32_t i = 0; i < length; i++)
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
