void sbox(int *out, int a, int b)
{
  int i;
  int in = a | (b << 1);
  for (i = 0; i < 1; i++)
  {
    out[i] = (in & (1 << i)) ? 1 : 0;
  }
}