// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "../BlockEncoder.h"
#include "../ToString.h"
#include "Label.h"
#include <vector>
#include <stdexcept>

namespace Iced::Intel
{
	/// <summary>
	/// Result of <see cref="Assembler.Assemble"/>.
	/// </summary>
	class AssemblerResult
	{
	public:
		constexpr AssemblerResult(const std::vector<BlockEncoderResult>& result);
		/// <summary>
		/// The associated block encoder result.
		/// </summary>
		std::vector<BlockEncoderResult> Result;
		/// <summary>
		/// Gets the RIP of the specified label.
		/// </summary>
		/// <param name="label">A label.</param>
		/// <param name="index">Result index</param>
		/// <returns>RIP of the label.</returns>
		constexpr std::uint64_t GetLabelRIP(const Label& label, std::int32_t index = 0);

		constexpr AssemblerResult() = default;
	};

	constexpr AssemblerResult::AssemblerResult(const std::vector<BlockEncoderResult>& result)
	{
		Result = result;
	}

	constexpr std::uint64_t AssemblerResult::GetLabelRIP(const Label& label, std::int32_t index)
	{
		if (label.IsEmpty())
		{
			throw std::invalid_argument("Invalid label. Must be created via Assembler::CreateLabel.");
		}
		if (label.GetInstructionIndex() < 0)
		{
			throw std::invalid_argument("The label is not associated with an instruction index. It must be emitted via Assembler::Label.");
		}
		if (Result.empty() || static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(Result.size()))
		{
			throw std::out_of_range("index");
		}
		auto result = Result[index];
		if (result.NewInstructionOffsets.empty() || label.GetInstructionIndex() >= result.NewInstructionOffsets.size())
		{
			throw std::out_of_range(
				"The label instruction index " +
				Iced::Intel::ToString(label.GetInstructionIndex()) +
				" is out of range of the instruction offsets results" +
				Iced::Intel::ToString(result.NewInstructionOffsets.size()) +
				". Did you forget to pass BlockEncoderOptions::ReturnNewInstructionOffsets to Assembler::Assemble / TryAssemble ? ");
		}
		return result.RIP + result.NewInstructionOffsets[label.GetInstructionIndex()];
	}

}
