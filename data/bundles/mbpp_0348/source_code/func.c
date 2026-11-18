

#include <assert.h>



long bin_coff(int n, int r) {

    long val = 1;

    if (r > (n - r)) {

        r = (n - r);

    }

    for (int i = 0; i < r; i++) {

        val *= (n - i);

        val /= (i + 1);

    }

    return val;

}



long func0(int M) {
  int n = M / 2;
  long a = bin_coff(2 * n, n);
  long b = a / (n + 1);
  return b;
}
