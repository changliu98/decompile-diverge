int get_int(unsigned char *in, unsigned int *out, unsigned int *prev)
{
  *out = in[0] & 0x7f;
  if (in[0] < 0x80)
  {
    *prev += *out;
    *out = *prev;
    return 1;
  }
  *out |= (in[1] & 0x7f) << 7;
  if (in[1] < 0x80)
  {
    *prev += *out;
    *out = *prev;
    return 2;
  }
  *out |= (in[2] & 0x7f) << 14;
  if (in[2] < 0x80)
  {
    *prev += *out;
    *out = *prev;
    return 3;
  }
  *out |= (in[3] & 0x7f) << 21;
  if (in[3] < 0x80)
  {
    *prev += *out;
    *out = *prev;
    return 4;
  }
  *out |= (in[4] & 0x7f) << 28;
  *prev += *out;
  *out = *prev;
  return 5;
}