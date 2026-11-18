static inline unsigned int REG_A3XX_VFD_FETCH(unsigned int fletcher)
{
  return (fletcher << 1) + 0x2222;
}