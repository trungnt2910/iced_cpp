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

#include "../Encoder.h"
#include "../Iced.Intel.Instruction.h"
#include "../OpKind.g.h"
#include "../Register.g.h"
#include <format>
#include <cassert>

namespace Iced::Intel { class Encoder; }

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
namespace Iced::Intel::EncoderInternal
{
	class Op
	{
	public:
		virtual void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) = 0;
		/// <summary>
		/// If this is an immediate operand, it returns the <see cref="OpKind"/> value, else it returns -1
		/// </summary>
		/// <returns></returns>
		virtual OpKind GetImmediateOpKind();
		/// <summary>
		/// If this is a near branch operand, it returns the <see cref="OpKind"/> value, else it returns -1
		/// </summary>
		/// <returns></returns>
		virtual OpKind GetNearBranchOpKind();
		/// <summary>
		/// If this is a far branch operand, it returns the <see cref="OpKind"/> value, else it returns -1
		/// </summary>
		/// <returns></returns>
		virtual OpKind GetFarBranchOpKind();
	};
	class OpModRM_rm_mem_only final : public Op
	{
		/* readonly */
	private:
		bool mustUseSib = false;
	public:
		OpModRM_rm_mem_only(bool mustUseSib);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpModRM_rm final : public Op
	{
		/* readonly */
	private:
		Register regLo = static_cast<Register>(0);
		/* readonly */
		Register regHi = static_cast<Register>(0);
	public:
		OpModRM_rm(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpRegEmbed8 final : public Op
	{
		/* readonly */
	private:
		Register regLo = static_cast<Register>(0);
		/* readonly */
		Register regHi = static_cast<Register>(0);
	public:
		OpRegEmbed8(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpModRM_rm_reg_only final : public Op
	{
		/* readonly */
	private:
		Register regLo = static_cast<Register>(0);
		/* readonly */
		Register regHi = static_cast<Register>(0);
	public:
		OpModRM_rm_reg_only(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpModRM_reg final : public Op
	{
		/* readonly */
	private:
		Register regLo = static_cast<Register>(0);
		/* readonly */
		Register regHi = static_cast<Register>(0);
	public:
		OpModRM_reg(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpModRM_reg_mem final : public Op
	{
		/* readonly */
	private:
		Register regLo = static_cast<Register>(0);
		/* readonly */
		Register regHi = static_cast<Register>(0);
	public:
		OpModRM_reg_mem(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpModRM_regF0 final : public Op
	{
		/* readonly */
	private:
		Register regLo = static_cast<Register>(0);
		/* readonly */
		Register regHi = static_cast<Register>(0);
	public:
		OpModRM_regF0(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpReg final : public Op
	{
		/* readonly */
	private:
		Register register_ = static_cast<Register>(0);
	public:
		OpReg(Register register_);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpRegSTi final : public Op
	{
	public:
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OprDI final : public Op
	{
	private:
		static std::int32_t GetRegSize(OpKind opKind);
	public:
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpIb final : public Op
	{
		/* readonly */
	private:
		OpKind opKind = static_cast<OpKind>(0);
	public:
		OpIb(OpKind opKind);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetImmediateOpKind() override;
	};
	class OpIw final : public Op
	{
	public:
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetImmediateOpKind() override;
	};
	class OpId final : public Op
	{
		/* readonly */
	private:
		OpKind opKind = static_cast<OpKind>(0);
	public:
		OpId(OpKind opKind);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetImmediateOpKind() override;
	};
	class OpIq final : public Op
	{
	public:
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetImmediateOpKind() override;
	};
	class OpI4 final : public Op
	{
	public:
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetImmediateOpKind() override;
	};
	class OpX final : public Op
	{
	public:
		static std::int32_t GetXRegSize(OpKind opKind);
		static std::int32_t GetYRegSize(OpKind opKind);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpY final : public Op
	{
	public:
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpMRBX final : public Op
	{
	public:
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpJ final : public Op
	{
		/* readonly */
	private:
		OpKind opKind = static_cast<OpKind>(0);
		/* readonly */
		std::int32_t immSize = 0;
	public:
		OpJ(OpKind opKind, std::int32_t immSize);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetNearBranchOpKind() override;
	};
	class OpJx final : public Op
	{
		/* readonly */
	private:
		std::int32_t immSize = 0;
	public:
		OpJx(std::int32_t immSize);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetNearBranchOpKind() override;
	};
	class OpJdisp final : public Op
	{
		/* readonly */
	private:
		std::int32_t displSize = 0;
	public:
		OpJdisp(std::int32_t displSize);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetNearBranchOpKind() override;
	};
	class OpA final : public Op
	{
		/* readonly */
	private:
		std::int32_t size = 0;
	public:
		OpA(std::int32_t size);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetFarBranchOpKind() override;
	};
	class OpO final : public Op
	{
	public:
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpImm final : public Op
	{
		/* readonly */
	private:
		std::uint8_t value = 0;
	public:
		OpImm(std::uint8_t value);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
		OpKind GetImmediateOpKind() override;
	};
	class OpHx final : public Op
	{
		/* readonly */
	private:
		Register regLo = static_cast<Register>(0);
		/* readonly */
		Register regHi = static_cast<Register>(0);
	public:
		OpHx(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpVsib final : public Op
	{
		/* readonly */
	private:
		Register vsibIndexRegLo = static_cast<Register>(0);
		/* readonly */
		Register vsibIndexRegHi = static_cast<Register>(0);
	public:
		OpVsib(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
	class OpIsX final : public Op
	{
		/* readonly */
	private:
		Register regLo = static_cast<Register>(0);
		/* readonly */
		Register regHi = static_cast<Register>(0);
	public:
		OpIsX(Register regLo, Register regHi);
		void Encode(Encoder* encoder, Instruction const instruction, std::int32_t operand) override;
	};
}
