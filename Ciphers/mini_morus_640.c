#include "mini_morus_640.h"

inline void mini_morus_640_print_state(state state) {
	printf("%08x %08x %08x %08x %08x\n", state[0].m32, state[1].m32, state[2].m32, state[3].m32, state[4].m32);
}

inline void print_word(union Register *word) {
	printf("%08x\n", word->m32);
}

void mini_morus_640_print(state *saved_state, union Register *saved_cipher) {
	printf("-------------------------------------------- Ciphers\n");
	print_word(&(saved_cipher[0]));
	print_word(&(saved_cipher[1]));
	print_word(&(saved_cipher[2]));
	print_word(&(saved_cipher[3]));
	print_word(&(saved_cipher[4]));
	printf("-------------------------------------------- States\n");
	mini_morus_640_print_state(saved_state[0]);
	mini_morus_640_print_state(saved_state[1]);
	mini_morus_640_print_state(saved_state[2]);
	mini_morus_640_print_state(saved_state[3]);
	mini_morus_640_print_state(saved_state[4]);
	mini_morus_640_print_state(saved_state[5]);
}

void mini_morus_640_copy_state(state to, state from) {
	to[0].m32 = from[0].m32;
	to[1].m32 = from[1].m32;
	to[2].m32 = from[2].m32;
	to[3].m32 = from[3].m32;
	to[4].m32 = from[4].m32;
}

void mini_morus_640_rand_init(state st, struct RNG_state *seed) {
	st[0].m32 = aesrand_int32_r(seed);
	st[1].m32 = aesrand_int32_r(seed);
	st[2].m32 = aesrand_int32_r(seed);
	st[3].m32 = aesrand_int32_r(seed);
	st[4].m32 = aesrand_int32_r(seed);
}

void mini_morus_640_iterate(state st) {
	st[0].m32 ^= st[1].m32 & st[2].m32;
	st[0].m32 ^= st[3].m32;
	st[0].m32 = rotate_left_32(st[0].m32, 5);

	st[1].m32 ^= st[2].m32 & st[3].m32;
	st[1].m32 ^= st[4].m32;
	st[1].m32 = rotate_left_32(st[1].m32, 31);

	st[2].m32 ^= st[3].m32 & st[4].m32;
	st[2].m32 ^= st[0].m32;
	st[2].m32 = rotate_left_32(st[2].m32, 7);

	st[3].m32 ^= st[4].m32 & st[0].m32;
	st[3].m32 ^= st[1].m32;
	st[3].m32 = rotate_left_32(st[3].m32, 22);

	st[4].m32 ^= st[0].m32 & st[1].m32;
	st[4].m32 ^= st[2].m32;
	st[4].m32 = rotate_left_32(st[4].m32, 13);
}

void mini_morus_640_encrypt(union Register *out, state st) {
	out->m32 = 0;
	out->m32 ^= st[0].m32;
	out->m32 ^= st[1].m32;
	out->m32 ^= st[2].m32 & st[3].m32;
	mini_morus_640_iterate(st);
}
