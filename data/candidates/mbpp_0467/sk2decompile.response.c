int func0(int n) {
  int octal = 0, i = 1;
  while (n != 0) {
    octal += (n % 8) * i;
    i *= 10;
    n /= 8;
  }
  return octal;
}