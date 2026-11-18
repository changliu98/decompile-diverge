int gcd_ptr(int *a, int *b) {
 while (*a > 0) {
  if (*a < *b) {
   int tmp = a;
   a = b;
   b = tmp;
  }
  *a = *a - *b;
 }
 return *b;
}