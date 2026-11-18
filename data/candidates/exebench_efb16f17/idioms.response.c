static unsigned int ether_hash(void *key)
{
  unsigned int hash = 0;
  int i;
  for (i = 0; i < 6; i++)
  {
    hash = (hash << 16) + (hash << 6) + ((unsigned char *)key)[i] - hash;
  }
  return hash;
}