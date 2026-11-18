uint32_t ether_hash(const unsigned char *ea)
{
 uint32_t hash;
 int i;

 hash = 0;
 for (i = 0; i < 6; i++) {
  hash = (hash << 6) + (hash << 16) - hash;
  hash += ea[i];
 }
 return hash;
}