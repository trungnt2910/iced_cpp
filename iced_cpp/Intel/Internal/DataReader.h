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

#pragma once

#include <string>
#include <vector>
#include <csharp/exceptionhelper.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::Internal
{
	class DataReader
	{
		/* readonly */
	private:
		std::vector<std::uint8_t> data;
		/* readonly */
		std::vector<char> stringData;
		std::int32_t index = 0;
	public:
		/* readonly */
		std::int32_t GetIndex() const;
		void SetIndex(std::int32_t value);
		bool GetCanRead() const;
		DataReader(std::vector<std::uint8_t>& data);
		DataReader(std::vector<std::uint8_t>& data, std::int32_t maxStringLength);
		std::uint8_t ReadByte();
		std::uint32_t ReadCompressedUInt32();
		std::string ReadAsciiString();

		DataReader() = default;
	};
}
