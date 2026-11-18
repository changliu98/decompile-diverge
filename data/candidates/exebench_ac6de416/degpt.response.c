void adjust_mode_num(int *mode_value)
{
  // Clamp the mode value to a minimum of 0 if it is negative
  if (*mode_value < 0) {
    *mode_value = 0;
  } else if (*mode_value > 9) {
    // Clamp the mode value to a maximum of 9 if it exceeds 9
    *mode_value = 9;
  }
}