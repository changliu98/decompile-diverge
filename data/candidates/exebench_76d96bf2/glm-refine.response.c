void __cdecl goertzel_filter_v1(short *delay, short input, short coefficient)
{
  // The Goertzel algorithm computes the intermediate state:
  // s[n] = x[n] + (coeff * s[n-1]) - s[n-2]
  // 
  // In this fixed-point implementation, the coefficient and previous state 
  // are multiplied as 32-bit integers and shifted right by 14 to maintain 
  // the Q15 fixed-point precision.
  int product = ((coefficient * (int)delay[1]) >> 14) - delay[2];
  
  // Shift the delay line states
  delay[2] = delay[1];
  
  // The input signal is scaled down by 7 bits (input >> 7) before being 
  // added to the new state.
  delay[1] = (short)(product + (input >> 7));
}