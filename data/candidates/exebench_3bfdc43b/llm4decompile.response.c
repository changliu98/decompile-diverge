void norm(int *hi, int *lo, int base)
{
 if (*lo < 0) {
  int n = (-1 - *lo) / base + 1;
  *hi -= n;
  *lo += n * base;
 }
 if (*lo >= base) {
  int n = *lo / base;
  *hi += n;
  *lo -= n * base;
 }
}