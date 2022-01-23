/* 
SPDX-License-Identifier: MIT
Copyright (C) 2018-present iced project and contributors
 */

// ⚠️This file was generated by GENERATOR!🦹‍♂️

#pragma once

#if defined(DECODER) && defined(MVEX)
#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include "../ToString.h"
#include "../Internal/StringHelpers.h"
namespace Iced::Intel::DecoderInternal {
	enum class MvexOpCodeHandlerKind : std::uint8_t {
		Invalid ,
		Invalid2 ,
		Dup ,
		HandlerReference ,
		ArrayReference ,
		RM ,
		Group ,
		W ,
		MandatoryPrefix2 ,
		EH ,
		M ,
		MV ,
		VW ,
		HWIb ,
		VWIb ,
		VHW ,
		VHWIb ,
		VKW ,
		KHW ,
		KHWIb ,
		VSIB ,
		VSIB_V ,
		V_VSIB ,
	};
	constexpr std::uint8_t operator+(const MvexOpCodeHandlerKind& a, const MvexOpCodeHandlerKind& b) { return ((std::uint8_t)a + (std::uint8_t)b); }
	constexpr std::uint8_t operator+(const MvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a + b); }
	constexpr std::uint8_t operator+(const std::uint8_t& a, const MvexOpCodeHandlerKind& b) { return (a + (std::uint8_t)b); }
	constexpr std::uint8_t operator-(const MvexOpCodeHandlerKind& a, const MvexOpCodeHandlerKind& b) { return ((std::uint8_t)a - (std::uint8_t)b); }
	constexpr std::uint8_t operator-(const MvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a - b); }
	constexpr std::uint8_t operator-(const std::uint8_t& a, const MvexOpCodeHandlerKind& b) { return (a - (std::uint8_t)b); }
	constexpr MvexOpCodeHandlerKind operator++(MvexOpCodeHandlerKind& a, int) { auto temp = a; a = MvexOpCodeHandlerKind(a + 1); return temp; }
	constexpr MvexOpCodeHandlerKind& operator++(MvexOpCodeHandlerKind& a) { return a = MvexOpCodeHandlerKind(a + 1); }
	constexpr MvexOpCodeHandlerKind operator--(MvexOpCodeHandlerKind& a, int) { auto temp = a; a = MvexOpCodeHandlerKind(a - 1); return temp; }
	constexpr MvexOpCodeHandlerKind& operator--(MvexOpCodeHandlerKind& a) { return a = MvexOpCodeHandlerKind(a - 1); }
	constexpr bool operator==(const MvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a == b); }
	constexpr bool operator==(const std::uint8_t& a, const MvexOpCodeHandlerKind& b) { return (a == (std::uint8_t)b); }
	constexpr bool operator>=(const MvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a >= b); }
	constexpr bool operator>=(const std::uint8_t& a, const MvexOpCodeHandlerKind& b) { return (a >= (std::uint8_t)b); }
	constexpr bool operator<=(const MvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a <= b); }
	constexpr bool operator<=(const std::uint8_t& a, const MvexOpCodeHandlerKind& b) { return (a <= (std::uint8_t)b); }
	constexpr bool operator>(const MvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a > b); }
	constexpr bool operator>(const std::uint8_t& a, const MvexOpCodeHandlerKind& b) { return (a > (std::uint8_t)b); }
	constexpr bool operator<(const MvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a < b); }
	constexpr bool operator<(const std::uint8_t& a, const MvexOpCodeHandlerKind& b) { return (a < (std::uint8_t)b); }
	constexpr bool operator!=(const MvexOpCodeHandlerKind& a, const std::uint8_t& b) { return ((std::uint8_t)a != b); }
	constexpr bool operator!=(const std::uint8_t& a, const MvexOpCodeHandlerKind& b) { return (a != (std::uint8_t)b); }
}
template <>
constexpr std::string Iced::Intel::ToString(const Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind& e) {
	switch (e) {
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::Invalid: return "Invalid";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::Invalid2: return "Invalid2";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::Dup: return "Dup";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::HandlerReference: return "HandlerReference";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::ArrayReference: return "ArrayReference";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::RM: return "RM";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::Group: return "Group";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::W: return "W";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::MandatoryPrefix2: return "MandatoryPrefix2";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::EH: return "EH";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::M: return "M";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::MV: return "MV";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::VW: return "VW";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::HWIb: return "HWIb";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::VWIb: return "VWIb";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::VHW: return "VHW";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::VHWIb: return "VHWIb";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::VKW: return "VKW";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::KHW: return "KHW";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::KHWIb: return "KHWIb";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::VSIB: return "VSIB";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::VSIB_V: return "VSIB_V";
		case Iced::Intel::DecoderInternal::MvexOpCodeHandlerKind::V_VSIB: return "V_VSIB";
		default: return Internal::StringHelpers::ToDec((std::uint8_t)e);
	}
}
#endif
