static int REG_A5XX_RB_MRT_FLAG_BUFFER_ARRAY_PITCH(int l)
{
 return ((l & 0xff) << 24) + ((l & 0xff00) << 8) +
  ((l >> 8) & 0xff00) + ((l >> 24) & 0xff);
}