// Use AES-based RNG
#include "aes-rng.h"

#ifdef __AES__

struct RNG_state *init_aesrand_r(uint32_t seed1, uint32_t seed2) {
	// Internal state: count + t
	struct RNG_state *rng = (struct RNG_state *) malloc(sizeof(struct RNG_state));
	assert(rng);
	rng->count = _mm_setr_epi32(seed1, seed2, 0, 0);
	rng->k = _mm_setr_epi32(0, 0, seed1, seed2);
	rng->next = 0;
	return rng;
}

uint32_t aesrand_int32_r(struct RNG_state *rng) {
	switch (rng->next++) {
		case 0:
			// Increment counter
			rng->count = _mm_add_epi64(rng->count, _mm_setr_epi32(0, 0, 1, 0));

			// 6 AES rounds
			rng->t = rng->count;
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);

			return (uint32_t) _mm_extract_epi32(rng->t, 0);
		case 1:
			return (uint32_t) _mm_extract_epi32(rng->t, 1);
		case 2:
			return (uint32_t) _mm_extract_epi32(rng->t, 2);
		case 3:
			rng->next = 0;
			return (uint32_t) _mm_extract_epi32(rng->t, 3);
		default:
			assert(0);
	}
}

uint64_t aesrand_int64_r(struct RNG_state *rng) {
	switch (rng->next++) {
		case 0:
			// Increment counter
			rng->count = _mm_add_epi64(rng->count, _mm_setr_epi32(0, 0, 1, 0));

			// 6 AES rounds
			rng->t = rng->count;
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);

			return (uint64_t) _mm_extract_epi64(rng->t, 0);
		case 1:
			rng->next = 0;
			return (uint64_t) _mm_extract_epi64(rng->t, 1);
		default:
			assert(0);
	}
}

__m128i aesrand_m128i_r(struct RNG_state *rng) {
		// Increment counter
		rng->count = _mm_add_epi64(rng->count, _mm_setr_epi32(0, 0, 1, 0));

		// 6 AES rounds
		rng->t = rng->count;
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);

		return rng->t;
}

#ifdef __AVX2__

__m256i aesrand_m256i_r(struct RNG_state *rng) {

		__m256i r;
		// Increment counter
		rng->count = _mm_add_epi64(rng->count, _mm_setr_epi32(0, 0, 1, 0));

		// 6 AES rounds
		rng->t = rng->count;
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);

		r = _mm256_castsi128_si256(rng->t);

		// Increment counter
		rng->count = _mm_add_epi64(rng->count, _mm_setr_epi32(0, 0, 1, 0));
		// 6 AES rounds
		rng->t = rng->count;
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);
		rng->t = _mm_aesenc_si128(rng->t, rng->k);

		return _mm256_inserti128_si256(r, rng->t, 1);
}

#endif

uint8_t aesrand_int8_r(struct RNG_state *rng) {
	switch (rng->next++) {
		case 0:
			// Increment counter
			rng->count = _mm_add_epi64(rng->count, _mm_setr_epi32(0, 0, 1, 0));

			// 6 AES rounds
			rng->t = rng->count;
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);
			rng->t = _mm_aesenc_si128(rng->t, rng->k);

			return (uint8_t) _mm_extract_epi8(rng->t, 0);
		case 1:
			return (uint8_t) _mm_extract_epi8(rng->t, 1);
		case 2:
			return (uint8_t) _mm_extract_epi8(rng->t, 2);
		case 3:
			return (uint8_t) _mm_extract_epi8(rng->t, 3);
		case 4:
			return (uint8_t) _mm_extract_epi8(rng->t, 4);
		case 5:
			return (uint8_t) _mm_extract_epi8(rng->t, 5);
		case 6:
			return (uint8_t) _mm_extract_epi8(rng->t, 6);
		case 7:
			return (uint8_t) _mm_extract_epi8(rng->t, 7);
		case 8:
			return (uint8_t) _mm_extract_epi8(rng->t, 8);
		case 9:
			return (uint8_t) _mm_extract_epi8(rng->t, 9);
		case 10:
			return (uint8_t) _mm_extract_epi8(rng->t, 10);
		case 11:
			return (uint8_t) _mm_extract_epi8(rng->t, 11);
		case 12:
			return (uint8_t) _mm_extract_epi8(rng->t, 12);
		case 13:
			return (uint8_t) _mm_extract_epi8(rng->t, 13);
		case 14:
			return (uint8_t) _mm_extract_epi8(rng->t, 14);
		case 15:
			rng->next = 0;
			return (uint8_t) _mm_extract_epi8(rng->t, 15);
		default:
			assert(0);
	}
}

#else

struct RNG_state* init_aesrand_r(uint32_t seed1, uint32_t seed2) {
  die ("AES-NI support not enabled!\n");
}

uint32_t aesrand_int32_r(struct RNG_state* rng) {
  die ("AES-NI support not enabled!\n");
}

uint64_t aesrand_int64_r(struct RNG_state* rng) {
  die ("AES-NI support not enabled!\n");
}

uint8_t aesrand_int8_r(struct RNG_state* rng) {
  die ("AES-NI support not enabled!\n");
}

__m128i aesrand_m128i_r(struct RNG_state *rng) {
	die ("AES-NI support not enabled!\n");
}

#ifdef __AVX2__

__m256i aesrand_m256i_r(struct RNG_state *rng) {
	die ("AES-NI support not enabled!\n");
}

#endif


#endif
