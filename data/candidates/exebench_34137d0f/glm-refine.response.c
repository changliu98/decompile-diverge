int __cdecl sha_init(unsigned int *hash)
{
  hash[0] = 0x67452301;
  hash[1] = 0xEFCDAB89;
  hash[2] = 0x98BADCFE;
  hash[3] = 0x10325476;
  hash[4] = 0xC3D2E1F0;
  return 0;
}