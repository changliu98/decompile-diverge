#include <stdio.h>

unsigned answer;

static unsigned target(unsigned x) {
    return x * 2u;
}

int main(void) {
    unsigned x = 0;
    if (scanf("%u", &x) != 1) return 0;
    answer = target(x);
    printf("%u\n", answer);
    return 0;
}
