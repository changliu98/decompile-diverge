int stringmatchlen_fuzz_test(void) {
  int n = 10000000;
  int sum = 0;
  char a[32];
  char b[32];
  int i, alen, blen;
  while (n--) {
    blen = rand() & 31;
    alen = rand() & 31;
    for (i = 0; i < blen; i++) b[i] = rand() % 128;
    for (i = 0; i < alen; i++) a[i] = rand() % 128;
    sum += stringmatchlen(a, alen, b, blen, 0);
  }
  return sum;
}