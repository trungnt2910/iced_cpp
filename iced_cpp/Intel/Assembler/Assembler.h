// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#if defined(ENCODER) && defined(BLOCK_ENCODER) && defined(CODE_ASSEMBLER)
#include "../InstructionList.h"
#include "Label.h"
#include "../Iced.Intel.Instruction.h"
#include "AssemblerOperandFlags.h"
#include "../BlockEncoder.h"
#include "../CodeWriter.h"
#include "AssemblerResult.h"
#include "../Mnemonic.g.h"
#include "AssemblerRegister.g.h"
#include "AssemblerMemoryOperand.h"
#include "../Code.g.h"
#include "../Internal/Math.h"
#include "../Internal/Enum.h"
#include <bit>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace Iced::Intel
{
	/// <summary>
	/// High-Level Assembler.
	/// </summary>
	class Assembler
	{
	private:
		enum class PrefixFlags
		{
			None = 0,
			Lock = 0x01,
			Repe = 0x02,
			Repne = 0x04,
			Notrack = 0x08,
			PreferVex = 0x10,
			PreferEvex = 0x20
		};
		ICED_DEFINE_FLAGS_FRIEND(PrefixFlags)
		ICED_DEFINE_COMP_FRIEND(PrefixFlags)
		ICED_DEFINE_ARITH_FRIEND(PrefixFlags)
	private:
		std::int32_t Bitness = 0;
		bool PreferVex = false;
		bool PreferShortBranch = false;
		InstructionList instructions;
		std::uint64_t currentLabelId = 0;
		Iced::Intel::Label currentLabel;
		Iced::Intel::Label currentAnonLabel;
		Iced::Intel::Label nextAnonLabel;
		bool definedAnonLabel = false;
		PrefixFlags prefixFlags = static_cast<PrefixFlags>(0);
		/// <summary>
		/// Creates a new instance of this assembler
		/// </summary>
		/// <param name="bitness">The assembler instruction set bitness, either 16, 32 or 64 bit.</param>
	public:
		constexpr Assembler(std::int32_t bitness);
		/// <summary>
		/// Gets the bitness defined for this assembler.
		/// </summary>
		constexpr std::int32_t GetBitness() const;
		/// <summary>
		/// <c>true</c> to prefer VEX encoding over EVEX. This is the default. See also <see cref="vex"/> and <see cref="evex"/>.
		/// </summary>
		constexpr bool GetPreferVex() const;
		constexpr void SetPreferVex(bool value);
		/// <summary>
		/// <c>true</c> to prefer short branch encoding. This is the default.
		/// </summary>
		constexpr bool GetPreferShortBranch() const;
		constexpr void SetPreferShortBranch(bool value);
		constexpr bool GetInstructionPreferVex() const;
		/// <summary>
		/// Gets the instructions.
		/// </summary>
		constexpr InstructionList& GetInstructions();
		/// <summary>
		/// Gets the instructions.
		/// </summary>
		constexpr const InstructionList& GetInstructions() const;
		/// <summary>
		/// Reset the current set of instructions and labels added to this instance.
		/// </summary>
		constexpr void Reset();
		/// <summary>
		/// Creates a label.
		/// </summary>
		/// <param name="name">Optional name of the label.</param>
		/// <returns></returns>
		constexpr Iced::Intel::Label CreateLabel(const std::string& name = "");
		/// <summary>
		/// Gets the current label used by this instance.
		/// </summary>
		constexpr Iced::Intel::Label GetCurrentLabel() const;
		/// <summary>
		/// Use the specified label.
		/// </summary>
		/// <param name="label">Label to use</param>
		/// <exception cref="ArgumentException"></exception>
		constexpr void Label(Iced::Intel::Label& label);
		/// <summary>
		/// Creates an anonymous label that can be referenced by using <see cref="B"/> (backward anonymous label)
		/// and <see cref="F"/> (forward anonymous label).
		/// </summary>
		constexpr void AnonymousLabel();
		/// <summary>
		/// References the previous anonymous label created by <see cref="AnonymousLabel"/>
		/// </summary>
		constexpr Iced::Intel::Label B() const;
		/// <summary>
		/// References the next anonymous label created by a future call to <see cref="AnonymousLabel"/>
		/// </summary>
		constexpr Iced::Intel::Label F();
		/// <summary>
		/// Add an instruction directly to the flow of instructions.
		/// </summary>
		/// <param name="instruction"></param>
		constexpr void AddInstruction(Instruction instruction);
		/// <summary>
		/// Add an instruction directly to the flow of instructions.
		/// </summary>
		/// <param name="instruction"></param>
		/// <param name="flags">Operand flags passed.</param>
	private:
		constexpr void AddInstruction(Instruction instruction, AssemblerOperandFlags flags);
		/// <summary>
		/// Add lock prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
	public:
		constexpr Assembler& lock();
		/// <summary>
		/// Add xacquire prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& xacquire();
		/// <summary>
		/// Add xrelease prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& xrelease();
		/// <summary>
		/// Add rep prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& rep();
		/// <summary>
		/// Add repe/repz prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& repe();
		/// <summary>
		/// Add repe/repz prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& repz();
		/// <summary>
		/// Add repne/repnz prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& repne();
		/// <summary>
		/// Add repne/repnz prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& repnz();
		/// <summary>
		/// Add bnd prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& bnd();
		/// <summary>
		/// Add notrack prefix before the next instruction.
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& notrack();
		/// <summary>
		/// Prefer VEX encoding if the next instruction can be VEX and EVEX encoded
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& vex();
		/// <summary>
		/// Prefer EVEX encoding if the next instruction can be VEX and EVEX encoded
		/// </summary>
		/// <returns></returns>
		constexpr Assembler& evex();
		/// <summary>
		/// Adds data
		/// </summary>
		/// <param name="array">Data</param>
		constexpr void db(std::vector<std::uint8_t>& array);
		/// <summary>
		/// Adds data
		/// </summary>
		/// <param name="array">Data</param>
		/// <param name="index">Start index</param>
		/// <param name="length">Length in bytes</param>
		constexpr void db(std::vector<std::uint8_t>& array, std::int32_t index, std::int32_t length);
		/// <summary>call selector:offset instruction.</summary>
		constexpr void call(std::uint16_t selector, std::uint32_t offset);
		/// <summary>jmp selector:offset instruction.</summary>
		constexpr void jmp(std::uint16_t selector, std::uint32_t offset);
		/// <summary>xlatb instruction.</summary>
		constexpr void xlatb();
		/// <summary>
		/// Generates multibyte NOP instructions
		/// </summary>
		/// <param name="sizeInBytes">Size in bytes of all nops</param>
		constexpr void nop(std::int32_t sizeInBytes);
		/// <summary>
		/// Assembles the instructions of this assembler with the specified options.
		/// </summary>
		/// <param name="writer">The code writer.</param>
		/// <param name="rip">Base address.</param>
		/// <param name="options">Encoding options.</param>
		/// <returns></returns>
		/// <exception cref="InvalidOperationException"></exception>
		constexpr AssemblerResult Assemble(CodeWriter& writer, std::uint64_t rip, BlockEncoderOptions options = BlockEncoderOptions::None);
		/// <summary>
		/// Tries to assemble the instructions of this assembler with the specified options.
		/// </summary>
		/// <param name="writer">The code writer.</param>
		/// <param name="rip">Base address.</param>
		/// <param name="errorMessage">Error messages.</param>
		/// <param name="assemblerResult">The assembler result if successful.</param>
		/// <param name="options">Encoding options.</param>
		/// <returns><c>true</c> if the encoding was successful; <c>false</c> otherwise.</returns>
		constexpr bool TryAssemble(CodeWriter& writer, std::uint64_t rip, std::string& errorMessage, AssemblerResult& assemblerResult, BlockEncoderOptions options = BlockEncoderOptions::None);
		/// <summary>
		/// Internal method used to throw an InvalidOperationException if it was not possible to encode an OpCode.
		/// </summary>
		/// <param name="mnemonic">The mnemonic of the instruction</param>
		/// <param name="argNames">The argument values.</param>
		/// <returns></returns>
	private:
		template <typename T>
		constexpr void NoOpCodeFoundForBuildInternal(std::string& builder, const T& arg)
		{
			builder.append(Iced::Intel::ToString(arg));
		}

		template <typename T, typename... Args>
		constexpr void NoOpCodeFoundForBuildInternal(std::string& builder, const T& arg, const Args&... argNames)
		{
			builder.append(Iced::Intel::ToString(arg));
			builder.append(", ");
			NoOpCodeFoundForBuildInternal(builder, argNames...);
		}

		template <typename... Args>
		constexpr std::invalid_argument NoOpCodeFoundFor(Mnemonic mnemonic, const Args&... argNames)
		{
			auto builder = std::string();
			builder.append("Unable to calculate an OpCode for `");
			builder.append(Internal::StringHelpers::ToLower(ToString(mnemonic)));
			NoOpCodeFoundForBuildInternal(builder, argNames...);
			builder.append(" ");
			builder.append("`. Combination of arguments and/or current bitness ");
			builder.append(Iced::Intel::ToString(GetBitness()));
			builder.append(" is not compatible with any existing OpCode encoding.");
			return std::invalid_argument(builder);
		}
	public:
#include "Assembler.Functions.g.h"
	};
}

