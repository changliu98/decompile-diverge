

#include <assert.h>



int factorial(int start, int end) {

    int res = 1;

    for (int i = start; i <= end; i++) {

        res *= i;

    }

    return res;

}



int func0(int n) { return factorial(n + 1, 2 * n) / factorial(1, n); }
