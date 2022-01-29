// C# helper headers




// Commonly used headers
#include <cstdint>
#include <format>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#pragma once

#include "FormatterInternal/FormatterString.h"
#include "FormatterInternal/PseudoOpsKind.g.h"
#include <string>
#include <vector>

// Code generated from Iced. Do not edit.
// Commit tag: badb6147c0994a4954fa27645aba2b02c2bb9502.
// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors
using namespace Iced::Intel::FormatterInternal;
namespace Iced::Intel
{
	class FormatterConstants final
	{
	public:
		static std::vector<FormatterString> GetPseudoOps(PseudoOpsKind kind);
	private:
		class StaticConstructor
		{
		public:
			StaticConstructor();
		};

	private:
		static FormatterConstants::StaticConstructor staticConstructor;

		static std::vector<FormatterString> Create(const std::vector<std::string>& cc, std::int32_t size, const std::string& prefix, const std::string& suffix);
		static std::vector<FormatterString> cmpps_pseudo_ops;
		static std::vector<FormatterString> vcmpps_pseudo_ops;
		static std::vector<FormatterString> cmppd_pseudo_ops;
		static std::vector<FormatterString> vcmppd_pseudo_ops;
		static std::vector<FormatterString> cmpss_pseudo_ops;
		static std::vector<FormatterString> vcmpss_pseudo_ops;
		static std::vector<FormatterString> cmpsd_pseudo_ops;
		static std::vector<FormatterString> vcmpsd_pseudo_ops;
		static std::vector<FormatterString> vcmpph_pseudo_ops;
		static std::vector<FormatterString> vcmpsh_pseudo_ops;
		static std::vector<FormatterString> vcmpps8_pseudo_ops;
		static std::vector<FormatterString> vcmppd8_pseudo_ops;
		static std::vector<FormatterString> vpcmpd6_pseudo_ops;
		static std::vector<FormatterString> vpcmpud6_pseudo_ops;
		static std::vector<FormatterString> pclmulqdq_pseudo_ops;
		static std::vector<FormatterString> vpclmulqdq_pseudo_ops;
		static std::vector<FormatterString> vpcomb_pseudo_ops;
		static std::vector<FormatterString> vpcomw_pseudo_ops;
		static std::vector<FormatterString> vpcomd_pseudo_ops;
		static std::vector<FormatterString> vpcomq_pseudo_ops;
		static std::vector<FormatterString> vpcomub_pseudo_ops;
		static std::vector<FormatterString> vpcomuw_pseudo_ops;
		static std::vector<FormatterString> vpcomud_pseudo_ops;
		static std::vector<FormatterString> vpcomuq_pseudo_ops;
		static std::vector<FormatterString> vpcmpb_pseudo_ops;
		static std::vector<FormatterString> vpcmpw_pseudo_ops;
		static std::vector<FormatterString> vpcmpd_pseudo_ops;
		static std::vector<FormatterString> vpcmpq_pseudo_ops;
		static std::vector<FormatterString> vpcmpub_pseudo_ops;
		static std::vector<FormatterString> vpcmpuw_pseudo_ops;
		static std::vector<FormatterString> vpcmpud_pseudo_ops;
		static std::vector<FormatterString> vpcmpuq_pseudo_ops;
	};
}
