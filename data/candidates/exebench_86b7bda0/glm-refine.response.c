void __cdecl njRowIDCT(int *blk)
{
  int x0, x1, x2, x3, x4, x5, x6, x7, x8;

  // Load the 8 coefficients from the block
  x1 = blk[4] << 11;
  x2 = blk[6];
  x3 = blk[2];
  x4 = blk[1];
  x5 = blk[7];
  x6 = blk[5];
  x7 = blk[3];

  // Fast path: if all AC coefficients are zero, just scale the DC coefficient
  if ( (x7 | x6 | x5 | x4 | x3 | x2 | x1) == 0 )
  {
    x0 = 8 * *blk;
    blk[0] = x0;
    blk[1] = x0;
    blk[2] = x0;
    blk[3] = x0;
    blk[4] = x0;
    blk[5] = x0;
    blk[6] = x0;
    blk[7] = x0;
    return;
  }

  // DC coefficient scaling with rounding offset
  x0 = (*blk << 11) + 128;

  // Stage 1: Odd part
  x8 = 565 * (x4 + x5);
  x4 = x8 + 2276 * x4;   // x4a
  x5 = x8 - 3406 * x5;   // x5a

  x8 = 2408 * (x6 + x7);
  x6 = x8 - 799 * x6;    // x6a
  x7 = x8 - 4017 * x7;   // x7a

  x8 = x0 - x1;
  x0 = x0 + x1;          // x0b (renamed for clarity as the upper even butterfly)

  // Stage 1: Even part
  x1 = 1108 * (x2 + x3);
  x2 = x1 - 3784 * x2;   // x2a
  x3 = x1 + 1568 * x3;   // x3a

  // Stage 2: Odd part
  x1 = x4 + x6;          // x1b
  x4 = x4 - x6;          // x4b
  x6 = x5 + x7;          // x6b
  x5 = x5 - x7;          // x5b

  // Stage 2: Even part
  x7 = x3 + x0;          // x7b
  x8 = x0 - x3;          // x8c
  x3 = x2 + x8;          // x3b
  x0 = x8 - x2;          // x0b

  // Stage 3: Final odd part
  x2 = (181 * (x4 + x5) + 128) >> 8; // x2b
  x4 = (181 * (x4 - x5) + 128) >> 8; // x4c

  // Stage 3: Final output scaling
  blk[0] = (x1 + x7) >> 8;
  blk[1] = (x2 + x3) >> 8;
  blk[2] = (x4 + x0) >> 8;
  blk[3] = (x6 + x8) >> 8;
  blk[4] = (x8 - x6) >> 8;
  blk[5] = (x0 - x4) >> 8;
  blk[6] = (x3 - x2) >> 8;
  blk[7] = (x7 - x1) >> 8;
}