double __cdecl randum(long *seed)
{
  long current_seed = *seed;
  
  // The 36-bit state is split into three 12-bit chunks.
  // Note: The original code used BYTE3(*seed) which is equivalent to (current_seed >> 24).
  int s0 = current_seed & 0xFFF;
  int s1 = (current_seed >> 12) & 0xFFF;
  int s2 = current_seed >> 24; // Extracts the top 12 bits (bits 24-35)

  // Calculate the next state for s0
  // The (unsigned short) cast accurately reflects the 16-bit truncation seen in IDA's (_WORD) cast.
  int new_s0 = (1549 * (unsigned short)s0) & 0xFFF;

  // Calculate the next state for s1, including the carry from s0's multiplication
  long sum = ((1549 * s0) >> 12) + 406 * s0 + 1549 * s1;
  int new_s1 = sum & 0xFFF;

  // Calculate the next state for s2, including the carry from the previous sum
  // The (unsigned char) cast mimics the 8-bit truncation from IDA's (unsigned __int8) cast.
  int new_s2 = (unsigned char)((sum >> 12) - 106 * s1 + 13 * s2);

  // Recombine the three 12-bit chunks into the 36-bit state
  *seed = new_s0 | (new_s1 << 12) | (new_s2 << 24);

  // Convert the 36-bit state to a double in [0.0, 1.0).
  // The constants are mathematically equivalent to:
  // 0.00390625 = 1 / 256
  // 0.000244140625 = 1 / 4096
  // This structure effectively treats the state as a 36-bit fractional binary number:
  // (s2 / 256) + (s1 / (256 * 4096)) + (s0 / (256 * 4096 * 4096))
  return 0.00390625 * (((double)new_s0 * 0.000244140625 + (double)new_s1) * 0.000244140625 + (double)new_s2);
}