#pragma once

#include <csharp/enum.h>
#include <csharp/exceptionhelper.h>
#include <csharp/primitives.h>

#include <any>
#include <cctype>
#include <iostream>
#include <functional>
#include <string>
#include <type_traits>

class Stream
{
private:
	std::ios_base* _stream;
	bool _canRead;
	bool _canWrite;
	bool _owns;

public:
	Stream(std::istream* is, bool owns = false) : _stream(is), _canRead(true), _canWrite(false), _owns(owns) {}
	Stream(std::ostream* os, bool owns = false) : _stream(os), _canRead(false), _canWrite(true), _owns(owns) {}
	Stream(std::iostream* ios, bool owns = false) : _stream(ios), _canRead(true), _canWrite(true), _owns(owns) {}

	inline void WriteByte(byte value) { if (!_canWrite) throw NotSupportedException(); reinterpret_cast<std::ostream*>(_stream)->put(value); }
	inline byte ReadByte() { if (!_canRead) throw NotSupportedException(); return reinterpret_cast<std::istream*>(_stream)->get(); }

	~Stream() { if (_owns) delete _stream; }
};

class Attribute {};

class SerializationInfo {};
class StreamingContext {};

template<typename T>
concept HasToString = requires(const T& t) { t.ToString(); };

template<typename T>
concept HasStdto_string = requires(const T& t) { std::to_string(t); };

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
inline std::string to_string(const T& t) { return t.ToString(); }

template <HasStdto_string T>
inline std::string to_string(const T& t) { return std::to_string(t); }

template <HasCharIter T>
inline std::string to_string(const T& t) 
{
	std::string s;
	std::copy(t.begin(), t.end(), std::back_inserter(s));
	return s;
}

template <Enum T>
inline std::string to_string(const T& t)
{
	return std::string(magic_enum::enum_flags_name(t));
}

template<typename T>
concept HasStdHash = requires(const T& t) { std::hash<T>()(t); };

template <typename T>
concept HasGetHashCode = requires(const T& t) { t.GetHashCode(); };

template <HasStdHash T>
inline int GetHashCode(const T& t) { return (int)std::hash<T>()(t); }

template <HasGetHashCode T>
inline int GetHashCode(T t) { return t.GetHashCode(); }

inline std::string tolower(const std::string& original)
{
	std::string result; result.reserve(original.size());
	for (auto ch : original) result.push_back(tolower(ch));
	return result;
}

inline std::string toupper(const std::string& original)
{
	std::string result; result.reserve(original.size());
	for (auto ch : original) result.push_back(toupper(ch));
	return result;
}

class Math
{
public:
	template <typename T>
	inline static T DivRem(const T& a, const T& b, T& remainder)
	{
		auto [res, rem] = std::div(a, b);
		remainder = rem;
		return res;
	}
};