void __cdecl julian_to_date(long jd, int *y, int *m, int *d)
{
  long j; // [rsp+18h] [rbp-40h]
  long i; // [rsp+20h] [rbp-38h]
  long n; // [rsp+28h] [rbp-30h]

  n = 4 * (jd + 68569) / 146097;
  i = 4000 * (jd + 68569 - (146097 * n + 3) / 4 + 1) / 1461001;
  j = 80 * (jd + 68569 - (146097 * n + 3) / 4 - 1461 * i / 4 + 31) / 2447;
  *d = jd + 68569 - (146097 * n + 3) / 4 - 1461 * i / 4 + 31 - 2447 * j / 80;
  *m = j + 2 - 12 * (j / 11);
  *y = j / 11 + i + 100 * (n - 49);
}