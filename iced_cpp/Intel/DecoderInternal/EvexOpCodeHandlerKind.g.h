/* 
SPDX-License-Identifier: MIT
Copyright (C) 2018-present iced project and contributors
 */

// ⚠️This file was generated by GENERATOR!🦹‍♂️

#pragma once

#if defined(DECODER) && !defined(NO_EVEX)
#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include "../ToString.h"
#include "../Internal/StringHelpers.h"
namespace Iced::Intel::DecoderInternal {
	enum class EvexOpCodeHandlerKind : std::uint8_t {
		Invalid ,
		Invalid2 ,
		Dup ,
		HandlerReference ,
		ArrayReference ,
		RM ,
		Group ,
		W ,
		MandatoryPrefix2 ,
		VectorLength ,
		VectorLength_er ,
		Ed_V_Ib ,
		Ev_VX ,
		Ev_VX_Ib ,
		Gv_W_er ,
		GvM_VX_Ib ,
		HkWIb_3 ,
		HkWIb_3b ,
		HWIb ,
		KkHW_3 ,
		KkHW_3b ,
		KkHWIb_sae_3 ,
		KkHWIb_sae_3b ,
		KkHWIb_3 ,
		KkHWIb_3b ,
		KkWIb_3 ,
		KkWIb_3b ,
		KP1HW ,
		KR ,
		MV ,
		V_H_Ev_er ,
		V_H_Ev_Ib ,
		VHM ,
		VHW_3 ,
		VHW_4 ,
		VHWIb ,
		VK ,
		Vk_VSIB ,
		VkEv_REXW_2 ,
		VkEv_REXW_3 ,
		VkHM ,
		VkHW_3 ,
		VkHW_3b ,
		VkHW_5 ,
		VkHW_er_4 ,
		VkHW_er_4b ,
		VkHWIb_3 ,
		VkHWIb_3b ,
		VkHWIb_5 ,
		VkHWIb_er_4 ,
		VkHWIb_er_4b ,
		VkM ,
		VkW_3 ,
		VkW_3b ,
		VkW_4 ,
		VkW_4b ,
		VkW_er_4 ,
		VkW_er_5 ,
		VkW_er_6 ,
		VkWIb_3 ,
		VkWIb_3b ,
		VkWIb_er ,
		VM ,
		VSIB_k1 ,
		VSIB_k1_VX ,
		VW ,
		VW_er ,
		VX_Ev ,
		WkHV ,
		WkV_3 ,
		WkV_4a ,
		WkV_4b ,
		WkVIb ,
		WkVIb_er ,
		WV ,
		VkHW_er_ur_3 ,
		VkHW_er_ur_3b ,
	};
	constexpr std::uint8_t operator+(const EvexOpCodeHandlerKind& a, const EvexOpCodeHandlerKind& b) { return ((std::uint8_t)a + (std::uint8_t)b); }
	constexpr std::uint8_t operator+(const EvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a + b); }
	constexpr std::uint8_t operator+(const std::uint8_t& a, const EvexOpCodeHandlerKind& b) { return (a + (std::uint8_t)b); }
	constexpr std::uint8_t operator-(const EvexOpCodeHandlerKind& a, const EvexOpCodeHandlerKind& b) { return ((std::uint8_t)a - (std::uint8_t)b); }
	constexpr std::uint8_t operator-(const EvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a - b); }
	constexpr std::uint8_t operator-(const std::uint8_t& a, const EvexOpCodeHandlerKind& b) { return (a - (std::uint8_t)b); }
	constexpr EvexOpCodeHandlerKind operator++(EvexOpCodeHandlerKind& a, int) { auto temp = a; a = EvexOpCodeHandlerKind(a + 1); return temp; }
	constexpr EvexOpCodeHandlerKind& operator++(EvexOpCodeHandlerKind& a) { return a = EvexOpCodeHandlerKind(a + 1); }
	constexpr EvexOpCodeHandlerKind operator--(EvexOpCodeHandlerKind& a, int) { auto temp = a; a = EvexOpCodeHandlerKind(a - 1); return temp; }
	constexpr EvexOpCodeHandlerKind& operator--(EvexOpCodeHandlerKind& a) { return a = EvexOpCodeHandlerKind(a - 1); }
	constexpr bool operator==(const EvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a == b); }
	constexpr bool operator==(const std::uint8_t& a, const EvexOpCodeHandlerKind& b) { return (a == (std::uint8_t)b); }
	constexpr bool operator>=(const EvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a >= b); }
	constexpr bool operator>=(const std::uint8_t& a, const EvexOpCodeHandlerKind& b) { return (a >= (std::uint8_t)b); }
	constexpr bool operator<=(const EvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a <= b); }
	constexpr bool operator<=(const std::uint8_t& a, const EvexOpCodeHandlerKind& b) { return (a <= (std::uint8_t)b); }
	constexpr bool operator>(const EvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a > b); }
	constexpr bool operator>(const std::uint8_t& a, const EvexOpCodeHandlerKind& b) { return (a > (std::uint8_t)b); }
	constexpr bool operator<(const EvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a < b); }
	constexpr bool operator<(const std::uint8_t& a, const EvexOpCodeHandlerKind& b) { return (a < (std::uint8_t)b); }
	constexpr bool operator!=(const EvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a != b); }
	constexpr bool operator!=(const std::uint8_t& a, const EvexOpCodeHandlerKind& b) { return (a != (std::uint8_t)b); }
}
template <>
constexpr std::string Iced::Intel::ToString(const Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind& e) {
	switch (e) {
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Invalid: return "Invalid";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Invalid2: return "Invalid2";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Dup: return "Dup";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::HandlerReference: return "HandlerReference";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::ArrayReference: return "ArrayReference";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::RM: return "RM";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Group: return "Group";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::W: return "W";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::MandatoryPrefix2: return "MandatoryPrefix2";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VectorLength: return "VectorLength";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VectorLength_er: return "VectorLength_er";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Ed_V_Ib: return "Ed_V_Ib";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Ev_VX: return "Ev_VX";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Ev_VX_Ib: return "Ev_VX_Ib";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Gv_W_er: return "Gv_W_er";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::GvM_VX_Ib: return "GvM_VX_Ib";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::HkWIb_3: return "HkWIb_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::HkWIb_3b: return "HkWIb_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::HWIb: return "HWIb";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KkHW_3: return "KkHW_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KkHW_3b: return "KkHW_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KkHWIb_sae_3: return "KkHWIb_sae_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KkHWIb_sae_3b: return "KkHWIb_sae_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KkHWIb_3: return "KkHWIb_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KkHWIb_3b: return "KkHWIb_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KkWIb_3: return "KkWIb_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KkWIb_3b: return "KkWIb_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KP1HW: return "KP1HW";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::KR: return "KR";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::MV: return "MV";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::V_H_Ev_er: return "V_H_Ev_er";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::V_H_Ev_Ib: return "V_H_Ev_Ib";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VHM: return "VHM";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VHW_3: return "VHW_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VHW_4: return "VHW_4";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VHWIb: return "VHWIb";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VK: return "VK";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::Vk_VSIB: return "Vk_VSIB";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkEv_REXW_2: return "VkEv_REXW_2";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkEv_REXW_3: return "VkEv_REXW_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHM: return "VkHM";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHW_3: return "VkHW_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHW_3b: return "VkHW_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHW_5: return "VkHW_5";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHW_er_4: return "VkHW_er_4";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHW_er_4b: return "VkHW_er_4b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHWIb_3: return "VkHWIb_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHWIb_3b: return "VkHWIb_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHWIb_5: return "VkHWIb_5";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHWIb_er_4: return "VkHWIb_er_4";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHWIb_er_4b: return "VkHWIb_er_4b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkM: return "VkM";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkW_3: return "VkW_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkW_3b: return "VkW_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkW_4: return "VkW_4";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkW_4b: return "VkW_4b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkW_er_4: return "VkW_er_4";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkW_er_5: return "VkW_er_5";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkW_er_6: return "VkW_er_6";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkWIb_3: return "VkWIb_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkWIb_3b: return "VkWIb_3b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkWIb_er: return "VkWIb_er";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VM: return "VM";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VSIB_k1: return "VSIB_k1";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VSIB_k1_VX: return "VSIB_k1_VX";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VW: return "VW";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VW_er: return "VW_er";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VX_Ev: return "VX_Ev";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::WkHV: return "WkHV";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::WkV_3: return "WkV_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::WkV_4a: return "WkV_4a";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::WkV_4b: return "WkV_4b";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::WkVIb: return "WkVIb";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::WkVIb_er: return "WkVIb_er";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::WV: return "WV";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHW_er_ur_3: return "VkHW_er_ur_3";
		case Iced::Intel::DecoderInternal::EvexOpCodeHandlerKind::VkHW_er_ur_3b: return "VkHW_er_ur_3b";
		default: return Internal::StringHelpers::ToDec((std::uint8_t)e);
	}
}
#endif
