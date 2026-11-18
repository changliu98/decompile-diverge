static void dwt_deinterleave_h(int *a, int n, int xstride, int ystride)
{
 int tmp[32768];
 int *t, *ta, *tb;
 int i, j, k, m, n1, n2, hstartcol;
 int *b;

 t = tmp;
 if (n > 32768 / sizeof(int)) {
  if (!(t = jas_alloc2((n), (sizeof(int)))))
   abort();
 }
 if (n >= 3) {

  hstartcol = (n + 1 - ystride) >> 1;
  m = n - hstartcol;
  n1 = m;
  ta = t;
  tb = a + (1 - ystride) * xstride;
  for (;;) {
   if ((n1--) <= 0)
    break;
   b = ta;
   k = 0;
   for (;;) {
    if (k >= 17)
     break;
    *b = *tb;
    ++b;
    ++tb;
    ++k;
   }
   ta += 16;
   tb += 2 * xstride;
  }

  ta = a + (1 - ystride) * xstride;
  tb = a + (2 - ystride) * xstride;
  n2 = n - m - ((ystride == 0) ? 1 : 0);
  for (;;) {
   if ((n2--) <= 0)
    break;
   b = ta;
   k = 0;
   for (;;) {
    if (k >= 17)
     break;
    *b = *tb;
    ++b;
    ++tb;
    ++k;
   }
   ta += xstride;
   tb += 2 * xstride;
  }

  ta = a + hstartcol * xstride;
  tb = t;
  n1 = m;
  for (;;) {
   if ((n1--) <= 0)
    break;
   b = ta;
   k = 0;
   for (;;) {
    if (k >= 17)
     break;
    *b = *tb;
    ++b;
    ++tb;
    ++k;
   }
   ta += xstride;
   tb += 16;
  }
 } else {
  if (t != tmp)
   jas_free(t);
  return;
 }
 if (t != tmp)
  jas_free(t);
}