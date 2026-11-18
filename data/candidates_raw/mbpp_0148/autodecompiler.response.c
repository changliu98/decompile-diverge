int sum_digits_closest(int n) {
 int c = closest(n);
 return sum_digits_single(c) + sum_digits_single(n-c);
}