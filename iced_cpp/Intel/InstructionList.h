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
	class InstructionList final : public IList<Instruction>, public IReadOnlyList<Instruction>, public System::Collections::IList
	{
	private:
		std::vector<Instruction> elements;
		std::int32_t count = 0;
		/// <summary>
		/// Gets the number of valid elements
		/// </summary>
	public:
		std::int32_t GetCount() const override;
	private:
		std::int32_t ICollection = 0;
		std::int32_t ICollection = 0;
		std::int32_t IReadOnlyCollection = 0;
		/// <summary>
		/// Gets the size of the internal array
		/// </summary>
	public:
		std::int32_t GetCapacity() const;
	private:
		bool ICollection = false;
		bool IList = false;
		bool IList = false;
		bool ICollection = false;
		std::any ICollection;
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
	private:
		Instruction IReadOnlyList;
	public:
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: Object? System.Collections.IList.this[int index]
		std::any& operator [](std::int32_t index);
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
		InstructionList(std::vector<Instruction>& collection);
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
		void Insert(std::int32_t index, Instruction const instruction) override;
		void IList_Insert(std::int32_t index, Instruction instruction) override;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: void System.Collections.IList.Insert(int index, Object? value)
		void System_Collections_IList_Insert(std::int32_t index, std::any value) override;
		/// <summary>
		/// Removes an element from the list
		/// </summary>
		/// <param name="index">Index of element to remove</param>
		void RemoveAt(std::int32_t index) override;
		void IList_RemoveAt(std::int32_t index) override;
		void System_Collections_IList_RemoveAt(std::int32_t index) override;
		/// <summary>
		/// Adds a collection to the end of this list
		/// </summary>
		/// <param name="collection">Collection to add</param>
		void AddRange(std::vector<Instruction>& collection);
		/// <summary>
		/// Inserts elements
		/// </summary>
		/// <param name="index">Index of element</param>
		/// <param name="collection">Items to insert</param>
		void InsertRange(std::int32_t index, std::vector<Instruction>& collection);
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
		void Add(Instruction const instruction) override;
		void ICollection_Add(Instruction instruction) override;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: int IList.Add(Object? value)
		std::int32_t IList_Add(std::any value) override;
		/// <summary>
		/// Clears the list
		/// </summary>
		void Clear() override;
		void ICollection_Clear() override;
		void System_Collections_IList_Clear() override;
		/// <summary>
		/// Checks if <paramref name="instruction"/> exists in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		bool Contains(Instruction const instruction) override;
		bool ICollection_Contains(Instruction instruction) override;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: bool IList.Contains(Object? value)
		bool IList_Contains(std::any value) override;
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		std::int32_t IndexOf(Instruction const instruction) override;
		std::int32_t IList_IndexOf(Instruction instruction) override;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: int IList.IndexOf(Object? value)
		std::int32_t IList_IndexOf(std::any value) override;
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <returns></returns>
		std::int32_t IndexOf(Instruction const instruction, std::int32_t index);
		/// <summary>
		/// Gets the index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <param name="count">Number of instructions to check</param>
		/// <returns></returns>
		std::int32_t IndexOf(Instruction const instruction, std::int32_t index, std::int32_t count);
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		std::int32_t LastIndexOf(Instruction const instruction);
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <returns></returns>
		std::int32_t LastIndexOf(Instruction const instruction, std::int32_t index);
		/// <summary>
		/// Gets the last index of <paramref name="instruction"/> or -1 if it doesn't exist in the list
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <param name="index">Start index</param>
		/// <param name="count">Number of instructions to check</param>
		/// <returns></returns>
		std::int32_t LastIndexOf(Instruction const instruction, std::int32_t index, std::int32_t count);
		/// <summary>
		/// Removes the first copy of <paramref name="instruction"/> and returns <see langword="true"/> if it was removed
		/// </summary>
		/// <param name="instruction">Instruction</param>
		/// <returns></returns>
		bool Remove(Instruction const instruction) override;
		bool ICollection_Remove(Instruction instruction) override;
		//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
		//ORIGINAL LINE: void System.Collections.IList.Remove(Object? value)
		void System_Collections_IList_Remove(std::any value) override;
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
		void CopyTo(std::vector<Instruction>& array, std::int32_t arrayIndex) override;
		void ICollection_CopyTo(std::vector<Instruction>& array, std::int32_t arrayIndex) override;
		void System_Collections_ICollection_CopyTo(Array* array, std::int32_t index) override;
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
	public:
		class Enumerator : public IEnumerator<Instruction>
		{
			/* readonly */
		private:
			InstructionList* list;
			std::int32_t index = 0;
			//C# TO C++ CONVERTER TODO TASK: 'ref return' methods are not converted by C# to C++ Converter:
			//   public ref Instruction Current
			//   {
			//	   get
			//	   {
			//		   return ref list.elements[index];
			//	   }
			//   }
			Instruction IEnumerator;
			std::any IEnumerator;
		public:
			Enumerator(InstructionList* list);
			bool MoveNext() override;
			void Reset() override;
			~Enumerator();

			Enumerator() = default;
		};
		/// <summary>
		/// Gets a ref iterator (use 'foreach ref')
		/// </summary>
		/// <returns></returns>
	public:
		Enumerator GetEnumerator();
		IEnumerator<Instruction>* IEnumerable_GetEnumerator() override;
		System::Collections::IEnumerator* IEnumerable_GetEnumerator() override;
		/// <summary>
		/// Creates a new array with all instructions and returns it
		/// </summary>
		/// <returns></returns>
		std::vector<Instruction> ToArray();
	};
}
