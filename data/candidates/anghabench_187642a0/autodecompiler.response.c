static int REG_A3XX_RB_MRT_BLEND_CONTROL(int l)
{
 return ((l << 24) & 0xff000000) |
  ((l << 8) & 0x00ff0000) |
  ((l >> 8) & 0x0000ff00) |
  ((l >> 24) & 0x000000ff);
}