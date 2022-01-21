#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <type_traits>

#include <csharp/classes.h>

namespace Iced::Intel
{
	template<typename T>
	concept HasToString = requires(const T & t) { t.ToString(); };

	template<typename T>
	concept Hasto_string = requires(const T & t) { ::to_string(t); };

	template<typename T>
	concept HasIter = requires(const T & t)
	{
		{ t.begin() } -> std::same_as<typename T::const_iterator>;
		{ t.end() } -> std::same_as<typename T::const_iterator>;
	};

	template<typename T>
	concept HasCharIter = requires(const T & t)
	{
		requires HasIter<T>;
		requires std::same_as<typename T::const_reference, const char&>;
	};

	template<typename T>
	concept Enum = requires(const T & t)
	{
		requires std::is_enum_v<T>;
	};

	template <HasToString T>
	constexpr std::string ToString(const T& t) { return t.ToString(); }

	// To-Do: Remove this template.
	template <Hasto_string T>
	inline std::string ToString(const T& t) { return to_string(t); }

	template <HasCharIter T>
	constexpr std::string ToString(const T& t)
	{
		std::string s;
		std::copy(t.begin(), t.end(), std::back_inserter(s));
		return s;
	}
}