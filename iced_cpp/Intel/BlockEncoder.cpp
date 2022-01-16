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

#include "BlockEncoder.h"
#include "../Array2.h"
#include "Iced.Intel.IcedConstants.h"

using namespace Iced::Intel::BlockEncoderInternal;

namespace Iced::Intel
{

	RelocInfo::RelocInfo(RelocKind kind, std::uint64_t address)
	{
		Kind = kind;
		Address = address;
	}

	InstructionBlock::InstructionBlock(CodeWriter* codeWriter, std::vector<Instruction>& instructions, std::uint64_t rip)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: CodeWriter = codeWriter ?? throw new ArgumentNullException(nameof(codeWriter));
		CodeWriter = (codeWriter != nullptr) ? codeWriter : throw std::invalid_argument("codeWriter");
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: Instructions = instructions ?? throw new ArgumentNullException(nameof(instructions));
		Instructions = instructions ? instructions : throw std::invalid_argument("instructions");
		RIP = rip;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: internal BlockEncoderResult(ulong rip, List<RelocInfo>? relocInfos, uint[]? newInstructionOffsets, ConstantOffsets[]? constantOffsets)
	BlockEncoderResult::BlockEncoderResult(std::uint64_t rip, std::vector<RelocInfo>& relocInfos, std::uint32_t[] ? *newInstructionOffsets, ConstantOffsets[] ? *constantOffsets)
	{
		RIP = rip;
		RelocInfos = relocInfos;
		NewInstructionOffsets = (newInstructionOffsets != nullptr) ? newInstructionOffsets : Array2::Empty<std::uint32_t>();
		ConstantOffsets = (constantOffsets != nullptr) ? constantOffsets : Array2::Empty<ConstantOffsets>();
	}

	std::int32_t BlockEncoder::GetBitness() const
	{
		return bitness;
	}

	bool BlockEncoder::GetFixBranches() const
	{
		return (options & BlockEncoderOptions::DontFixBranches) == 0;
	}

	BlockEncoder::NullCodeWriter* BlockEncoder::NullCodeWriter::Instance = new NullCodeWriter();

	BlockEncoder::NullCodeWriter::NullCodeWriter()
	{
	}

	void BlockEncoder::NullCodeWriter::WriteByte(std::uint8_t value)
	{
	}

