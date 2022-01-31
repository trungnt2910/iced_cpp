#pragma once

#include "../Iced.Intel.Instruction.h"
#include "../Code.g.h"
#include "../DecoderOptions.g.h"
#include "../Static.h"
#include "../Internal/MemoryPool.h"
#include <vector>
#include <stdexcept>
#include <cassert>

namespace Iced::Intel { class Decoder; }

namespace Iced::Intel::DecoderInternal
{
	class OpCodeHandler : public Internal::Relocatable
	{
	public:
		bool HasModRM = false;
	protected:
		constexpr OpCodeHandler() = default;
		constexpr OpCodeHandler(bool hasModRM)
			: HasModRM(hasModRM)
		{
		}
	public:
		constexpr virtual void Decode(Decoder& decoder, Instruction& instruction) const = 0;
	};
	class OpCodeHandlerModRM : public OpCodeHandler
	{
	protected:
		constexpr OpCodeHandlerModRM()
			: OpCodeHandler(true)
		{
		}
	};
	class OpCodeHandler_Invalid final : public OpCodeHandlerModRM
	{
	public:
		constexpr OpCodeHandler_Invalid() = default;
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	inline static constexpr auto OpCodeHandler_Invalid_Instance = OpCodeHandler_Invalid();
	class OpCodeHandler_Invalid_NoModRM final : public OpCodeHandler
	{
	public:
		constexpr OpCodeHandler_Invalid_NoModRM() = default;
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	inline static constexpr auto OpCodeHandler_Invalid_NoModRM_Instance = OpCodeHandler_Invalid_NoModRM();
	class OpCodeHandler_Simple final : public OpCodeHandler
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_Simple(Code code)
			: code(code)
		{
		}
		constexpr void Decode(Decoder& decoder, Instruction& instruction) const override
		{
			instruction.SetCode(code);
		}
	};
	class OpCodeHandler_Simple_ModRM final : public OpCodeHandlerModRM
	{
	private:
		Code code = static_cast<Code>(0);
	public:
		constexpr OpCodeHandler_Simple_ModRM(Code code)
			: code(code)
		{
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_Group8x8 final : public OpCodeHandlerModRM
	{
	private:
		inline static constexpr std::size_t tableSize = 8;
		std::array<const OpCodeHandler*, tableSize> tableLow;
		std::array<const OpCodeHandler*, tableSize> tableHigh;
	public:
		constexpr OpCodeHandler_Group8x8(const std::vector<const OpCodeHandler*>& tableLow, const std::vector<const OpCodeHandler*>& tableHigh)
		{
			if (tableLow.size() != tableSize)
			{
				throw std::out_of_range("tableLow");
			}
			if (tableHigh.size() != tableSize)
			{
				throw std::out_of_range("tableHigh");
			}
			this->tableLow = std::array<const OpCodeHandler*, tableSize>();
			this->tableHigh = std::array<const OpCodeHandler*, tableSize>();
			std::copy(tableLow.begin(), tableLow.end(), this->tableLow.begin());
			std::copy(tableHigh.begin(), tableHigh.end(), this->tableHigh.begin());
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (auto& ptr : tableLow)
			{
				for (const auto& [oldPtr, newPtr] : info)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}

			for (auto& ptr : tableHigh)
			{
				for (const auto& [oldPtr, newPtr] : info)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_Group8x64 final : public OpCodeHandlerModRM
	{
	private:
		inline static constexpr std::size_t tableLowSize = 8;
		inline static constexpr std::size_t tableHighSize = 64;
		std::array<const OpCodeHandler*, tableLowSize> tableLow;
		std::array<const OpCodeHandler*, tableHighSize> tableHigh;
	public:
		constexpr OpCodeHandler_Group8x64(const std::vector<const OpCodeHandler*>& tableLow, const std::vector<const OpCodeHandler*>& tableHigh)
		{
			if (tableLow.size() != tableLowSize)
			{
				throw std::out_of_range("tableLow");
			}
			if (tableHigh.size() != tableHighSize)
			{
				throw std::out_of_range("tableHigh");
			}
			this->tableLow = std::array<const OpCodeHandler*, tableLowSize>();
			this->tableHigh = std::array<const OpCodeHandler*, tableHighSize>();
			std::copy(tableLow.begin(), tableLow.end(), this->tableLow.begin());
			std::copy(tableHigh.begin(), tableHigh.end(), this->tableHigh.begin());
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (auto& ptr : tableLow)
			{
				for (const auto& [oldPtr, newPtr] : info)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}

			for (auto& ptr : tableHigh)
			{
				for (const auto& [oldPtr, newPtr] : info)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_Group final : public OpCodeHandlerModRM
	{
	private:
		inline static constexpr std::size_t maxSize = 8;
		std::array<const OpCodeHandler*, maxSize> groupHandlers;
	public:
		constexpr OpCodeHandler_Group(const std::vector<const OpCodeHandler*>& groupHandlers)
		{
			if (groupHandlers.size() > maxSize)
			{
				throw std::out_of_range("bug. Please increase maxSize");
			}
			std::copy(groupHandlers.begin(), groupHandlers.end(), this->groupHandlers.begin());
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (auto& ptr : groupHandlers)
			{
				for (const auto& [oldPtr, newPtr] : info)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_AnotherTable final : public OpCodeHandler
	{
	private:
		inline static constexpr std::size_t maxSize = 256;
		std::array<const OpCodeHandler*, maxSize> otherTable;
		std::size_t otherTableSize;
	public:
		constexpr OpCodeHandler_AnotherTable(const std::vector<const OpCodeHandler*>& otherTable)
			: otherTableSize(otherTable.size())
		{
			if (otherTable.size() > maxSize)
			{
				throw std::out_of_range("bug. Please increase maxSize");
			}
			std::copy(otherTable.begin(), otherTable.end(), this->otherTable.begin());
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (std::size_t i = 0; i < otherTableSize; ++i)
			{
				auto& ptr = otherTable[i];
				for (const auto& [oldPtr, newPtr] : info)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_MandatoryPrefix2 final : public OpCodeHandlerModRM
	{
	private:
		inline static constexpr std::size_t maxSize = 4;
		std::array<const OpCodeHandler*, maxSize> handlers;
	public:
		constexpr OpCodeHandler_MandatoryPrefix2(const OpCodeHandler* handler) 
			: OpCodeHandler_MandatoryPrefix2(
				handler, 
				&OpCodeHandler_Invalid_Instance,
				&OpCodeHandler_Invalid_Instance,
				&OpCodeHandler_Invalid_Instance)
		{
		}
		constexpr OpCodeHandler_MandatoryPrefix2(
			const OpCodeHandler* handler, 
			const OpCodeHandler* handler66, 
			const OpCodeHandler* handlerF3, 
			const OpCodeHandler* handlerF2)
		{
			Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
			handlers = 
			{ 
				(handler != nullptr) ? handler : throw std::invalid_argument("handler"), 
				(handler66 != nullptr) ? handler66 : throw std::invalid_argument("handler66"), 
				(handlerF3 != nullptr) ? handlerF3 : throw std::invalid_argument("handlerF3"), 
				(handlerF2 != nullptr) ? handlerF2 : throw std::invalid_argument("handlerF2") 
			};
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handler) != nullptr);
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handler66) != nullptr);
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handlerF3) != nullptr);
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handlerF2) != nullptr);
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (auto& ptr : handlers)
			{
				for (const auto& [oldPtr, newPtr] : info)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_MandatoryPrefix2_NoModRM final : public OpCodeHandler
	{
	private:
		inline static constexpr std::size_t maxSize = 4;
		std::array<const OpCodeHandler*, maxSize> handlers;
	public:
		constexpr OpCodeHandler_MandatoryPrefix2_NoModRM(
			const OpCodeHandler* handler, 
			const OpCodeHandler* handler66, 
			const OpCodeHandler* handlerF3, 
			const OpCodeHandler* handlerF2)
		{
			Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::None) == 0 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::P66) == 1 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF3) == 2 ? 0 : -1);
			Static::Assert(static_cast<std::int32_t>(MandatoryPrefixByte::PF2) == 3 ? 0 : -1);
			handlers = 
			{ 
				(handler != nullptr) ? handler : throw std::invalid_argument("handler"), 
				(handler66 != nullptr) ? handler66 : throw std::invalid_argument("handler66"), 
				(handlerF3 != nullptr) ? handlerF3 : throw std::invalid_argument("handlerF3"), 
				(handlerF2 != nullptr) ? handlerF2 : throw std::invalid_argument("handlerF2")
			};
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handler) != nullptr);
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handler66) != nullptr);
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handlerF3) != nullptr);
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handlerF2) != nullptr);
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (auto& ptr : handlers)
			{
				for (const auto& [oldPtr, newPtr] : info)
				{
					if (ptr == oldPtr)
					{
						ptr = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_W final : public OpCodeHandlerModRM
	{
	private:
		const OpCodeHandler* handlerW0;
		const OpCodeHandler* handlerW1;
	public:
		constexpr OpCodeHandler_W(
			const OpCodeHandler* handlerW0, 
			const OpCodeHandler* handlerW1)
		{
			this->handlerW0 = (handlerW0 != nullptr) ? handlerW0 : throw std::invalid_argument("handlerW0");
			this->handlerW1 = (handlerW1 != nullptr) ? handlerW1 : throw std::invalid_argument("handlerW1");
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handlerW0) != nullptr);
			assert(dynamic_cast<const OpCodeHandlerModRM*>(handlerW1) != nullptr);
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (const auto& [oldPtr, newPtr] : info)
			{
				if (handlerW0 == oldPtr)
				{
					handlerW0 = dynamic_cast<const OpCodeHandler*>(newPtr);
				}

				if (handlerW1 == oldPtr)
				{
					handlerW1 = dynamic_cast<const OpCodeHandler*>(newPtr);
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_Bitness final : public OpCodeHandler
	{
	private:
		const OpCodeHandler* handler1632;
		const OpCodeHandler* handler64;
	public:
		constexpr OpCodeHandler_Bitness(
			const OpCodeHandler* handler1632,
			const OpCodeHandler* handler64)
			: handler1632(handler1632), handler64(handler64)
		{
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (const auto& [oldPtr, newPtr] : info)
			{
				if (handler1632 == oldPtr)
				{
					handler1632 = dynamic_cast<const OpCodeHandler*>(newPtr);
				}

				if (handler64 == oldPtr)
				{
					handler64 = dynamic_cast<const OpCodeHandler*>(newPtr);
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_Bitness_DontReadModRM final : public OpCodeHandlerModRM
	{
	private:
		const OpCodeHandler* handler1632;
		const OpCodeHandler* handler64;
	public:
		constexpr OpCodeHandler_Bitness_DontReadModRM(
			const OpCodeHandler* handler1632,
			const OpCodeHandler* handler64)
			: handler1632(handler1632), handler64(handler64)
		{
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (const auto& [oldPtr, newPtr] : info)
			{
				if (handler1632 == oldPtr)
				{
					handler1632 = dynamic_cast<const OpCodeHandler*>(newPtr);
				}

				if (handler64 == oldPtr)
				{
					handler64 = dynamic_cast<const OpCodeHandler*>(newPtr);
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_RM final : public OpCodeHandlerModRM
	{
	private:
		const OpCodeHandler* reg;
		const OpCodeHandler* mem;
	public:
		constexpr OpCodeHandler_RM(const OpCodeHandler* reg, const OpCodeHandler* mem)
		{
			this->reg = (reg != nullptr) ? reg : throw std::invalid_argument("reg");
			this->mem = (mem != nullptr) ? mem : throw std::invalid_argument("mem");
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (const auto& [oldPtr, newPtr] : info)
			{
				if (reg == oldPtr)
				{
					reg = dynamic_cast<const OpCodeHandler*>(newPtr);
				}

				if (mem == oldPtr)
				{
					mem = dynamic_cast<const OpCodeHandler*>(newPtr);
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class HandlerOptions : Internal::Relocatable
	{
	public:
		const OpCodeHandler* handler = nullptr;
		DecoderOptions options = static_cast<DecoderOptions>(0);
		constexpr HandlerOptions(const OpCodeHandler* handler, DecoderOptions options)
			: handler(handler), options(options)
		{
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (const auto& [oldPtr, newPtr] : info)
			{
				if (handler == oldPtr)
				{
					handler = dynamic_cast<const OpCodeHandler*>(newPtr);
				}
			}
		}
		constexpr HandlerOptions() = default;
	};
	class OpCodeHandler_Options1632 final : public OpCodeHandler
	{
	private:
		const OpCodeHandler* defaultHandler;
		inline static constexpr std::size_t maxSize = 2;
		std::array<HandlerOptions, maxSize> infos;
		std::size_t infoSize = 0;
		DecoderOptions infoOptions = static_cast<DecoderOptions>(0);
	public:
		constexpr OpCodeHandler_Options1632(
			const OpCodeHandler* defaultHandler, 
			const OpCodeHandler* handler1, 
			DecoderOptions options1)
		{
			this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
			infos = { HandlerOptions(handler1, options1) };
			infoSize = 1;
			infoOptions = options1;
		}

		constexpr OpCodeHandler_Options1632(
			const OpCodeHandler* defaultHandler, 
			const OpCodeHandler* handler1, 
			DecoderOptions options1, 
			const OpCodeHandler* handler2, 
			DecoderOptions options2)
		{
			this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
			infos = 
			{ 
				HandlerOptions((handler1 != nullptr) ? handler1 : throw std::invalid_argument("handler1"), options1),
				HandlerOptions((handler2 != nullptr) ? handler2 : throw std::invalid_argument("handler2"), options2) 
			};
			infoSize = 2;
			infoOptions = options1 | options2;
		}
		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (const auto& [oldPtr, newPtr] : info)
			{
				if (defaultHandler == oldPtr)
				{
					defaultHandler = dynamic_cast<const OpCodeHandler*>(newPtr);
				}
				for (std::size_t i = 0; i < infoSize; ++i)
				{
					if (infos[i].handler == oldPtr)
					{
						infos[i].handler = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}
		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_Options final : public OpCodeHandler
	{
	private:
		const OpCodeHandler* defaultHandler;
		inline static constexpr std::size_t maxSize = 2;
		std::array<HandlerOptions, maxSize> infos;
		std::size_t infoSize = 0;
		DecoderOptions infoOptions = static_cast<DecoderOptions>(0);
	public:
		constexpr OpCodeHandler_Options(
			const OpCodeHandler* defaultHandler, 
			const OpCodeHandler* handler1, 
			DecoderOptions options1)
		{
			this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
			infos = { HandlerOptions(handler1, options1) };
			infoSize = 1;
			infoOptions = options1;
		}

		constexpr OpCodeHandler_Options(
			const OpCodeHandler* defaultHandler, 
			const OpCodeHandler* handler1, 
			DecoderOptions options1, 
			const OpCodeHandler* handler2, 
			DecoderOptions options2)
		{
			this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
			infos = 
			{ 
				HandlerOptions((handler1 != nullptr) ? handler1 : throw std::invalid_argument("handler1"), options1), 
				HandlerOptions((handler2 != nullptr) ? handler2 : throw std::invalid_argument("handler2"), options2) 
			};
			infoSize = 2;
			infoOptions = options1 | options2;
		}

		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (const auto& [oldPtr, newPtr] : info)
			{
				if (defaultHandler == oldPtr)
				{
					defaultHandler = dynamic_cast<const OpCodeHandler*>(newPtr);
				}
				for (std::size_t i = 0; i < infoSize; ++i)
				{
					if (infos[i].handler == oldPtr)
					{
						infos[i].handler = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}

		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
	class OpCodeHandler_Options_DontReadModRM final : public OpCodeHandlerModRM
	{
	private:
		const OpCodeHandler* defaultHandler;
		inline static constexpr std::size_t maxSize = 1;
		std::array<HandlerOptions, maxSize> infos;
		std::size_t infoSize = 0;
	public:
		constexpr OpCodeHandler_Options_DontReadModRM(
			const OpCodeHandler* defaultHandler, 
			const OpCodeHandler* handler1, 
			DecoderOptions options1)
		{
			this->defaultHandler = (defaultHandler != nullptr) ? defaultHandler : throw std::invalid_argument("defaultHandler");
			infos = { HandlerOptions(handler1, options1) };
			infoSize = 1;
		}

		constexpr void Relocate(const std::vector<std::pair<const Relocatable*, const Relocatable*>>& info) override
		{
			for (const auto& [oldPtr, newPtr] : info)
			{
				if (defaultHandler == oldPtr)
				{
					defaultHandler = dynamic_cast<const OpCodeHandler*>(newPtr);
				}
				for (std::size_t i = 0; i < infoSize; ++i)
				{
					if (infos[i].handler == oldPtr)
					{
						infos[i].handler = dynamic_cast<const OpCodeHandler*>(newPtr);
					}
				}
			}
		}

		inline void Decode(Decoder& decoder, Instruction& instruction) const override;
	};
}