namespace Iced::Intel
{
	constexpr Assembler::Assembler(std::int32_t bitness)
	{
		switch (bitness)
		{
		case 16:
		case 32:
		case 64:
			break;
		default:
			throw std::out_of_range("bitness");
		}
		Bitness = bitness;
		instructions = InstructionList();
		currentLabelId = (std::uint8_t)0;
		currentLabel = Iced::Intel::Label();
		currentAnonLabel = Iced::Intel::Label();
		nextAnonLabel = Iced::Intel::Label();
		definedAnonLabel = false;
		prefixFlags = PrefixFlags::None;
		SetPreferVex(true);
		SetPreferShortBranch(true);
	}

	constexpr std::int32_t Assembler::GetBitness() const
	{
		return Bitness;
	}

	constexpr bool Assembler::GetPreferVex() const
	{
		return PreferVex;
	}

	constexpr void Assembler::SetPreferVex(bool value)
	{
		PreferVex = value;
	}

	constexpr bool Assembler::GetPreferShortBranch() const
	{
		return PreferShortBranch;
	}

	constexpr void Assembler::SetPreferShortBranch(bool value)
	{
		PreferShortBranch = value;
	}

	constexpr bool Assembler::GetInstructionPreferVex() const
	{
		if ((prefixFlags & (PrefixFlags::PreferVex | PrefixFlags::PreferEvex)) != (std::uint8_t)0)
		{
			return (prefixFlags & PrefixFlags::PreferVex) != (std::uint8_t)0;
		}
		return GetPreferVex();
	}

