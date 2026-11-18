static void int2str(int num, int base, char *bf) {
  int n = 0;
  while (true) {
    if (num == 0)
      break;
    char digit = (char)((num % base) + ((num % base) < 10? '0' : 'A' - 10));
    bf[n++] = digit;
    num /= base;
  }
  bf[n] = 0;
}