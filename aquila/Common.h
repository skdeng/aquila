#ifndef _AQUILA_COMMON_H_
#define _AQUILA_COMMON_H_

#include "glmath.h"
#include "Values.h"
#include "Types.h"
#include "Utils.h"
#include "Ray.h"

#define AQ_DEBUG
#define AQ_PARANOID1

#ifdef AQ_DEBUG
	#include <iostream>
	#define DEBUG_LOG std::cout
#endif

#ifdef AQ_PARANOID
	#define PARANOID_PTR_CHECK(ptr, s) if (ptr == nullptr) { DEBUG_LOG << s << std::endl; return; }
#else
	#define PARANOID_PTR_CHECK 
#endif

#endif