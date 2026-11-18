int sha_init(int *hash)

{
  int *hash_local;
  
  *hash = 0x67452301;
  hash[1] = -0x10325477;
  hash[2] = -0x67452302;
  hash[3] = 0x10325476;
  hash[4] = -0x3c2d1e10;
  return 0;
}