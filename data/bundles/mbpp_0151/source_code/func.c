

#include <assert.h>



int gcd(int p, int q) {

    while (q != 0) {

        int temp = q;

        q = p % q;

        p = temp;

    }

    return p;

}



int func0(int x, int y) { return gcd(x, y) == 1; }
