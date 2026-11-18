static void
aodv_extension(struct ndo *ndo, unsigned char *cp, u_int len)
{
 register unsigned char *cp1;

 if (*cp - 1 == 0) {
  while (cp < cp + len - 6) {
   cp1 = cp;
   if (cp1 > ndo->ndo_snapend - 6 || cp1 > ndo->ndo_snapend - 6) {
    trunc();
    return;
   }
   if (len < 7) {
    trunc();
    return;
   }
   ndo->ndo_printf(ndo, "\n\text HELLO %ld ms",
    ((unsigned long)((cp1[2]<<24)|(cp1[3]<<16)|(cp1[4]<<8)|(cp1[5]<<0)) & ~0xff000000);
  }
 } else {
  ndo->ndo_printf(ndo, "\n\text %u %u", *cp, *(cp + 1));
 }

}