double __cdecl randum(long *seed)
{
  long newseed2; // [rsp+8h] [rbp-50h]
  long newseed1; // [rsp+10h] [rbp-48h]
  long newseed0; // [rsp+18h] [rbp-40h]
  long seed0; // [rsp+30h] [rbp-28h]
  long sum; // [rsp+48h] [rbp-10h]

  seed0 = *seed & 0xFFF;
  newseed0 = (1549 * (_WORD)seed0) & 0xFFF;
  sum = ((1549 * seed0) >> 12) + 406 * seed0 + 1549 * ((*seed >> 12) & 0xFFF);
  newseed1 = sum & 0xFFF;
  newseed2 = (unsigned __int8)((sum >> 12) + -106 * (*seed >> 12) + 13 * BYTE3(*seed));
  *seed = newseed0 | (newseed1 << 12) | (newseed2 << 24);
  return 0.00390625
       * (((double)(int)newseed0 * 0.000244140625 + (double)(int)newseed1) * 0.000244140625 + (double)(int)newseed2);
}