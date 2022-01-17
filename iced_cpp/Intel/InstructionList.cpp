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

#include "InstructionList.h"
#include "ThrowHelper.h"
#include "../Array2.h"

namespace Iced::Intel
{

	std::int32_t InstructionList::GetCount() const
	{
		return count;
	}

	std::int32_t InstructionList::GetCapacity() const
	{
		return elements.size();
	}

	Instruction& InstructionList::operator [](std::int32_t index)
	{
		return elements[index];
	}

	const Instruction& InstructionList::operator [](std::int32_t index) const
	{
		return elements[index];
	}


	//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in C++:
	//	void InstructionList::SetIndexer(std::int32_t index, std::any value)
	//	{
	//	 if (!value.has_value())
	//	 {
	//	  ThrowHelper::ThrowArgumentNullException_value();
	//	 }
	//	 if (!(value.type() == typeid(Instruction)))
	//	 {
	//	  ThrowHelper::ThrowArgumentException();
	//	 }
	//	 elements[index] = std::any_cast<Instruction>(value);
	//	}

	InstructionList::InstructionList()
	{
		elements = System::Array2::Empty<Instruction>();
	}

	InstructionList::InstructionList(std::int32_t capacity)
	{
		if (capacity < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_capacity();
		}
		elements = capacity == 0 ? System::Array2::Empty<Instruction>() : std::vector<Instruction>(capacity);
	}

	InstructionList::InstructionList(const InstructionList& list)
	{
		if (list.count == 0)
		{
			ThrowHelper::ThrowArgumentNullException_list();
		}
		std::int32_t length = list.count;
		if (length == 0)
		{
			elements = System::Array2::Empty<Instruction>();
		}
		else
		{
			auto elements = std::vector<Instruction>(length);
			this->elements = elements;
			count = length;
			std::copy_n(list.elements.begin(), length, elements.begin());
		}
	}

	// To-Do: Use concepts
	InstructionList::InstructionList(const std::vector<Instruction>& collection)
	{
		elements = collection;
	}

	void InstructionList::SetMinCapacity(std::int32_t minCapacity)
	{
		auto elements = this->elements;
		std::uint32_t capacity = static_cast<std::uint32_t>(elements.size());
		if (minCapacity <= static_cast<std::int32_t>(capacity))
		{
			return;
		}
		constexpr std::uint32_t DEFAULT_SIZE = 4; // Same as List<Instruction>
		std::uint32_t newCapacity = capacity * 2;
		if (newCapacity < DEFAULT_SIZE)
		{
			newCapacity = DEFAULT_SIZE;
		}
		if (newCapacity < static_cast<std::uint32_t>(minCapacity))
		{
			newCapacity = static_cast<std::uint32_t>(minCapacity);
		}
		// See coreclr/vm/gchelpers.cpp:MaxArrayLength()
		constexpr std::uint32_t MaxArrayLength = 0x7FEFFFFF;
		assert(MaxArrayLength <= std::numeric_limits<std::int32_t>::max());
		if (newCapacity > MaxArrayLength)
		{
			newCapacity = MaxArrayLength;
		}
		auto newElements = std::vector<Instruction>(static_cast<std::int32_t>(newCapacity));
		std::copy_n(elements.begin(), count, newElements.begin());
		this->elements = newElements;
	}

	void InstructionList::MakeRoom(std::int32_t index, std::int32_t extraLength)
	{
		//TODO: This can be optimized to copy less data. The current code can copy the same
		//      data twice if the internal array is resized by SetMinCapacity()
		SetMinCapacity(count + extraLength);
		std::int32_t copyCount = count - index;
		if (copyCount != 0)
		{
			auto elements = this->elements;
			std::copy_n(elements.begin() + index, copyCount, elements.begin() + index + extraLength);
		}
	}

	void InstructionList::Insert(std::int32_t index, Instruction const instruction)
	{
		auto count = this->count;
		if (static_cast<std::uint32_t>(index) > static_cast<std::uint32_t>(count))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		MakeRoom(index, 1);
		elements[index] = instruction;
		this->count = count + 1;
	}

	void InstructionList::RemoveAt(std::int32_t index)
	{
		auto newCount = count;
		if (static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(newCount))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		newCount--;
		count = newCount;
		std::int32_t copyCount = newCount - index;
		if (copyCount != 0)
		{
			auto elements = this->elements;
			std::copy_n(elements.begin() + index + 1, copyCount, elements.begin() + index);
		}
	}

	void InstructionList::AddRange(const std::vector<Instruction>& collection)
	{
		InsertRange(count, collection);
	}

	void InstructionList::InsertRange(std::int32_t index, const std::vector<Instruction>& collection)
	{
		if (static_cast<std::uint32_t>(index) > static_cast<std::uint32_t>(count))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		if (collection.empty())
		{
			ThrowHelper::ThrowArgumentNullException_collection();
		}
		MakeRoom(index, (std::int32_t)collection.size());
		std::copy(collection.begin(), collection.end(), elements.begin() + index);
	}

