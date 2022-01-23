#pragma once

#include <functional>

namespace Iced::Intel
{
	template<typename T>
	concept HasStdHash = requires(const T & t) { std::hash<T>()(t); };

	template <typename T>
	concept HasGetHashCode = requires(const T & t) { t.GetHashCode(); };

	template <HasStdHash T>
	constexpr int GetHashCode(const T& t) { return (int)std::hash<T>()(t); }

	template <HasGetHashCode T>
	constexpr int GetHashCode(T t) { return t.GetHashCode(); }

	template <HasGetHashCode T>
	struct std::hash<T>
	{
		constexpr std::size_t operator()(const T& t) const
		{
			return (std::size_t)t.GetHashCode();
		}
	};
}
