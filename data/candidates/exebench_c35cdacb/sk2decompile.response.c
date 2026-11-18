int libbf_is_composed_poweroftwo(unsigned int value, int *first_bit,
                                 int *second_bit) {
  unsigned int v = value;
  int bit = 0;
  int count = 0;
  if (value == 0) return 0;
  if (first_bit != NULL) *first_bit = 0;
  if (second_bit != NULL) *second_bit = 0;
  while (v != 0) {
    if (v & 1) {
      count++;
      if (count == 1) {
        if (first_bit != NULL) *first_bit = bit;
      } else if (count == 2) {
        if (second_bit != NULL) *second_bit = bit;
      } else {
        return 0;
      }
    }
    bit++;
    v >>= 1;
  }
  return 1;
}