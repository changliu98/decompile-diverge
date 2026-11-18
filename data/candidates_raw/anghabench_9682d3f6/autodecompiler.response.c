void reverse(char *s, int n) {
  char t;
  int j = 0, k = n-1;

  while (1) {
    if (j >= k)
      break;

    t = *(s+j);
    *(s+j) = *(s+k);
    *(s+k) = t;

    j++;
    k--;
  }
}