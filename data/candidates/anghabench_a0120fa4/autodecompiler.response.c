static int REG_A5XX_VFD_FETCH_BASE_HI(int l)
{
 return ((l & 0xff) << 24) + ((l & 0xff00) << 8) +
  ((l >> 8) & 0xff00) + ((l >> 24) & 0xff);
}