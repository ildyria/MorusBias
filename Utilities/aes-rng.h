#pragma once

#include "types.h"

//struct RNG_state {
//    __m128i count;
//    __m128i t;
//    __m128i k;
//    int next;
//};

struct RNG_state *init_aesrand_r(uint32_t seed1, uint32_t seed2);

uint32_t aesrand_int32_r(struct RNG_state *rng);

uint64_t aesrand_int64_r(struct RNG_state *rng);

uint8_t aesrand_int8_r(struct RNG_state *rng);

__m128i aesrand_m128i_r(struct RNG_state *rng);

#ifdef __AVX2__

__m256i aesrand_m256i_r(struct RNG_state *rng);

#endif
