#pragma once

#include <cstdlib>

class Math
{
public:
	template <typename T>
	static constexpr T DivRem(const T& a, const T& b, T& remainder)
	{
		remainder = a % b;
		return a / b;
	}
};

#define nameof(x) #x