void insert_dle(unsigned char *out, unsigned char *in, int count)
{
  while (count--) {
    *out++ = *in++;
    if (*in == DLE) {
      *out++ = DLE;
    }
  }
}