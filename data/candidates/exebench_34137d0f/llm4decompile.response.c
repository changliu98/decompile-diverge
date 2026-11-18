int sha_init(uint32_t *hash)
{
 hash[0] = 0x67452301;
 hash[1] = 0xEFCDAB89;
 hash[2] = 0x98BADCFE;
 hash[3] = 0x10325476;
 hash[4] = 0xc3d2e1f0;

 return 0;
}