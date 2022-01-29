#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <array>   // std::array
#include <utility> // std::index_sequence

namespace Iced::Intel::Internal
{
	namespace
	{
		template <std::size_t N>
		constexpr auto substring_as_array(std::string_view str)
		{
			auto result = std::array<char, N>();
			std::copy_n(str.begin(), N, result.begin());
			return result;
		}


		template <typename T>
		constexpr auto type_name_array()
		{
#if defined(__clang__)
			constexpr auto prefix = std::string_view{ "[T = " };
			constexpr auto suffix = std::string_view{ "]" };
			constexpr auto function = std::string_view{ __PRETTY_FUNCTION__ };
#elif defined(__GNUC__)
			constexpr auto prefix = std::string_view{ "with T = " };
			constexpr auto suffix = std::string_view{ "]" };
			constexpr auto function = std::string_view{ __PRETTY_FUNCTION__ };
#elif defined(_MSC_VER)
			constexpr auto prefix = std::string_view{ "type_name_array<" };
			constexpr auto suffix = std::string_view{ ">(void)" };
			constexpr auto function = std::string_view{ __FUNCSIG__ };
#else
# error Unsupported compiler
#endif

			constexpr auto start = function.find(prefix) + prefix.size();
			constexpr auto end = function.rfind(suffix);

			static_assert(start < end);

			constexpr auto name = function.substr(start, (end - start));
			return substring_as_array<name.size()>(name);
		}

		template <typename T>
		struct type_name_holder {
			static inline constexpr auto value = type_name_array<T>();
		};
	}

	template <typename T>
	constexpr auto type_name() -> std::string_view
	{
		constexpr auto& value = type_name_holder<T>::value;
		return std::string_view{ value.data(), value.size() };
	}
}