// C# helper headers
#include <csharp/classes.h>
#include <csharp/enum.h>



// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "AssemblerResult.h"

namespace Iced::Intel
{

	AssemblerResult::AssemblerResult(const std::vector<BlockEncoderResult>& result)
	{
		Result = result;
	}

	std::uint64_t AssemblerResult::GetLabelRIP(const Label& label, std::int32_t index)
	{
		if (label.IsEmpty())
		{
			//C# TO C++ CONVERTER TODO TASK: This exception's constructor requires only one argument:
			//ORIGINAL LINE: throw new ArgumentException(string.Format("Invalid label. Must be created via {0}.{1}", nameof(Assembler), nameof(Assembler.CreateLabel)), nameof(label));
			throw std::invalid_argument(std::format("Invalid label. Must be created via {0:s}.{1:s}", "Assembler", "CreateLabel"));
		}
		if (label.GetInstructionIndex() < 0)
		{
			//C# TO C++ CONVERTER TODO TASK: This exception's constructor requires only one argument:
			//ORIGINAL LINE: throw new ArgumentException(string.Format("The label is not associated with an instruction index. It must be emitted via {0}.{1}.", nameof(Assembler), nameof(Assembler.Label)), nameof(label));
			throw std::invalid_argument(std::format("The label is not associated with an instruction index. It must be emitted via {0:s}.{1:s}.", "Assembler", "Label"));
		}
		if (Result.empty() || static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(Result.size()))
		{
			throw ArgumentOutOfRangeException("index");
		}
		auto result = Result[index];
		if (result.NewInstructionOffsets.empty() || label.GetInstructionIndex() >= result.NewInstructionOffsets.size())
		{
			throw ArgumentOutOfRangeException("label" ", " + std::format("The label instruction index {0:s} is out of range of the instruction offsets results {1:s}. Did you forget to pass {2:s}.{3:s} to {4:s}.{5:s}/{6:s}?", label.GetInstructionIndex(), result.NewInstructionOffsets.size(), "BlockEncoderOptions", "ReturnNewInstructionOffsets", "Assembler", "Assemble", "TryAssemble"));
		}
		return result.RIP + result.NewInstructionOffsets[label.GetInstructionIndex()];
	}
}
