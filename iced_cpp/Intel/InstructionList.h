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

#include "Iced.Intel.Instruction.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <any>
#include <csharp/exceptionhelper.h>
#include <cassert>
#include <csharp/vectorhelper.h>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel
{
	/// <summary>
	/// A list of <see cref="Instruction"/>s. It's faster than <see cref="List{T}"/> and has
	/// methods to get references to the elements so no <see cref="Instruction"/> gets copied.
	/// Use 'foreach (ref var instr in list)' to use the foreach ref iterator.
	/// </summary>
   //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
   //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
   //ORIGINAL LINE: [DebuggerDisplay("Count = {" + nameof(Count) + "}")][DebuggerTypeProxy(typeof(InstructionListDebugView))][System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)] public sealed class InstructionList : IList<Instruction>, IReadOnlyList<Instruction>, System.Collections.IList
	class InstructionList final
	{
	private:
		std::vector<Instruction> elements;
		std::int32_t count = 0;
		/// <summary>
		/// Gets the number of valid elements
		/// </summary>
	public:
		std::int32_t GetCount() const;
	private:
		/// <summary>
		/// Gets the size of the internal array
		/// </summary>
	public:
		std::int32_t GetCapacity() const;
	private:
		/// <summary>
		/// Gets a reference to an element. The returned reference is valid until the internal array is resized.
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <returns></returns>
	  //C# TO C++ CONVERTER TODO TASK: 'ref return' methods are not converted by C# to C++ Converter:
	  //  public ref Instruction this[int index]
	  //  {
	  //	  get
	  //	  {
	  //		  return ref elements[index];
	  //	  }
	  //  }
	public:
		Instruction& operator [](std::int32_t index);
		const Instruction& operator [](std::int32_t index) const;
	private:
		Instruction IReadOnlyList;
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: Object? System.Collections.IList.this[int index]
		/// <summary>
		/// Constructor
		/// </summary>
		InstructionList();
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="capacity">Initial size of the internal array</param>
		InstructionList(std::int32_t capacity);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="list">List that will be copied to this instance</param>
		InstructionList(const InstructionList& list);
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="collection">Collection that will be copied to this instance</param>
		InstructionList(const std::vector<Instruction>& collection);
	private:
		void SetMinCapacity(std::int32_t minCapacity);
		/// <summary>
		/// Allocates an uninitialized element at the end of the list and returns a reference to it.
		/// The return value can be passed to eg. Decoder.Decode(out Instruction).
		/// The returned reference is valid until the internal array is resized.
		/// </summary>
		/// <returns></returns>
	  //C# TO C++ CONVERTER TODO TASK: 'ref return' methods are not converted by C# to C++ Converter:
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public ref Instruction AllocUninitializedElement()
	  //  public ref Instruction AllocUninitializedElement()
	  //  {
	  //   var count = this.count;
	  //   var elements = this.elements;
	  //   if (count == elements.Length)
	  //   {
	  //	SetMinCapacity(count + 1);
	  //	elements = this.elements;
	  //   }
	  //   this.count = count + 1;
	  //   return ref elements[count];
	  //  }
		void MakeRoom(std::int32_t index, std::int32_t extraLength);
		/// <summary>
		/// Inserts an element
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <param name="instruction">Instruction to add</param>
	public:
		void Insert(std::int32_t index, const Instruction& instruction);
		/// <summary>
		/// Removes an element from the list
		/// </summary>
		/// <param name="index">Index of element to remove</param>
		void RemoveAt(std::int32_t index);
		/// <summary>
		/// Adds a collection to the end of this list
		/// </summary>
		/// <param name="collection">Collection to add</param>
		void AddRange(const std::vector<Instruction>& collection);
		/// <summary>
		/// Inserts elements
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <param name="collection">Items to insert</param>
		void InsertRange(std::int32_t index, const std::vector<Instruction>& collection);
		/// <summary>
		/// Removes elements
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <param name="count">Number of elements to remove</param>
		void RemoveRange(std::int32_t index, std::int32_t count);
		/// <summary>
		/// Adds a new instruction to the end of the list
		/// </summary>
		/// <param name="instruction">Instruction to add</param>
	  //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
	  //ORIGINAL LINE: [MethodImpl(MethodImplOptions.AggressiveInlining)] public void Add(in Instruction instruction)
		void Add(const Instruction& instruction);
		/// <summary>
		/// Clears the list
		/// </summary>
		void Clear();
		/// <summary>
		/// Checks if <paramref name="instruction"/> exists in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		bool Contains(const Instruction& instruction);
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		std::int32_t IndexOf(const Instruction& instruction);
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <returns></returns>
		std::int32_t IndexOf(const Instruction& instruction, std::int32_t index);
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <param name="count">Number of instructions to check</param>
		/// <returns></returns>
		std::int32_t IndexOf(const Instruction& instruction, std::int32_t index, std::int32_t count);
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		std::int32_t LastIndexOf(const Instruction& instruction);
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <returns></returns>
		std::int32_t LastIndexOf(const Instruction& instruction, std::int32_t index);
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <param name="count">Number of instructions to check</param>
		/// <returns></returns>
		std::int32_t LastIndexOf(const Instruction& instruction, std::int32_t index, std::int32_t count);
		/// <summary>
		/// Removes the first copy of <paramref name="instruction"/> and returns <see langword="true"/> if it was removed
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		bool Remove(const Instruction& instruction);
		/// <summary>
		/// Copies this collection to <paramref name="array"/>
		/// </summary>
		/// <param name="array">Destination array</param>
		void CopyTo(std::vector<Instruction>& array);
		/// <summary>
		/// Copies this collection to <paramref name="array"/>
		/// </summary>
		/// <param name="array">Destination array</param>
		/// <param name="arrayIndex">Start index in <paramref name="array"/></param>
		void CopyTo(std::vector<Instruction>& array, std::int32_t arrayIndex);
		/// <summary>
		/// Copies this collection to <paramref name="array"/>
		/// </summary>
		/// <param name="index">Index in this collection</param>
		/// <param name="array">Destination array</param>
		/// <param name="arrayIndex">Destination index</param>
		/// <param name="count">Number of elements to copy</param>
		void CopyTo(std::int32_t index, std::vector<Instruction>& array, std::int32_t arrayIndex, std::int32_t count);
		/// <summary>
		/// Creates a new list that contains some of the instructions in this list
		/// </summary>
		/// <param name="index">Index of first instruction</param>
		/// <param name="count">Number of instructions</param>
		/// <returns></returns>
		InstructionList* GetRange(std::int32_t index, std::int32_t count);
		/// <summary>
		/// Gets a ref iterator (use 'foreach ref')
		/// </summary>
		/// <returns></returns>
	public:
		/// <summary>
		/// Creates a new array with all instructions and returns it
		/// </summary>
		/// <returns></returns>
		std::vector<Instruction> ToArray();
	};
}
