void sub(unsigned int *result, unsigned int *a, unsigned int *b) {
  unsigned int carry = 0xda;
  unsigned int temp;
  unsigned int i;
  for (i = 0; i < 31; i++) {
    temp = carry + a[i] + 0xff00 - b[i];
    result[i] = temp & 0xff;
    carry = temp >> 8;
  }
  result[31] = carry + a[31] - b[31];
}