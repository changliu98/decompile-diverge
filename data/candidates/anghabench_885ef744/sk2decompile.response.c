void ui2a(unsigned int num, int base, int uc, char *bf) {
  int n, div, mod;
  char c;
  n = 0;
  div = 1;
  while (num / div >= base) {
    div *= base;
  }
  while (div != 0) {
    mod = num / div;
    num %= div;
    div /= base;
    if (n || mod > 0 || div == 0) {
      c = (mod < 10) ? '0' : (uc ? 'A' : 'a') - 10;
      *bf++ = mod + c;
      n++;
    }
  }
  *bf = '\0';
}