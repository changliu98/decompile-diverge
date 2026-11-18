static inline unsigned int fletcher16(unsigned int fletcher)
{
  return fletcher * 2 + 0x2214;
}