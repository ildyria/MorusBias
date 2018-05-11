#include "printing.h"

void print_results(uint64_t weight, uint64_t num, int64_t inbalance, uint64_t bias) {
    printf("\r-----------------------------\n");
    printf("expected weight: %lu\n", weight);
    printf("num:  %lu\n", num);
    printf("inba: %ld\n", inbalance);
    printf("bias: %lu\n", bias);
    printf("log2_num: %Lf\n", log2l(num));
    printf("log2_imba: %Lf\n", log2l(labs(inbalance)));
    printf("Resulting Weight: %Lf\n", log2l(labs(inbalance)) - log2l(2 * num));
    printf("-----------------------------\n");
}

void die(const char *message) {
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}
