void __cdecl goertzel_filter_v1(short *delay, short input, short coefficient)
{
  short product; // [rsp+0h] [rbp-Eh]

  product = ((coefficient * (__int64)delay[1]) >> 14) - delay[2];
  delay[2] = delay[1];
  delay[1] = product + (input >> 7);
}