#pragma once

#include "RegisterExtensions.defs.h"
#include "RegisterInfo.h"
#include "IcedConstants.h"
#include "ThrowHelper.h"

#include <array>

namespace Iced::Intel
{
	namespace RegisterExtensions
	{
		namespace Internal
		{
			constexpr std::array<RegisterInfo, IcedConstants::RegisterEnumCount> GetRegisterInfos()
			{
				auto regInfos = std::array<RegisterInfo, IcedConstants::RegisterEnumCount>();
				regInfos[static_cast<std::int32_t>(Register::EIP)] = RegisterInfo(Register::EIP, Register::EIP, Register::RIP, 4);
				regInfos[static_cast<std::int32_t>(Register::RIP)] = RegisterInfo(Register::RIP, Register::EIP, Register::RIP, 8);
				// Using std::to_array results in an internal compiler error.
#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4996)
				constexpr std::uint8_t data[] = { static_cast<std::uint8_t>(Register::AL), static_cast<std::uint8_t>(Register::R15L), static_cast<std::uint8_t>(Register::RAX), 1, 0, static_cast<std::uint8_t>(Register::AX), static_cast<std::uint8_t>(Register::R15W), static_cast<std::uint8_t>(Register::RAX), 2, 0, static_cast<std::uint8_t>(Register::EAX), static_cast<std::uint8_t>(Register::R15D), static_cast<std::uint8_t>(Register::RAX), 4, 0, static_cast<std::uint8_t>(Register::RAX), static_cast<std::uint8_t>(Register::R15), static_cast<std::uint8_t>(Register::RAX), 8, 0, static_cast<std::uint8_t>(Register::ES), static_cast<std::uint8_t>(Register::GS), static_cast<std::uint8_t>(Register::ES), 2, 0, static_cast<std::uint8_t>(Register::XMM0), static_cast<std::uint8_t>(Register::XMM31), static_cast<std::uint8_t>(Register::ZMM0), 16, 0, static_cast<std::uint8_t>(Register::YMM0), static_cast<std::uint8_t>(Register::YMM31), static_cast<std::uint8_t>(Register::ZMM0), 32, 0, static_cast<std::uint8_t>(Register::ZMM0), static_cast<std::uint8_t>(Register::ZMM31), static_cast<std::uint8_t>(Register::ZMM0), 64, 0, static_cast<std::uint8_t>(Register::K0), static_cast<std::uint8_t>(Register::K7), static_cast<std::uint8_t>(Register::K0), 8, 0, static_cast<std::uint8_t>(Register::BND0), static_cast<std::uint8_t>(Register::BND3), static_cast<std::uint8_t>(Register::BND0), 16, 0, static_cast<std::uint8_t>(Register::CR0), static_cast<std::uint8_t>(Register::CR15), static_cast<std::uint8_t>(Register::CR0), 8, 0, static_cast<std::uint8_t>(Register::DR0), static_cast<std::uint8_t>(Register::DR15), static_cast<std::uint8_t>(Register::DR0), 8, 0, static_cast<std::uint8_t>(Register::ST0), static_cast<std::uint8_t>(Register::ST7), static_cast<std::uint8_t>(Register::ST0), 10, 0, static_cast<std::uint8_t>(Register::MM0), static_cast<std::uint8_t>(Register::MM7), static_cast<std::uint8_t>(Register::MM0), 8, 0, static_cast<std::uint8_t>(Register::TR0), static_cast<std::uint8_t>(Register::TR7), static_cast<std::uint8_t>(Register::TR0), 4, 0, static_cast<std::uint8_t>(Register::TMM0), static_cast<std::uint8_t>(Register::TMM7), static_cast<std::uint8_t>(Register::TMM0), 0, 4, static_cast<std::uint8_t>(Register::DontUse0), static_cast<std::uint8_t>(Register::DontUse0), static_cast<std::uint8_t>(Register::DontUse0), 0, 0, static_cast<std::uint8_t>(Register::DontUseFA), static_cast<std::uint8_t>(Register::DontUseFF), static_cast<std::uint8_t>(Register::DontUseFA), 0, 0 };
#pragma warning (pop)
#endif
				std::int32_t i;
				constexpr std::uint32_t data_size = sizeof(data) / sizeof(data[0]);
				for (i = 0; i < data_size; i += 5)
				{
					auto baseReg = static_cast<Register>(data[i]);
					auto reg = baseReg;
					auto regEnd = static_cast<Register>(data[i + 1]);
					auto fullReg = static_cast<Register>(data[i + 2]);
					std::int32_t size = data[i + 3] | (data[i + 4] << 8);
					while (reg <= regEnd)
					{
						regInfos[static_cast<std::int32_t>(reg)] = RegisterInfo(reg, baseReg, fullReg, size);
						reg++;
						fullReg++;
						if (reg == Register::AH)
						{
							fullReg = (Register)(fullReg - 4);
						}
					}
				}
				if (i != data_size)
				{
					throw std::runtime_error("invalid operation");
				}
				return regInfos;
				return std::array<RegisterInfo, IcedConstants::RegisterEnumCount>();
			}
		}

