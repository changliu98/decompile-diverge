void __cdecl sjis_shift(int *p1, int *p2)
{
  unsigned __int8 c1 = *p1;
  unsigned __int8 c2 = *p2;
  int rowOffset;
  int colOffset;

  // Determine the row offset based on the first byte
  if (c1 < 0xA0u)
    rowOffset = 112;  // 0x70
  else
    rowOffset = 176;  // 0xB0

  // Determine the column offset based on the second byte
  if (c2 >= 0x9Fu)
  {
    colOffset = 126;  // 0x7E
  }
  else
  {
    if (c2 > 0x7Fu)
      colOffset = 32; // 0x20
    else
      colOffset = 31; // 0x1F
  }

  // The original code uses a 64-bit multiplication trick to compute the high 32 bits.
  // __PAIR64__(A, B) creates a 64-bit integer where A is the high 32 bits and B is the low 32 bits.
  // Thus, __PAIR64__(2 * (c1 - rowOffset), c2) is mathematically equivalent to:
  // (2 * (c1 - rowOffset)) * 0x100000000 + c2
  // 
  // Subtracting 159 and shifting right by 32 isolates the high 32 bits, yielding:
  // 2 * (c1 - rowOffset) - (159 > c2 ? 1 : 0)
  *p1 = 2 * (c1 - rowOffset) - (c2 < 159 ? 1 : 0);
  
  *p2 -= colOffset;
}