

#include <assert.h>



int sum_Odd(int n) {

    int terms = (n + 1) / 2;

    int sum1 = terms * terms;

    return sum1;

}



int func0(int l, int r) { return sum_Odd(r) - sum_Odd(l - 1); }
