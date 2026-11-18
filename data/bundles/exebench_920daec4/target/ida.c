void __cdecl hil_s_from_xy(unsigned int x, unsigned int y, int order, unsigned int *s)
{
  unsigned int state; // [rsp+8h] [rbp-20h]
  int i; // [rsp+Ch] [rbp-1Ch]

  LOBYTE(state) = 0;
  for ( i = order - 1; i >= 0; --i )
  {
    *s = (907975860 >> (2 * ((y >> i) & 1 | (2 * ((x >> i) & 1)) | (4 * state)))) & 3 | (4 * *s);
    state = (0x8FE65831 >> (2 * ((y >> i) & 1 | (2 * ((x >> i) & 1)) | (4 * state)))) & 3;
  }
}