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

#include "Block.h"
#include "../../Array2.h"
#include "../ThrowHelper.h"

namespace Iced::Intel::BlockEncoderInternal
{

	std::vector<Instr*> Block::GetInstructions() const
	{
		return instructions;
	}

	//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
	//ORIGINAL LINE: public Block(BlockEncoder blockEncoder, CodeWriter codeWriter, ulong rip, List<RelocInfo>? relocInfos)
	Block::Block(BlockEncoder* blockEncoder, CodeWriter* codeWriter, std::uint64_t rip, std::vector<RelocInfo>& relocInfos)
	{
		CodeWriter = new CodeWriterImpl(codeWriter);
		RIP = rip;
		this->relocInfos = relocInfos;
		instructions = Array2::Empty<Instr*>();
		dataList = std::vector<BlockData*>();
		alignment = static_cast<std::uint32_t>(blockEncoder->GetBitness()) / 8;
		validData = std::vector<BlockData*>();
	}

	void Block::SetInstructions(std::vector<Instr*>& instructions)
	{
		this->instructions = instructions;
	}

	BlockData* Block::AllocPointerLocation()
	{
		auto data = { .IsValid = true };
		dataList.push_back(data);
		return data;
	}

	void Block::InitializeData()
	{
		std::uint64_t baseAddr;
		if (GetInstructions().size() > 0)
		{
			auto instr = GetInstructions()[GetInstructions().size() - 1];
			baseAddr = instr->IP + instr->Size;
		}
		else
		{
			baseAddr = RIP;
		}
		validDataAddress = baseAddr;
		std::uint64_t addr = (baseAddr + alignment - 1) & ~(alignment - 1);
		validDataAddressAligned = addr;
		for (auto data : dataList)
		{
			if (!data->IsValid)
			{
				continue;
			}
			data->__dont_use_address = addr;
			data->__dont_use_address_initd = true;
			validData.push_back(data);
			addr += alignment;
		}
	}

	void Block::WriteData()
	{
		if (validData.empty())
		{
			return;
		}
		auto codeWriter = CodeWriter;
		std::int32_t alignment = static_cast<std::int32_t>(validDataAddressAligned - validDataAddress);
		for (std::int32_t i = 0; i < alignment; i++)
		{
			codeWriter->WriteByte(0xCC);
		}
		auto relocInfos = this->relocInfos;
		std::uint32_t d;
		switch (static_cast<std::int32_t>(this->alignment))
		{
		case 8:
			for (auto data : validData)
			{
				if (!relocInfos.empty())
				{
					relocInfos.push_back(RelocInfo(RelocKind::Offset64, data->GetAddress()));
				}
				d = static_cast<std::uint32_t>(data->Data);
				codeWriter->WriteByte(static_cast<std::uint8_t>(d));
				codeWriter->WriteByte(static_cast<std::uint8_t>(d >> 8));
				codeWriter->WriteByte(static_cast<std::uint8_t>(d >> 16));
				codeWriter->WriteByte(static_cast<std::uint8_t>(d >> 24));
				d = static_cast<std::uint32_t>(data->Data >> 32);
				codeWriter->WriteByte(static_cast<std::uint8_t>(d));
				codeWriter->WriteByte(static_cast<std::uint8_t>(d >> 8));
				codeWriter->WriteByte(static_cast<std::uint8_t>(d >> 16));
				codeWriter->WriteByte(static_cast<std::uint8_t>(d >> 24));
			}
			break;
		default:
			throw InvalidOperationException();
		}
	}

	bool Block::GetCanAddRelocInfos() const
	{
		return !relocInfos.empty();
	}

	void Block::AddRelocInfo(RelocInfo relocInfo)
	{
		if (!relocInfos.empty())
		{
			relocInfos.push_back(relocInfo);
		}
	}

	std::uint64_t BlockData::GetAddress() const
	{
		if (!IsValid)
		{
			ThrowHelper::ThrowInvalidOperationException();
		}
		if (!__dont_use_address_initd)
		{
			ThrowHelper::ThrowInvalidOperationException();
		}
		return __dont_use_address;
	}
}
