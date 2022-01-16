#pragma once

#include <any>
#include <stdexcept>
#include <vector>

namespace System::Collections
{
	class IList
	{

	};

	class IEnumerator
	{

	};
}

struct InterfaceException : std::exception
{
	InterfaceException(std::string s) : base(s) {};
};

#define INTERFACE_FUNC { throw InterfaceException(__FUNCSIG__); }

template <typename T>
class IEquatable
{
public:
	virtual bool Equals(T other) INTERFACE_FUNC
		virtual bool IEquatable_Equals(T other) INTERFACE_FUNC
};

template <typename T>
class IEnumerator
{
public:
	virtual T GetCurrent() const = 0; INTERFACE_FUNC
		virtual bool MoveNext() INTERFACE_FUNC
		virtual void Reset() INTERFACE_FUNC
};

template <typename T>
class IReadOnlyList
{
public:
	virtual std::int32_t GetCount() const INTERFACE_FUNC
		virtual bool Contains(T const instruction) INTERFACE_FUNC
		virtual std::int32_t IndexOf(T const instruction) INTERFACE_FUNC
		virtual void CopyTo(std::vector<T>& array, std::int32_t arrayIndex) INTERFACE_FUNC
};

template <typename T>
class IList : IReadOnlyList<T>
{
public:
	virtual T& operator[](std::int32_t index) INTERFACE_FUNC
		virtual void Insert(std::int32_t index, T const instruction) INTERFACE_FUNC
		virtual void RemoveAt(std::int32_t index) INTERFACE_FUNC
		virtual void Add(T const instruction) INTERFACE_FUNC
		virtual void Clear() INTERFACE_FUNC
		virtual bool Remove(T const instruction) INTERFACE_FUNC
		virtual IReadOnlyList<T>& AsReadOnly() INTERFACE_FUNC
};
