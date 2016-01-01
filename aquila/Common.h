#ifndef _AQUILA_COMMON_H_
#define _AQUILA_COMMON_H_

#include "glmath.h"
#include "Values.h"
#include "Types.h"
#include "Utils.h"
#include "Ray.h"

#include <memory>
#include <SDL.h>

#define AQ_DEBUG

#ifdef AQ_DEBUG
	#include <iostream>
	#define DEBUG_LOG(s) std::cout << s << std::endl
#else
	#define DEBUG_LOG
#endif

#endif