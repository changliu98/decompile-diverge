int func0(int n) {
 int i, j, k, d;
 for (i = 0; ; ++i) {
  if (i >= 11) break;
  for (j = n, d = 0; j > 0; j /= 10) {
   if (j % 10 == i) d++;
   if (d > i) break;
  }
  if (d <= i) continue;
  return 0;
 }
 return 1;
}