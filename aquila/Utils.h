#ifndef _AQUILA_UTILS_H_
#define _AQUILA_UTILS_H_

#include <algorithm>

namespace Utils
{
	template <typename T>
	inline T Clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}
}

#endif