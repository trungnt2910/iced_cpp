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

#include "InstructionList.h"
#include "Iced.Intel.Instruction.h"
#include <vector>
#include <stdexcept>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	class InstructionListDebugView final
	{
		/* readonly */
	private:
		InstructionList* list;
	public:
		InstructionListDebugView(InstructionList* list);
		//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
		//ORIGINAL LINE: [DebuggerBrowsable(DebuggerBrowsableState.RootHidden)] public Instruction[] Items
		std::vector<Instruction> GetItems() const;
	};
}
