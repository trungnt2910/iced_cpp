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

#include "MemorySizes.h"
#include "../Iced.Intel.IcedConstants.h"
#include "../../Array2.h"

using namespace Iced::Intel::FormatterInternal;

namespace Iced::Intel::MasmFormatterInternal
{

	std::vector<FormatterString> MemorySizes::dword_ptr;
	std::vector<FormatterString> MemorySizes::qword_ptr;
	std::vector<FormatterString> MemorySizes::mmword_ptr;
	std::vector<FormatterString> MemorySizes::xmmword_ptr;
	std::vector<FormatterString> MemorySizes::oword_ptr;

	MemorySizes::Info::Info(bool isBroadcast, std::int32_t size, const std::vector<FormatterString>& keywords)
	{
		this->isBroadcast = isBroadcast;
		this->size = size;
		this->keywords = keywords;
	}

	std::vector<MemorySizes::Info> MemorySizes::AllMemorySizes = GetMemorySizes();

	std::vector<MemorySizes::Info> MemorySizes::GetMemorySizes()
	{
		// GENERATOR-BEGIN: ConstData
		// ⚠️This was generated by GENERATOR!🦹‍♂️
		constexpr std::int32_t SizeKindShift = 5;
		constexpr std::int32_t MemoryKeywordsMask = 31;
		auto byte = FormatterString("byte");
		auto ptr = FormatterString("ptr");
		auto byte_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ byte, ptr };
		auto dword = FormatterString("dword");
		auto bcst = FormatterString("bcst");
		auto dword_bcst = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ dword, bcst };
		auto dword_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ dword, ptr };
		auto fpuenv14 = FormatterString("fpuenv14");
		auto fpuenv14_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ fpuenv14, ptr };
		auto fpuenv28 = FormatterString("fpuenv28");
		auto fpuenv28_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ fpuenv28, ptr };
		auto fpustate108 = FormatterString("fpustate108");
		auto fpustate108_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ fpustate108, ptr };
		auto fpustate94 = FormatterString("fpustate94");
		auto fpustate94_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ fpustate94, ptr };
		auto fword = FormatterString("fword");
		auto fword_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ fword, ptr };
		auto oword = FormatterString("oword");
		auto oword_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ oword, ptr };
		auto qword = FormatterString("qword");
		auto qword_bcst = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ qword, bcst };
		auto qword_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ qword, ptr };
		auto tbyte = FormatterString("tbyte");
		auto tbyte_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ tbyte, ptr };
		auto word = FormatterString("word");
		auto word_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ word, ptr };
		auto xmmword = FormatterString("xmmword");
		auto xmmword_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ xmmword, ptr };
		auto ymmword = FormatterString("ymmword");
		auto ymmword_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ ymmword, ptr };
		auto zmmword = FormatterString("zmmword");
		auto zmmword_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ zmmword, ptr };
		auto mem384 = FormatterString("mem384");
		auto mem384_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ mem384, ptr };
		auto word_bcst = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ word, bcst };
		auto mmword = FormatterString("mmword");
		auto mmword_ptr = std::vector<Iced::Intel::FormatterInternal::FormatterString>{ mmword, ptr };
		auto sizes = std::vector<std::uint16_t>{ 0, 1, 2, 4, 6, 8, 10, 14, 16, 28, 32, 48, 64, 94, 108, 512 };
		// GENERATOR-END: ConstData
		MemorySizes::mmword_ptr = mmword_ptr;
		MemorySizes::dword_ptr = dword_ptr;
		MemorySizes::oword_ptr = oword_ptr;
		MemorySizes::qword_ptr = qword_ptr;
		MemorySizes::xmmword_ptr = xmmword_ptr;
		auto infos = std::vector<Info>(IcedConstants::MemorySizeEnumCount);
		std::vector<std::int32_t> data = { 0x0000, 0x0021, 0x004D, 0x0063, 0x00AB, 0x00AB, 0x010E, 0x014F, 0x0190, 0x0021, 0x004D, 0x0063, 0x00AB, 0x010E, 0x014F, 0x0190, 0x0063, 0x0088, 0x00CC, 0x004D, 0x0063, 0x00AB, 0x0063, 0x00AB, 0x00AB, 0x0109, 0x0088, 0x00C8, 0x004D, 0x0063, 0x00AB, 0x00CC, 0x010E, 0x004D, 0x00E4, 0x0125, 0x01A7, 0x01C6, 0x01E0, 0x01E0, 0x0000, 0x0000, 0x00CC, 0x0190, 0x0000, 0x00CC, 0x0171, 0x0190, 0x004D, 0x004D, 0x0063, 0x0063, 0x0063, 0x0063, 0x0063, 0x0063, 0x00AB, 0x00AB, 0x00AB, 0x00AB, 0x00AB, 0x00AB, 0x00AB, 0x00AB, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x010E, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x014F, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0052, 0x0062, 0x0062, 0x0052, 0x0062, 0x0052, 0x0052, 0x0062, 0x0062, 0x00AA, 0x00AA, 0x00AA, 0x0052, 0x0062, 0x00AA, 0x0062, 0x00AA, 0x00AA, 0x0062, 0x0062, 0x0052, 0x0052, 0x0062, 0x0062, 0x00AA, 0x00AA, 0x00AA, 0x0052, 0x0062, 0x00AA, 0x0062, 0x00AA, 0x00AA, 0x0062, 0x0062, 0x0052, 0x0052, 0x0062, 0x0062, 0x00AA, 0x00AA, 0x00AA, 0x0052, 0x0062, 0x00AA, 0x0062, 0x0062, 0x00AA, 0x00AA, 0x0062 };
		for (std::int32_t i = 0; i < infos.size(); i++)
		{
			auto d = data[i];
			auto switchTempVar_0 = (d & MemoryKeywordsMask);
			// GENERATOR-BEGIN: MemoryKeywordsSwitch
			// ⚠️This was generated by GENERATOR!🦹‍♂️
			// GENERATOR-END: MemoryKeywordsSwitch

	 //C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
	 //ORIGINAL LINE: var keywords = (switchTempVar_0 == 0x00) ? Array2.Empty<FormatterString>() : (switchTempVar_0 == 0x01) ? byte_ptr : (switchTempVar_0 == 0x02) ? dword_bcst : (switchTempVar_0 == 0x03) ? dword_ptr : (switchTempVar_0 == 0x04) ? fpuenv14_ptr : (switchTempVar_0 == 0x05) ? fpuenv28_ptr : (switchTempVar_0 == 0x06) ? fpustate108_ptr : (switchTempVar_0 == 0x07) ? fpustate94_ptr : (switchTempVar_0 == 0x08) ? fword_ptr : (switchTempVar_0 == 0x09) ? oword_ptr : (switchTempVar_0 == 0x0A) ? qword_bcst : (switchTempVar_0 == 0x0B) ? qword_ptr : (switchTempVar_0 == 0x0C) ? tbyte_ptr : (switchTempVar_0 == 0x0D) ? word_ptr : (switchTempVar_0 == 0x0E) ? xmmword_ptr : (switchTempVar_0 == 0x0F) ? ymmword_ptr : (switchTempVar_0 == 0x10) ? zmmword_ptr : (switchTempVar_0 == 0x11) ? mem384_ptr : (switchTempVar_0 == 0x12) ? word_bcst : throw new InvalidOperationException();
			auto keywords = (switchTempVar_0 == 0x00) ? System::Array2::Empty<FormatterString>() : (switchTempVar_0 == 0x01) ? byte_ptr : (switchTempVar_0 == 0x02) ? dword_bcst : (switchTempVar_0 == 0x03) ? dword_ptr : (switchTempVar_0 == 0x04) ? fpuenv14_ptr : (switchTempVar_0 == 0x05) ? fpuenv28_ptr : (switchTempVar_0 == 0x06) ? fpustate108_ptr : (switchTempVar_0 == 0x07) ? fpustate94_ptr : (switchTempVar_0 == 0x08) ? fword_ptr : (switchTempVar_0 == 0x09) ? oword_ptr : (switchTempVar_0 == 0x0A) ? qword_bcst : (switchTempVar_0 == 0x0B) ? qword_ptr : (switchTempVar_0 == 0x0C) ? tbyte_ptr : (switchTempVar_0 == 0x0D) ? word_ptr : (switchTempVar_0 == 0x0E) ? xmmword_ptr : (switchTempVar_0 == 0x0F) ? ymmword_ptr : (switchTempVar_0 == 0x10) ? zmmword_ptr : (switchTempVar_0 == 0x11) ? mem384_ptr : (switchTempVar_0 == 0x12) ? word_bcst : throw InvalidOperationException();
			infos[i] = Info(i >= static_cast<std::int32_t>(IcedConstants::FirstBroadcastMemorySize), sizes[d >> SizeKindShift], keywords);
		}
		return infos;
	}
}
