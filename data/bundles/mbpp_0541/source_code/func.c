

#include <math.h>

#include <assert.h>



double get_sum(int n) {

    double sum = 0;

    int i = 1;

    while (i <= (int)(sqrt(n))) {

        if (n % i == 0) {

            if (n / i == i) {

                sum = sum + i;

            } else {

                sum = sum + i;

                sum = sum + (n / i);

            }

        }

        i = i + 1;

    }

    sum = sum - n;

    return sum;

}



int func0(int n) {
  if (get_sum(n) > n) {
    return 1;
  } else {
    return 0;
  }
}
