void itoa(unsigned long n, char *s) {
  unsigned long i = n;
  unsigned long j = n;
  do {
    s++;
    j /= 10;
  } while (j);
  *s = '\0';
  do {
    *--s = i % 10 + '0';
    i /= 10;
  } while (i);
}