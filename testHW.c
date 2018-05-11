#include "testHW.h"

int main(int argc, char const *argv[]) {
	struct RNG_state *seed;
	unsigned int small_seed = rand();
	int tid;
	int r;
	uint64_t test_value;
	srand(time(NULL));

# pragma omp parallel private(tid, seed, r, test_value)
	{
		tid = omp_get_thread_num();
		seed = init_aesrand_r(small_seed, tid);

		for (uint64_t k = 0; k < 0xFFFFFF; k++) {
			r = 0;
			test_value = aesrand_int64_r(seed);
			for (int k = 0; k < 64; ++k) {
				r += ((test_value >> k) & 1);
			}
			if (r != HW64(test_value)) {
				printf("ERROR %016lx\n", test_value);
			}
		}
	}

	return 0;
}
