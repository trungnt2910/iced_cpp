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

#include "../CodeWriter.h"

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::BlockEncoderInternal
{
	class CodeWriterImpl final : public CodeWriter
	{
	public:
		std::uint32_t BytesWritten = 0;
		/* readonly */
	private:
		CodeWriter* codeWriter;
	public:
		CodeWriterImpl(CodeWriter* codeWriter);
		void WriteByte(std::uint8_t value) override;
	};
}
