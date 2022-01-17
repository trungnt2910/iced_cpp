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

#include "CodeReader.h"
#include <string>
#include <vector>

#include <string_view>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// A <see cref="CodeReader"/> that reads data from a byte array
	/// </summary>
	class ByteArrayCodeReader final : public CodeReader
	{
		/* readonly */
	private:
		std::vector<std::uint8_t> data;
		std::int32_t currentPosition = 0;
		/* readonly */
		std::int32_t startPosition = 0;
		/* readonly */
		std::int32_t endPosition = 0;
		/// <summary>
		/// Current position
		/// </summary>
	public:
		std::int32_t GetPosition() const;
		void SetPosition(std::int32_t value);
		/// <summary>
		/// Number of bytes that can be read
		/// </summary>
		std::int32_t GetCount() const;
		/// <summary>
		/// Checks if it's possible to read another byte
		/// </summary>
		bool GetCanReadByte() const;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="hexData">Hex bytes encoded in a string</param>
		ByteArrayCodeReader(const std::string& hexData);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="data">Data</param>
		ByteArrayCodeReader(const std::vector<std::uint8_t>& data);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="data">Data</param>
		/// <param name="index">Start index</param>
		/// <param name="count">Number of bytes</param>
		ByteArrayCodeReader(const std::vector<std::uint8_t>& data, std::int32_t index, std::int32_t count);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="data">Data</param>
		ByteArrayCodeReader(const std::basic_string_view<std::uint8_t>& data);
		/// <summary>
		/// Reads the next byte or returns less than 0 if there are no more bytes
		/// </summary>
		/// <returns></returns>
		std::int32_t ReadByte() override;
	};
}
