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

#include "InstructionListDebugView.h"

namespace Iced::Intel
{

	InstructionListDebugView::InstructionListDebugView(InstructionList* list)
	{
		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: this.list = list ?? throw new ArgumentNullException(nameof(list));
		this->list = (!list->empty()) ? list : throw std::invalid_argument("list");
	}

	std::vector<Instruction> InstructionListDebugView::GetItems() const
	{
		return list->ToArray();
	}
}
