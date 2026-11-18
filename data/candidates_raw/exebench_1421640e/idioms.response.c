void sbox(char *out, int x, int y)
{
  out[0] = (char)(y / 32 + ' ');
  out[1] = (char)(y % 32 + 'a');
  out[2] = (char)(x / 32 + ' ');
  out[3] = (char)(x % 32 + '@');
  out[4] = '\0';
}