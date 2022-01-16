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

#include "FormatterConstants.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel
{

	std::vector<FormatterString> FormatterConstants::GetPseudoOps(PseudoOpsKind kind)
	{
		auto switchTempVar_0 = kind;

		//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
		//ORIGINAL LINE: return (switchTempVar_0 == PseudoOpsKind.cmpps) ? cmpps_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vcmpps) ? vcmpps_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.cmppd) ? cmppd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vcmppd) ? vcmppd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.cmpss) ? cmpss_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vcmpss) ? vcmpss_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.cmpsd) ? cmpsd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vcmpsd) ? vcmpsd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.pclmulqdq) ? pclmulqdq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpclmulqdq) ? vpclmulqdq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcomb) ? vpcomb_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcomw) ? vpcomw_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcomd) ? vpcomd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcomq) ? vpcomq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcomub) ? vpcomub_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcomuw) ? vpcomuw_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcomud) ? vpcomud_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcomuq) ? vpcomuq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpb) ? vpcmpb_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpw) ? vpcmpw_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpd) ? vpcmpd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpq) ? vpcmpq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpub) ? vpcmpub_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpuw) ? vpcmpuw_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpud) ? vpcmpud_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpuq) ? vpcmpuq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vcmpph) ? vcmpph_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vcmpsh) ? vcmpsh_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vcmpps8) ? vcmpps8_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vcmppd8) ? vcmppd8_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpd6) ? vpcmpd6_pseudo_ops : (switchTempVar_0 == PseudoOpsKind.vpcmpud6) ? vpcmpud6_pseudo_ops : throw new ArgumentOutOfRangeException(nameof(kind));
		return (switchTempVar_0 == PseudoOpsKind::cmpps) ? cmpps_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vcmpps) ? vcmpps_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::cmppd) ? cmppd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vcmppd) ? vcmppd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::cmpss) ? cmpss_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vcmpss) ? vcmpss_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::cmpsd) ? cmpsd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vcmpsd) ? vcmpsd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::pclmulqdq) ? pclmulqdq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpclmulqdq) ? vpclmulqdq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcomb) ? vpcomb_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcomw) ? vpcomw_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcomd) ? vpcomd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcomq) ? vpcomq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcomub) ? vpcomub_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcomuw) ? vpcomuw_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcomud) ? vpcomud_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcomuq) ? vpcomuq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpb) ? vpcmpb_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpw) ? vpcmpw_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpd) ? vpcmpd_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpq) ? vpcmpq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpub) ? vpcmpub_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpuw) ? vpcmpuw_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpud) ? vpcmpud_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpuq) ? vpcmpuq_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vcmpph) ? vcmpph_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vcmpsh) ? vcmpsh_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vcmpps8) ? vcmpps8_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vcmppd8) ? vcmppd8_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpd6) ? vpcmpd6_pseudo_ops : (switchTempVar_0 == PseudoOpsKind::vpcmpud6) ? vpcmpud6_pseudo_ops : throw ArgumentOutOfRangeException("kind");
	}

	FormatterConstants::StaticConstructor::StaticConstructor()
	{
		auto cc = { "eq", "lt", "le", "unord", "neq", "nlt", "nle", "ord", "eq_uq", "nge", "ngt", "false", "neq_oq", "ge", "gt", "true", "eq_os", "lt_oq", "le_oq", "unord_s", "neq_us", "nlt_uq", "nle_uq", "ord_s", "eq_us", "nge_uq", "ngt_uq", "false_os", "neq_os", "ge_oq", "gt_oq", "true_us" };
		cmpps_pseudo_ops = Create(cc, 8, "cmp", "ps");
		vcmpps_pseudo_ops = Create(cc, 32, "vcmp", "ps");
		cmppd_pseudo_ops = Create(cc, 8, "cmp", "pd");
		vcmppd_pseudo_ops = Create(cc, 32, "vcmp", "pd");
		cmpss_pseudo_ops = Create(cc, 8, "cmp", "ss");
		vcmpss_pseudo_ops = Create(cc, 32, "vcmp", "ss");
		cmpsd_pseudo_ops = Create(cc, 8, "cmp", "sd");
		vcmpsd_pseudo_ops = Create(cc, 32, "vcmp", "sd");
		vcmpph_pseudo_ops = Create(cc, 32, "vcmp", "ph");
		vcmpsh_pseudo_ops = Create(cc, 32, "vcmp", "sh");
		vcmpps8_pseudo_ops = Create(cc, 8, "vcmp", "ps");
		vcmppd8_pseudo_ops = Create(cc, 8, "vcmp", "pd");
		auto cc6 = { "eq", "lt", "le", "??", "neq", "nlt", "nle", "???" };
		vpcmpd6_pseudo_ops = Create(cc6, 8, "vpcmp", "d");
		vpcmpud6_pseudo_ops = Create(cc6, 8, "vpcmp", "ud");
		auto xopcc = { "lt", "le", "gt", "ge", "eq", "neq", "false", "true" };
		vpcomb_pseudo_ops = Create(xopcc, 8, "vpcom", "b");
		vpcomw_pseudo_ops = Create(xopcc, 8, "vpcom", "w");
		vpcomd_pseudo_ops = Create(xopcc, 8, "vpcom", "d");
		vpcomq_pseudo_ops = Create(xopcc, 8, "vpcom", "q");
		vpcomub_pseudo_ops = Create(xopcc, 8, "vpcom", "ub");
		vpcomuw_pseudo_ops = Create(xopcc, 8, "vpcom", "uw");
		vpcomud_pseudo_ops = Create(xopcc, 8, "vpcom", "ud");
		vpcomuq_pseudo_ops = Create(xopcc, 8, "vpcom", "uq");
		auto pcmpcc = { "eq", "lt", "le", "false", "neq", "nlt", "nle", "true" };
		vpcmpb_pseudo_ops = Create(pcmpcc, 8, "vpcmp", "b");
		vpcmpw_pseudo_ops = Create(pcmpcc, 8, "vpcmp", "w");
		vpcmpd_pseudo_ops = Create(pcmpcc, 8, "vpcmp", "d");
		vpcmpq_pseudo_ops = Create(pcmpcc, 8, "vpcmp", "q");
		vpcmpub_pseudo_ops = Create(pcmpcc, 8, "vpcmp", "ub");
		vpcmpuw_pseudo_ops = Create(pcmpcc, 8, "vpcmp", "uw");
		vpcmpud_pseudo_ops = Create(pcmpcc, 8, "vpcmp", "ud");
		vpcmpuq_pseudo_ops = Create(pcmpcc, 8, "vpcmp", "uq");
	}

	FormatterConstants::StaticConstructor FormatterConstants::staticConstructor;

	std::vector<FormatterString> FormatterConstants::Create(std::vector<std::string>& cc, std::int32_t size, const std::string& prefix, const std::string& suffix)
	{
		auto strings = std::vector<FormatterString>(size);
		for (std::int32_t i = 0; i < strings.size(); i++)
		{
			strings[i] = FormatterString(prefix + cc[i] + suffix);
		}
		return strings;
	}

	std::vector<FormatterString> FormatterConstants::cmpps_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vcmpps_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::cmppd_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vcmppd_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::cmpss_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vcmpss_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::cmpsd_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vcmpsd_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vcmpph_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vcmpsh_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vcmpps8_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vcmppd8_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpd6_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpud6_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::pclmulqdq_pseudo_ops = { FormatterString("pclmullqlqdq"), FormatterString("pclmulhqlqdq"), FormatterString("pclmullqhqdq"), FormatterString("pclmulhqhqdq") };
	std::vector<FormatterString> FormatterConstants::vpclmulqdq_pseudo_ops = { FormatterString("vpclmullqlqdq"), FormatterString("vpclmulhqlqdq"), FormatterString("vpclmullqhqdq"), FormatterString("vpclmulhqhqdq") };
	std::vector<FormatterString> FormatterConstants::vpcomb_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcomw_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcomd_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcomq_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcomub_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcomuw_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcomud_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcomuq_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpb_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpw_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpd_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpq_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpub_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpuw_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpud_pseudo_ops;
	std::vector<FormatterString> FormatterConstants::vpcmpuq_pseudo_ops;
}
