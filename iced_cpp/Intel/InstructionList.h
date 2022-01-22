// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "Iced.Intel.Instruction.h"
#include <algorithm>
#include <concepts>
#include <limits>
#include <span>
#include <vector>

namespace Iced::Intel
{
	/// <summary>
	/// A list of <see cref="Instruction"/>s. It's faster than <see cref="List{T}"/> and has
	/// methods to get references to the elements so no <see cref="Instruction"/> gets copied.
	/// Use 'foreach (ref var instr in list)' to use the foreach ref iterator.
	/// </summary>
	class InstructionList final
	{
	private:
		std::vector<Instruction> elements;
		/// <summary>
		/// Gets the number of valid elements
		/// </summary>
	public:
		constexpr std::size_t size() const
		{
			return elements.size();
		}
		constexpr std::int32_t GetCount() const
		{
			return (std::int32_t)elements.size();
		}
		/// <summary>
		/// Gets the size of the internal array
		/// </summary>
		constexpr std::size_t capacity() const
		{
			return elements.capacity();
		}
		constexpr std::int32_t GetCapacity() const
		{
			return (std::int32_t)elements.capacity();
		}
		/// <summary>
		/// Gets a reference to an element. The returned reference is valid until the internal array is resized.
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <returns></returns>
		constexpr Instruction& operator [](std::int32_t index)
		{
			return elements[index];
		}
		constexpr const Instruction& operator [](std::int32_t index) const
		{
			return elements[index];
		}
		/// <summary>
		/// Constructor
		/// </summary>
		constexpr InstructionList() = default;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="capacity">Initial size of the internal array</param>
		constexpr InstructionList(std::int32_t capacity)
		{
			elements.reserve(capacity);
		}
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="list">List that will be copied to this instance</param>
		constexpr InstructionList(const InstructionList& list) = default;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="list">List that will be moved to this instance</param>
		constexpr InstructionList(InstructionList&& list) = default;
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="collection">Collection that will be copied to this instance</param>
		constexpr InstructionList(const std::vector<Instruction>& collection) : elements(collection)
		{
		}
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="first">Iterator to first element</param>
		/// <param name="last">Iterator to last element</param>
		template <std::forward_iterator Iter>
		constexpr InstructionList(const Iter& first, const Iter& last) : elements(first, last)
		{
		}
		/// <summary>
		/// Copy assignment operator
		/// </summary>
		/// <param name="other">Other instance</param>
		/// <returns></returns>
		constexpr InstructionList& operator=(const InstructionList& other) = default;
	private:
		constexpr void SetMinCapacity(std::int32_t minCapacity)
		{
			elements.reserve(minCapacity);
		}
	public:
		constexpr void reserve(std::size_t minCapacity)
		{
			elements.reserve(minCapacity);
		}
	private:
		/// <summary>
		/// Allocates an uninitialized element at the end of the list and returns a reference to it.
		/// The return value can be passed to eg. Decoder.Decode(out Instruction).
		/// The returned reference is valid until the internal array is resized.
		/// </summary>
		/// <returns></returns>
		constexpr Instruction& AllocUninitializedElement()
		{
			elements.resize(elements.size() + 1);
			return elements.back();
		}
		constexpr void MakeRoom(std::int32_t index, std::int32_t extraLength)
		{
			std::size_t oldSize = elements.size();
			elements.resize(elements.size() + (std::size_t)extraLength);
			// To-Do: Can the ranges overlap?
			std::copy_backward(elements.begin() + index, elements.begin() + oldSize, elements.end() - (std::size_t)extraLength);
		}
	public:
		constexpr auto begin()
		{
			return elements.begin();
		}
		constexpr auto end()
		{
			return elements.end();
		}
		/// <summary>
		/// Inserts an element
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <param name="instruction">Instruction to add</param>
		constexpr void Insert(std::int32_t index, const Instruction& instruction)
		{
			elements.insert(elements.begin() + index, instruction);
		}
		constexpr auto insert(std::vector<Instruction>::const_iterator pos, const Instruction& instruction)
		{
			return elements.insert(pos, instruction);
		}
		/// <summary>
		/// Removes an element from the list
		/// </summary>
		/// <param name="index">Index of element to remove</param>
		constexpr void RemoveAt(std::int32_t index)
		{
			elements.erase(elements.begin() + index);
		}
		constexpr auto erase(std::vector<Instruction>::const_iterator pos)
		{
			return elements.erase(pos);
		}
		/// <summary>
		/// Adds a collection to the end of this list
		/// </summary>
		/// <param name="collection">Collection to add</param>
		constexpr void AddRange(const std::vector<Instruction>& collection)
		{
			elements.insert(elements.end(), collection.begin(), collection.end());
		}
		/// <summary>
		/// Inserts elements
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <param name="collection">Items to insert</param>
		constexpr void InsertRange(std::int32_t index, const std::vector<Instruction>& collection)
		{
			elements.insert(elements.begin() + index, collection.begin(), collection.end());
		}
		constexpr auto insert(std::vector<Instruction>::const_iterator pos, std::vector<Instruction>::const_iterator first, std::vector<Instruction>::const_iterator last)
		{
			return elements.insert(pos, first, last);
		}
		/// <summary>
		/// Removes elements
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <param name="count">Number of elements to remove</param>
		constexpr void RemoveRange(std::int32_t index, std::int32_t count)
		{
			elements.erase(elements.begin() + index, elements.begin() + index + count);
		}
		constexpr auto insert(std::vector<Instruction>::const_iterator first, std::vector<Instruction>::const_iterator last)
		{
			return elements.erase(first, last);
		}
		/// <summary>
		/// Adds a new instruction to the end of the list
		/// </summary>
		/// <param name="instruction">Instruction to add</param>
		constexpr void Add(const Instruction& instruction)
		{
			elements.push_back(instruction);
		}
		constexpr void push_back(const Instruction& instruction)
		{
			elements.push_back(instruction);
		}
		/// <summary>
		/// Clears the list
		/// </summary>
		constexpr void Clear()
		{
			elements.clear();
		}
		constexpr void clear()
		{
			elements.clear();
		}
		/// <summary>
		/// Checks if <paramref name="instruction"/> exists in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		constexpr bool Contains(const Instruction& instruction)
		{
			return std::find(elements.begin(), elements.end(), instruction) != elements.end();
		}
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		constexpr std::int32_t IndexOf(const Instruction& instruction)
		{
			auto it = std::find(elements.begin(), elements.end(), instruction);
			return (it == elements.end()) ? -1 : (std::int32_t)(it - elements.begin());
		}
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <returns></returns>
		constexpr std::int32_t IndexOf(const Instruction& instruction, std::int32_t index)
		{
			auto it = std::find(elements.begin() + index, elements.end(), instruction);
			return (it == elements.end()) ? -1 : (std::int32_t)(it - elements.begin());
		}
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <param name="count">Number of instructions to check</param>
		/// <returns></returns>
		constexpr std::int32_t IndexOf(const Instruction& instruction, std::int32_t index, std::int32_t count)
		{
			auto it = std::find(elements.begin() + index, elements.begin() + (index + count), instruction);
			auto diff = (std::int32_t)(it - elements.begin());
			return (diff == count) ? -1 : diff;
		}
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		constexpr std::int32_t LastIndexOf(const Instruction& instruction)
		{
			auto it = std::find(elements.rbegin(), elements.rend(), instruction);
			return (it == elements.rbegin()) ? -1 : (std::int32_t)(it.base() - 1 - elements.begin());
		}
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <returns></returns>
		constexpr std::int32_t LastIndexOf(const Instruction& instruction, std::int32_t index)
		{
			auto it = std::find(std::make_reverse_iterator(elements.begin() + index + 1), elements.rend(), instruction);
			return (it == elements.rbegin()) ? -1 : (std::int32_t)(it.base() - 1 - elements.begin());
		}
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <param name="count">Number of instructions to check</param>
		/// <returns></returns>
		constexpr std::int32_t LastIndexOf(const Instruction& instruction, std::int32_t index, std::int32_t count)
		{
			auto it = std::find(std::make_reverse_iterator(elements.begin() + index + 1), std::make_reverse_iterator(elements.begin() + index + 1 - count), instruction);
			return (it == elements.rbegin()) ? -1 : (std::int32_t)(it.base() - 1 - elements.begin());
		}
		/// <summary>
		/// Removes the first copy of <paramref name="instruction"/> and returns <see langword="true"/> if it was removed
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		constexpr bool Remove(const Instruction& instruction)
		{
			auto it = std::find(elements.begin(), elements.end(), instruction);
			if (it == elements.end())
			{
				return false;
			}
			elements.erase(it);
			return true;
		}
		/// <summary>
		/// Copies this collection to <paramref name="array"/>
		/// </summary>
		/// <param name="array">Destination array</param>
		constexpr void CopyTo(std::vector<Instruction>& array)
		{
			copy(elements.begin(), elements.end(), array.begin());
		}
		/// <summary>
		/// Copies this collection to <paramref name="array"/>
		/// </summary>
		/// <param name="array">Destination array</param>
		/// <param name="arrayIndex">Start index in <paramref name="array"/></param>
		constexpr void CopyTo(std::vector<Instruction>& array, std::int32_t arrayIndex)
		{
			copy(elements.begin(), elements.end(), array.begin() + arrayIndex);
		}
		/// <summary>
		/// Copies this collection to <paramref name="array"/>
		/// </summary>
		/// <param name="index">Index in this collection</param>
		/// <param name="array">Destination array</param>
		/// <param name="arrayIndex">Destination index</param>
		/// <param name="count">Number of elements to copy</param>
		constexpr void CopyTo(std::int32_t index, std::vector<Instruction>& array, std::int32_t arrayIndex, std::int32_t count)
		{
			copy_n(elements.begin() + index, (std::size_t) count, array.begin() + arrayIndex);
		}
		/// <summary>
		/// Creates a new list that contains some of the instructions in this list
		/// </summary>
		/// <param name="index">Index of first instruction</param>
		/// <param name="count">Number of instructions</param>
		/// <returns></returns>
		constexpr std::span<Instruction> GetRange(std::int32_t index, std::int32_t count)
		{
			return std::span<Instruction>(&elements[index], count);
		}
		/// <summary>
		/// Gets a ref iterator (use 'foreach ref')
		/// </summary>
		/// <returns></returns>
	public:
		/// <summary>
		/// Creates a new array with all instructions and returns it
		/// </summary>
		/// <returns></returns>
		constexpr const std::vector<Instruction>& ToArray() const
		{
			return elements;
		}
	};
}
