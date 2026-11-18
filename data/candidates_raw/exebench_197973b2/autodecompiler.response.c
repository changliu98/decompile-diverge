static void
calc_runlen(int *run, int n, int *r, int *b)
{
 int i, j, k, l, m, nrun;

 j = k = run[0];
 l = (j == 0) ? -1 : 0;
 for (i = 1;; i++) {
  if ((k < *r) && (*r >= (1 << (i - 1))))
   if (run[i] > 0) {
    k += run[i];
    if (k >= (1 << (i - 1))) {
     l = i;
     j = k;
    }
   } else
    continue;
  else
   break;
 }

 *b = n - j;
 if (l == -1)
  m = 0;
 else
  m = (1 << l);
 *r = m;
}