// Clips the input value to the range [-32767, 32767]
int clip_f15(int value)
{
  // If value is less than minimum, return minimum
  if (value < -0x7fff) {
    return -0x7fff;
  }
  // If value is greater than maximum, return maximum
  if (value > 0x7fff) {
    return 0x7fff;
  }
  // Return the original value if within range
  return value;
}