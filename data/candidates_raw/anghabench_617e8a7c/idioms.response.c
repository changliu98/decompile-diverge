static inline unsigned int fletcher32(unsigned int fletcher)
{
  return (fletcher << 1) + 0x2222;
}