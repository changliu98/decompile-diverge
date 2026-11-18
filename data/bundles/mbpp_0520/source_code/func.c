

#include <stdio.h>

#include <assert.h>



int find_lcm(int num1, int num2) {

    int num, den, rem, gcd, lcm;

    if (num1 > num2) {

        num = num1;

        den = num2;

    } else {

        num = num2;

        den = num1;

    }

    rem = num % den;

    while (rem != 0) {

        num = den;

        den = rem;

        rem = num % den;

    }

    gcd = den;

    lcm = (num1 * num2) / gcd;

    return lcm;

}



int func0(int *l, int size) {
  int num1 = l[0];
  int num2 = l[1];
  int lcm = find_lcm(num1, num2);
  for (int i = 2; i < size; i++) {
    lcm = find_lcm(lcm, l[i]);
  }
  return lcm;
}
