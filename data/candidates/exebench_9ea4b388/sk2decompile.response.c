void combain_sorted_array(int *a, int *b, int *c) {
  int *p = a;
  int *q = b;
  int *pa = a + 5;
  int *pb = b + 5;
  while (p < pa && q < pb) {
    if (*p <= *q) {
      if (p == pa - 1) {
        *c = *p;
        c++;
        while (q < pb) {
          *c = *q;
          c++;
          q++;
        }
        return;
      }
      *c = *p;
      c++;
      p++;
    } else {
      if (q == pb - 1) {
        *c = *q;
        c++;
        while (p < pa) {
          *c = *p;
          c++;
          p++;
        }
        return;
      }
      *c = *q;
      c++;
      q++;
    }
  }
}