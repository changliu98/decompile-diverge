int readUnicode(int *bit_ptr, int *bit_no, int total_bits)
{
  int val, idx, sign, n, s;

  idx = getStepCodeIdx(bit_ptr, total_bits, bit_no, 5);
  if (idx == 99)
    val = -157;
  else if (idx == 5) {
    idx = getStepCodeIdx(bit_ptr, total_bits, bit_no, 4);
    val = idx - 256;
  } else if (idx >= 0) {
    if (*bit_no < total_bits)
      sign = readBit(bit_ptr, *bit_no);
    else
      sign = 0;
    *bit_no += 1;
    if ((*bit_no + uni_bit_len[idx] - 1) > total_bits)
      val = -157;
    else {
      n = getNumFromBits(bit_ptr, total_bits, *bit_no, uni_bit_len[idx]);
      n += uni_adder[idx];
      *bit_no += uni_bit_len[idx];
      if (sign)
        s = 0 - n;
      else
        s = n;
      val = s;
    }
  } else
    val = 0;

  return (val);
}