	constexpr InstructionList& Assembler::GetInstructions()
	{
		return instructions;
	}

	constexpr const InstructionList& Assembler::GetInstructions() const
	{
		return instructions;
	}

	constexpr void Assembler::Reset()
	{
		instructions.Clear();
		currentLabelId = (std::uint8_t)0;
		currentLabel = Iced::Intel::Label();
		currentAnonLabel = Iced::Intel::Label();
		nextAnonLabel = Iced::Intel::Label();
		definedAnonLabel = false;
		prefixFlags = PrefixFlags::None;
	}

	constexpr Iced::Intel::Label Assembler::CreateLabel(const std::string& name)
	{
		currentLabelId++;
		auto label = Iced::Intel::Label(name, currentLabelId);
		return label;
	}

	constexpr Iced::Intel::Label Assembler::GetCurrentLabel() const
	{
		return currentLabel;
	}

	constexpr void Assembler::Label(Iced::Intel::Label& label)
	{
		if (label.IsEmpty())
		{
			throw std::invalid_argument("Invalid label. Must be created via CreateLabel");
		}
		if (label.GetInstructionIndex() >= (std::uint8_t)0)
		{
			throw std::invalid_argument("Cannot reuse label. The specified label is already associated with an instruction at index " + Iced::Intel::ToString(label.GetInstructionIndex() + "."));
		}
		if (!currentLabel.IsEmpty())
		{
			throw std::logic_error("At most one label per instruction is allowed");
		}
		label.SetInstructionIndex(instructions.GetCount());
		currentLabel = label;
	}

