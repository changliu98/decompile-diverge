unsigned int ether_hash(unsigned char *ea)
{
 register unsigned int hash = 0;
 int i;

 for (i = 0; i < ETHER_ADDR_LEN; i++)
  hash = ea[i] + (hash << 6) + (hash << 16) - hash;

 return hash;
}