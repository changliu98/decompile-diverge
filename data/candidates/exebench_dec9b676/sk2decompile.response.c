void mult121665(unsigned int *result, const unsigned int *input) {
  unsigned int carry = 0;
  unsigned int i;
  unsigned int tmp;
  for (i = 0; i < 31; i++) {
    tmp = carry + input[i] * 121665;
    result[i] = tmp & 0xff;
    carry = tmp >> 8;
  }
  tmp = carry + input[31] * 121665;
  result[31] = tmp & 0x7f;
  carry = (tmp >> 7) * 19;
  for (i = 0; i < 31; i++) {
    tmp = carry + result[i];
    result[i] = tmp & 0xff;
    carry = tmp >> 8;
  }
  result[i] += carry;
}