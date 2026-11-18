void limit2_u16(short* val, short min, short max) {
  if (*val >= max) {
    *val = max;
  }
  else if (*val <= min) {
    *val = min;
  }
}