	constexpr void Assembler::AnonymousLabel()
	{
		if (definedAnonLabel)
		{
			throw std::logic_error("At most one anonymous label per instruction is allowed");
		}
		if (nextAnonLabel.IsEmpty())
		{
			currentAnonLabel = CreateLabel();
		}
		else
		{
			currentAnonLabel = nextAnonLabel;
		}
		nextAnonLabel = Iced::Intel::Label();
		definedAnonLabel = true;
	}

	constexpr Iced::Intel::Label Assembler::B() const
	{
		if (currentAnonLabel.IsEmpty())
		{
			throw std::runtime_error("No anonymous label has been created yet");
		}
		return currentAnonLabel;
	}

	constexpr Iced::Intel::Label Assembler::F()
	{
		if (nextAnonLabel.IsEmpty())
		{
			nextAnonLabel = CreateLabel();
		}
		return nextAnonLabel;
	}

	constexpr void Assembler::AddInstruction(Instruction instruction)
	{
		if (!currentLabel.IsEmpty() && definedAnonLabel)
		{
			throw std::runtime_error("You can't create both an anonymous label and a normal label");
		}
		if (!currentLabel.IsEmpty())
		{
			instruction.SetIP(currentLabel.Id);
		}
		else if (definedAnonLabel)
		{
			instruction.SetIP(currentAnonLabel.Id);
		}
		// Setup prefixes
		if (prefixFlags != PrefixFlags::None)
		{
			if ((prefixFlags & PrefixFlags::Lock) != (std::uint8_t)0)
			{
				instruction.SetHasLockPrefix(true);
			}
			if ((prefixFlags & PrefixFlags::Repe) != (std::uint8_t)0)
			{
				instruction.SetHasRepePrefix(true);
			}
			else if ((prefixFlags & PrefixFlags::Repne) != (std::uint8_t)0)
			{
				instruction.SetHasRepnePrefix(true);
			}
			if ((prefixFlags & PrefixFlags::Notrack) != (std::uint8_t)0)
			{
				instruction.SetSegmentPrefix(Register::DS);
			}
		}
		instructions.Add(instruction);
		currentLabel = Iced::Intel::Label();
		definedAnonLabel = false;
		prefixFlags = PrefixFlags::None;
	}

	constexpr void Assembler::AddInstruction(Instruction instruction, AssemblerOperandFlags flags)
	{
		if (flags != AssemblerOperandFlags::None)
		{
			if ((flags & AssemblerOperandFlags::Broadcast) != (std::uint8_t)0)
			{
				instruction.SetBroadcast(true);
			}
			if ((flags & AssemblerOperandFlags::Zeroing) != (std::uint8_t)0)
			{
				instruction.SetZeroingMasking(true);
			}
			if ((flags & AssemblerOperandFlags::RegisterMask) != (std::uint8_t)0)
			{
				// register mask is shift by (std::uint8_t)2 (starts at index (std::uint8_t)1 for K1)
				instruction.SetOpMask(static_cast<Register>(static_cast<std::int32_t>(Register::K0) + ((static_cast<std::int32_t>(flags & AssemblerOperandFlags::RegisterMask)) >> (std::uint8_t)6)));
			}
			if ((flags & AssemblerOperandFlags::SuppressAllExceptions) != (std::uint8_t)0)
			{
				instruction.SetSuppressAllExceptions(true);
			}
			if ((flags & AssemblerOperandFlags::RoundControlMask) != (std::uint8_t)0)
			{
				instruction.SetRoundingControl(static_cast<RoundingControl>(((static_cast<std::int32_t>(flags & AssemblerOperandFlags::RoundControlMask)) >> (std::uint8_t)3)));
			}
		}
		AddInstruction(instruction);
	}

	constexpr Assembler& Assembler::lock()
	{
		prefixFlags |= PrefixFlags::Lock;
		return *this;
	}

	constexpr Assembler& Assembler::xacquire()
	{
		prefixFlags |= PrefixFlags::Repne;
		return *this;
	}

	constexpr Assembler& Assembler::xrelease()
	{
		prefixFlags |= PrefixFlags::Repe;
		return *this;
	}

	constexpr Assembler& Assembler::rep()
	{
		prefixFlags |= PrefixFlags::Repe;
		return *this;
	}

	constexpr Assembler& Assembler::repe()
	{
		prefixFlags |= PrefixFlags::Repe;
		return *this;
	}

