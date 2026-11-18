void adjust_point(int *value)
{
  // If the value is negative, clamp it to 0
  if (*value < 0) {
    *value = 0;
  }
  // If the value exceeds 100, clamp it to 100
  else if (100 < *value) {
    *value = 100;
  }
}