	void InstructionList::RemoveRange(std::int32_t index, std::int32_t count)
	{
		if (index < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		if (count < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		if (static_cast<std::uint32_t>(index) + static_cast<std::uint32_t>(count) > static_cast<std::uint32_t>(this->count))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		auto newCount = this->count;
		newCount -= count;
		this->count = newCount;
		std::int32_t copyCount = newCount - index;
		if (copyCount != 0)
		{
			auto elements = this->elements;
			std::copy_n(elements.begin() + index + count, copyCount, elements.begin() + index);
		}
	}

	void InstructionList::Add(Instruction const instruction)
	{
		auto count = this->count;
		auto elements = this->elements;
		if (count == elements.size())
		{
			SetMinCapacity(count + 1);
			elements = this->elements;
		}
		elements[count] = instruction;
		this->count = count + 1;
	}

	void InstructionList::Clear()
	{
		count = 0;
	} // There are no GC refs in Instruction, so we don't have to clear the elements

	bool InstructionList::Contains(Instruction const instruction)
	{
		return VectorHelper::indexOf(elements, instruction) >= 0;
	}

	std::int32_t InstructionList::IndexOf(Instruction const instruction)
	{
		auto elements = this->elements;
		std::int32_t count = this->count;
		for (std::int32_t i = 0; i < count; i++)
		{
			if (elements[i] == instruction)
			{
				return i;
			}
		}
		return -1;
	}

	std::int32_t InstructionList::IndexOf(Instruction const instruction, std::int32_t index)
	{
		std::int32_t count = this->count;
		if (static_cast<std::uint32_t>(index) > static_cast<std::uint32_t>(count))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		auto elements = this->elements;
		for (std::int32_t i = index; i < count; i++)
		{
			if (elements[i] == instruction)
			{
				return i;
			}
		}
		return -1;
	}

	std::int32_t InstructionList::IndexOf(Instruction const instruction, std::int32_t index, std::int32_t count)
	{
		if (index < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		if (count < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		std::int32_t end = index + count;
		if (static_cast<std::uint32_t>(end) > static_cast<std::uint32_t>(this->count))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		auto elements = this->elements;
		for (std::int32_t i = index; i < end; i++)
		{
			if (elements[i] == instruction)
			{
				return i;
			}
		}
		return -1;
	}

	std::int32_t InstructionList::LastIndexOf(Instruction const instruction)
	{
		for (std::int32_t i = count - 1; i >= 0; i--)
		{
			if (elements[i] == instruction)
			{
				return i;
			}
		}
		return -1;
	}

	std::int32_t InstructionList::LastIndexOf(Instruction const instruction, std::int32_t index)
	{
		std::int32_t count = this->count;
		if (static_cast<std::uint32_t>(index) > static_cast<std::uint32_t>(count))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		auto elements = this->elements;
		for (std::int32_t i = count - 1; i >= index; i--)
		{
			if (elements[i] == instruction)
			{
				return i;
			}
		}
		return -1;
	}

	std::int32_t InstructionList::LastIndexOf(Instruction const instruction, std::int32_t index, std::int32_t count)
	{
		if (index < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		if (count < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		std::int32_t end = index + count;
		if (static_cast<std::uint32_t>(end) > static_cast<std::uint32_t>(this->count))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		auto elements = this->elements;
		for (std::int32_t i = end - 1; i >= index; i--)
		{
			if (elements[i] == instruction)
			{
				return i;
			}
		}
		return -1;
	}

	bool InstructionList::Remove(Instruction const instruction)
	{
		std::int32_t index = VectorHelper::indexOf(elements, instruction);
		if (index >= 0)
		{
			elements.erase(elements.begin() + index);
		}
		return index >= 0;
	}

	void InstructionList::CopyTo(std::vector<Instruction>& array)
	{
		CopyTo(array, 0);
	}

	void InstructionList::CopyTo(std::vector<Instruction>& array, std::int32_t arrayIndex)
	{
		std::copy_n(elements.begin(), count, array.begin() + arrayIndex);
	}

	void InstructionList::CopyTo(std::int32_t index, std::vector<Instruction>& array, std::int32_t arrayIndex, std::int32_t count)
	{
		std::copy_n(elements.begin() + index, count, array.begin() + arrayIndex);
	}

	InstructionList* InstructionList::GetRange(std::int32_t index, std::int32_t count)
	{
		if (index < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		if (count < 0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		if (static_cast<std::uint32_t>(index) + static_cast<std::uint32_t>(count) > static_cast<std::uint32_t>(this->count))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_count();
		}
		auto list = new InstructionList(count);
		std::copy_n(elements.begin() + index, count, list->elements.begin());
		list->count = count;
		return list;
	}

	std::vector<Instruction> InstructionList::ToArray()
	{
		std::int32_t count = this->count;
		if (count == 0)
		{
			return System::Array2::Empty<Instruction>();
		}
		auto res = std::vector<Instruction>(count);
		std::copy_n(elements.begin(), res.size(), res.begin());
		return res;
	}
}