	constexpr Assembler& Assembler::repz()
	{
		return repe();
	}

	constexpr Assembler& Assembler::repne()
	{
		prefixFlags |= PrefixFlags::Repne;
		return *this;
	}

	constexpr Assembler& Assembler::repnz()
	{
		return repne();
	}

	constexpr Assembler& Assembler::bnd()
	{
		prefixFlags |= PrefixFlags::Repne;
		return *this;
	}

	constexpr Assembler& Assembler::notrack()
	{
		prefixFlags |= PrefixFlags::Notrack;
		return *this;
	}

	constexpr Assembler& Assembler::vex()
	{
		prefixFlags |= PrefixFlags::PreferVex;
		return *this;
	}

	constexpr Assembler& Assembler::evex()
	{
		prefixFlags |= PrefixFlags::PreferEvex;
		return *this;
	}

	constexpr void Assembler::db(std::vector<std::uint8_t>& array)
	{
		if (array.empty())
		{
			ThrowHelper::ThrowArgumentNullException_array();
		}
		db(array, (std::uint8_t)0, (std::int32_t)array.size());
	}

	constexpr void Assembler::db(std::vector<std::uint8_t>& array, std::int32_t index, std::int32_t length)
	{
		if (array.empty())
		{
			ThrowHelper::ThrowArgumentNullException_array();
		}
		if (index < (std::uint8_t)0)
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_index();
		}
		if (length < (std::uint8_t)0 || static_cast<std::uint32_t>(index + length) > static_cast<std::uint32_t>(array.size()))
		{
			ThrowHelper::ThrowArgumentOutOfRangeException_length();
		}
		constexpr std::int32_t maxLength = (std::uint8_t)16;
		std::int32_t rest;
		std::int32_t cycles = Internal::Math::DivRem(length, maxLength, rest);
		std::int32_t currentPosition = index;
		for (std::int32_t i = (std::uint8_t)0; i < cycles; i++)
		{
			AddInstruction(Instruction::CreateDeclareByte(array, currentPosition, maxLength));
			currentPosition += maxLength;
		}
		if (rest > (std::uint8_t)0)
		{
			AddInstruction(Instruction::CreateDeclareByte(array, currentPosition, rest));
		}
	}

	constexpr void Assembler::call(std::uint16_t selector, std::uint32_t offset)
	{
		AddInstruction(Instruction::CreateBranch(GetBitness() >= 32 ? Code::Call_ptr1632 : Code::Call_ptr1616, selector, offset));
	}

	constexpr void Assembler::jmp(std::uint16_t selector, std::uint32_t offset)
	{
		AddInstruction(Instruction::CreateBranch(GetBitness() >= 32 ? Code::Jmp_ptr1632 : Code::Jmp_ptr1616, selector, offset));
	}

	constexpr void Assembler::xlatb()
	{
		auto switchTempVar_0 = GetBitness();


		auto baseReg = (switchTempVar_0 == 64) ? Register::RBX : (switchTempVar_0 == 32) ? Register::EBX : Register::BX;
		AddInstruction(Instruction::Create(Code::Xlat_m8, MemoryOperand(baseReg, Register::AL)));
	}

	constexpr void Assembler::nop(std::int32_t sizeInBytes)
	{
		const auto AppendNop = [&](int amount)
		{
			switch (amount)
			{
			case 1:
				db((std::uint8_t)0x90); // NOP
				break;
			case 2:
				db((std::uint8_t)0x66, (std::uint8_t)0x90); // 66 NOP
				break;
			case 3:
				db((std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x00); // NOP dword ptr [eax] or NOP word ptr [bx+si]
				break;
			case 4:
				db((std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x40, (std::uint8_t)0x00); // NOP dword ptr [eax + 00] or NOP word ptr [bx+si]
				break;
			case 5:
				if (Bitness != 16)
					db((std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x44, (std::uint8_t)0x00, (std::uint8_t)0x00); // NOP dword ptr [eax + eax*(std::uint8_t)1 + 00]
				else
					db((std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x80, (std::uint8_t)0x00, (std::uint8_t)0x00); // NOP word ptr[bx + si]
				break;
			case 6:
				if (Bitness != 16)
					db((std::uint8_t)0x66, (std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x44, (std::uint8_t)0x00, (std::uint8_t)0x00); // 66 NOP dword ptr [eax + eax*(std::uint8_t)1 + 00]
				else
					db((std::uint8_t)0x66, (std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x80, (std::uint8_t)0x00, (std::uint8_t)0x00); // NOP dword ptr [bx+si]
				break;
			case 7:
				if (Bitness != 16)
					db((std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x80, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00); // NOP dword ptr [eax + 00000000]
				else
					db((std::uint8_t)0x67, (std::uint8_t)0x66, (std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x44, (std::uint8_t)0x00, (std::uint8_t)0x00); // NOP dword ptr [eax+eax]
				break;
			case 8:
				if (Bitness != 16)
					db((std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x84, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00); // NOP dword ptr [eax + eax*(std::uint8_t)1 + 00000000]
				else
					db((std::uint8_t)0x67, (std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x80, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00); // NOP word ptr [eax]
				break;
			case 9:
				if (Bitness != 16)
					db((std::uint8_t)0x66, (std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x84, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00); // 66 NOP dword ptr [eax + eax*(std::uint8_t)1 + 00000000]
				else
					db((std::uint8_t)0x67, (std::uint8_t)0x0F, (std::uint8_t)0x1F, (std::uint8_t)0x84, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00, (std::uint8_t)0x00); // NOP word ptr [eax+eax]
				break;
			}
		};

		if (sizeInBytes < (std::uint8_t)0)
		{
			throw std::out_of_range("sizeInBytes");
		}
		if (this->prefixFlags != PrefixFlags::None)
		{
			throw std::runtime_error("No prefixes are allowed");
		}
		if (sizeInBytes == (std::uint8_t)0)
		{
			return;
		}
		constexpr std::int32_t maxMultibyteNopInstructionLength = (std::uint8_t)9;
		std::int32_t rest;
		std::int32_t cycles = Internal::Math::DivRem(sizeInBytes, maxMultibyteNopInstructionLength, rest);
		for (std::int32_t i = (std::uint8_t)0; i < cycles; i++)
		{
			AppendNop(maxMultibyteNopInstructionLength);
		}
		if (rest > (std::uint8_t)0)
		{
			AppendNop(rest);
		}
	}

	constexpr AssemblerResult Assembler::Assemble(CodeWriter& writer, std::uint64_t rip, BlockEncoderOptions options)
	{
		std::string errorMessage;
		Iced::Intel::AssemblerResult assemblerResult;
		if (!TryAssemble(writer, rip, errorMessage, assemblerResult, options))
		{
			throw std::runtime_error(errorMessage);
		}
		return assemblerResult;
	}

	constexpr bool Assembler::TryAssemble(CodeWriter& writer, std::uint64_t rip, std::string& errorMessage, AssemblerResult& assemblerResult, BlockEncoderOptions options)
	{
		assemblerResult = Iced::Intel::AssemblerResult();
		// Protect against using a prefix without actually using it
		if (prefixFlags != PrefixFlags::None)
		{
			errorMessage = std::format("Unused prefixes {0:s}. You must emit an instruction after using an instruction prefix.", Iced::Intel::ToString(prefixFlags));
			return false;
		}
		// Protect against a label emitted without being attached to an instruction
		if (!currentLabel.IsEmpty())
		{
			errorMessage = std::format("Unused label {0:s}. You must emit an instruction after emitting a label.", Iced::Intel::ToString(currentLabel));
			return false;
		}
		if (definedAnonLabel)
		{
			errorMessage = "Unused anonymous label. You must emit an instruction after emitting a label.";
			return false;
		}
		if (!nextAnonLabel.IsEmpty())
		{
			errorMessage = "Found an @F anonymous label reference but there was no call to " "AnonymousLabel";
			return false;
		}
		auto blocks = std::vector<InstructionBlock>{ InstructionBlock(&writer, instructions.ToArray(), rip) };
		std::vector<BlockEncoderResult> blockResults;
		if (BlockEncoder::TryEncode(GetBitness(), blocks, errorMessage, blockResults, options))
		{
			assemblerResult = AssemblerResult(blockResults);
			return true;
		}
		else
		{
			assemblerResult = AssemblerResult(std::vector<BlockEncoderResult>());
			return false;
		}
	}

}
#endif