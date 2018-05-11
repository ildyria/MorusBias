#pragma once

#include "std.h"

static inline uint64_t ilog2(const uint32_t x) {
	uint32_t y;
	asm ( "\tbsr %1, %0\n" : "=r"(y) : "r" (x));
	return (uint64_t) y;
}

// Compute the Hamming Weight over 64 bits
static inline uint64_t HW64(uint64_t i) {
	i = i - ((i >> 1) & 0x5555555555555555UL);
	i = (i & 0x3333333333333333UL) + ((i >> 2) & 0x3333333333333333UL);
	return (((i + (i >> 4)) & 0xF0F0F0F0F0F0F0FUL) * 0x101010101010101UL) >> 56;
}

// Compute the Hamming Weight over 32 bits
static inline uint64_t HW32(uint32_t x) {
	x = x - ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F;
	x = x + (x >> 8);
	x = x + (x >> 16);
	return (uint64_t) (x & 0x0000003F);
}

static inline uint32_t rotate_left_32(uint32_t x, int bits) {
	if (bits == 0) return x;
	return (x << bits) | (x >> (32 - bits));
}

static inline uint64_t rotate_left_64(uint64_t x, int bits) {
	if (bits == 0) return x;
	return (x << bits) | (x >> (64 - bits));
}

#ifndef max
#define max(a, b) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
#define min(a, b) ( ((a) < (b)) ? (a) : (b) )
#endif
