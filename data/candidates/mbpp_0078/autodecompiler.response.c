int func0(int v) {
  int next_pow_of_two;
  if (v % 2 != 0) {
    next_pow_of_two = (v + 1) / 2;
  } else {
    int bit_count = 0;
    int i = 0;
    while (1) {
      if (i >= 33) {
        break;
      }
      bit_count += (v >> i) & 1;
      i++;
    }

    int div = v / 2;
    if (bit_count % 2 != 0) {
      div++;
    }
    next_pow_of_two = div;
  }
  return next_pow_of_two;
}