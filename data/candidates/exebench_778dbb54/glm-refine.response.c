int __cdecl obdRevConvert_43(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // Calculate the scaled value (255.0 / 100.0 is optimized to 2.55f)
  float scaled_val = val * 2.55f;

  // Cast to integer to extract the high and low bytes
  unsigned int int_val = (unsigned int)scaled_val;

  // Extract the high byte (Most Significant Byte)
  *A = int_val / 256;

  // Extract the low byte (Least Significant Byte)
  *B = int_val % 256;

  // C and D are unused in this function, likely part of a standard OBD2 signature
  return 2;
}