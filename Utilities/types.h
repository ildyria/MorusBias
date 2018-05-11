#pragma once

#include "std.h"

union Register {
	uint32_t m32;
	uint64_t m64;
	__m128i f32;
#ifdef __AVX2__
	__m256i f64;
#endif
};

struct RNG_state {
	__m128i count;
	__m128i t;
	__m128i k;
	int next;
};

typedef union Register state[5];

struct Properties {
	uint8_t num_proc_to_use;       // specify the number of cores to use
};
