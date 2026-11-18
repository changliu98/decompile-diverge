void iw_restrict_to_range(int min, int max, int *value) {
  if (*value < min)
    *value = min;
  else if (*value > max)
    *value = max;
}