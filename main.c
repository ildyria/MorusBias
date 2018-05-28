#include "main.h"

uint64_t linear_sample(struct RNG_state* seed)
{
	state saved_state[6];
	state state;
	union Register saved_cipher[5];

	// printf("START SAMPLING !!! \n");
	// PRINT(saved_state,saved_cipher);
	RAND(state,seed);
	COPY(saved_state[0], state);
	// printf("======================================================\n");
	// STATE(state);
	// printf("======================================================\n");
	// PRINT(saved_state,saved_cipher);
	ENCR(&saved_cipher[0], state);

	COPY(saved_state[1], state);
	// printf("======================================================\n");
	// STATE(state);
	// printf("======================================================\n");
	// PRINT(saved_state,saved_cipher);
	ENCR(&saved_cipher[1], state);

	COPY(saved_state[2], state);
	// printf("======================================================\n");
	// STATE(state);
	// printf("======================================================\n");
	// PRINT(saved_state,saved_cipher);
	ENCR(&saved_cipher[2], state);

	COPY(saved_state[3], state);
	// printf("======================================================\n");
	// STATE(state);
	// printf("======================================================\n");
	// PRINT(saved_state,saved_cipher);
	ENCR(&saved_cipher[3], state);

	COPY(saved_state[4], state);
	// printf("======================================================\n");
	// STATE(state);
	// printf("======================================================\n");
	// PRINT(saved_state,saved_cipher);
	ENCR(&saved_cipher[4], state);

	COPY(saved_state[5], state);
	// printf("======================================================\n");
	// STATE(state);
	// printf("======================================================\n");
	// PRINT(saved_state,saved_cipher);

	// printf("STOP SAMPLING !!! \n");

	return MASK(saved_state, saved_cipher);
}

int main(int argc, char const *argv[]) {

	struct Properties *prop;
	struct RNG_state *seed;

	uint32_t small_seed = 0;
	uint64_t num = 1;
	int64_t res = 0;
	int64_t inbalance = 0;
	uint64_t bias = 0;
	uint64_t i = 0;
	uint32_t tid;
	uint8_t progress = 0;
	uint8_t t_progress = 0;
	uint32_t shift = 0;
	srand((uint32_t) time(NULL));
	small_seed = (uint32_t) rand();

	prop = read_args(argc, argv);
	shift = (WEIGHT * 2 + 5 - ilog2(prop->num_proc_to_use));
	num <<= shift;

	# pragma omp parallel private(i, tid, seed) shared(num) reduction(+:bias,inbalance)
	{
		tid = (uint32_t) omp_get_thread_num();
		seed = init_aesrand_r(small_seed^tid,tid);

		#pragma omp parallel for private(i) shared(bias,inbalance) shared(num)
		for(i = 0 ; i < num; ++i)
		{
			res = linear_sample(seed);
			inbalance += 1 - 2*res;
			bias += res;
			if(tid == 0)
			{
				t_progress = ((i << 7) >> shift);
				if( progress < t_progress)
				{
					printf("\rProgress (over 128): %u%%", progress);
					progress = t_progress;
				}
			}
		}
	}

	num = num * prop->num_proc_to_use;

	print_results(WEIGHT, num, inbalance, bias);
}
