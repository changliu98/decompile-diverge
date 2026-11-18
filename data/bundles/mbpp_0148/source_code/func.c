

#include <assert.h>



int sum_digits_single(int x) {

    int ans = 0;

    while (x) {

        ans += x % 10;

        x /= 10;

    }

    return ans;

}



int closest(int x) {

    int ans = 0;

    while (ans * 10 + 9 <= x) {

        ans = ans * 10 + 9;

    }

    return ans;

}



int func0(int N) {
  int A = closest(N);
  return sum_digits_single(A) + sum_digits_single(N - A);
}
