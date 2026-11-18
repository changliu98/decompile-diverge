static int cdb_htonl(int l)
{
 return ((l << 24) & 0xff000000) |
  ((l << 8) & 0x00ff0000) |
  ((l >> 8) & 0x0000ff00) |
  ((l >> 24) & 0x000000ff);
}