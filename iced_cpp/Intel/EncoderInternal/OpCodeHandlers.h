// SPDX-License-Identifier: MIT
// Copyright (C) 2018-present iced project and contributors

#pragma once

#include "EncoderOpCodeHandler.h"
#include "EncoderData.g.h"
#include "../Iced.Intel.IcedConstants.h"
#include "Enums.h"
#include "../EncodingKind.g.h"
#include "../Code.g.h"

#include <array>
#include <tuple>
#include <type_traits>
#include <variant>

namespace Iced::Intel::EncoderInternal
{
	class OpCodeHandlers;

	class OpCodeHandlerInfo
	{
	public:
		Code code;
		EncFlags1 encFlags1;
		EncFlags2 encFlags2;
		EncFlags3 encFlags3;
		constexpr OpCodeHandlerInfo() = default;
		constexpr OpCodeHandlerInfo(Code c, EncFlags1 e1, EncFlags2 e2, EncFlags3 e3) : code(c), encFlags1(e1), encFlags2(e2), encFlags3(e3)
		{
		}
	private:
		friend class OpCodeHandlers;
		static consteval std::array<OpCodeHandlerInfo, IcedConstants::CodeEnumCount> ConstructInfos()
		{
			auto result = std::array<OpCodeHandlerInfo, IcedConstants::CodeEnumCount>();
			for (std::size_t i = 0; i < result.size(); ++i)
			{
				std::construct_at<OpCodeHandlerInfo>(&result[i], (Code)i, (EncFlags1)EncoderData::EncFlags1[i], (EncFlags2)EncoderData::EncFlags2[i], (EncFlags3)EncoderData::EncFlags3[i]);
			}
			return result;
		}
	};

	template <OpCodeHandlerInfo... info>
	class OpCodeHandlerValues;

	template <OpCodeHandlerInfo info>
	class OpCodeHandlerFactory
	{
		friend class OpCodeHandlers;
		template <OpCodeHandlerInfo... info>
		friend class OpCodeHandlerValues;

		inline static constexpr Code code = info.code;
		inline static constexpr EncFlags1 encFlags1 = info.encFlags1;
		inline static constexpr EncFlags2 encFlags2 = info.encFlags2;
		inline static constexpr EncFlags3 encFlags3 = info.encFlags3;
		inline static constexpr EncodingKind kind = (EncodingKind)(((std::uint32_t)encFlags3 >> (std::uint32_t)EncFlags3::EncodingShift) & (std::uint32_t)EncFlags3::EncodingMask);

		template <EncodingKind k = kind, Code c = code>
		static constexpr std::enable_if<k == EncodingKind::Legacy && c == Code::INVALID, InvalidHandler>::type GetHandler()
		{
			return InvalidHandler();
		}

		template <EncodingKind k = kind, Code c = code>
		static constexpr std::enable_if<k == EncodingKind::Legacy && c != Code::INVALID && c <= Code::DeclareQword, DeclareDataHandler>::type GetHandler()
		{
			return DeclareDataHandler(c);
		}

		template <EncodingKind k = kind, Code c = code>
		static constexpr std::enable_if<(k == EncodingKind::Legacy && c != Code::INVALID && c > Code::DeclareQword), LegacyHandler>::type GetHandler()
		{
			return LegacyHandler(encFlags1, encFlags2, encFlags3);
		}

		template <EncodingKind k = kind>
		static constexpr std::enable_if<k == EncodingKind::VEX, VexHandler>::type GetHandler()
		{
			return VexHandler(encFlags1, encFlags2, encFlags3);
		}

		template <EncodingKind k = kind>
		static constexpr std::enable_if<k == EncodingKind::EVEX, EvexHandler>::type GetHandler()
		{
			return EvexHandler(encFlags1, encFlags2, encFlags3);
		}

		template <EncodingKind k = kind>
		static constexpr std::enable_if<k == EncodingKind::XOP, XopHandler>::type GetHandler()
		{
			return XopHandler(encFlags1, encFlags2, encFlags3);
		}

		template <EncodingKind k = kind>
		static constexpr std::enable_if<k == EncodingKind::D3NOW, D3nowHandler>::type GetHandler()
		{
			return D3nowHandler(encFlags2, encFlags3);
		}

		template <EncodingKind k = kind>
		static constexpr std::enable_if<k == EncodingKind::MVEX, MvexHandler>::type GetHandler()
		{
			return MvexHandler(encFlags1, encFlags2, encFlags3);
		}
	};

	using OpCodeHandlerVariant = std::variant<
		InvalidHandler,
		DeclareDataHandler,
		LegacyHandler,
		VexHandler,
		EvexHandler,
		XopHandler,
		D3nowHandler,
		MvexHandler>;

	template <OpCodeHandlerInfo... info>
	class OpCodeHandlerValues
	{
		friend class OpCodeHandlers;
		inline static constexpr std::array Value = std::to_array<OpCodeHandlerVariant>({ (OpCodeHandlerVariant)OpCodeHandlerFactory<info>::GetHandler()... });
	};

	template <typename X, auto arr, template <X...> typename Target,
		typename Sequence = decltype(std::make_index_sequence<arr.size()>())> struct ArrayToPack;

	template <typename X, auto arr, template <X...> typename Target, std::size_t... I>
	struct ArrayToPack<X, arr, Target, std::index_sequence<I...>> {
		using Type = Target<arr[I]...>;
	};

	constexpr const OpCodeHandler* cast(const OpCodeHandlerVariant& v)
	{
		return std::visit([](const OpCodeHandler& o) { return &o; }, v);
	}

	constexpr decltype(auto) GetPointers(const std::array<OpCodeHandlerVariant, IcedConstants::CodeEnumCount>& a)
	{
		const auto GetPointersInternal = []
			<typename Tuple, std::size_t... I>
			(const Tuple & a, std::index_sequence<I...>) constexpr
		{
			return std::to_array<const OpCodeHandler*>({ (cast(std::get<I>(a)))... });
		};

		return GetPointersInternal(a, std::make_index_sequence<IcedConstants::CodeEnumCount>());
	}

	class OpCodeHandlers final
	{
	private:
		inline static constexpr std::array Data = ArrayToPack<OpCodeHandlerInfo, OpCodeHandlerInfo::ConstructInfos(), OpCodeHandlerValues>::Type::Value;
	public:
		inline static constexpr std::array<const OpCodeHandler*, IcedConstants::CodeEnumCount> Handlers = GetPointers(Data);
	};
}
