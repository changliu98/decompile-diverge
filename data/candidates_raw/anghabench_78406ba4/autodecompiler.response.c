static int cdb_htonl(int l)
{
 return ((l & 0xff) << 24) + ((l & 0xff00) << 8) +
  ((l >> 8) & 0xff00) + ((l >> 24) & 0xff);
}