	BlockEncoder::BlockEncoder(std::int32_t bitness, std::vector<InstructionBlock>& instrBlocks, BlockEncoderOptions options)
	{
		if (bitness != 16 && bitness != 32 && bitness != 64)
		{
			throw ArgumentOutOfRangeException("bitness");
		}
		if (instrBlocks.empty())
		{
			throw std::invalid_argument("instrBlocks");
		}
		this->bitness = bitness;
		nullEncoder = Encoder::Create(bitness, NullCodeWriter::Instance);
		this->options = options;
		blocks = std::vector<Block*>(instrBlocks.size());
		std::int32_t instrCount = 0;
		for (std::int32_t i = 0; i < instrBlocks.size(); i++)
		{
			auto instructions = instrBlocks[i].Instructions;
			if (instructions.empty())
			{
				//C# TO C++ CONVERTER TODO TASK: This exception's constructor requires an argument:
				//ORIGINAL LINE: throw new ArgumentException();
				throw std::invalid_argument();
			}
			auto block = new Block(this, instrBlocks[i].CodeWriter, instrBlocks[i].RIP, ReturnRelocInfos ? std::vector<RelocInfo>() : std::vector<RelocInfo>());
			blocks[i] = block;
			auto instrs = std::vector<Instr*>(instructions.size());
			std::uint64_t ip = instrBlocks[i].RIP;
			for (std::int32_t j = 0; j < instrs.size(); j++)
			{
				auto instruction = instructions[j];
				auto instr = Instr::Create(this, block, instruction);
				instr->IP = ip;
				instrs[j] = instr;
				instrCount++;
				assert(instr->Size != 0);
				ip += instr->Size;
			}
			block->SetInstructions(instrs);
		}
		// Optimize from low to high addresses
		Array::Sort(blocks, [&](a, b)
			{
				a::RIP->CompareTo(b::RIP);
			});
		// There must not be any instructions with the same IP, except if IP = 0 (default value)
		auto toInstr = std::unordered_map<std::uint64_t, Instr*>(instrCount);
		this->toInstr = toInstr;
		bool hasMultipleZeroIPInstrs = false;
		for (auto block : blocks)
		{
			for (auto instr : *block->GetInstructions())
			{
				std::uint64_t origIP = instr->OrigIP;
				std::unordered_map<std::uint64_t, Instr*>::const_iterator toInstr_iterator = toInstr.find(origIP);
				if (toInstr_iterator != toInstr.end())
				{
					_ = toInstr_iterator->second;
					if (origIP != 0)
					{
						throw std::invalid_argument(std::format("Multiple instructions with the same IP: 0x{0:0>X}", origIP));
					}
					hasMultipleZeroIPInstrs = true;
				}
				else
				{
					_ = toInstr_iterator->second;
					toInstr[origIP] = instr;
				}
			}
		}
		if (hasMultipleZeroIPInstrs)
		{
			toInstr.erase(0);
		}
		for (auto block : blocks)
		{
			std::uint64_t ip = block->RIP;
			for (auto instr : *block->GetInstructions())
			{
				instr->IP = ip;
				auto oldSize = instr->Size;
				instr->Initialize(this);
				if (instr->Size > oldSize)
				{
					throw InvalidOperationException();
				}
				ip += instr->Size;
			}
		}
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public static bool TryEncode(int bitness, InstructionBlock block, [NotNullWhen(false)] out string? errorMessage, out BlockEncoderResult result, BlockEncoderOptions options = BlockEncoderOptions.None)
	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	bool BlockEncoder::TryEncode(std::int32_t bitness, InstructionBlock block, std::string& errorMessage, BlockEncoderResult& result, BlockEncoderOptions options)
	{
		std::any resultArray;
		if (TryEncode(bitness, { block }, errorMessage, resultArray, options))
		{
			assert(resultArray->Length == 1);
			result = resultArray[0];
			return true;
		}
		else
		{
			result = Iced::Intel::BlockEncoderResult();
			return false;
		}
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public static bool TryEncode(int bitness, InstructionBlock[] blocks, [NotNullWhen(false)] out string? errorMessage, [NotNullWhen(true)] out BlockEncoderResult[]? result, BlockEncoderOptions options = BlockEncoderOptions.None)
	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	bool BlockEncoder::TryEncode(std::int32_t bitness, std::vector<InstructionBlock>& blocks, std::string& errorMessage, BlockEncoderResult[] ? *&result, BlockEncoderOptions options)
	{
		BlockEncoder tempVar(bitness, blocks, options);
		return (&tempVar)->Encode(errorMessage, result);
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: bool Encode([NotNullWhen(false)] out string? errorMessage, [NotNullWhen(true)] out BlockEncoderResult[]? result)
	//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	bool BlockEncoder::Encode(std::string& errorMessage, BlockEncoderResult[] ? *&result)
	{
		constexpr std::int32_t MAX_ITERS = 1000;
		for (std::int32_t iter = 0; iter < MAX_ITERS; iter++)
		{
			bool updated = false;
			for (auto block : blocks)
			{
				std::uint64_t ip = block->RIP;
				std::uint64_t gained = 0;
				for (auto instr : *block->GetInstructions())
				{
					instr->IP = ip;
					auto oldSize = instr->Size;
					if (instr->Optimize(gained))
					{
						if (instr->Size > oldSize)
						{
							errorMessage = "Internal error: new size > old size";
							result = nullptr;
							return false;
						}
						if (instr->Size < oldSize)
						{
							gained += oldSize - instr->Size;
							updated = true;
						}
					}
					else if (instr->Size != oldSize)
					{
						errorMessage = "Internal error: new size != old size";
						result = nullptr;
						return false;
					}
					ip += instr->Size;
				}
			}
			if (!updated)
			{
				break;
			}
		}
		for (auto block : blocks)
		{
			block->InitializeData();
		}
		auto resultArray = std::vector<BlockEncoderResult>(blocks.size());
		for (std::int32_t i = 0; i < blocks.size(); i++)
		{
			auto block = blocks[i];
			auto encoder = Encoder::Create(bitness, block->CodeWriter);
			std::uint64_t ip = block->RIP;
			auto newInstructionOffsets = ReturnNewInstructionOffsets ? std::vector<std::uint32_t>(block->GetInstructions().size()) : std::vector<std::uint32_t>();
			auto constantOffsets = ReturnConstantOffsets ? std::vector<ConstantOffsets>(block->GetInstructions().size()) : std::vector<ConstantOffsets>();
			auto instructions = block->GetInstructions();
			for (std::int32_t j = 0; j < instructions.size(); j++)
			{
				auto instr = instructions[j];
				std::uint32_t bytesWritten = block->CodeWriter->BytesWritten;
				bool isOriginalInstruction;
				if (!constantOffsets.empty())
				{
					errorMessage = instr->TryEncode(encoder, constantOffsets[j], isOriginalInstruction);
				}
				else
				{
					errorMessage = instr->TryEncode(encoder, _, isOriginalInstruction);
				}
				if (errorMessage != "")
				{
					result = nullptr;
					return false;
				}
				std::uint32_t size = block->CodeWriter->BytesWritten - bytesWritten;
				if (size != instr->Size)
				{
					errorMessage = "Internal error: didn't write all bytes";
					result = nullptr;
					return false;
				}
				if (!newInstructionOffsets.empty())
				{
					if (isOriginalInstruction)
					{
						newInstructionOffsets[j] = static_cast<std::uint32_t>(ip - block->RIP);
					}
					else
					{
						newInstructionOffsets[j] = std::numeric_limits<std::uint32_t>::max();
					}
				}
				ip += size;
			}
			resultArray[i] = BlockEncoderResult(block->RIP, block->relocInfos, newInstructionOffsets, constantOffsets);
			block->WriteData();
		}
		errorMessage = "";
		result = resultArray;
		return true;
	}

	TargetInstr BlockEncoder::GetTarget(std::uint64_t address)
	{
		TValue instr;
		std::unordered_map<std::uint64_t, Instr*>::const_iterator toInstr_iterator = toInstr.find(address);
		if (toInstr_iterator != toInstr.end())
		{
			instr = toInstr_iterator->second;
			return TargetInstr(instr);
		}
		else
		{
			instr = toInstr_iterator->second;
		}
		return TargetInstr(address);
	}

	std::uint32_t BlockEncoder::GetInstructionSize(Instruction const instruction, std::uint64_t ip)
	{
		std::uint32_t size;
		if (!nullEncoder->TryEncode(instruction, ip, size, _))
		{
			size = IcedConstants::MaxInstructionLength;
		}
		return size;
	}
}