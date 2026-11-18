#include <assert.h>

#include <math.h>



int ngcd(int x, int y) {

    int gcd = 1;

    int i = 1;

    while (i <= x && i <= y) {

        if (x % i == 0 && y % i == 0) {

            gcd = i;

        }

        i++;

    }

    return gcd;

}



int func0(int x, int y) {
  int n = ngcd(x, y);
  int result = 0;
  int z = (int)sqrt(n);
  int i = 1;
  while (i <= z) {
    if (n % i == 0) {
      result += 2;
      if (i == n / i) {
        result -= 1;
      }
    }
    i++;
  }
  return result;
}
