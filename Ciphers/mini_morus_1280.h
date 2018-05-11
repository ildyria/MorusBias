#include "../Utilities/utilities.h"

void mini_morus_1280_print_state(state st);

void mini_morus_1280_print(state *saved_state, union Register *saved_cipher);

void mini_morus_1280_copy_state(state to, state from);

void mini_morus_1280_rand_init(state st, struct RNG_state *rng);

void mini_morus_1280_iterate(state st);

void mini_morus_1280_encrypt(union Register *out, state state);
