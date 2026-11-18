

#include <math.h>

#include <assert.h>



int divSum(int n) {

    int sum = 1;

    int i = 2;

    while (i * i <= n) {

        if (n % i == 0) {

            sum += i + (int)floor(n / i);

        }

        i++;

    }

    return sum;

}



int func0(int num1, int num2) { return divSum(num1) == divSum(num2); }
