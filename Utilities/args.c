#include "args.h"

struct Properties *read_args(int argc, const char **argv) {

	uint8_t j;
	uint8_t max_num_proc;
	struct Properties *prop = (struct Properties *) malloc(sizeof(struct Properties));
	assert(prop);

	max_num_proc = (uint8_t) omp_get_num_procs();
	// prop->kind = 1;
	// prop->width = 32;
	prop->num_proc_to_use = max_num_proc;
	// prop->test = 1;

	// get settings
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-n") == 0) {
			if (i + 1 < argc) {
				i++;
				j = (uint8_t) atoi(argv[i]);
				prop->num_proc_to_use = max((uint8_t) 1, j);
				prop->num_proc_to_use = min(prop->num_proc_to_use, max_num_proc);
				printf("%i core selected over %i.\n", prop->num_proc_to_use, max_num_proc);
				omp_set_num_threads(prop->num_proc_to_use);
			}
			else {
				die("-n require an additional parameter.\n");
			}
		}
		// else if (strcmp(argv[i], "-w") == 0) {
		// 	if (i + 1 < argc) {
		// 		i++;
		// 		j = (uint8_t) atoi(argv[i]);
		// 		if (j == 32 || j == 64)
		// 			prop->width = j;
		// 	}
		// 	else {
		// 		die("-w require an additional parameter.\n");
		// 	}
		// }
		// else if (strcmp(argv[i], "-k") == 0) {
		// 	if (i + 1 < argc) {
		// 		i++;
		// 		j = (uint8_t) atoi(argv[i]);
		// 		if (j == 1 || j == 2)
		// 			prop->kind = j;
		// 	}
		// 	else {
		// 		die("-k require an additional parameter.\n");
		// 	}
		// }
		// else if (strcmp(argv[i], "-t") == 0) {
		// 	if (i + 1 < argc) {
		// 		i++;
		// 		j = (uint8_t) atoi(argv[i]);
		// 		if (j == 1 || j == 2)
		// 			prop->test = j;
		// 	}
		// 	else {
		// 		die("-t require an additional parameter.\n");
		// 	}
		// }
		else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "help") == 0) {
			printf("-n <int>   : number of process to use over %u.  [default: max]\n", max_num_proc);
			// printf("-w [32|64] : 640 (32) or 1280 (64).             [default: 32]\n");
			// printf("-k [1|2]   : MiniMorus (1) or FullMorus(2).     [default: 1]\n");
			// printf("-t <int>   : Test to execute.                   [default: 1]\n");
			exit(1);
		}
		else {
			printf("Argument %d:%s\n", i, argv[i]);
		}
	}


	printf("we will use %i threads\n", prop->num_proc_to_use);
	// if (prop->width == 32 && prop->kind == 1)
	// 	printf("We will use MiniMorus640\n");
	// if (prop->width == 32 && prop->kind == 2)
	// 	printf("We will use Morus640\n");
	// if (prop->width == 64 && prop->kind == 1)
	// 	printf("We will use MiniMorus1280\n");
	// if (prop->width == 64 && prop->kind == 2)
	// 	printf("We will use Morus1280\n");

	return prop;
}
