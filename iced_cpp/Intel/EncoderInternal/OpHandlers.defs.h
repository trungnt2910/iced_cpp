// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "../Encoder.h"
#include "../Iced.Intel.Instruction.h"
#include "../OpKind.g.h"
#include "../Register.g.h"
#include <format>
#include <cassert>

namespace Iced::Intel { class Encoder; }

namespace Iced::Intel::EncoderInternal
{
	class Op
	{
	public:
		constexpr virtual void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const = 0;
		/// <summary>
		/// If this is an immediate operand, it returns the <see cref="OpKind"/> value, else it returns -1
		/// </summary>
		/// <returns></returns>
		constexpr virtual OpKind GetImmediateOpKind() const;
		/// <summary>
		/// If this is a near branch operand, it returns the <see cref="OpKind"/> value, else it returns -1
		/// </summary>
		/// <returns></returns>
		constexpr virtual OpKind GetNearBranchOpKind() const;
		/// <summary>
		/// If this is a far branch operand, it returns the <see cref="OpKind"/> value, else it returns -1
		/// </summary>
		/// <returns></returns>
		constexpr virtual OpKind GetFarBranchOpKind() const;
	};
	class OpModRM_rm_mem_only final : public Op
	{
	private:
		bool mustUseSib = false;
	public:
		constexpr OpModRM_rm_mem_only(bool mustUseSib);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpModRM_rm final : public Op
	{
	private:
		Register regLo = static_cast<Register>(0);
		Register regHi = static_cast<Register>(0);
	public:
		constexpr OpModRM_rm(Register regLo, Register regHi)
			: regLo(regLo), regHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpRegEmbed8 final : public Op
	{
	private:
		Register regLo = static_cast<Register>(0);
		Register regHi = static_cast<Register>(0);
	public:
		constexpr OpRegEmbed8(Register regLo, Register regHi)
			: regLo(regLo), regHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpModRM_rm_reg_only final : public Op
	{
	private:
		Register regLo = static_cast<Register>(0);
		Register regHi = static_cast<Register>(0);
	public:
		constexpr OpModRM_rm_reg_only(Register regLo, Register regHi)
			: regLo(regLo), regHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpModRM_reg final : public Op
	{
	private:
		Register regLo = static_cast<Register>(0);
		Register regHi = static_cast<Register>(0);
	public:
		constexpr OpModRM_reg(Register regLo, Register regHi)
			: regLo(regLo), regHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpModRM_reg_mem final : public Op
	{
	private:
		Register regLo = static_cast<Register>(0);
		Register regHi = static_cast<Register>(0);
	public:
		constexpr OpModRM_reg_mem(Register regLo, Register regHi)
			: regLo(regLo), regHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpModRM_regF0 final : public Op
	{
	private:
		Register regLo = static_cast<Register>(0);
		Register regHi = static_cast<Register>(0);
	public:
		constexpr OpModRM_regF0(Register regLo, Register regHi)
			: regLo(regLo), regHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpReg final : public Op
	{
	private:
		Register register_ = static_cast<Register>(0);
	public:
		constexpr OpReg(Register register_);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpRegSTi final : public Op
	{
	public:
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OprDI final : public Op
	{
	private:
		constexpr static std::int32_t GetRegSize(OpKind opKind);
	public:
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpIb final : public Op
	{
	private:
		OpKind opKind = static_cast<OpKind>(0);
	public:
		constexpr OpIb(OpKind opKind);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetImmediateOpKind() const override;
	};
	class OpIw final : public Op
	{
	public:
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetImmediateOpKind() const override;
	};
	class OpId final : public Op
	{
	private:
		OpKind opKind = static_cast<OpKind>(0);
	public:
		constexpr OpId(OpKind opKind);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetImmediateOpKind() const override;
	};
	class OpIq final : public Op
	{
	public:
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetImmediateOpKind() const override;
	};
	class OpI4 final : public Op
	{
	public:
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetImmediateOpKind() const override;
	};
	class OpX final : public Op
	{
	public:
		constexpr static std::int32_t GetXRegSize(OpKind opKind);
		constexpr static std::int32_t GetYRegSize(OpKind opKind);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpY final : public Op
	{
	public:
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpMRBX final : public Op
	{
	public:
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpJ final : public Op
	{
	private:
		OpKind opKind = static_cast<OpKind>(0);
		std::int32_t immSize = 0;
	public:
		constexpr OpJ(OpKind opKind, std::int32_t immSize);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetNearBranchOpKind() const override;
	};
	class OpJx final : public Op
	{
	private:
		std::int32_t immSize = 0;
	public:
		constexpr OpJx(std::int32_t immSize);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetNearBranchOpKind() const override;
	};
	class OpJdisp final : public Op
	{
	private:
		std::int32_t displSize = 0;
	public:
		constexpr OpJdisp(std::int32_t displSize);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetNearBranchOpKind() const override;
	};
	class OpA final : public Op
	{
	private:
		std::int32_t size = 0;
	public:
		constexpr OpA(std::int32_t size);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetFarBranchOpKind() const override;
	};
	class OpO final : public Op
	{
	public:
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpImm final : public Op
	{
	private:
		std::uint8_t value = 0;
	public:
		constexpr OpImm(std::uint8_t value);
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
		constexpr OpKind GetImmediateOpKind() const override;
	};
	class OpHx final : public Op
	{
	private:
		Register regLo = static_cast<Register>(0);
		Register regHi = static_cast<Register>(0);
	public:
		constexpr OpHx(Register regLo, Register regHi)
			: regLo(regLo), regHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpVsib final : public Op
	{
	private:
		Register vsibIndexRegLo = static_cast<Register>(0);
		Register vsibIndexRegHi = static_cast<Register>(0);
	public:
		constexpr OpVsib(Register regLo, Register regHi)
			: vsibIndexRegLo(regLo), vsibIndexRegHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
	class OpIsX final : public Op
	{
	private:
		Register regLo = static_cast<Register>(0);
		Register regHi = static_cast<Register>(0);
	public:
		constexpr OpIsX(Register regLo, Register regHi)
			: regLo(regLo), regHi(regHi)
		{
		}
		void Encode(Encoder& encoder, const Instruction& instruction, std::int32_t operand) const override;
	};
}
