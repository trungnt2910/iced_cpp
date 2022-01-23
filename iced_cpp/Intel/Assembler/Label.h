// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include <cstdint>
#include <string>

#include "../GetHashCode.h"
#include "../ToString.h"

namespace Iced::Intel
{
	/// <summary>
	/// A label that can be created by <see cref="Assembler.CreateLabel"/>.
	/// </summary>
	class Label
	{
	private:
		friend class Assembler;
		std::int32_t InstructionIndex = 0;
		constexpr Label(const std::string& name, std::uint64_t id);
		/// <summary>
		/// Id of this label.
		/// </summary>
		std::uint64_t Id = 0;
		/// <summary>
		/// Name of this label.
		/// </summary>
		std::string Name;
	public:
		/// <summary>
		/// Gets the Label's Id
		/// </summary>
		/// <returns></returns>
		constexpr std::uint64_t GetId() const;
		/// <summary>
		/// Gets the Label's Name
		/// </summary>
		/// <returns></returns>
		constexpr const std::string& GetName() const;
		/// <summary>
		/// Gets the instruction index associated with this label. This is setup after calling <see cref="Assembler.Label"/>.
		/// </summary>
		constexpr std::int32_t GetInstructionIndex() const;
		constexpr void SetInstructionIndex(std::int32_t value);
		/// <summary>
		/// <c>true</c> if this label is empty and was not created by <see cref="Assembler.CreateLabel"/>.
		/// </summary>
		constexpr bool IsEmpty() const;
		/// <inheritdoc />
		constexpr std::string ToString() const;
		/// <inheritdoc />
		constexpr bool Equals(const Label& other) const;
		/// <inheritdoc />
		constexpr std::int32_t GetHashCode() const;
		/// <summary>
		/// Equality operator for <see cref="Label"/>
		/// </summary>
		/// <param name="left">Label</param>
		/// <param name="right">Label</param>
		/// <returns></returns>
		constexpr bool operator == (const Label& right) const;
		/// <summary>
		/// Inequality operator for <see cref="Label"/>
		/// </summary>
		/// <param name="left">Label</param>
		/// <param name="right">Label</param>
		/// <returns></returns>
		constexpr bool operator != (const Label& right) const;
		constexpr Label() = default;
	};

	constexpr Label::Label(const std::string& name, std::uint64_t id)
	{
		Name = (name != "") ? name : "___label";
		Id = id;
		SetInstructionIndex(-1);
	}

	constexpr std::uint64_t Label::GetId() const
	{
		return Id;
	}

	constexpr const std::string& Label::GetName() const
	{
		return Name;
	}

	constexpr std::int32_t Label::GetInstructionIndex() const
	{
		return InstructionIndex;
	}

	constexpr void Label::SetInstructionIndex(std::int32_t value)
	{
		InstructionIndex = value;
	}

	constexpr bool Label::IsEmpty() const
	{
		return Id == 0;
	}

	constexpr std::string Label::ToString() const
	{
		return Iced::Intel::ToString(Name) + "@" + Iced::Intel::ToString(Id);
	}

	constexpr bool Label::Equals(const Label& other) const
	{
		return Name == other.Name && Id == other.Id;
	}

	constexpr std::int32_t Label::GetHashCode() const
	{
		return (Iced::Intel::GetHashCode(Name) * 397) ^ Iced::Intel::GetHashCode(Id);
	}

	constexpr bool Label::operator == (const Label& right) const
	{
		return this->Equals(right);
	}

	constexpr bool Label::operator != (const Label& right) const
	{
		return !this->Equals(right);
	}
}
