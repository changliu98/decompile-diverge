void sbox_hash(unsigned long *hash, unsigned long *key)
{
  unsigned long a = hash[0];
  unsigned long b = hash[1];
  unsigned long c = 0;
  unsigned long i;
  for (i = 0; i < 32; i += 2)
  {
    c += 0x9e370001;
    a += b + c + (key[0] + (key[1]<<32));
    b += a + c + (key[2] + (key[3]<<32));
  }
  hash[0] = a;
  hash[1] = b;
}