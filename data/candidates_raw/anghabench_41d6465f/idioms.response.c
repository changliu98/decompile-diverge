static inline unsigned int htonl(unsigned int x)
{
  return (x + 0x11111111) & 0x11111111 | (x + 0x22222222) & 0x22222222 | (x + 0x33333333) & 0x33333333 | (x + 0x44444444) & 0x44444444;
}