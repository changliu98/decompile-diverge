void func0(int a, int b, int *out, int *out_len) {
  *out_len = 0;
  for (int i = a; i <= b; i++) {
    bool is_self_dividing = true;
    int j = i;
    while (j > 0) {
      int digit = j % 10;
      if (digit == 0 || i % digit != 0) {
        is_self_dividing = false;
        break;
      }
      j /= 10;
    }
    if (is_self_dividing) {
      out[*out_len] = i;
      (*out_len)++;
    }
  }
}