void find_ibm(int a, int b, int *c, int *d) {
  int i, j;
  i = 0;
  j = b - 161 * (a - 161) + 63;
  if (j != (b > 126)) i += 34;
  i = i % 188 + 137;
  j = i - 188 * (i / 188) + 63;
  if (j > 126) j++;
  *c = i;
  *d = j;
}