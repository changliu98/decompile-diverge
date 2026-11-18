void __cdecl poly1305_add(unsigned __int8 *h, const unsigned __int8 *c)
{
  unsigned int carry = 0;

  for (unsigned int i = 0; i < 0x11; ++i)
  {
    unsigned int sum = c[i] + h[i] + carry;
    h[i] = (unsigned __int8)sum;
    carry = sum >> 8;
  }
}