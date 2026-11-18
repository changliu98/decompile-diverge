int32_t readUnicode(const char *in, int *bit_no_p, int len) {
  int idx = getStepCodeIdx(in, len, bit_no_p, 5);
  if (idx == 99)
    return 0x7FFFFF00 + 99;
  if (idx == 5) {
    idx = getStepCodeIdx(in, len, bit_no_p, 4);
    return 0x7FFFFF00 + idx;
  }
  if (idx >= 0) {
    int sign = (*bit_no_p < len ? readBit(in, *bit_no_p) : 0);
    (*bit_no_p)++;
    if (*bit_no_p + uni_bit_len[idx] - 1 >= len)
      return 0x7FFFFF00 + 99;
    int32_t count = getNumFromBits(in, len, *bit_no_p, uni_bit_len[idx]);
    count += uni_adder[idx];
    (*bit_no_p) += uni_bit_len[idx];
    //printf("Sign: %d, Val:%d", sign, count);
    return sign ? -count : count;
  }
  return 0;
}