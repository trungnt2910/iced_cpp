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
#include "CodeWriterImpl.h"
#include "../BlockEncoder.h"
#include "Instr.h"
#include <vector>
#include <csharp/exceptionhelper.h>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Iced::Intel::BlockEncoderInternal { class BlockData; class Instr; }

namespace Iced::Intel { class RelocInfo; class CodeWriter; class BlockEncoder; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::BlockEncoderInternal
{
	class Block final
	{
	public:
		CodeWriterImpl CodeWriter;
		std::uint64_t RIP = 0;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public List<RelocInfo>? relocInfos;
		std::vector<RelocInfo> relocInfos;
		const std::vector<std::shared_ptr<Instr>>& GetInstructions() const;
		std::vector<std::shared_ptr<Instr>>& GetInstructions();
	private:
		std::vector<std::shared_ptr<Instr>> instructions;
		/* readonly */
		std::vector<BlockData*> dataList;
		/* readonly */
		std::uint64_t alignment = 0;
		/* readonly */
		std::vector<BlockData*> validData;
		std::uint64_t validDataAddress = 0;
		std::uint64_t validDataAddressAligned = 0;
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: public Block(BlockEncoder blockEncoder, CodeWriter codeWriter, ulong rip, List<RelocInfo>? relocInfos)
		Block(::Iced::Intel::BlockEncoder* blockEncoder, Iced::Intel::CodeWriter* codeWriter, std::uint64_t rip, const std::vector<RelocInfo>& relocInfos);
		void SetInstructions(std::vector<std::shared_ptr<Instr>>& instructions);
		BlockData* AllocPointerLocation();
		void InitializeData();
		void WriteData();
		bool GetCanAddRelocInfos() const;
		void AddRelocInfo(RelocInfo relocInfo);
	};
	class BlockData final
	{
	public:
		std::uint64_t __dont_use_address = 0;
		bool __dont_use_address_initd = false;
		bool IsValid = false;
		std::uint64_t GetAddress() const;
		std::uint64_t Data = 0;
	};
}
