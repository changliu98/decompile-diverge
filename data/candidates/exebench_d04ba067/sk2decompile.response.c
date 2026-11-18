unsigned char itochar(int i, char *s) {
  unsigned char tmp[16];
  unsigned char j, k;
  j = 0;
  k = 0;
  do {
    tmp[j++] = i % 10 + '0';
    i /= 10;
  } while (i);
  do {
    s[k] = tmp[j - k - 1];
    k++;
  } while (k < j);
  return k;
}