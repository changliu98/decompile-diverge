char *to_binary(char c, char *out)
{
  int i;
  for (i = 0; i < 8; i++)
    out[i] = (c & (1 << (7 - i))) ? '1' : '0';
  out[8] = '\0';
  return out;
}