void __cdecl encode_vector(char *c, int x, int y)
{
  *c = (y >> 5) + 32;
  c[1] = (y & 0x1F) + 96;
  c[2] = (x >> 5) + 32;
  c[3] = (x & 0x1F) + 64;
  c[4] = 0;
}