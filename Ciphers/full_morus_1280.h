#include "../Utilities/utilities.h"

void morus_1280_print_state(state st);

void morus_1280_print(state *saved_state, union Register *saved_cipher);

void morus_1280_copy_state(state to, state from);

void morus_1280_rand_init(state st, struct RNG_state *rng);

void morus_1280_iterate(state st);

void morus_1280_encrypt(union Register *out, state state);