		constexpr inline std::array<RegisterInfo, IcedConstants::RegisterEnumCount> RegisterInfos = Internal::GetRegisterInfos();

		constexpr RegisterInfo GetInfo(Register register_)
		{
			const auto& infos = RegisterInfos;
			if (static_cast<std::uint32_t>(register_) >= static_cast<std::uint32_t>(infos.size()))
			{
				ThrowHelper::ThrowArgumentOutOfRangeException_register();
			}
			return infos[static_cast<std::int32_t>(register_)];
		}

		constexpr Register GetBaseRegister(Register register_)
		{
			return GetInfo(register_).GetBase();
		}

		constexpr std::int32_t GetNumber(Register register_)
		{
			return GetInfo(register_).GetNumber();
		}

		constexpr Register GetFullRegister(Register register_)
		{
			return GetInfo(register_).GetFullRegister();
		}

		constexpr Register GetFullRegister32(Register register_)
		{
			return GetInfo(register_).GetFullRegister32();
		}

		constexpr std::int32_t GetSize(Register register_)
		{
			return GetInfo(register_).GetSize();
		}

		constexpr bool IsSegmentRegister(Register register_)
		{
			return Register::ES <= register_ && register_ <= Register::GS;
		}

		constexpr bool IsGPR(Register register_)
		{
			return Register::AL <= register_ && register_ <= Register::R15;
		}

		constexpr bool IsGPR8(Register register_)
		{
			return Register::AL <= register_ && register_ <= Register::R15L;
		}

		constexpr bool IsGPR16(Register register_)
		{
			return Register::AX <= register_ && register_ <= Register::R15W;
		}

		constexpr bool IsGPR32(Register register_)
		{
			return Register::EAX <= register_ && register_ <= Register::R15D;
		}

		constexpr bool IsGPR64(Register register_)
		{
			return Register::RAX <= register_ && register_ <= Register::R15;
		}

		constexpr bool IsXMM(Register register_)
		{
			return Register::XMM0 <= register_ && register_ <= IcedConstants::XMM_last;
		}

		constexpr bool IsYMM(Register register_)
		{
			return Register::YMM0 <= register_ && register_ <= IcedConstants::YMM_last;
		}

		constexpr bool IsZMM(Register register_)
		{
			return Register::ZMM0 <= register_ && register_ <= IcedConstants::ZMM_last;
		}

		constexpr bool IsIP(Register register_)
		{
			return register_ == Register::EIP || register_ == Register::RIP;
		}

		constexpr bool IsK(Register register_)
		{
			return Register::K0 <= register_ && register_ <= Register::K7;
		}

		constexpr bool IsCR(Register register_)
		{
			return Register::CR0 <= register_ && register_ <= Register::CR15;
		}

		constexpr bool IsDR(Register register_)
		{
			return Register::DR0 <= register_ && register_ <= Register::DR15;
		}

		constexpr bool IsTR(Register register_)
		{
			return Register::TR0 <= register_ && register_ <= Register::TR7;
		}

		constexpr bool IsST(Register register_)
		{
			return Register::ST0 <= register_ && register_ <= Register::ST7;
		}

		constexpr bool IsBND(Register register_)
		{
			return Register::BND0 <= register_ && register_ <= Register::BND3;
		}

		constexpr bool IsMM(Register register_)
		{
			return Register::MM0 <= register_ && register_ <= Register::MM7;
		}

		constexpr bool IsTMM(Register register_)
		{
			return Register::TMM0 <= register_ && register_ <= IcedConstants::TMM_last;
		}

		constexpr bool IsVectorRegister(Register register_)
		{
			return Register::XMM0 <= register_ && register_ <= IcedConstants::VMM_last;
		}

	}
}
