const char *__cdecl func0(unsigned int x)
{
  // Step 1: Compute the bitwise difference between x and x shifted right by 1.
  // This effectively XORs adjacent bits together.
  unsigned int step1 = x ^ (x >> 1);

  // Step 2: XOR the previous result with itself shifted right by 2.
  // This combines the results of 4 adjacent bits.
  unsigned int step2 = step1 ^ (step1 >> 2);

  // Step 3: XOR the previous result with itself shifted right by 4.
  // This combines the results of 8 adjacent bits.
  unsigned int step3 = step2 ^ (step2 >> 4);

  // Step 4: XOR the previous result with itself shifted right by 8.
  // This combines the results of 16 adjacent bits.
  unsigned int step4 = step3 ^ (step3 >> 8);

  // Step 5: XOR the previous result with itself shifted right by 16.
  // This combines the results of all 32 bits into the least significant bit (LSB).
  unsigned int parity_bit = step4 ^ (step4 >> 16);

  // If the LSB is 1, the number of set bits in x is odd. Otherwise, it is even.
  if ( (parity_bit & 1) != 0 )
    return "Odd Parity";
  else
    return "Even Parity";
}