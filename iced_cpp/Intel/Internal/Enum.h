#pragma once

#include <climits>
#include <type_traits>

namespace
{
	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T& enum_or_eq(T& t1, const T& t2)
	{
		return t1 = (T)((std::underlying_type_t<T>)t1 | (std::underlying_type_t<T>)t2);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T& enum_and_eq(T& t1, const T& t2)
	{
		return t1 = (T)((std::underlying_type_t<T>)t1 & (std::underlying_type_t<T>)t2);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T& enum_xor_eq(T& t1, const T& t2)
	{
		return t1 = (T)((std::underlying_type_t<T>)t1 ^ (std::underlying_type_t<T>)t2);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T& enum_add_eq(T& t1, const T& t2)
	{
		return t1 = (T)((std::underlying_type_t<T>)t1 + (std::underlying_type_t<T>)t2);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T& enum_sub_eq(T& t1, const T& t2)
	{
		return t1 = (T)((std::underlying_type_t<T>)t1 - (std::underlying_type_t<T>)t2);
	}


	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T enum_or(const T& t1, const T& t2)
	{
		return (T)((std::underlying_type_t<T>)t1 | (std::underlying_type_t<T>)t2);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T enum_and(const T& t1, const T& t2)
	{
		return (T)((std::underlying_type_t<T>)t1 & (std::underlying_type_t<T>)t2);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T enum_xor(const T& t1, const T& t2)
	{
		return (T)((std::underlying_type_t<T>)t1 ^ (std::underlying_type_t<T>)t2);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T enum_not(const T& t1)
	{
		return (T)(~(std::underlying_type_t<T>)t1);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T enum_add(const T& t1, const T& t2)
	{
		return (T)((std::underlying_type_t<T>)t1 + (std::underlying_type_t<T>)t2);
	}

	template<typename T,
		typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
		inline constexpr T enum_sub(const T& t1, const T& t2)
	{
		return (T)((std::underlying_type_t<T>)t1 - (std::underlying_type_t<T>)t2);
	}
}

// Flag enums.
#define ICED_DEFINE_AND(enum_name) inline static constexpr enum_name operator&(const enum_name& e1, const enum_name& e2) { return enum_and(e1, e2); }
#define ICED_DEFINE_OR(enum_name) inline static constexpr enum_name operator|(const enum_name& e1, const enum_name& e2) { return enum_or(e1, e2); }
#define ICED_DEFINE_XOR(enum_name) inline static constexpr enum_name operator^(const enum_name& e1, const enum_name& e2) { return enum_xor(e1, e2); }
#define ICED_DEFINE_AND_EQ(enum_name) inline static constexpr enum_name& operator&=(enum_name& e1, const enum_name& e2) { return enum_and_eq(e1, e2); }
#define ICED_DEFINE_OR_EQ(enum_name) inline static constexpr enum_name& operator|=(enum_name& e1, const enum_name& e2) { return enum_or_eq(e1, e2); }
#define ICED_DEFINE_XOR_EQ(enum_name) inline static constexpr enum_name& operator^=(enum_name& e1, const enum_name& e2) { return enum_xor_eq(e1, e2); }
#define ICED_DEFINE_NOT(enum_name) inline static constexpr enum_name operator~(const enum_name& e1) { return enum_not(e1); }

// Enums in C# can compare with 0. Define these functions to allow the same in C++.
#define ICED_DEFINE_EQ(enum_name) inline static constexpr bool operator==(const enum_name& e1, const std::underlying_type_t<enum_name>& i) { return static_cast<std::underlying_type_t<enum_name>>(e1) == i; }
#define ICED_DEFINE_NEQ(enum_name) inline static constexpr bool operator!=(const enum_name& e1, const std::underlying_type_t<enum_name>& i) { return static_cast<std::underlying_type_t<enum_name>>(e1) != i; }

// Some code also uses addition and subtraction.
#define ICED_DEFINE_ADD(enum_name) inline static constexpr std::underlying_type_t<enum_name> operator+(const enum_name& e1, const enum_name& e2) { return static_cast<std::underlying_type_t<enum_name>>(enum_add(e1, e2)); }
#define ICED_DEFINE_ADD1(enum_name) inline static constexpr std::underlying_type_t<enum_name> operator+(const enum_name& e1, const std::underlying_type_t<enum_name>& e2) { return static_cast<std::underlying_type_t<enum_name>>(enum_add(e1, static_cast<enum_name>(e2))); }
#define ICED_DEFINE_ADD2(enum_name) inline static constexpr std::underlying_type_t<enum_name> operator+(const std::underlying_type_t<enum_name>& e1, const enum_name& e2) { return e2 + e1; }
#define ICED_DEFINE_SUB(enum_name) inline static constexpr std::underlying_type_t<enum_name> operator-(const enum_name& e1, const enum_name& e2) { return static_cast<std::underlying_type_t<enum_name>>(enum_sub(e1, e2)); }
#define ICED_DEFINE_SUB1(enum_name) inline static constexpr std::underlying_type_t<enum_name> operator-(const enum_name& e1, const std::underlying_type_t<enum_name>& e2) { return static_cast<std::underlying_type_t<enum_name>>(enum_sub(e1, static_cast<enum_name>(e2))); }
#define ICED_DEFINE_SUB2(enum_name) inline static constexpr std::underlying_type_t<enum_name> operator-(const std::underlying_type_t<enum_name>& e1, const enum_name& e2) { return e2 - e1; }
#define ICED_DEFINE_INC_PRE(enum_name) inline static constexpr enum_name& operator++(enum_name& e) { return enum_add_eq(e, static_cast<enum_name>(1)); }
#define ICED_DEFINE_INC_POST(enum_name) inline static constexpr enum_name operator++(enum_name& e, int) { auto temp = e; ++e; return temp; }
#define ICED_DEFINE_DEC_PRE(enum_name) inline static constexpr enum_name& operator--(enum_name& e) { return enum_sub_eq(e, static_cast<enum_name>(1)); }
#define ICED_DEFINE_DEC_POST(enum_name) inline static constexpr enum_name operator--(enum_name& e, int) { auto temp = e; --e; return temp; }


// For private nested enums.
#define ICED_DEFINE_AND_FRIEND(enum_name) friend inline static constexpr enum_name operator&(const enum_name& e1, const enum_name& e2) { return enum_and(e1, e2); }
#define ICED_DEFINE_OR_FRIEND(enum_name) friend inline static constexpr enum_name operator|(const enum_name& e1, const enum_name& e2) { return enum_or(e1, e2); }
#define ICED_DEFINE_XOR_FRIEND(enum_name) friend inline static constexpr enum_name operator^(const enum_name& e1, const enum_name& e2) { return enum_xor(e1, e2); }
#define ICED_DEFINE_AND_EQ_FRIEND(enum_name) friend inline static constexpr enum_name& operator&=(enum_name& e1, const enum_name& e2) { return enum_and_eq(e1, e2); }
#define ICED_DEFINE_OR_EQ_FRIEND(enum_name) friend inline static constexpr enum_name& operator|=(enum_name& e1, const enum_name& e2) { return enum_or_eq(e1, e2); }
#define ICED_DEFINE_XOR_EQ_FRIEND(enum_name) friend inline static constexpr enum_name& operator^=(enum_name& e1, const enum_name& e2) { return enum_xor_eq(e1, e2); }
#define ICED_DEFINE_NOT_FRIEND(enum_name) friend inline static constexpr enum_name operator~(const enum_name& e1) { return enum_not(e1); }

#define ICED_DEFINE_EQ_FRIEND(enum_name) friend inline static constexpr bool operator==(const enum_name& e1, const std::underlying_type_t<enum_name>& i) { return static_cast<std::underlying_type_t<enum_name>>(e1) == i; }
#define ICED_DEFINE_NEQ_FRIEND(enum_name) friend inline static constexpr bool operator!=(const enum_name& e1, const std::underlying_type_t<enum_name>& i) { return static_cast<std::underlying_type_t<enum_name>>(e1) != i; }

#define ICED_DEFINE_ADD_FRIEND(enum_name) friend inline static constexpr std::underlying_type_t<enum_name> operator+(const enum_name& e1, const enum_name& e2) { return static_cast<std::underlying_type_t<enum_name>>(enum_add(e1, e2)); }
#define ICED_DEFINE_ADD1_FRIEND(enum_name) friend inline static constexpr std::underlying_type_t<enum_name> operator+(const enum_name& e1, const std::underlying_type_t<enum_name>& e2) { return static_cast<std::underlying_type_t<enum_name>>(enum_add(e1, static_cast<enum_name>(e2))); }
#define ICED_DEFINE_ADD2_FRIEND(enum_name) friend inline static constexpr std::underlying_type_t<enum_name> operator+(const std::underlying_type_t<enum_name>& e1, const enum_name& e2) { return e2 + e1; }
#define ICED_DEFINE_SUB_FRIEND(enum_name) friend inline static constexpr std::underlying_type_t<enum_name> operator-(const enum_name& e1, const enum_name& e2) { return static_cast<std::underlying_type_t<enum_name>>(enum_sub(e1, e2)); }
#define ICED_DEFINE_SUB1_FRIEND(enum_name) friend inline static constexpr std::underlying_type_t<enum_name> operator-(const enum_name& e1, const std::underlying_type_t<enum_name>& e2) { return static_cast<std::underlying_type_t<enum_name>>(enum_sub(e1, static_cast<enum_name>(e2))); }
#define ICED_DEFINE_SUB2_FRIEND(enum_name) friend inline static constexpr std::underlying_type_t<enum_name> operator-(const std::underlying_type_t<enum_name>& e1, const enum_name& e2) { return e2 - e1; }

#define ICED_DEFINE_COMP(enum_name) ICED_DEFINE_EQ(enum_name) ICED_DEFINE_NEQ(enum_name)
#define ICED_DEFINE_FLAGS(enum_name) ICED_DEFINE_AND(enum_name) ICED_DEFINE_OR(enum_name) ICED_DEFINE_XOR(enum_name) ICED_DEFINE_AND_EQ(enum_name) ICED_DEFINE_OR_EQ(enum_name) ICED_DEFINE_XOR_EQ(enum_name) ICED_DEFINE_NOT(enum_name)
#define ICED_DEFINE_ARITH(enum_name) ICED_DEFINE_ADD(enum_name) ICED_DEFINE_ADD1(enum_name) ICED_DEFINE_ADD2(enum_name) ICED_DEFINE_SUB(enum_name) ICED_DEFINE_SUB1(enum_name) ICED_DEFINE_SUB2(enum_name) ICED_DEFINE_INC_PRE(enum_name) ICED_DEFINE_INC_POST(enum_name) ICED_DEFINE_DEC_PRE(enum_name) ICED_DEFINE_DEC_POST(enum_name)

#define ICED_DEFINE_COMP_FRIEND(enum_name) ICED_DEFINE_EQ_FRIEND(enum_name) ICED_DEFINE_NEQ_FRIEND(enum_name)
#define ICED_DEFINE_FLAGS_FRIEND(enum_name) ICED_DEFINE_AND_FRIEND(enum_name) ICED_DEFINE_OR_FRIEND(enum_name) ICED_DEFINE_XOR_FRIEND(enum_name) ICED_DEFINE_AND_EQ_FRIEND(enum_name) ICED_DEFINE_OR_EQ_FRIEND(enum_name) ICED_DEFINE_XOR_EQ_FRIEND(enum_name) ICED_DEFINE_NOT_FRIEND(enum_name)
#define ICED_DEFINE_ARITH_FRIEND(enum_name) ICED_DEFINE_ADD_FRIEND(enum_name) ICED_DEFINE_ADD1_FRIEND(enum_name) ICED_DEFINE_ADD2_FRIEND(enum_name) ICED_DEFINE_SUB_FRIEND(enum_name) ICED_DEFINE_SUB1_FRIEND(enum_name) ICED_DEFINE_SUB2_FRIEND(enum_name)
