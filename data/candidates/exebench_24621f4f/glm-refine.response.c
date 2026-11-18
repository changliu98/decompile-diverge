int __cdecl obdRevConvert_34_3B(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // Calculate the raw 16-bit scaled value from the physical value
  unsigned int raw_val = (unsigned int)(int)(val / 0.000030499999f);

  // Split the raw value into Big-Endian format (High byte and Low byte)
  *A = raw_val / 256;  // High byte
  *B = raw_val % 256;  // Low byte

  // C and D are unused in this conversion
  return 2;
}