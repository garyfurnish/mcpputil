#pragma once
#include "declarations.hpp"
namespace mcpputil
{
#ifndef _WIN32
	mcpputil_always_inline size_t popcount(size_t x)
	{
		return __popcnt64(x);
	}
	mcpputil_always_inline size_t ffs(uint64_t x)
	{
		return static_cast<size_t>(__builtin_ffsll(static_cast<long long>(x)));
	}
	mcpputil_always_inline size_t clz(size_t x)
	{
		return __builtin_clzll(x);
	}
#else
	mcpputil_always_inline size_t popcount(size_t x)
	{
		return __popcnt64(x);
}
	mcpputil_always_inline size_t ffs(uint64_t x)
	{
		unsigned long index{ 0 };
		if (!_BitScanForward64(&index, x))
			return 0;
		index++;
		return index;
	}
	mcpputil_always_inline size_t clz(size_t x)
	{
		unsigned long index{ 0 };
		char found = _BitScanReverse64(&index, x);
		if (!found)
			return 64;
		return (63 - index);
	}
#endif
}