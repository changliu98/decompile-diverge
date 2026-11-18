int __cdecl obdRevConvert_10(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // Calculate the scaled value (100.0 * val) and cast it to a 32-bit integer.
  // The redundant explicit float cast is removed for readability.
  int scaled_val = (int)(100.0f * val);

  // Extract the high byte (A) and low byte (B) of the scaled value.
  // This represents a standard 16-bit OBD-II big-endian payload split.
  *A = (scaled_val >> 8) & 0xFF;
  *B = scaled_val & 0xFF;

  // C and D are unused in this conversion routine.
  return 2;
}