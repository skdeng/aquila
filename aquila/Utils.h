#ifndef _AQUILA_UTILS_H_
#define _AQUILA_UTILS_H_

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

namespace Utils
{
	template <typename T>
	inline T Clamp(const T& n, const T& lower, const T& upper) 
	{
		return std::max(lower, std::min(n, upper));
	}

	inline double RadToDeg(double rad)
	{
		return rad * 180 / M_PI;
	}

	inline double DegToRad(double deg)
	{
		return deg * M_PI / 180;
	}

	inline std::vector<std::string> explode(std::string const & s, char delim)
	{
		std::vector<std::string> result;
		std::istringstream iss(s);

		for (std::string token; std::getline(iss, token, delim); )
		{
			result.push_back(std::move(token));
		}

		return result;
	}

	//!Returns a random integer between x and y
	inline int RandInt(int x, int y) { return rand() % (y - x + 1) + x; }
	//!Returns a random aq_float between zero and 1
	inline double RandFloat() { return (rand()) / (RAND_MAX + 1.0); }
	//!Returns a random aq_float between the given interval
	inline double RandFloatInterval(double min, double max) { double interval = max - min;	return min + interval*RandFloat(); }
	//!Returns a random bool
	inline bool RandBool() { if (RandInt(0, 1)) return true;	else return false; }
	//!Returns a random aq_float in the range -1 < n < 1
	inline double RandNormal() { return RandFloat() - RandFloat(); }
}

#endif