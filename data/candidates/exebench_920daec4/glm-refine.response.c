void __cdecl hil_s_from_xy(unsigned int x, unsigned int y, int order, unsigned int *s)
{
  unsigned int state = 0; // Tracks the Hilbert curve orientation/rotation state

  // Initialize the output distance 's' to 0
  *s = 0;

  // Iterate from the most significant bit down to the least significant bit
  for (int i = order - 1; i >= 0; --i)
  {
    // Extract the i-th bit from x and y
    unsigned int xi = (x >> i) & 1;
    unsigned int yi = (y >> i) & 1;

    // Compute the 3-bit index for the lookup tables.
    // Format: [state (2 bits) | x_bit (1 bit) | y_bit (1 bit)]
    unsigned int idx = (state << 2) | (xi << 1) | yi;

    // Update the Hilbert distance 's' by appending the 2-bit quadrant index
    *s = (*s << 2) | ((0x3603603C >> (2 * idx)) & 3);

    // Update the state for the next iteration based on the current quadrant
    state = (0xC63C6396 >> (2 * idx)) & 3;
  }
}