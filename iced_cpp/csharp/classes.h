#pragma once

#include <cstdlib>

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

#define nameof(x) #x